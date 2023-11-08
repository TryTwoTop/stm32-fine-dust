#ifndef __VO_PIN_H__
#define __VO_PIN_H__

#include "stm32f1xx_hal.h"

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
} pin_t;

typedef enum
{
	LOW = 0u,
	HIGH
} pin_level_t;

void pin_init (pin_t *, GPIO_TypeDef *, uint16_t);
void pin_write (pin_t *, pin_level_t);

#endif //__VO_PIN_H__
