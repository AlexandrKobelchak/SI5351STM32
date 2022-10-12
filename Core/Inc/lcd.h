//https://github.com/afiskon/stm32-i2c-lcd-1602/blob/master/Src/main.c
#ifndef LCD_PCF8575_uidhfawiuefbiw
#define LCD_PCF8575_uidhfawiuefbiw

#include "main.h"



#define PIN_RS    (1 << 0)         // если на ножке 0, данные воспринимаются как команда, если 1 - как символы для вывода
#define PIN_EN    (1 << 2)         // бит, по изменению сост. которого считывается информация
#define BACKLIGHT (1 << 3)         // управление подсветкой

#define LCD_DELAY_MS 5             // пауза перед высвечиванием символ
#define LCD_ADDR  0x27             // адрес дисплея

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

void LCD_Init(uint8_t lcd_addr);
void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd);
void LCD_SendData(uint8_t lcd_addr, uint8_t data);
void LCD_SendString(uint8_t lcd_addr, char *str);
void LCD_SetCursor(uint8_t lcd_addr, uint8_t col, uint8_t row);

#endif //LCD_PCF8575_uidhfawiuefbiw
