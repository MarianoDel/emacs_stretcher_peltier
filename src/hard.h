//----------------------------------------------
// #### DEXEL 2CH PROJECT - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### HARD.H #################################
//----------------------------------------------
#ifndef _HARD_H_
#define _HARD_H_

#include "stm32f0xx.h"


//-- Defines For Configuration -------------------
//---- Configuration for Hardware Versions -------
// #define HARDWARE_VERSION_1_1    //fuente 48V->12V en placa control
#define HARDWARE_VERSION_1_0    //micro F030K6T6


// #define SOFTWARE_VERSION_1_1
#define SOFTWARE_VERSION_1_0


//---- Features Configuration -----------------
// #define USE_TEMP_PROT
// #define USE_CTROL_FAN_ALWAYS_ON

// -- Freq for the timers
// #define USE_PWM_16000_FREQ_1KHZ
#define USE_PWM_4000_FREQ_4KHZ
// #define USE_PWM_8000_FREQ_2KHZ
// #define USE_


//---- End of Features Configuration ----------


// Exported Pinout Names -------------------------------------------------------
//GPIOA pin0    NC

//GPIOA pin1    Analog Temp NTC 10K

//GPIOA pin2    NC

//GPIOA pin3    
#define CTRL_FAN1    ((GPIOA->ODR & 0x0008) != 0)
#define CTRL_FAN1_ON    (GPIOA->BSRR = 0x00000008)
#define CTRL_FAN1_OFF    (GPIOA->BSRR = 0x00080000)

//GPIOA pin4    NC

//GPIOA pin5    
#define CTRL_FAN2    ((GPIOA->ODR & 0x0020) != 0)
#define CTRL_FAN2_ON    (GPIOA->BSRR = 0x00000020)
#define CTRL_FAN2_OFF    (GPIOA->BSRR = 0x00200000)

//GPIOA pin6    NC

//GPIOA pin7    Analog pwm input

//GPIOB pin0    
//GPIOB pin1    NC

//GPIOA pin8    
//GPIOA pin9    
//GPIOA pin10
//GPIOA pin11    NC

//GPIOA pin12
#define LED    ((GPIOA->ODR & 0x1000) != 0)
#define LED_ON    (GPIOA->BSRR = 0x00001000)
#define LED_OFF    (GPIOA->BSRR = 0x10000000)

//GPIOA pin13
//GPIOA pin14    
//GPIOA pin15    NC

//GPIOB pin3    NC

//GPIOB pin4    TIM3_CH1

//GPIOB pin5    
//GPIOB pin6    
//GPIOB pin7    NC

// Exported Types & Macros -----------------------------------------------------


// Module Exported Functions ---------------------------------------------------


#endif    /* _HARD_H_ */

//--- end of file ---//

