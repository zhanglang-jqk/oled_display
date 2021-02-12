// Simple I2C test for ebay 128x64 oled.

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "ch/bsp.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

#define LED PC13

#define LOGO1_PIN PB5
#define LOGO2_PIN PB4
#define DOUBLE_PIN PB3
#define WELCOME_LOGO_PIN PA15

#define LOGO_WEIGHT 128
#define LOGO_HEIGHT 20
#define LOGO1_WEIGHT 128
#define LOGO1_HEIGHT 30
#define LOGO2_WEIGHT 128
#define LOGO2_HEIGHT 24
#define LOGO3_WEIGHT 128
#define LOGO3_HEIGHT 30

#define POWERON_DELAY 3000

//ʹ�� PCtoLCD2002 ���� �������� ����ʽ ���� �����ݣ�128��

u8 logo[][128] = {
    {0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0xC0, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0x7F, 0x07, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0xFE, 0x7E, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0xFE, 0x3E, 0x0F, 0x0F, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0xFE, 0xFE, 0xFC, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0xFF, 0xFC, 0xE0, 0x00, 0x00, 0x80, 0xF0, 0xFE, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
    {0x00, 0x00, 0x03, 0x3F, 0xFF, 0xFF, 0xFF, 0xF0, 0xFC, 0xFF, 0x7F, 0x07, 0x00, 0x03, 0x3F, 0xFF, 0xFF, 0xF0, 0xF8, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x03, 0x1F, 0x7F, 0x7E, 0x7C, 0x7F, 0x3F, 0x07, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x80},
    {0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07}, /*"D:\CH\code\mini motor\refrence\???��????.bmp",0*/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      /* (128 X 20 )*/
};
u8 logo1[][128] =
    {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x03, 0x01, 0xE0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x3F, 0x0F, 0x0F, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x80, 0x00, 0x0F, 0x0F, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xE7, 0xEF, 0xC7, 0x81, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x01, 0x01, 0x07, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7E, 0x78, 0x30, 0x01, 0x07, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7E, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x07, 0x03, 0x00, 0x38, 0x3F, 0x7F, 0x7F, 0x3F, 0x3F, 0x07, 0x0F, 0x3F, 0x7F, 0x7F, 0x7F, 0x1F, 0x07, 0x07, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7C, 0x70, 0x7C, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x07, 0x01, 0x03, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7E, 0x38, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x10, 0x3C, 0x3C, 0x3C, 0x7C, 0x7D, 0x7D, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x0F, 0x00, 0x00, 0x07, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x07, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"D:\CH\code\mini motor\refrence\logo1 (1).bmp",0*/
        /* (128 X 30 )*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  /* (128 X 30 )*/
};
u8 logo2[][128] = {
    {0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x9E, 0x0E, 0x0E, 0x0C, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x9E, 0x8E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0x78, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x80, 0x80, 0xC0, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x9E, 0x0E, 0x0E, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x1E, 0x0E, 0x9E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xF0, 0x60, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x0E, 0x1E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF8, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xC3, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xE3, 0x81, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00}, /*"D:\CH\code\mini motor\refrence\logo2.bmp",0*/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      /* (128 X 24 )*/
};
u8 logo3[][128] = {
    {0x00, 0x00, 0x00, 0x30, 0x70, 0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x70, 0x30, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x70, 0x70, 0x30, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0x70, 0x30, 0x70, 0x70, 0xF0, 0xF0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x30, 0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x70, 0x70, 0x20, 0x00, 0x00, 0x00, 0x20, 0x30, 0x30, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x30, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x30, 0x30, 0x30, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0x70, 0x70, 0x70, 0x70, 0xF0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xC0, 0xC0, 0xF0, 0xFC, 0xFE, 0x3F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0x00, 0x00, 0x03, 0x0F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xC0, 0xC0, 0xF0, 0xF8, 0xFE, 0x3F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"D:\CH\code\mini motor\refrence\logo3.bmp",0*/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      /* (128 X 30 )*/
};

// u8 icon1[][128]{0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x3F, 0x38, 0x60, 0x41, 0xC1, 0xC3, 0x43, 0x63, 0x33, 0x3F, 0x06, 0x00, 0x00}; /*"C:\Users\11345\Desktop\Temp\�͵�.bmp",0*/
/* (16 X 16 )*/

u8 icon1[][16] = {{0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE0, 0xC0, 0x00, 0x00, 0x00},
                  {0x00, 0x00, 0x06, 0x3F, 0x38, 0x60, 0x41, 0xC1, 0xC3, 0x43, 0x63, 0x33, 0x3F, 0x06, 0x00, 0x00},
                  /*"C:\Users\11345\Desktop\Temp\????.bmp",0*/};
u8 icon2[][16]{{0x00, 0xF8, 0x88, 0x8E, 0xEE, 0xEE, 0x88, 0x88, 0x08, 0x08, 0x8E, 0x8E, 0x8E, 0x88, 0xF8, 0x00},
             {0x00, 0x3F, 0x21, 0x21, 0x27, 0x27, 0x21, 0x21, 0x20, 0x20, 0x21, 0x21, 0x21, 0x21, 0x3F, 0x00},
             /*"C:\Users\11345\Desktop\Temp\battery.bmp",0*/};

u8 doubleMPa = 1;

//------------------------------------------------------------------------------

void drawImage(u8 image[8][128], u16 weight, u16 height, u8 startLine)
{
  // oled.setCursor(0, 0);
  u8 scanRow = height % 8 == 0 ? height / 8 : height / 8 + 1;
  for (int raw = startLine; raw < scanRow + startLine; raw++)
  {
    oled.setCursor(0, raw);
    for (int col = 0; col < weight; col++)
    {
      oled.ssd1306WriteRam(image[raw - startLine][col]);
    }
  }
}

void drawIcon(u8 icon[2][16], u8 startLine)
{
  for (int i = 0; i < 2; i++)
  {
    oled.setCursor(0, startLine + i);
    for (int j = 0; j < 16; j++)
      oled.ssd1306WriteRam(icon[i][j]);
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(LOGO1_PIN, INPUT_PULLUP);
  pinMode(LOGO2_PIN, INPUT_PULLUP);
  pinMode(DOUBLE_PIN, INPUT_PULLUP);
  pinMode(WELCOME_LOGO_PIN, INPUT_PULLUP);

  Wire.begin();
  Wire.setClock(400000L);
  pinMode(LED, OUTPUT);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else  // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  // delay(1000);

  oled.setFont(Adafruit5x7);
  oled.set2X();

  oled.clear();
  if (digitalRead(WELCOME_LOGO_PIN) == 1)
  {
    drawImage(logo, LOGO_WEIGHT, LOGO_HEIGHT, 3);
  }
  else
  {
    if (digitalRead(LOGO1_PIN) == 1 && digitalRead(LOGO2_PIN) == 1)
    {
      drawImage(logo1, LOGO1_WEIGHT, LOGO1_HEIGHT, 3);
    }
    else if (digitalRead(LOGO1_PIN) == 0 && digitalRead(LOGO2_PIN) == 1)
    {
      drawImage(logo2, LOGO2_WEIGHT, LOGO2_HEIGHT, 3);
    }
    else if (digitalRead(LOGO1_PIN) == 1 && digitalRead(LOGO2_PIN) == 0)
    {
      drawImage(logo3, LOGO3_WEIGHT, LOGO3_HEIGHT, 3);
    }
  }

  digitalRead(DOUBLE_PIN) == 1 ? doubleMPa = 1 : doubleMPa = 2;

  delay(POWERON_DELAY);

  oled.clear();
  oled.setCursor(0, 0);
  if (digitalRead(WELCOME_LOGO_PIN) == 1)
  {
    drawImage(logo, LOGO_WEIGHT, LOGO_HEIGHT, 0);
  }
  else
  {
    if (digitalRead(LOGO1_PIN) == 1 && digitalRead(LOGO2_PIN) == 1)
    {
      drawImage(logo1, LOGO1_WEIGHT, LOGO1_HEIGHT, 0);
    }
    else if (digitalRead(LOGO1_PIN) == 0 && digitalRead(LOGO2_PIN) == 1)
    {
      drawImage(logo2, LOGO2_WEIGHT, LOGO2_HEIGHT, 0);
    }
    else if (digitalRead(LOGO1_PIN) == 1 && digitalRead(LOGO2_PIN) == 0)
    {
      drawImage(logo3, LOGO3_WEIGHT, LOGO3_HEIGHT, 0);
    }
  }

  oled.setCursor(40 + 40, 4);
  oled.print("V");

  oled.setCursor(40 + 40, 6);
  oled.print("MPa");

  drawIcon(icon2, 4);
  drawIcon(icon1, 6);

}

uint32_t delay_c = 0;
void loop()
{

  // digitalWrite(LED,HIGH);
  // delay(100);
  // digitalWrite(LED,LOW);
  // delay(100);

  // Serial.println("hello world!");

  if (millis() - delay_c > 5)
  {
    int mpaADC = analogRead(A0);
    float mpaVolt = mpaADC * (3.3 / 1023.0);
    mpaVolt = mpaVolt * 2 * doubleMPa;

    int vinADC = analogRead(A1);
    float vinVolt = vinADC * (3.3 / 1023.0);
    vinVolt = vinVolt * 6;

    oled.clearField(16, 4, 4);
    oled.setCursor(16, 4);
    // oled.print(vinVolt);
    oled.printf("% 2d.%d", (int)vinVolt, (int)(vinVolt * 10) % 10);

    oled.clearField(16, 6, 4);
    oled.setCursor(16, 6);
    // oled.print(vinVolt);
    oled.printf("% 2d.%d", (int)mpaVolt, (int)(mpaVolt * 10) % 10);

    delay_c = millis();
  }
}

/**
  * @brief System Clock Configuration, set osc 8M
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}