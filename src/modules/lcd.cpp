/*

  16x16Font.ino
  
  Demonstration for 16x16 pixel fonts.
  Several fonts are included in the example. 

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include "lcd.h"
#include <Arduino.h>
#include <Wire.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

// Please UNCOMMENT one of the contructor lines below
// U8x8 Contructor List
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8x8setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
//U8X8_NULL lcd;	// null device, a 8x8 pixel display which does nothing
//U8X8_SSD1306_128X64_NONAME_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1306_128X64_NONAME_4W_HW_SPI lcd(/* cs=*/ 6, /* dc=*/ 4, /* reset=*/ 12);	// Arduboy (DevKit)
//U8X8_SSD1306_128X64_NONAME_4W_HW_SPI lcd(/* cs=*/ 12, /* dc=*/ 4, /* reset=*/ 6);	// Arduboy 10 (Production, Kickstarter Edition)
//U8X8_SSD1306_128X64_NONAME_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1306_128X64_NONAME_3W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
//U8X8_SSD1306_128X64_NONAME_3W_HW_SPI lcd(/* cs=*/ 10, /* reset=*/ 8);
U8X8_SSD1306_128X64_NONAME_HW_I2C lcd(/* reset=*/U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_ALT0_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE); 	      // same as the NONAME variant, but may solve the "every 2nd line skipped" problem
//U8X8_SSD1306_128X64_NONAME_SW_I2C lcd(/* clock=*/ 2, /* data=*/ 0, /* reset=*/ U8X8_PIN_NONE); 	      // Digispark ATTiny85
// U8X8_SSD1306_128X64_NONAME_SW_I2C lcd(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
// U8X8_SSD1306_128X64_NONAME_SW_I2C lcd(/* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE); // OLEDs without Reset of the Display
//U8X8_SSD1306_128X64_VCOMH0_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);		// same as the NONAME variant, but maximizes setContrast() range
//U8X8_SSD1306_128X64_ALT0_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);		// same as the NONAME variant, but may solve the "every 2nd line skipped" problem
//U8X8_SH1106_128X64_NONAME_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SH1106_128X64_NONAME_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SH1106_128X64_VCOMH0_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);		// same as the NONAME variant, but maximizes setContrast() range
//U8X8_SH1106_128X64_WINSTAR_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);		// same as the NONAME variant, but uses updated SH1106 init sequence
//U8X8_SH1106_72X40_WISE_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SH1107_64X128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SH1107_128X128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SH1107_128X128_HW_I2C lcd(/* reset=*/ 8);
//U8X8_SH1107_PIMORONI_128X128_HW_I2C lcd(/* reset=*/ 8);
//U8X8_SH1107_SEEED_128X128_SW_I2C lcd(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
//U8X8_SH1107_SEEED_128X128_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SH1107_SEEED_96X96_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SH1108_160X160_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1306_128X32_UNIVISION_SW_I2C lcd(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
//U8X8_SSD1306_128X32_UNIVISION_SW_I2C lcd(/* clock=*/ 21, /* data=*/ 20, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather M0 Basic Proto + FeatherWing OLED
//U8X8_SSD1306_128X32_UNIVISION_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);   // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
//U8X8_SSD1306_128X32_UNIVISION_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8X8_SSD1306_128X32_WINSTAR_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8X8_SSD1306_64X48_ER_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);   // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered
//U8X8_SSD1306_48X64_WINSTAR_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SSD1306_64X32_NONAME_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SSD1306_64X32_1F_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SSD1306_96X16_ER_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);   // EastRising 0.69"
//U8X8_SSD1306_72X40_ER_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);   // EastRising 0.42"
//U8X8_SSD1306_128X64_NONAME_6800 lcd(13, 11, 2, 3, 4, 5, 6, A4, /*enable=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8);
//U8X8_SSD1306_128X64_NONAME_8080 lcd(13, 11, 2, 3, 4, 5, 6, A4, /*enable=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8);
//U8X8_SSD1309_128X64_NONAME0_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1309_128X64_NONAME0_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1309_128X64_NONAME2_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1309_128X64_NONAME2_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1316_128X32_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1316_128X32_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1317_96X96_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // not tested, not confirmed
//U8X8_SSD1317_96X96_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // not tested, not confirmed
//U8X8_SSD1318_128X96_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1318_128X96_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1322_NHD_256X64_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1322_NHD_256X64_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1322_NHD_128X64_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1322_NHD_128X64_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1325_NHD_128X64_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1325_NHD_128X64_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD0323_OS128064_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD0323_OS128064_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1326_ER_256X32_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);         // experimental driver for ER-OLED018-1
//U8X8_SSD1327_SEEED_96X96_SW_I2C lcd(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);	// Seeedstudio Grove OLED 96x96
//U8X8_SSD1327_SEEED_96X96_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);	// Seeedstudio Grove OLED 96x96
//U8X8_SSD1327_EA_W128128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_EA_W128128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_MIDAS_128X128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_WS_128X128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_WS_128X128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_VISIONOX_128X96_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1327_VISIONOX_128X96_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1329_128X96_NONAME_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1329_128X96_NONAME_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1305_128X32_NONAME_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1305_128X32_NONAME_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1305_128X32_ADAFRUIT_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1305_128X32_ADAFRUIT_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1305_128X64_ADAFRUIT_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_SSD1305_128X64_ADAFRUIT_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_KS0108_128X64 lcd(8, 9, 10, 11, 4, 5, 6, 7, /*enable=*/ 18, /*dc=*/ 17, /*cs0=*/ 14, /*cs1=*/ 15, /*cs2=*/ U8X8_PIN_NONE, /* reset=*/  U8X8_PIN_NONE); 	// Set R/W to low!
//U8X8_KS0108_ERM19264 lcd(8, 9, 10, 11, 4, 5, 6, 7, /*enable=*/ 18, /*dc=*/ 17, /*cs0=*/ 14, /*cs1=*/ 15, /*cs2=*/ 16, /* reset=*/  U8X8_PIN_NONE); 	// Set R/W to low!
//U8X8_UC1701_EA_DOGS102_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1701_EA_DOGS102_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_PCD8544_84X48_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// Nokia 5110 Display
//U8X8_PCD8544_84X48_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);							// Nokia 5110 Display
//U8X8_PCF8812_96X65_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// Could be also PCF8814
//U8X8_PCF8812_96X65_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);			// Could be also PCF8814
//U8X8_HX1230_96X68_3W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
//U8X8_HX1230_96X68_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_EA_DOGM128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_EA_DOGM128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_64128N_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_64128N_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_EA_DOGM132_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ U8X8_PIN_NONE);	// DOGM132 Shield
//U8X8_ST7565_EA_DOGM132_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ U8X8_PIN_NONE);	// DOGM132 Shield
//U8X8_ST7565_ZOLEN_128X64_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_ZOLEN_128X64_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_LM6059_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// Adafruit ST7565 GLCD
//U8X8_ST7565_LM6059_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);		// Adafruit ST7565 GLCD
//U8X8_ST7565_KS0713_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// KS0713 controller
//U8X8_ST7565_KS0713_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);		// KS0713 controller
//U8X8_ST7565_LX12864_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_LX12864_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_ERC12864_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_ERC12864_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_ERC12864_ALT_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); // contrast improved version for ERC12864
//U8X8_ST7565_ERC12864_ALT_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// contrast improved version for ERC12864
//U8X8_ST7565_NHD_C12832_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_NHD_C12832_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_NHD_C12864_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_NHD_C12864_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_JLX12864_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7565_JLX12864_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_PI_132X64_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  // Pax Instruments Shield, LCD_BL=6
//U8X8_ST7567_PI_132X64_4W_HW_SPI lcd(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  // Pax Instruments Shield, LCD_BL=6
//U8X8_ST7567_JLX12864_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_JLX12864_4W_HW_SPI lcd(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_OS12864_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_OS12864_4W_HW_SPI lcd(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_ENH_DG128064_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_ENH_DG128064_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_ENH_DG128064I_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_ENH_DG128064I_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7567_64X32_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_ST7567_HEM6432_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
//U8X8_ST75256_JLX172104_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX172104_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX19296_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX19296_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256128_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_WO256X128_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_WO256X128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256160_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256160_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256160M_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256160M_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256160_ALT_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX256160_ALT_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX240160_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX240160_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75256_JLX25664_2ND_HW_I2C lcd(/* reset=*/ 8);	// Due, 2nd I2C
//U8X8_ST75320_JLX320240_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST75320_JLX320240_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_NT7534_TG12864R_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_NT7534_TG12864R_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_ST7588_JLX12864_SW_I2C lcd(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ 5);
//U8X8_ST7588_JLX12864_HW_I2C lcd(/* reset=*/ 5);
//U8X8_IST3020_ERC19264_6800 lcd(44, 43, 42, 41, 40, 39, 38, 37,  /*enable=*/ 28, /*cs=*/ 32, /*dc=*/ 30, /*reset=*/ 31); // Connect WR pin with GND
//U8X8_IST3020_ERC19264_8080 lcd(44, 43, 42, 41, 40, 39, 38, 37,  /*enable=*/ 29, /*cs=*/ 32, /*dc=*/ 30, /*reset=*/ 31); // Connect RD pin with 3.3V
//U8X8_IST3020_ERC19264_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_IST7920_128X128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); // Round display
//U8X8_IST7920_128X128_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); // Round display
//U8X8_UC1601_128X32_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1601_128X32_3W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
//U8X8_UC1604_JLX19264_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1604_JLX19264_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1608_ERC24064_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // Due, SW SPI, ERC24064-1 Test Board
//U8X8_UC1608_DEM240064_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // Due, SW SPI, ERC24064-1 Test Board
//U8X8_UC1608_ERC240120_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1608_240X128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1610_EA_DOGXL160_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/  U8X8_PIN_NONE);
//U8X8_UC1610_EA_DOGXL160_4W_HW_SPI lcd(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/  U8X8_PIN_NONE);
//U8X8_UC1611_EA_DOGM240_2ND_HW_I2C lcd(/* reset=*/ 8);	// Due, 2nd I2C, DOGM240 Test Board
//U8X8_UC1611_EA_DOGM240_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // SW SPI, Due DOGXL240 Test Board
//U8X8_UC1611_EA_DOGXL240_2ND_HW_I2C lcd(/* reset=*/ 8);	// Due, 2nd I2C, DOGXL240 Test Board
//U8X8_UC1611_EA_DOGXL240_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // SW SPI, Due DOGXL240 Test Board
//U8X8_UC1611_EW50850_8080 lcd(8, 9, 10, 11, 4, 5, 6, 7,  /*enable=*/ 18, /*cs=*/ 3, /*dc=*/ 16, /*reset=*/ 17); // 240x160, Connect RD/WR1 pin with 3.3V, CS is aktive high
//U8X8_UC1611_CG160160_8080 lcd(8, 9, 10, 11, 4, 5, 6, 7,  /*enable=*/ 18, /*cs=*/ 3, /*dc=*/ 16, /*reset=*/ 17); // Connect WR1 and CD1 pin with 3.3V, connect CS0 with cs, WR0 with enable, CD with dc
//U8X8_UC1617_JLX128128_4W_SW_SPI lcd( /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1617_JLX128128_4W_HW_SPI lcd( /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8X8_UC1638_160X128_4W_HW_SPI lcd(/* cs=*/ 2, /* dc=*/ 3, /* reset=*/ 4); 	 // Not tested
//U8X8_SSD1606_172X72_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// eInk/ePaper Display
//U8X8_SSD1607_200X200_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// eInk/ePaper Display, original LUT from embedded artists
//U8X8_SSD1607_GS_200X200_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// Good Display
//U8X8_SSD1607_WS_200X200_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// Waveshare
//U8X8_IL3820_296X128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// eInk/ePaper Display, original LUT
//U8X8_IL3820_V2_296X128_4W_SW_SPI lcd(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// eInk/ePaper Display, optimized (lesser screen flicker)
//U8X8_ST7511_AVD_320X240_8080 lcd(13, 11, 2, 3, 4, 5, 6, A4, /*enable/WR=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8); // Connect RD pin with 3.3V/5V

