#include "pin.h"

void pin_init (pin_t *pin, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	pin->GPIOx = GPIOx;
	pin->GPIO_Pin = GPIO_Pin;
}

void pin_write (pin_t *pin, pin_level_t level)
{
	if (level != LOW)
	{
		HAL_GPIO_WritePin(pin->GPIOx, pin->GPIO_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(pin->GPIOx, pin->GPIO_Pin, GPIO_PIN_RESET);
	}
}
