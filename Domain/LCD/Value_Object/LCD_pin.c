/*
 * LCD_pin.c
 *
 *  Created on: Nov 8, 2023
 *      Author: try
 */

#include "LCD_pin.h"

LCD_pin_t _LCD_pin;

void LCD_pin_init (LCD_pin_t *LCD_pin)
{
	_LCD_pin = *LCD_pin;
}
