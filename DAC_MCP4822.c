/**
 * @file DAC_MCP4822.c
 *
 * @brief Source file for the MCP4822 (DAC) driver.
 *
 * This file contains the function definitions for the MCP4822 (DAC) driver.
 *
 * @note Assumes that the system clock (50 MHz) is used.
 *
 * @author
 */

#include "DAC_MCP4822.h"

#define SSI0_BUSY_BIT_MASK (0x10)
#define SSI0_RX_FIFO_NOT_EMPTY_BIT_MASK (0x04)
#define SSI0_TX_FIFO_EMPTY_BIT_MASK (0x01)

#define DAC_SELECT_BIT_POSITION				(15)
#define DAC_GAIN_BIT_POSITION					(13)
#define DAC_OUTPUT_SHUTDOWN_BIT_POSITION	(12)
#define DAC_INPUT_DATA_BIT_MASK					(0x0FFF)

void MCP4822_Init(void)
{
SYSCTL -> RCGCSSI |= 0x01;
	
	SYSCTL-> RCGCGPIO |= 0x01;
	
	GPIOA -> AFSEL |= 0x3C;
	
	GPIOA -> PCTL &= ~0x00FFFF00;
	
	GPIOA -> PCTL |= 0x00222200;
	
	GPIOA-> DEN |= 0x3C;
	
	SSI0 -> CR1 &= ~ 0x02;
	
	SSI0 -> CR1 &= ~0x01;
	
	SSI0 -> CR1 &= ~0x04;
	
	SSI0 -> CC &= ~ 0xF;
	
	SSI0 -> CPSR =10;
	
	SSI0 -> CR0 &= ~0xFF00;
	
	SSI0 -> CR0 &= ~0x0080;
	
	SSI0 -> CR0 &= ~0x0040;
	
	SSI0 -> CR0 &= ~0x0030;
	
	SSI0 -> CR0 |= 0x000F;
	
	SSI0 -> CR1 |= 0x02;
	
	
	
}

void SSI0_Output_Data(uint16_t data)
{
	while((SSI0-> SR & SSI0_TX_FIFO_EMPTY_BIT_MASK) ==0);
	
	SSI0-> DR = data;
}

void MCP4822_Write(uint16_t data, uint8_t channel_select, uint8_t gain_select)
{
	uint16_t dac_config =0;
	uint16_t dac_data = data & DAC_INPUT_DATA_BIT_MASK;
	uint16_t dac_word =0;
	
	dac_config |= ((channel_select &0x01) << DAC_SELECT_BIT_POSITION);
	dac_config |= ((gain_select & 0x01) << DAC_GAIN_BIT_POSITION);
	dac_config |= (1<< DAC_OUTPUT_SHUTDOWN_BIT_POSITION);
	
	dac_word = (dac_config | dac_data);
	
	SSI0_Output_Data(dac_word);
	
}
