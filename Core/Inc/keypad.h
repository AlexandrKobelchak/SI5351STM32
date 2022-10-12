#ifndef KEYPAD_PCF8574_H
#define KEYPAD_PCF8574_H

#include "pcf857x.h"

#define KEYPAD_DELAY_MS 5
#define KEYPAD_ADDR  0x3F

#define I2C_KEYPAD_NOKEY          16
#define I2C_KEYPAD_FAIL           17

PCF857x_TypeDef KEYPAD_Init();
uint8_t KEYPAD_getKey4x4();
void KEYPAD_setKeyMap(char* keyMap);
char KEYPAD_getKeyChar();
uint8_t KEYPAD_getLastKey();
char KEYPAD_getLastKeyChar();

#endif //KEYPAD_PCF8574_H
