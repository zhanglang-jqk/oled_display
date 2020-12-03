#include <Arduino.h>
#include "modules/mpu.h"
#include "modules/lcd.h"
#include "modules/key.h"

/* define ---------------------------------------------------------------------------------------------------------------*/
#define PITCH_THRESHOLD 40
#define ROLL_THRESHOLD 40
#define YAW_THRESHOLD 30

#define ACCELERO_X_THRESHOLD 1
#define ACCELERO_Y_THRESHOLD 1
#define ACCELERO_Z_THRESHOLD 1

#define GYRO_X_THRESHOLD 5000
#define GYRO_Y_THRESHOLD 5000
#define GYRO_Z_THRESHOLD 5000

#define LED1_PIN PA12
#define LED2_PIN PA11

#define OPEN_LED1() digitalWrite(LED1_PIN, LOW)
#define CLOSE_LED1() digitalWrite(LED1_PIN, HIGH)
#define OPEN_LED2() digitalWrite(LED2_PIN, LOW)
#define CLOSE_LED2() digitalWrite(LED2_PIN, HIGH)
/*  ---------------------------------------------------------------------------------------------------------------*/

bool isFirst_f = true;
float set_yaw = 0, set_pitch = 0, set_roll = 0;

#pragma pack(4)
typedef struct
{
    float pitchThreshold;
    float rollThreshold;
    float yawThreshold;

    int16_t accelleroX_Threshold;
    int16_t accelleroY_Threshold;
    int16_t accelleroZ_Threshold;

    int16_t gyroX_Threshold;
    int16_t gyroY_Threshold;
    int16_t gyroZ_Threshold;
} PAREMETER_STRU;
PAREMETER_STRU parems;

/*  ---------------------------------------------------------------------------------------------------------------*/
void refreshMenu()
{
    { //refresh lcd
        char disStr[32] = {0};

        memset(disStr, 0, sizeof(disStr));
        sprintf(disStr, "acc  :%05d", parems.accelleroX_Threshold);
        lcd.drawString(2, 0, disStr);

        memset(disStr, 0, sizeof(disStr));
        sprintf(disStr, "gyro :%05d", parems.gyroX_Threshold);
        lcd.drawString(2, 1, disStr);

        memset(disStr, 0, sizeof(disStr));
        char tmp[16] = {0};
        dtostrf(parems.pitchThreshold, 3, 1, tmp);
        sprintf(disStr, "angle:%s", tmp);
        lcd.drawString(2, 2, disStr);
        lcd.refreshDisplay();
    }
}
/*  ---------------------------------------------------------------------------------------------------------------*/

void setup()
{

    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    CLOSE_LED1(), CLOSE_LED2();

    KEY_Init();

    MPU_Init();
    LCD_Init();
    // lcd.setFont(u8x8_font_8x13B_1x2_f);
    lcd.setFont(u8x8_font_artossans8_r);

    // u32 tmp = *(u32 *)FLASH_START_ADDRESS;
    // if (tmp == 0xffffffff) //{} writing default paremeter
    // {
    parems.pitchThreshold = PITCH_THRESHOLD;
    parems.rollThreshold = ROLL_THRESHOLD;
    parems.yawThreshold = YAW_THRESHOLD;

    parems.accelleroX_Threshold = ACCELERO_X_THRESHOLD;
    parems.accelleroY_Threshold = ACCELERO_Y_THRESHOLD;
    parems.accelleroZ_Threshold = ACCELERO_Z_THRESHOLD;

    parems.gyroX_Threshold = GYRO_X_THRESHOLD;
    parems.gyroY_Threshold = GYRO_Y_THRESHOLD;
    parems.gyroZ_Threshold = GYRO_Z_THRESHOLD;

    //     writeBufferFlash(FLASH_START_ADDRESS, (u8 *)&parems, sizeof(PAREMETER_STRU));
    // }
    // else
    // {
    //     readBufferFlash(FLASH_START_ADDRESS, (u8 *)&parems, sizeof(PAREMETER_STRU));
    // }
}
bool gyro_f = false;

