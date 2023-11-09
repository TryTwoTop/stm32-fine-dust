/*
 * LCD_pin.h
 *
 *  Created on: Nov 8, 2023
 *      Author: try
 */

#ifndef LCD_VALUE_OBJECT_LCD_PIN_H_
#define LCD_VALUE_OBJECT_LCD_PIN_H_

#include "../../Pin/Value_Object/pin.h"

#define LCD_BIT_MODE_MAX	(8)

typedef struct
{
	pin_t rs;
	pin_t rw;
	pin_t e;
	pin_t db[LCD_BIT_MODE_MAX];
} LCD_pin_t;

extern LCD_pin_t _LCD_pin;

void LCD_pin_init (LCD_pin_t *);

#endif /* LCD_VALUE_OBJECT_LCD_PIN_H_ */
