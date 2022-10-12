/*
 * pcf857x.h
 *
 *  Created on: 19 квіт. 2018 р.
 *      Author: Andriy
 */


#ifndef pcf857x_H_
#define pcf857x_H_

#include "stdint.h"
#include "stdbool.h"

//-----------User Defines---------------//
#define STM32F4XX
#define STM32_I2C_PORT			hi2c1
//--------------------------------------//

#define PCF857x_I2C_PORT		STM32_I2C_PORT

#ifdef STM32F0XX
#include "stm32f0xx_hal.h"
#endif

#ifdef STM32F1XX
#include "stm32f1xx_hal.h"
#endif

#ifdef STM32F2XX
#include "stm32f2xx_hal.h"
#endif

#ifdef STM32F3XX
#include "stm32f3xx_hal.h"
#endif

#ifdef STM32F4XX
#include "stm32f4xx_hal.h"
#endif

#define	_BIT_SET(reg, bit)		reg |= 1 << bit
#define	_BIT_CLEAR(reg, bit)		reg &= ~(1 << bit)
#define	_BIT_TOGGLE(reg, bit)	reg ^= 1 << bit
#define	_BIT_IS_SET(reg, bit)	(reg & (1 << bit)) != 0
#define	_BIT_IS_CLEAR(reg, bit)	(reg & (1 << bit)) == 0

#define PCF857X_IS_READY(PCF857x_I2C_ADDR) HAL_I2C_IsDeviceReady(&STM32_I2C_PORT, PCF857x_I2C_ADDR, 5, 1000)
#define PCF857X_READ(PCF857x_I2C_ADDR, data, num_bytes) HAL_I2C_Master_Receive(&STM32_I2C_PORT, PCF857x_I2C_ADDR, data, num_bytes, 1000)
#define PCF857X_WRITE(PCF857x_I2C_ADDR, data, num_bytes) HAL_I2C_Master_Transmit(&STM32_I2C_PORT, PCF857x_I2C_ADDR, data, num_bytes, 1000)

typedef enum{
	PCF857x_OK 			= 0x00,
	PCF857x_PIN_ERROR 	= 0x01,
	PCF857x_I2C_ERROR 	= 0x02,
	PCF857x_FUN_ERROR	= 0x03,
	PCF857x_VAL_ERROR	= 0x04
}PCF857x_TypeDef;

extern I2C_HandleTypeDef PCF857x_I2C_PORT;

// Початкова ініціалізація pcf857x. На вхід число, початковий стан P0 - P7 та false якщо pcf8574 або true якщо pcf8575
PCF857x_TypeDef pcf857x_Init(uint8_t addr, uint16_t value_init, bool is8575);

// Читання 8 бітів з P0 - P7
uint8_t pcf857x_Read8(uint8_t addr);

// Читання 16 бітів з P0 - P15
uint16_t pcf857x_Read16(uint8_t addr);

// Читання шпильки pin на pcf857x
bool pcf857x_Read(uint8_t addr, uint8_t pin);

 // Запис 8 бітів до P0 - P7. Повертає код помилки.
PCF857x_TypeDef pcf857x_Write8(uint8_t addr, uint8_t value);

// Запис 16 бітів до P0 - P15. Повертає код помилки.
PCF857x_TypeDef pcf857x_Write16(uint8_t addr, uint16_t value);

// Запис значення до шпильки pin. Повертає код помилки.
PCF857x_TypeDef pcf857x_Write(uint8_t addr, uint8_t pin, bool value);

// Поміняти стан шпильки pin. Повертає код помилки.
PCF857x_TypeDef pcf857x_Toggle(uint8_t addr, uint8_t pin);

 // Поміняти стан всіх шпильок. Повертає код помилки.
PCF857x_TypeDef pcf857x_ToggleAll(uint8_t addr);

// Зсув праворуч на n бітів. Повертає код помилки.
PCF857x_TypeDef pcf857x_ShiftRight(uint8_t addr, uint8_t n);

 // Зсув ліворуч на n бітів. Повертає код помилки.
PCF857x_TypeDef pcf857x_ShiftLeft(uint8_t addr, uint8_t n);

 // Обертання праворуч на n бітів. Повертає код помилки.
PCF857x_TypeDef pcf857x_RotateRight(uint8_t addr, uint8_t n);

// Обертання ліворуч на n бітів. Повертає код помилки.
PCF857x_TypeDef pcf857x_RotateLeft(uint8_t addr, uint8_t n);

 // Скидання шпильки INT в початковий стан. Повертає код помилки.
PCF857x_TypeDef pcf857x_ResetInterruptPin(uint8_t addr);

// Повертає останній код помилки.
PCF857x_TypeDef pcf857x_GetLastError();



#endif /* pcf857x_H_ */
