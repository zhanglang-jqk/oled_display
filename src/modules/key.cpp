/***********************************************************************
 * @file 	:	key.cpp
 * @author	:	ch
 * @brief	:	
 * @version:	v1.0
 * @Copyright (C)  2020-12-02  .cdWFVCEL. all right reserved
***********************************************************************/

/* 包含头文件 -------------------------------------------------------------------*/
#include "key.h"
#include "Arduino.h"
/* 宏定义 -----------------------------------------------------------------------*/
/* 类型定义 ---------------------------------------------------------------------*/
#define KEY_UP 0
#define KEY_SHORT_PRESS 1
#define KEY_LONG_PRESS 2
/* 私有变量 ---------------------------------------------------------------------*/
/* 扩展变量 ---------------------------------------------------------------------*/
/* 私有函数声明 -----------------------------------------------------------------*/
/* 函数声明 ---------------------------------------------------------------------*/
/* 函数实现 ---------------------------------------------------------------------*/

void KEY_Init()
{
    pinMode(SET_KEY, INPUT_PULLUP);
    pinMode(UP_KEY, INPUT_PULLUP);
    pinMode(DOWN_KEY, INPUT_PULLUP);
}

u8 KEY_ScanBlock(u8 keyPin)
{
    u32 keyCnt = 0;
    if (digitalRead(keyPin) == LOW)
    {
        delay(KEY_DELAY);
        if (digitalRead(keyPin) == LOW)
        {
            while (digitalRead(keyPin) == LOW)
            {
                keyCnt++;
                delay(1);

                if (keyCnt >= 1000)
                {
                    return KEY_LONG_PRESS;
                }
            }
            if (keyCnt < 1000)
            {
                return KEY_SHORT_PRESS;
            }
        }
    }
    return KEY_UP;
}
//key.cpp
