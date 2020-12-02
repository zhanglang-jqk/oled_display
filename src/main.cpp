#include <Arduino.h>
#include "modules/mpu.h"
#include "modules/lcd.h"

void setup()
{
    MPU_Init();
    LCD_Init();
    // lcd.setFont(u8x8_font_8x13B_1x2_f);
    lcd.setFont(u8x8_font_artossans8_r);
}
void loop()
{
    u8 isok = MPU_Process();

    if (isok == 0)
    {
        char ypr_str[64] = {0};

        char yaw_str[16] = {0}, pitch_str[16] = {0}, roll_str[16] = {0};
        memset(yaw_str, 0, sizeof(yaw_str)), memset(pitch_str, 0, sizeof(pitch_str)), memset(roll_str, 0, sizeof(roll_str));
        dtostrf(yaw, 2, 1, yaw_str), dtostrf(pitch, 2, 1, pitch_str), dtostrf(roll, 2, 1, roll_str);
        sprintf(ypr_str, "%04s %04s %04s", yaw_str, pitch_str, roll_str);

        // lcd.clear();
        lcd.drawString(0, 0, ypr_str);
        lcd.refreshDisplay(); // only required for SSD1606/7
        // delay(2000);
    }
}

/********************************************************************************
*  
* @biref£º set 
* @biref£º set crystal Oscillator to internal
* @param£º
********************************************************************************/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}
