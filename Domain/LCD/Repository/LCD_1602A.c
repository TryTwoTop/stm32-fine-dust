/*
 * LCD_1602A.c
 *
 *  Created on: Nov 8, 2023
 *      Author: try
 */

#include "../Service/LCD_1602A.h"
#include "../Value_Object/LCD_pin.h"

/* LCD Instruction */
#define INST_CLEAR_DISPLAY					((uint8_t)0x01)
#define INST_RET_HOME						((uint8_t)0x02)
#define INST_ENTRY_MODE_SET					((uint8_t)0x04)
#define INST_DISPLAY_ON_OFF_CTRL			((uint8_t)0x08)
#define INST_CURSOR_OR_DISPLAY_SHIFT		((uint8_t)0x10)
#define INST_FUNC_SET						((uint8_t)0x20)
#define INST_SET_CGRAM_ADDR					((uint8_t)0x40)
#define INST_SET_DDRAM_ADDR					((uint8_t)0x80)

/* LCD Instruction Execution Time (min ms) */
#define EXEC_TIME_CLEAR_DISPLAY				(2)
#define EXEC_TIME_RET_HOME					(2)
#define EXEC_TIME_ENTRY_MODE_SET			(1)
#define EXEC_TIME_DISPLAY_ON_OFF_CTRL		(1)
#define EXEC_TIME_CURSOR_OR_DISPLAY_SHIFT	(1)
#define EXEC_TIME_FUNC_SET					(1)
#define EXEC_TIME_SET_CGRAM_ADDR			(1)
#define EXEC_TIME_SET_DDRAM_ADDR			(1)
#define EXEC_TIME_READ_BUSY_FLAG_AND_ADDR	(0)
#define EXEC_TIME_WRITE_DATA				(1)
#define EXEC_TIME_READ_DATA					(1)

/* LCD Operation Time (min ms) */
#define TIME_OF_E_HALF_CYCLE				(1)
#define TIME_TO_WAIT_AFTER_PWR_ON			(15)

static void __LCD_pin_e_generate_impulse (void)
{
	// Pin E HIGH
	pin_write(&_LCD_pin.e, HIGH);
	HAL_Delay(TIME_OF_E_HALF_CYCLE);

	// Pin E LOW
	pin_write(&_LCD_pin.e, LOW);
	HAL_Delay(TIME_OF_E_HALF_CYCLE);
}

static void __LCD_load_data_or_instruction (uint8_t data)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		uint8_t bit = 1 << i;

		pin_write(&_LCD_pin.db[i], (data & bit) ? HIGH : LOW);
	}
}

static void __LCD_write_data (uint8_t data)
{
	// Pin RS HIGH
	pin_write(&_LCD_pin.rs, HIGH);

	__LCD_load_data_or_instruction(data);

	__LCD_pin_e_generate_impulse();
}

static void __LCD_write_instruction (uint8_t instruction)
{
	// Pin RS LOW
	pin_write(&_LCD_pin.rs, LOW);

	__LCD_load_data_or_instruction(instruction);

	__LCD_pin_e_generate_impulse();
}

void LCD_init (void)
{
	HAL_Delay(TIME_TO_WAIT_AFTER_PWR_ON);

	// 8 Bit mode, 2 Lines, 5 X 8 Dots
	__LCD_write_instruction(INST_FUNC_SET | 0x18);

	// Diplsy On
	__LCD_write_instruction(INST_DISPLAY_ON_OFF_CTRL | 0x04);

	// Cursor moves to the right
	__LCD_write_instruction(INST_ENTRY_MODE_SET | 0x02);

	LCD_clear();
}

void LCD_clear (void)
{
	__LCD_write_instruction(INST_CLEAR_DISPLAY);

	HAL_Delay(EXEC_TIME_CLEAR_DISPLAY);
}

void LCD_print (char *str)
{
	while (*str)
	{
		__LCD_write_data((uint8_t)*str);
		str++;
	}
}