void loop()
{
    u8 isok = MPU_Process();

    // if(0)
    if (isok == 0)
    {
        if (isFirst_f) //set compare yaw
        {
            set_yaw = yaw, set_pitch = pitch, set_roll = roll;
            isFirst_f = false;
        }

        char space_str[17] = {0};
        memset(space_str, ' ', sizeof(space_str) - 1);

        char axyz_str[32] = {0};
        memset(axyz_str, 0, sizeof(axyz_str));
        sprintf(axyz_str, "%05d %05d %05d", abs(ax), abs(ay), abs(az));
        lcd.drawString(0, 0, space_str), lcd.drawString(0, 0, axyz_str);

        char gxyz_str[32] = {0};
        memset(gxyz_str, 0, sizeof(gxyz_str));
        sprintf(gxyz_str, "%05d %05d %05d", abs(gx), abs(gy), abs(gz));
        lcd.drawString(0, 1, space_str), lcd.drawString(0, 1, gxyz_str);

        char ypr_str[32] = {0};
        char yaw_str[16] = {0}, pitch_str[16] = {0}, roll_str[16] = {0};
        memset(yaw_str, 0, sizeof(yaw_str)), memset(pitch_str, 0, sizeof(pitch_str)), memset(roll_str, 0, sizeof(roll_str));
        dtostrf(yaw, 2, 1, yaw_str), dtostrf(pitch, 2, 1, pitch_str), dtostrf(roll, 2, 1, roll_str);
        // sprintf(ypr_str, "% 5s % 5s % 5s", yaw_str, pitch_str, roll_str);
        sprintf(ypr_str, "% 5s % 5s", pitch_str, roll_str);
        // lcd.clear();
        lcd.drawString(0, 2, space_str), lcd.drawString(0, 2, ypr_str);

        lcd.refreshDisplay(); // only required for SSD1606/7

        if ((gx < (0.0 - parems.gyroX_Threshold) || gx > parems.gyroX_Threshold) ||
            (gy < (0.0 - parems.gyroY_Threshold) || gy > parems.gyroY_Threshold) ||
            (gz < (0.0 - parems.gyroZ_Threshold) || gz > parems.gyroZ_Threshold))
        {
            gyro_f = true;
        }

        if (gyro_f)
        {
            if ((abs(pitch - set_pitch) > parems.pitchThreshold) || (abs(roll - set_roll) > parems.rollThreshold))
            {
                OPEN_LED1();

                //display set parames
                char axyz_str[32] = {0};
                memset(axyz_str, 0, sizeof(axyz_str));
                sprintf(axyz_str, "%05d %05d %05d", abs(ax), abs(ay), abs(az));
                lcd.drawString(0, 4, axyz_str);

                char gxyz_str[32] = {0};
                memset(gxyz_str, 0, sizeof(gxyz_str));
                sprintf(gxyz_str, "%05d %05d %05d", abs(gx), abs(gy), abs(gz));
                lcd.drawString(0, 5, gxyz_str);

                char ypr_str[32] = {0};
                char yaw_str[16] = {0}, pitch_str[16] = {0}, roll_str[16] = {0};
                memset(yaw_str, 0, sizeof(yaw_str)), memset(pitch_str, 0, sizeof(pitch_str)), memset(roll_str, 0, sizeof(roll_str));
                dtostrf(yaw, 2, 1, yaw_str), dtostrf(pitch, 2, 1, pitch_str), dtostrf(roll, 2, 1, roll_str);
                // sprintf(ypr_str, "% 5s % 5s % 5s", yaw_str, pitch_str, roll_str);
                sprintf(ypr_str, "% 5s % 5s", pitch_str, roll_str);
                // lcd.clear();
                lcd.drawString(0, 6, ypr_str);

                lcd.refreshDisplay(); // only required for SSD1606/7

                gyro_f = false;
            }
            // else
            // {
            //     CLOSE_LED1();
            //     gyro_f = false;
            // }
        }
    }

    u8 tmp = KEY_ScanBlock(SET_KEY);
    if (tmp == KEY_SHORT_PRESS)
    {
        goto menu;
    }
    else if (tmp == KEY_LONG_PRESS)
    {
        Serial.println("system reset");
        for (int i = 0; i < 5; i++)
        {
            digitalToggle(LED1_PIN);
            delay(100);
        }
        HAL_NVIC_SystemReset();
    }

    if (0) //menu control
    {
    menu:
    { //{} menu display init
        lcd.clear();
        lcd.drawString(0, 0, "->");
    }

        u8 item = 1;
        u32 setKeyCnt = 0, upKeyCnt = 0, downKeyCnt = 0;
        u8 key = KEY_UP;
        while (1)
        {
            key = KEY_ScanBlock(SET_KEY);

            if (key == KEY_SHORT_PRESS) //{} 'set 	key' short press, select next menu item
            {
                item < 3 ? item++ : item = 1;

                lcd.drawString(0, 0, "                ");
                lcd.drawString(0, 1, "                ");
                lcd.drawString(0, 2, "                ");
                //{elif} item icon display
                if (item == 1)
                {
                    lcd.drawString(0, 0, "->");
                }
                else if (item == 2)
                {
                    lcd.drawString(0, 1, "->");
                }
                else if (item == 3)
                {
                    lcd.drawString(0, 2, "->");
                }

                //{} if 'set key' long press , save config paremes data and quick menu setting
            }
            else if (key == KEY_LONG_PRESS)
            {
                parems.accelleroZ_Threshold = parems.accelleroY_Threshold = parems.accelleroX_Threshold;
                parems.rollThreshold = parems.yawThreshold = parems.pitchThreshold;
                parems.gyroZ_Threshold = parems.gyroY_Threshold = parems.gyroX_Threshold;

                // writeBufferFlash(FLASH_START_ADDRESS, (u8 *)&parems, sizeof(PAREMETER_STRU));

                lcd.clear();

                while (digitalRead(SET_KEY) == LOW)
                    ; //wait key up
                break;
            }
            key = KEY_UP;

            key = KEY_ScanBlock(UP_KEY);
            if (key == KEY_SHORT_PRESS)
            {
                switch (item)
                {
                case 1:
                    parems.accelleroX_Threshold += 1;
                    break;
                case 2:
                    parems.gyroX_Threshold += 100;
                    break;
                case 3:
                    parems.pitchThreshold += 5;
                    break;
                }
            }
            else if (key == KEY_LONG_PRESS)
            {
                while (digitalRead(UP_KEY) == LOW) //wait key up
                {
                    switch (item)
                    {
                    case 1:
                        parems.accelleroX_Threshold += 1;
                        break;
                    case 2:
                        parems.gyroX_Threshold += 10;
                        break;
                    case 3:
                        parems.pitchThreshold += 1;
                        break;
                    }
                    // lcd.refreshDisplay();
                    refreshMenu();
                    delay(10);
                }
            }
            key = KEY_UP;

            key = KEY_ScanBlock(DOWN_KEY);
            if (key == KEY_SHORT_PRESS)
            {
                switch (item)
                {
                case 1:
                    parems.accelleroX_Threshold -= 1;
                    break;
                case 2:
                    parems.gyroX_Threshold -= 10;
                    break;
                case 3:
                    parems.pitchThreshold -= 5;
                    break;
                }
            }
            else if (key == KEY_LONG_PRESS)
            {
                while (digitalRead(DOWN_KEY) == LOW) //wait key up
                {
                    switch (item)
                    {
                    case 1:
                        parems.accelleroX_Threshold -= 1;
                        break;
                    case 2:
                        parems.gyroX_Threshold -= 10;
                        break;
                    case 3:
                        parems.pitchThreshold -= 1;
                        break;
                    }
                    // lcd.refreshDisplay();
                    refreshMenu();
                    delay(10);
                }
            }
            key = KEY_UP;

            refreshMenu();
        }
    }

    char set_str[32] = {0};
    sprintf(set_str, "%05d %05d ", parems.accelleroX_Threshold, parems.gyroX_Threshold);
    char buf[16] = {0};
    dtostrf(parems.pitchThreshold, 5, 1, (char *)buf);
    strcat(set_str, buf);
    lcd.drawString(0, 7, set_str);
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
