/**
 * @file can_bms_driver.h
 * @brief BMS CAN messages
 *
 * @date Nov 29, 2025
 * @author lenovo
 */

#ifndef SRC_CAN_BMS_DRIVER_H_
#define SRC_CAN_BMS_DRIVER_H_

#include <stdint.h>

/**
 * @brief BMS CAN Frame-0 structure (Index = 0x00).
 *
 * Frame contents:
 *   - Byte0 : Frame index (0x00)
 *   - Byte1-Byte7 : 7-byte unique BMS ID
 */
typedef struct
{
    uint8_t index_00;              /**< Frame index, always 0x00 */
    uint8_t uinque_bms_id[8];      /**< 7–byte unique BMS ID (Byte[0] used, remaining 7 bytes transmitted) */
} bms_data_index0;


/**
 * @brief BMS CAN Frame-1 structure (Index = 0x01).
 *
 * Frame contents:
 *   - Byte0 : Frame index (0x01)
 *   - Byte1-2 : Battery voltage (scaled as required)
 *   - Byte3-4 : Battery current  (scaled as required)
 *   - Byte5 : Battery temperature (°C)
 *   - Byte6 : Load status (0-No load, 3-Discharge, 4-Charge)
 *   - Byte7 : Reserved
 */
typedef struct
{
    uint8_t  index_01;            /**< Frame index, always 0x01 */
    uint16_t battery_voltage;     /**< Battery voltage (apply scaling factor before assignment) */
    uint16_t current;             /**< Battery current (apply scaling factor before assignment) */
    uint8_t  battery_temperature; /**< Battery temperature in °C */
    uint8_t  load_status;         /**< Load status: 0=No load, 3=Discharge, 4=Charge */
    uint8_t  reserved;            /**< Reserved / padding */
} bms_data_index1;


/* --------------------------------------------------------------------------
 * External variables
 * -------------------------------------------------------------------------- */

/** Global frame-0 data */
extern bms_data_index0 data0;

/** Global frame-1 data */
extern bms_data_index1 data1;


/* --------------------------------------------------------------------------
 * Public API
 * -------------------------------------------------------------------------- */

/**
 * @brief Prepares CAN Frame-0 (index 0x00).
 *
 * Populates TxData0 buffer with:
 *   - Index
 *   - BMS unique ID (7 bytes)
 *
 * Does NOT transmit by itself. Caller must use HAL_CAN_AddTxMessage().
 */
void send_frame0(void);


/**
 * @brief Prepares CAN Frame-1 (index 0x01).
 *
 * Populates TxData1 buffer with:
 *   - Voltage MSB/LSB
 *   - Current MSB/LSB
 *   - Temperature
 *   - Load status
 *
 * Does NOT transmit by itself. Caller must use HAL_CAN_AddTxMessage().
 */
void send_frame1(void);

#endif /* SRC_CAN_BMS_DRIVER_H_ */
