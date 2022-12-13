/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**********************************************************************************************************************

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define SYSCTL_RCGCGPIO_R                                               (*(( volatile unsigned long *)0x400FE608))
# define GPIO_PORTF_DEN_R                                                (*(( volatile unsigned long *)0x4002551C))
# define GPIO_PORTE_DEN_R                                                (*(( volatile unsigned long *)0x4002451C))
# define GPIO_PORTF_DIR_R                                                (*(( volatile unsigned long *)0x40025400))
#	define GPIO_PORTF_PIN0_DATA_R                                          (*(( volatile unsigned long *)(0x40025000+0x04)))
#	define GPIO_PORTF_PIN1_DATA_R                                          (*(( volatile unsigned long *)(0x40025000+0x08)))
#	define GPIO_PORTF_PIN2_DATA_R                                          (*(( volatile unsigned long *)(0x40025000+0x10)))
#	define GPIO_PORTF_PIN3_DATA_R                                          (*(( volatile unsigned long *)(0x40025000+0x20)))
#	define GPIO_PORTF_PIN4_DATA_R                                          (*(( volatile unsigned long *)(0x40025000+0x40)))
#	define GPIO_PORTF_LOCK_R                                               (*(( volatile unsigned long *) 0x40025520))
#	define GPIO_PORTF_CR_R                                                 (*(( volatile unsigned long *) 0x40025524))
#	define GPIO_PORTF_PUR_R                                                (*(( volatile unsigned long *) 0x40025510))
# define RCGCADC_R                                                       (*(( volatile unsigned long *) 0x400FE638))
#	define GPIOAFSEL_PORTE_R                                               (*(( volatile unsigned long *) 0x40024420))
# define GPIOAMSEL_PORTE_R                                               (*(( volatile unsigned long *) 0x40024528))
# define ADCACTSS_ADC0_R                                                 (*(( volatile unsigned long *) 0x40038000)) 
# define ADCEMUX_ADC0_R                                                  (*(( volatile unsigned long *) 0x40038014))
# define ADCSSMUX3_ADC0_R                                                (*(( volatile unsigned long *) 0x400380A0))
# define ADCPC_ADC0_R                                                    (*(( volatile unsigned long *) 0x40038FC4))
# define ADCPSSI_ADC0_R                                                  (*(( volatile unsigned long *) 0x40038028))
# define ADCRIS_ADC0_R                                                   (*(( volatile unsigned long *) 0x40038004))
# define ADCSSFIFO3_ADC0_R	                                             (*(( volatile unsigned long *) 0x400380A8))    
# define ADCSSCTL3_ADC0_R                                                (*(( volatile unsigned long *) 0x400380A4))
# define ADCDCISC_ADC0_R                                                 (*(( volatile unsigned long *) 0x40038034))
# define NVIC_EN0_R                                                      (*(( volatile unsigned long *) 0xE000E100))
# define GPIOIM_PORTF_R                                                  (*(( volatile unsigned long *) 0x40025410))
# define GPIOIS_PORTF_R                                                  (*(( volatile unsigned long *) 0x40025404))
# define GPIOIEV_PORTF_R                                                 (*(( volatile unsigned long *) 0x4002540C))
# define GPIOIBE_PORTF_R                                                 (*(( volatile unsigned long *) 0x40025408))
# define GPIOICR_PORTF_R                                                 (*(( volatile unsigned long *) 0x4002541C))
# define GPIOMIS_PORTF_R                                                 (*(( volatile unsigned long *) 0x40025418))
# define GPIORIS_PORTF_R                                                 (*(( volatile unsigned long *) 0x40025414))
# define NVIC_PRI7_R                                                     (*(( volatile unsigned long *) 0xE000E41C))
# define RCGCTIMER_R                                                     (*(( volatile unsigned long *) 0x400FE604))
# define GPTMCTL_Timer_1_R                                               (*(( volatile unsigned long *) 0x4003100C))
# define GPTMCFG_Timer_1_R                                               (*(( volatile unsigned long *) 0x40031000))
# define GPTMTAMR_TimerA_1_R                                             (*(( volatile unsigned long *) 0x40031004))
# define GPTMTAPR_TimerA_1_R                                             (*(( volatile unsigned long *) 0x40031038))
# define GPTMTAILR_TimreA_1_R                                            (*(( volatile unsigned long *) 0x40031028))
# define GPTMICR_Timer_1_R                                               (*(( volatile unsigned long *) 0x40031024))
# define GPTMIMR_Timer_1_R                                               (*(( volatile unsigned long *) 0x40031018))
# define GPTMMIS_Timer_1_R                                               (*(( volatile unsigned long *) 0x40031020))
# define GPTMRIS_Timer_1_R                                               (*(( volatile unsigned long *) 0x4003101C))
# define SysTick_STCTRL_R                                                (*(( volatile unsigned long *) 0xE000E010))
# define SysTick_STRELOAD_R                                              (*(( volatile unsigned long *) 0xE000E014))
# define SysTick_STCURRENT_R                                             (*(( volatile unsigned long *) 0xE000E018))
# define GPIO_PORTB_DIR_R                                                (*(( volatile unsigned long *) 0x40005400))
# define GPIO_PORTB_DEN_R                                                (*(( volatile unsigned long *) 0x4000551C))
#	define GPIOAFSEL_PORTB_R                                               (*(( volatile unsigned long *) 0x40005420))
# define GPIOPCTL_PORTB_R                                                (*(( volatile unsigned long *) 0x4000552C))
# define GPTMCTL_Timer_0_R                                               (*(( volatile unsigned long *) 0x4003000C))
# define GPTMCFG_Timer_0_R                                               (*(( volatile unsigned long *) 0x40030000))
# define GPTMTAMR_TimerA_0_R                                             (*(( volatile unsigned long *) 0x40030004))
# define GPTMICR_Timer_0_R                                               (*(( volatile unsigned long *) 0x40030024))
# define GPTMRIS_Timer_0_R                                               (*(( volatile unsigned long *) 0x4003001C))
#	define GPIO_PORTB_PIN0_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x04)))
#	define GPIO_PORTB_PIN1_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x08)))
#	define GPIO_PORTB_PIN2_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x10)))
#	define GPIO_PORTB_PIN3_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x20)))
#	define GPIO_PORTB_PIN4_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x40)))
#	define GPIO_PORTB_PIN5_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x80)))
#	define GPIO_PORTB_PIN6_DATA_R                                          (*(( volatile unsigned long *)(0x40005000+0x100)))
# define GPTMTAR_TimerA_0_R                                              (*(( volatile unsigned long *) 0x40030048))
# define CPAC_SCB_R                                                      (*(( volatile unsigned long *) 0xE000ED88))
# define GPTMCTL_Timer_3_R                                               (*(( volatile unsigned long *) 0x4003300C))
# define GPTMCFG_Timer_3_R                                               (*(( volatile unsigned long *) 0x40033000))
# define GPTMTAMR_TimerA_3_R                                             (*(( volatile unsigned long *) 0x40033004))
# define GPTMTAMATCHR_TimerA_3_R                                         (*(( volatile unsigned long *) 0x40033030))
# define GPTMTAPMR_TimerA_3_R                                            (*(( volatile unsigned long *) 0x40033040))
# define GPTMTAR_TimerA_3_R                                              (*(( volatile unsigned long *) 0x40033048))
# define GPTMTAV_TimerA_3_R                                              (*(( volatile unsigned long *) 0x40033050))
# define RCGCPWM_R                                                       (*(( volatile unsigned long *) 0x400FE640))
# define RCC_R                                                           (*(( volatile unsigned long *) 0x400FE060))
# define PWM0CTL__G0_M0_R                                                (*(( volatile unsigned long *) 0x40028040))
# define PWM0LOAD_G0_M0_R                                                (*(( volatile unsigned long *) 0x40028050))
#	define GPIOAFSEL_PORTF_R                                               (*(( volatile unsigned long *) 0x40025420))
# define GPIOPCTL_PORTF_R                                                (*(( volatile unsigned long *) 0x4002552C))
# define PWM3CTL__G3_M1_R                                                (*(( volatile unsigned long *) 0x40029100))
# define PWM3GENA__G3_M1_R                                               (*(( volatile unsigned long *) 0x40029120))
# define PWM3LOAD__G3_M1_R                                               (*(( volatile unsigned long *) 0x40029110))
# define PWM3CMPA__G3_M1_R                                               (*(( volatile unsigned long *) 0x40029118))
# define PWMENABLE_M1_R                                                  (*(( volatile unsigned long *) 0x40029008))




/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
