//------------------------------------------------
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C #########################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "hard.h"
#include "tim.h"
#include "adc.h"
#include "dma.h"

#include <stdio.h>


// Externals -------------------------------------------------------------------
extern volatile unsigned short adc_ch [];


// Globals ---------------------------------------------------------------------


// Module Private Types & Macros -----------------------------------------------


// Module Private Functions ----------------------------------------------------
void TF_Led (void);
void TF_Control_Fan1 (void);
void TF_Control_Fan2 (void);
void TF_TIM3_Pwm_CH1 (void);
void TF_Adc_With_DMA_Pote_TIM3_Pwm_CH1 (void);
void TF_Adc_With_DMA_Ntc_TIM3_Pwm_CH1 (void);
    

// Module Functions ------------------------------------------------------------
void TF_Hardware_Tests (void)
{
    // TF_Led ();

    // TF_Control_Fan1 ();

    // TF_Control_Fan2 ();

    // TF_TIM3_Pwm_CH1 ();

    // TF_Adc_With_DMA_Pote_TIM3_Pwm_CH1 ();

    TF_Adc_With_DMA_Ntc_TIM3_Pwm_CH1 ();    

}


void TF_Led (void)
{
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        Wait_ms(1000);
    }
}


void TF_Control_Fan1 (void)
{
    while (1)
    {
        if (CTRL_FAN1)
            CTRL_FAN1_OFF;
        else
            CTRL_FAN1_ON;

        Wait_ms(5000);
    }
}


void TF_Control_Fan2 (void)
{
    while (1)
    {
        if (CTRL_FAN2)
            CTRL_FAN2_OFF;
        else
            CTRL_FAN2_ON;

        Wait_ms(5000);
    }
}


void TF_TIM3_Pwm_CH1 (void)
{
    TIM_3_Init ();
    Update_TIM3_CH1 (250);

    while (1);
    
}


void TF_Adc_With_DMA_Pote_TIM3_Pwm_CH1 (void)
{
    TIM_3_Init ();
    
    // Init ADC and DMA
    AdcConfig();
    DMAConfig();
    DMA1_Channel1->CCR |= DMA_CCR_EN;
    ADC1->CR |= ADC_CR_ADSTART;

    while (1)
    {
	if (LED)
	    LED_OFF;
	else
	    LED_ON;

        Wait_ms(5);
        Update_TIM3_CH1 (Pote_Sense >> 2);        
    }
}


void TF_Adc_With_DMA_Ntc_TIM3_Pwm_CH1 (void)
{
    TIM_3_Init ();
    
    // Init ADC and DMA
    AdcConfig();
    DMAConfig();
    DMA1_Channel1->CCR |= DMA_CCR_EN;
    ADC1->CR |= ADC_CR_ADSTART;

    while (1)
    {
	if (LED)
	    LED_OFF;
	else
	    LED_ON;
	
        Wait_ms(5);
        Update_TIM3_CH1 (Ntc_Sense >> 2);
    }
}


//--- end of file ---//
