/*
 * @file main.c
 *
 * @brief Main source code for the DAC program.
 *
 * This file contains the main entry point and function definitions for the DAC program.
 *
 * @author
 */


#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "DAC_MCP4822.h"
#include "math.h"


#define NUM_SAMPLES			(256)
#define DAC_MAX_VALUE		(4095)
#define DAC_AMPLITUDE		(DAC_MAX_VALUE/2)
#define DAC_OFFSET			(DAC_MAX_VALUE/2)

#define DAC_CHANNEL_A			(0)
#define DAC_CHANNEL_B		(1)
#define DAC_2x_GAIN			(0)
#define DAC_1x_GAIN			(1)


void Generate_Sine_Wave(uint16_t sine_wave[]);

void Generate_Cosine_Wave(uint16_t cosine_wave[]);


int main(void)
{
	uint16_t sine_wave[NUM_SAMPLES];
	uint16_t index =0;
	uint16_t sine_wave_data =0;
	
	Generate_Sine_Wave(sine_wave);
	
	
	uint16_t cosine_wave[NUM_SAMPLES];
	
	uint16_t cosine_wave_data =0;
	Generate_Cosine_Wave(cosine_wave);
	
	SysTick_Delay_Init();
	
	MCP4822_Init();

	while(1)
	{
sine_wave_data= sine_wave[index];
		MCP4822_Write(sine_wave_data, DAC_CHANNEL_A, DAC_1x_GAIN);
		index= (index+1) % NUM_SAMPLES;
		SysTick_Delay1us(1);
		
	cosine_wave_data = cosine_wave[index];
		MCP4822_Write(cosine_wave_data, DAC_CHANNEL_B, DAC_1x_GAIN);
			index= (index+1) % NUM_SAMPLES;
		SysTick_Delay1us(1);
		
		
	}
}

void Generate_Sine_Wave(uint16_t sine_wave[])
{
	for (int i=0; i<NUM_SAMPLES; i++)
	{
		
	sine_wave[i] = (int16_t) (DAC_AMPLITUDE *sin(2*3.14159 * ((double)(i) / (double)NUM_SAMPLES)));
		
		
		sine_wave[i] = sine_wave[i] + DAC_OFFSET;
	}
}


void Generate_Cosine_Wave(uint16_t cosine_wave[])
{
	for (int i =0; i<NUM_SAMPLES; i++)
	{
		cosine_wave[i] = (int16_t)(DAC_AMPLITUDE * cos(2 * 3.14159 * ((double)i / NUM_SAMPLES)));
		cosine_wave[i] = cosine_wave[i] + DAC_OFFSET;
	}
}