//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F030
// ##
// #### TIM.H #################################
//---------------------------------------------
#ifndef _TIM_H_
#define _TIM_H_

#include "hard.h"    //for freq conf


// Exported Types Constants and Macros -----------------------------------------
#define EnablePreload_TIM3_CH1    (TIM3->CCMR1 |= TIM_CCMR1_OC1PE)
#define EnablePreload_TIM3_CH2    (TIM3->CCMR1 |= TIM_CCMR1_OC2PE)

#define DisablePreload_TIM3_CH1    (TIM3->CCMR1 &= ~TIM_CCMR1_OC1PE)
#define DisablePreload_TIM3_CH2    (TIM3->CCMR1 &= ~TIM_CCMR1_OC2PE)

#define EnablePreload_TIM1_CH2    (TIM1->CCMR1 |= TIM_CCMR1_OC2PE)
#define EnablePreload_TIM1_CH4    (TIM1->CCMR1 |= TIM_CCMR2_OC4PE)

#define DisablePreload_TIM1_CH2    (TIM1->CCMR1 &= ~TIM_CCMR1_OC2PE)
#define DisablePreload_TIM1_CH4    (TIM1->CCMR1 &= ~TIM_CCMR2_OC4PE)



// Module Exported Functions -----------------------------------------
// void TIM_1_Init_pwm_neg_CH1_trig_CH2 (void);

void TIM_3_Init (void);
void TIM3_IRQHandler (void);

void TIM_6_Init (void);

void TIM_14_Init(void);
void TIM14_IRQHandler (void);

void TIM_16_Init(void);
void TIM16_IRQHandler (void);

void TIM_17_Init(void);
void TIM17_IRQHandler (void);
void TIM17Enable (void);
void TIM17Disable (void);
void TIM_17_Init_Pwm_Int (void);

void Update_TIM1_CH1 (unsigned short);
void Update_TIM1_CH2 (unsigned short);
void Update_TIM1_CH4 (unsigned short);
void Update_TIM3_CH1 (unsigned short);
void Update_TIM3_CH2 (unsigned short);
void Update_TIM3_CH3 (unsigned short);
void Update_TIM3_CH4 (unsigned short);
void Update_TIM14_CH1 (unsigned short); 
void Update_TIM16_CH1N (unsigned short);

void Wait_ms (unsigned short wait);

#endif    /* _TIM_H_ */

//--- end of file ---//
