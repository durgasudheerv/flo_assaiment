/*
 * can_bms_driver.c
 *
 *  Created on: Nov 29, 2025
 *      Author: lenovo
 */
#include "stm32f4xx_hal.h"
#include "can_bms_driver.h"

uint8_t TxData0[8];
uint8_t TxData1[8];

bms_data_index0 data0;
bms_data_index1 data1;

void send_frame0(void)
{
    bms_data_index0 data0 =
    {
        .index_00 = 0x00,
        .uinque_bms_id = {0x13, 0x97, 0x06, 0x0D, 0x1F, 0x00, 0x00},
    };

    TxData0[0] = data0.index_00;
    for(uint8_t count = 1;count < 8;count++ )
    {
           TxData0[count] = data0.uinque_bms_id[count];
           count++;
     }

}

void send_frame1(void)
{
    bms_data_index1 data1 = {
        .index_01 = 0x01,
        .battery_voltage = (uint16_t)57.1f,
        .current = (uint16_t)15.49f,
        .battery_temperature = 31,
        .load_status = 2,
        .reserved = 0x00
    };

           TxData1[0] = data1.index_01;
           TxData1[1] = data1.battery_voltage >> 8;
           TxData1[2] = data1.battery_voltage & 0xFF;
           TxData1[3] = (uint8_t)(data1.current >> 8);
           TxData1[4] = (uint8_t)(data1.current & 0xFF);
           TxData1[5] = data1.battery_temperature;
           TxData1[6] = data1.load_status;
           TxData1[7] = 0x00;  // reserved

}



