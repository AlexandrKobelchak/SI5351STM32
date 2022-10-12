#include "keypad.h"

extern I2C_HandleTypeDef hi2c1;
static uint8_t _lastKey = I2C_KEYPAD_NOKEY;
static char* _keyMap=NULL;

PCF857x_TypeDef KEYPAD_Init() {

	PCF857x_TypeDef res;
	while ((res = pcf857x_Init(KEYPAD_ADDR, 0xFF, false)) != PCF857x_OK);
	return res;
}

void KEYPAD_setKeyMap(char* keyMap){
	_keyMap=keyMap;
}

uint8_t KEYPAD_getLastKey() {

	return _lastKey;
}


char KEYPAD_getKeyChar(){

	if (!_keyMap) return ' ';
	return _keyMap[KEYPAD_getKey4x4()];
}

char KEYPAD_getLastKeyChar(){

	if (!_keyMap) return ' ';
	return _keyMap[_lastKey];
}


uint8_t KEYPAD_getKey4x4() {
	//  key = row + 4 x col
	uint8_t key = 0;

	pcf857x_Write8(KEYPAD_ADDR, 0xF0);

	//  mask = 4 rows as input pull up, 4 columns as output
	uint8_t rows = pcf857x_Read8(KEYPAD_ADDR) & 0xF0;

	//  check if single line has gone low.
	if (rows == 0xF0)
		return 0x10; //I2C_KEYPAD_NOKEY;
	else if (rows == 0xE0)
		key = 0;
	else if (rows == 0xD0)
		key = 1;
	else if (rows == 0xB0)
		key = 2;
	else if (rows == 0x70)
		key = 3;
	else
		return 0x11; //I2C_KEYPAD_FAIL;

	// 4 columns as input pull up, 4 rows as output
	//  mask = 4 rows as input pull up, 4 columns as output
	pcf857x_Write8(KEYPAD_ADDR, 0x0F);

	uint8_t cols = pcf857x_Read8(KEYPAD_ADDR) & 0x0F;

	// check if single line has gone low.
	if (cols == 0x0F)
		return I2C_KEYPAD_NOKEY;
	else if (cols == 0x0E)
		key += 0;
	else if (cols == 0x0D)
		key += 4;
	else if (cols == 0x0B)
		key += 8;
	else if (cols == 0x07)
		key += 12;
	else
		return I2C_KEYPAD_FAIL;

	_lastKey = key;
	pcf857x_Write8(KEYPAD_ADDR, 0xFF);//reset to interrupt

	return key;   // 0..15
}