// End of constructor list

void LCD_Init(void)
{
  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0);

  /* U8g2 Project: KS0108 Test Board */
  //pinMode(16, OUTPUT);
  //digitalWrite(16, 0);

  lcd.begin();

  lcd.clearDisplay();
}


TwoWire u8x8Wire;
/*=== HARDWARE I2C ===*/
extern "C" uint8_t u8x8_byte_arduino_hw_i2c(U8X8_UNUSED u8x8_t *lcd, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
#ifdef U8X8_HAVE_HW_I2C
  switch (msg)
  {
  case U8X8_MSG_BYTE_SEND:
    u8x8Wire.write((uint8_t *)arg_ptr, (int)arg_int);
    break;
  case U8X8_MSG_BYTE_INIT:
    if (lcd->bus_clock == 0) /* issue 769 */
      lcd->bus_clock = lcd->display_info->i2c_bus_clock_100kHz * 100000UL;
#if defined(ESP8266) || defined(ARDUINO_ARCH_ESP8266) || defined(ESP_PLATFORM) || defined(ARDUINO_ARCH_ESP32)
    /* for ESP8266/ESP32, u8x8Wire.begin has two more arguments: clock and data */
    if (lcd->pins[U8X8_PIN_I2C_CLOCK] != U8X8_PIN_NONE && lcd->pins[U8X8_PIN_I2C_DATA] != U8X8_PIN_NONE)
    {
      // second argument for the wire lib is the clock pin. In u8g2, the first argument of the  clock pin in the clock/data pair
      u8x8Wire.begin(lcd->pins[U8X8_PIN_I2C_DATA], lcd->pins[U8X8_PIN_I2C_CLOCK]);
    }
    else
    {
      u8x8Wire.begin();
    }
#else
    // u8x8Wire.begin();
    u8x8Wire.begin((uint8_t)U8X8_SDA, (uint8_t)U8X8_SCL);
#endif
    break;
  case U8X8_MSG_BYTE_SET_DC:
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
#if ARDUINO >= 10600
    /* not sure when the setClock function was introduced, but it is there since 1.6.0 */
    /* if there is any error with u8x8Wire.setClock() just remove this function call */
    u8x8Wire.setClock(lcd->bus_clock);
#endif
    u8x8Wire.beginTransmission(u8x8_GetI2CAddress(lcd) >> 1);
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    u8x8Wire.endTransmission();
    break;
  default:
    return 0;
  }
#endif
  return 1;
}
