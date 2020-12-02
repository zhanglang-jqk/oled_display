#include <Arduino.h>
#include "modules/mpu.h"
#include "modules/lcd.h"

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

    float accelleroX_Threshold;
    float accelleroY_Threshold;
    float accelleroZ_Threshold;

    float gyroX_Threshold;
    float gyroY_Threshold;
    float gyroZ_Threshold;
} PAREMETER_STRU;
PAREMETER_STRU parems;

/*  ---------------------------------------------------------------------------------------------------------------*/

void setup()
{

    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    CLOSE_LED1(), CLOSE_LED2();

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

        char ypr_str[64] = {0};
        char yaw_str[16] = {0}, pitch_str[16] = {0}, roll_str[16] = {0};
        memset(yaw_str, 0, sizeof(yaw_str)), memset(pitch_str, 0, sizeof(pitch_str)), memset(roll_str, 0, sizeof(roll_str));
        dtostrf(yaw, 2, 1, yaw_str), dtostrf(pitch, 2, 1, pitch_str), dtostrf(roll, 2, 1, roll_str);
        sprintf(ypr_str, "% 5s % 5s % 5s", yaw_str, pitch_str, roll_str);
        // lcd.clear();
        lcd.drawString(0, 0, space_str), lcd.drawString(0, 0, ypr_str);

        char gxyz_str[64] = {0};
        memset(gxyz_str, 0, sizeof(gxyz_str));
        sprintf(gxyz_str, "%05d %05d %05d", abs(gx), abs(gy), abs(gz));
        lcd.drawString(0, 1, space_str), lcd.drawString(0, 1, gxyz_str);

        lcd.refreshDisplay(); // only required for SSD1606/7

        if ((gx < (0.0 - parems.gyroX_Threshold) || gx > parems.gyroX_Threshold) ||
            (gy < (0.0 - parems.gyroY_Threshold) || gy > parems.gyroY_Threshold) ||
            (gz < (0.0 - parems.gyroZ_Threshold) || gz > parems.gyroZ_Threshold))
        {
            gyro_f = true;
        }

        if (gyro_f)
        {
            if (abs(pitch - set_pitch) > parems.pitchThreshold)
            {
                OPEN_LED1();
            }
            else if (abs(roll - set_roll) > parems.rollThreshold)
            {
                OPEN_LED1();
            }
            else
            {
                CLOSE_LED1();
                gyro_f = false;
            }
        }
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
