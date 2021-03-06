/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:
*   This projection is the modified version of handsfree_simple_app which
* is used for my graduation projection.
*   pkgs: imu
*         servo
*                                                           by cyb, 2017.04.17
***********************************************************************************************************************/

#include "main_config.h"
#include "board.h"
#include "stdlib.h"

#include "imu_top.h"

int main(void)
{
    Board *board = Board::getInstance();
    board->boardBasicInit();

    HF_USART_printf(USART1, " >> welcome to the graduation projection of cyb \r\n");

    IMU imu_top;
    imu_top.topInit(1, 0, 1, 0, 0, 1);

    HF_USART_printf(USART1, ">> task begin \r\n");

    while(1)
    {
        if ( board->cnt_1ms >= 1 )    // 1000hz
        {
            imu_top.topCall();

            board->cnt_1ms=0;
        }

        if ( board->cnt_2ms >= 2 )    // 500hz
        {
            board->cnt_2ms=0;
        }

        if ( board->cnt_5ms >= 5 )    // 200hz
        {
            board->cnt_5ms=0;
        }

        if ( board->cnt_10ms >= 10 )  // 100hz
        {
            board->cnt_10ms=0;
            board->boardBasicCall();   // need time stm32f1 35us
        }

        if ( board->cnt_20ms >= 20 )  // 50hz
        {
            board->cnt_20ms = 0 ;
        }

        if ( board->cnt_50ms >= 50 )  // 20hz
        {
            board->cnt_50ms = 0 ;

            {   /// running the leds. lalalala....
                static char led_turns = 0;
                board->setLedState(led_turns, 2);
                if(led_turns >= 2)
                    led_turns = 0;
                else
                    ++led_turns;
            }

            {
                // float ttt;
                // ttt =  HF_Get_Dtime() / 1000;
                // printf("[debug]: %f ms \r\n", ttt);
            }

        }
    }

}
