//------------------------------------------------
// #### DEXEL 2CH POTE PROJECT - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### MAIN.C ###################################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "hard.h"
#include "stm32f0xx.h"

#include "gpio.h"
#include "tim.h"
#include "adc.h"
#include "dma.h"

#include "test_functions.h"
#include "temperatures.h"
#include "dsp.h"
// #include "pwm.h"

#include <stdio.h>
#include <string.h>


// Module Types Constants and Macros -------------------------------------------
typedef enum {
    MAIN_HARD_INIT,
    MAIN_RUNNING,
    MAIN_IN_OVERTEMP
    
} main_state_e;


// Ntc important points
#define NTC_FOR_30_DEGREES    2000
#define NTC_FOR_35_DEGREES    2500


// Externals -------------------------------------------------------------------
// externals for ADC
volatile unsigned short adc_ch [ADC_CHANNEL_QUANTITY];
// externals for timers
volatile unsigned short wait_ms_var = 0;

// Globals ---------------------------------------------------------------------
//-- Timers globals ----------------------------------
volatile unsigned short timer_standby = 0;
volatile unsigned short timer_check_temp = 0;

//-- for the filters and outputs
ma32_u16_data_obj_t preset_filter;
ma32_u16_data_obj_t ntc_filter;


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);


// Module Functions ------------------------------------------------------------
int main(void)
{
    //GPIO Configuration.
    GPIO_Config();

    //Systick Timer
    if (SysTick_Config(48000))
        SysTickError();

    // Hardware Tests -----------------------------------
    // TF_Hardware_Tests ();
    // End Hardware Tests -------------------------------

    // Hardware Inits. ---------------------------
    // Tim Inits
    TIM_3_Init ();
    Update_TIM3_CH1 (0);

    // Init ADC and DMA
    AdcConfig();
    DMAConfig();
    DMA1_Channel1->CCR |= DMA_CCR_EN;
    ADC1->CR |= ADC_CR_ADSTART;

    unsigned short preset_filtered = 0;
    unsigned short ntc_filtered = 0;
    main_state_e main_state = MAIN_HARD_INIT;

    while (1)
    {
        switch (main_state)
        {
        case MAIN_HARD_INIT:
            MA32_U16Circular_Reset (&preset_filter);
            MA32_U16Circular_Reset (&ntc_filter);    
            main_state++;
            break;

        case MAIN_RUNNING:
            if (timer_standby)
		break;

	    timer_standby = 30;    // 1000/32 steps

	    preset_filtered = MA32_U16Circular (&preset_filter, Pote_Sense);
	    ntc_filtered = MA32_U16Circular (&ntc_filter, Ntc_Sense);

//---- new production
	    if (ntc_filtered > NTC_FOR_35_DEGREES)
	    {
		ChangeLed(LED_COMMAND_ACTIVE);
		CTRL_FAN1_ON;
		CTRL_FAN2_ON;
		Update_TIM3_CH1 (preset_filtered >> 2);		
	    }
	    else if (ntc_filtered < NTC_FOR_30_DEGREES)
	    {
		ChangeLed(LED_COMMAND_STANDBY);
		CTRL_FAN1_OFF;
		CTRL_FAN2_OFF;
		Update_TIM3_CH1 (0);
	    }
//---- end of new production                
            break;

        case MAIN_IN_OVERTEMP:
            break;

        default:
            main_state = MAIN_HARD_INIT;
            break;
        }

	// concurrent things
	UpdateLed ();
	
    }    //end of while 1

    return 0;
}

//--- End of Main ---//


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    if (timer_check_temp)
        timer_check_temp--;
    
}


void SysTickError (void)
{
    // Capture systick error...
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}

//--- end of file ---//

