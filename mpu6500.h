/**
 * @file mpu6500.h 
 * @brief MPU6500 accelerometer and gyroscope driver header
 * @details This header file contains the declarations and definitions for the
 *          MPU6500 accelerometer and gyroscope driver, supporting various
 *          operations.
 * @author Cengiz Sinan Kostakoglu
 * @version 1.0
 * @date 2025-06-07
 */

#ifndef __MPU6500_H__
#define __MPU6500_H__

#ifdef __cplusplus
extern "C" {
#endif

/* For HAL functions and I2C initialization */
#include "main.h"

/**
 * @brief Initialize the MPU6500 accelerometer
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Configuration sequence:
 *       1. Reset device
 *       2. Wake up and configure clock
 *       3. Disable gyroscope
 *       4. Configure accelerometer (±16g, 20Hz bandwidth)
 *       5. Configure interrupt pin
 */
HAL_StatusTypeDef MPU6500_Init(void);

/**
 * @brief Enable data ready interrupts from the MPU6500
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Enables RAW_RDY_EN bit in INT_ENABLE register
 */
HAL_StatusTypeDef MPU6500_EnableDataReadyInterrupts(void);

/**
 * @brief Disable data ready interrupts from the MPU6500
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Disables RAW_RDY_EN bit in INT_ENABLE register
 */
HAL_StatusTypeDef MPU6500_DisableDataReadyInterrupts(void);

/**
 * @brief Read the WHO_AM_I register of the MPU6500
 * @param whoami Pointer to store the value read from WHO_AM_I register
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure    
 */
HAL_StatusTypeDef MPU6500_ReadWhoAmI(uint8_t *whoami);

/**
 * @brief Read accelerometer data from MPU6500
 * @param x Pointer to store X-axis acceleration
 * @param y Pointer to store Y-axis acceleration
 * @param z Pointer to store Z-axis acceleration
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Reads 6 bytes starting from ACCEL_XOUT_H register
 *       Data is in 16-bit format, high byte first
 */
HAL_StatusTypeDef MPU6500_ReadAccel(int16_t *x, int16_t *y, int16_t *z);

/**
 * @brief Read gyroscope data from MPU6500
 * @param x Pointer to store X-axis gyroscope data
 * @param y Pointer to store Y-axis gyroscope data
 * @param z Pointer to store Z-axis gyroscope data
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Reads 6 bytes starting from GYRO_XOUT_H register
 *       Data is in 16-bit format, high byte first
 */
HAL_StatusTypeDef MPU6500_ReadGyro(int16_t *x, int16_t *y, int16_t *z); 

/**
 * @brief Put the MPU6500 into sleep mode to save power
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Sets SLEEP bit (bit 6) in PWR_MGMT_1 register
 */
HAL_StatusTypeDef MPU6500_Sleep(void);

/**
 * @brief Wake up the MPU6500 from sleep mode
 * @return HAL_StatusTypeDef HAL_OK on success, error on failure
 * @note Clears SLEEP bit (bit 6) in PWR_MGMT_1 register
 */
HAL_StatusTypeDef MPU6500_WakeUp(void);

#ifdef __cplusplus
}
#endif

#endif
