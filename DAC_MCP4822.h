/**
 * @file DAC_MCP4822.h
 *
 * @brief Header file for the MCP4822 (DAC) driver.
 *
 * This file contains the function definitions for the MCP4822 (DAC) driver.
 *
 * @note Assumes that the system clock (50 MHz) is used.
 *
 * @author
 */

#include "TM4C123GH6PM.h"

#define SSI0_BUSY_BIT_MASK (0x10)
#define SSI0_RX_FIFO_NOT_EMPTY_BIT_MASK (0x04)
#define SSI0_TX_FIFO_EMPTY_BIT_MASK (0x01)

/**
 * @brief
 *
 * @param None
 *
 * @return None
 */
void MCP4822_Init(void);

/**
 * @brief
 *
 * @param uint16_t data
 *
 * @return None
 */
void SSI0_Output_Data(uint16_t data);

/**
 * @brief
 *
 * @param uint16_t data
 *
 * @param uint8_t channel_select
 *
 * @param uint8_t gain_select
 *
 * @return None
 */
void MCP4822_Write(uint16_t data, uint8_t channel_select, uint8_t gain_select);
