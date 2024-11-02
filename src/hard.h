//----------------------------------------------
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
#define HARDWARE_VERSION_1_0    //micro F030K6T6

#define SOFTWARE_VERSION_1_0

//---- Features Configuration -----------------


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
//GPIOA pin11
//GPIOA pin12
//GPIOA pin13
//GPIOA pin14    NC

//GPIOA pin15
#define LED    ((GPIOA->ODR & 0x8000) != 0)
#define LED_ON    (GPIOA->BSRR = 0x00008000)
#define LED_OFF    (GPIOA->BSRR = 0x80000000)

//GPIOB pin3    NC

//GPIOB pin4    TIM3_CH1

//GPIOB pin5    
//GPIOB pin6    
//GPIOB pin7    NC

// Exported Types & Macros -----------------------------------------------------
//--- LED states -----------
typedef enum
{    
    START_BLINKING = 0,
    WAIT_TO_OFF,
    WAIT_TO_ON,
    WAIT_NEW_CYCLE
} led_state_t;


// LED BLINKING commands
#define LED_NO_BLINKING    0     
#define LED_TREATMENT_STANDBY    1
#define LED_TREATMENT_GENERATING    2
#define LED_TREATMENT_PAUSED    3
#define LED_TREATMENT_BRIDGE_MODE    5

#define LED_COMMAND_STANDBY    LED_TREATMENT_STANDBY
#define LED_COMMAND_ACTIVE    LED_TREATMENT_GENERATING

// Module Exported Functions ---------------------------------------------------
void ChangeLed (unsigned char);
void UpdateLed (void);


#endif    /* _HARD_H_ */

//--- end of file ---//

