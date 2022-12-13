/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/* This function is called by the startup assembly code to perform system specific initialization tasks. */
/*
void SystemInit(void)
{
    __disable_irq()                                          ;    /* disable all IRQs */
    
    /* Grant coprocessor access */
    /* This is required since TM4C123G has a floating point coprocessor */
  /*  CPAC_SCB_R                         |= 0x00F00000         ;
}*/



/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void PWM_M1_G3_CH6_init         (void)
{
	/*There must be a delay of 3 system clocks after the PWM module clock is enabled before
     any PWM module registers are accessed.*/
	/*8MHz ----divide 16MHz system clck by 2
	  PWM0 Module Clock Period = 1/8Mhz = 0.125탎
    M0PWM4 Timer Period = 1/10KHz = 100탎
    PWM4LOAD Register value = 100탎 / 0.125탎 = 800
	  To generate, 10KHz PWM signal with M0PWM4, we must load 800 to the PWM4LOAD register.*/
	/* Clock setting for PWM and GPIO PORT */
	RCGCPWM_R                              |= 2                         ; /* Enable clock to PWM1 module */
	SYSCTL_RCGCGPIO_R                      |= 0x20                      ; /* Enable system clock to PORTF */
	RCC_R                                  &= ~0x00100000               ; /* Directly feed clock to PWM1 module without pre-divider */

	/* Setting of PF2 pin for M1PWM6 channel output pin */
	GPIOAFSEL_PORTF_R                      |= (1<<2)                    ; /* PF2 sets a alternate function */
	GPIOPCTL_PORTF_R                       &= ~0x00000F00               ; /*set PF2 as output pin */
	GPIOPCTL_PORTF_R                       |= 0x00000500                ; /* make PF2 PWM output pin */
	GPIO_PORTF_DEN_R                       |= (1<<2)                    ; /* set PF2 as a digital pin */

	/* PWM1 channel 6 setting */
	PWM3CTL__G3_M1_R                       &= ~(1<<0)                   ; /* Disable Generator 3 counter */
	PWM3CTL__G3_M1_R                       &= ~(1<<1)                   ; /* select down count mode of counter 3*/
	PWM3GENA__G3_M1_R                       = 0x0000008C                ; /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
	PWM3LOAD__G3_M1_R                       = 16000                     ; /* set load value for 1kHz (16MHz/16000) */
	PWM3CMPA__G3_M1_R                       = 15000-1                    ; /* set duty cyle to 50% by loading of 16000 to PWM1CMPA */
	PWM3CTL__G3_M1_R                        = 1                         ; /* Enable Generator 3 counter */
	PWMENABLE_M1_R                          = 0x40                      ; /* Enable PWM1 channel 6 output */
    
    while(1)
    {
			//do nothing 
    }

	
}


/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Delay_ms      (int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms ,   for execute 5 cycles*/
}

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Timer3ACaptureCount_init         (void)
{
	RCGCTIMER_R                           |= (1<<3)                     ;  /* enable clock to Timer Block 3  */
	SYSCTL_RCGCGPIO_R                     |= (1<<1)                     ;  /* enable clock to PORTB  */
	
	
	GPIO_PORTB_DIR_R                      &= ~(1<<2)                    ;   /* set PB2 an input pin */
	GPIO_PORTB_DEN_R                      |= (1<<2)                     ;   /* enable PB2 as digital pin */
  GPIOAFSEL_PORTB_R                     |= (1<<2)                     ;   /* use PB2 alternate function not DIGITAL GPIO */
  GPIOPCTL_PORTB_R                      &= ~0x00000F00                ;   /* configure PB2 for T3CCP0 ,capture pin for timer0 we get this from table functions and the value for it ,Signals by Pin Number Table*/
  GPIOPCTL_PORTB_R                      |= 0x00000700                 ;   /*the value is 7 from the table  GPIO Pins and Alternate Functions to enable T3CCP0*/


	GPTMCTL_Timer_3_R                     &= ~(1<<0)                    ;   /* disable TIMER3A during setup */
	GPTMCFG_Timer_3_R                     |= (1<<2)                     ;   /* configure as 16-bit timer mode */
	GPTMTAMR_TimerA_3_R                   = 0x13                        ;   /* up-counter, edge count, capture mode */
	GPTMTAMATCHR_TimerA_3_R               = 0xFFFF                      ;   /* set the count limit */
	GPTMTAPMR_TimerA_3_R                  = 0xFF                        ;	  /* set prescaler to 0xFF */
	GPTMCTL_Timer_3_R                    |= ~(1<<3)|~(1<<2)             ;   /* capture the rising edge */
	GPTMCTL_Timer_3_R                    |= (1<<0)                      ;   /* enable Timer3A */
	
}





/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

int Timer3A_countCapture(void)
{
    return GPTMTAR_TimerA_3_R                                        ;
}



/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

/* Create one second delay using Timer block 1 and sub timer A */

void timer1A_delaySec(int ttime)
{
	 int i                                                              ;
    RCGCTIMER_R                         |= 2                          ;         /* enable clock to Timer Block 1 */
    
    GPTMCTL_Timer_1_R                    = 0                          ;         /* disable Timer before initialization */
    GPTMCFG_Timer_1_R                    = 0x04                       ;         /* 16-bit option */ 
    GPTMTAMR_TimerA_1_R                  = 0x02                       ;         /* periodic mode and down-counter */
    GPTMTAILR_TimreA_1_R                 = 64000 - 1                  ;         /* TimerA interval load value reg */ 
    GPTMTAPR_TimerA_1_R                  = 250 - 1                    ;         /* TimerA Prescaler 16MHz/250=64000Hz */
    GPTMICR_Timer_1_R                    = 0x1                        ;         /* clear the TimerA timeout flag */
    GPTMCTL_Timer_1_R                   |= 0x01                       ;         /* enable Timer A after initialization */

    for(i = 0; i < ttime; i++)
    {
        while ((GPTMRIS_Timer_1_R & 0x1) == 0)                        ;         /* wait for TimerA timeout flag */
        GPTMICR_Timer_1_R                = 0x1                        ;         /* clear the TimerA timeout flag */
    }
}





/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Timer0ACapture_init         (void)
{
	RCGCTIMER_R                           |= 1                          ;  /* enable clock to Timer Block 0 */
	SYSCTL_RCGCGPIO_R                     |= 2                          ;  /* enable clock to PORTB PB6 to capture external signal*/
	
	
	GPIO_PORTB_DIR_R                      &= ~(1<<6)                    ;  /* make PB6 an input pin */
  GPIO_PORTB_DEN_R                      |= (1<<6)                     ;  /* enable PB6 as digital pin */
  GPIOAFSEL_PORTB_R                     |= (1<<6)                     ;  /* use PB6 alternate function not DIGITAL GPIO */
  GPIOPCTL_PORTB_R                      &= ~0x0F000000                ;  /* configure PB6 for T0CCP0 ,capture pin for timer0 we get this from table functions and the value for it ,Signals by Pin Number Table*/
  GPIOPCTL_PORTB_R                      |= 0x07000000                 ;  /*the value is 7 from the table GPIO Pins and Alternate Functions to enable T0CCP0*/
	
	

	GPTMCTL_Timer_0_R                     &= ~(1<<0)                    ;  /* disable timer0A during setup */
	GPTMCFG_Timer_0_R                      = 4                          ;  /* Timer0A in 16-bit timer mode */
	GPTMTAMR_TimerA_0_R                    = 0x17                       ;  /* Timer0A enable up-count, capture mod, input edge time mode*/
	GPTMCTL_Timer_0_R                     &= ~(1<<3)|~(1<<2)            ;  /* capture rising edges on PB6 pin */
	GPTMCTL_Timer_0_R                     |= (1<<0)                     ;  /* enable Timer0A */
}






/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
int Timer0ACapture_SignalPeriod(void)
{
	unsigned int risingEdge1, risingEdge2                                             ;
  GPTMICR_Timer_0_R                                    = 4                          ;    /* clear timer0A capture flag */
  while((GPTMRIS_Timer_0_R & (1<<2)) == 0)                                          ;    /* wait till captured */
	risingEdge1                                          = GPTMTAR_TimerA_0_R;             /* save the timestamp */
	GPTMICR_Timer_0_R                                    = 4                          ;    /* clear timer0A capture flag */
					/* detect falling edge */
	while((GPTMRIS_Timer_0_R & (1<<2)) == 0)                                          ;    /* wait till captured */
	risingEdge2                                          = GPTMTAR_TimerA_0_R         ;    /* save the timestamp */
	return (risingEdge2 - risingEdge1) & 0x00FFFFFF                                   ;    /* return the time difference */

}




/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
int Timer0ACapture_PulseWidth(void)
{
	unsigned int risingEdge, fallingEdge                                             ;
	while(1)
	{
    GPTMICR_Timer_0_R                                 = 4                          ;    /* clear timer0A capture flag */
    while((GPTMRIS_Timer_0_R & (1<<2)) == 0)                                       ;    /* wait till captured */
	  if(GPIO_PORTB_PIN6_DATA_R & (1<<6))                                                 /*check if rising edge occurs */
		{
			risingEdge                                      = GPTMTAR_TimerA_0_R;             /* save the timestamp */
			GPTMICR_Timer_0_R                               = 4                          ;    /* clear timer0A capture flag */
					/* detect falling edge */
			while((GPTMRIS_Timer_0_R & (1<<2)) == 0)                                     ;    /* wait till captured */
			fallingEdge                                     = GPTMTAR_TimerA_0_R         ;    /* save the timestamp */
			return (fallingEdge - risingEdge) & 0x00FFFFFF                               ;    /* return the time difference */
		}
	}
}



/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTickTimerInterrupt_Init         (void)
{
	        /*initiate PF3*/
	SYSCTL_RCGCGPIO_R                         |= 0x20                  ;     /* turn on bus clock for GPIOF*/
	GPIO_PORTF_DIR_R                          |= (1<<3)                ;     /* Set PF3 as digital output to control green LED */
	GPIO_PORTF_DEN_R                          |= (1<<3)                ;     /*enable digital function to pf3*/
	
	
	        /*initiate SysTick Timer*/
	SysTick_STRELOAD_R                        = 15999999               ;     /* one second delay relaod value*/
	SysTick_STCTRL_R                          = 7                      ;     /*enable counter, interrupt and select system bus clock*/
	SysTick_STCURRENT_R                       =0                       ;     /*initialize current value register */
	
}



/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_Handler         (void)
{
	GPIO_PORTF_PIN3_DATA_R  ^= (1<<3)                  ;          /* toggle green LED*/
}


/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPTimerInterrupt_Init         (void)
{
	     /*Init pf3*/
	SYSCTL_RCGCGPIO_R                   |= 0x20                        ;  /* turn on bus clock for GPIOF*/
	GPIO_PORTF_DIR_R                    |= (1<<3)                      ;  /* Set PF3 as digital output to control green LED */
	GPIO_PORTF_DEN_R                    |= (1<<3)                      ;  /*enable digital function to pf3*/
	
	     /*init the timer 1 in timer A*/
	RCGCTIMER_R                         |= (1<<1)                      ;  /*enable clock Timer1 subtimer A in run mode */
	GPTMCTL_Timer_1_R                    = 0                           ;  /* disable timer1 output during configuration */
	GPTMCFG_Timer_1_R                    = 0x4                         ;  /*select 16-bit configuration option */
	GPTMTAMR_TimerA_1_R                  = 0x02                        ;  /*select periodic down counter mode of timer1 */
	GPTMTAPR_TimerA_1_R                  = 250-1                       ;  /* TimerA prescaler value to divide 16MHz over 250 */
	GPTMTAILR_TimreA_1_R                 = 64000 - 1                   ;  /* TimerA counter starting count down value 64000 equal 1Second after prescaling */
	GPTMICR_Timer_1_R                    = 0x1                         ;  /* TimerA timeout flag bit clears*/
	GPTMCTL_Timer_1_R                   |= (1<<0)                      ;  /* Enable TimerA module */
	GPTMIMR_Timer_1_R                   |= (1<<0)                      ;  /*enables TimerA time-out  interrupt mask */
	NVIC_EN0_R                          |= (1<<21)                     ;  /*enable IRQ21 */
	
	
	
	
	
}


/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void TIMER1A_Handler         (void)
{
	if(GPTMMIS_Timer_1_R & 0x1)
       GPIO_PORTF_PIN3_DATA_R  ^= (1<<3)                  ;          /* toggle green LED*/
       GPTMICR_Timer_1_R        = 0x1                     ;          /* Timer1A timeout flag bit clears*/

}



/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Interrupt_Init         (void)
{
	     /*initiate PF0,PF4 as input pull up resistor and PF3 as output*/
	SYSCTL_RCGCGPIO_R                 |= (1<<5)                        ;   /* Set bit5 of RCGCGPIO to enable clock to PORTF*/
	     /*port PF0 has a special function so it needs to be unlocked to be modified */
	GPIO_PORTF_LOCK_R                  = 0x4C4F434B                    ;   /* unlock commit register */
	GPIO_PORTF_CR_R                    = 0x01                          ;   /* make PORTF0 configurable */
	GPIO_PORTF_LOCK_R                  = 0                             ;   /* lock commit register */
	GPIO_PORTF_DIR_R                  &= ~(1<<4)|~(1<<0)               ;   /* Set PF4 and PF0 as a digital input pins */
	GPIO_PORTF_DIR_R                  |= (1<<3)                        ;   /* Set PF3 as digital output to control green LED */
	GPIO_PORTF_DEN_R                  |= (1<<4)|(1<<3)|(1<<0)          ;   /* make PORTF4-0 digital pins */
	GPIO_PORTF_PUR_R                  |= (1<<4)|(1<<0)                 ;   /* enable pull up for PORTF4, 0 */
	
	     /* configure PORTF4, 0 for falling edge trigger interrupt */
	GPIOIS_PORTF_R                    &= ~(1<<4)|~(1<<0)               ;    /* make bit PF4, PF0 edge sensitive */
	GPIOIBE_PORTF_R                   &= ~(1<<4)|~(1<<0)               ;    /* trigger is controlled by IEV not both edges */
	GPIOIEV_PORTF_R                   &= ~(1<<4)|~(1<<0)               ;    /*PF0, PF4 falling edge trigger */
	GPIOICR_PORTF_R                   |= (1<<4)|(1<<0)                 ;    /* clear any prior interrupt it clears GPIOMIS_PORTF_R,GPIORIS_PORTF_R*/
	/*GPIORIS_PORTF_R                                                          ?????*/
	/*GPIOMIS_PORTF_R                                                          indicates that the interrupt has been triggered*/
	GPIOIM_PORTF_R                    |= (1<<4)|(1<<0)                 ;    /*use PF0 and PF4 pins of  PORTF to get SW1 and SW2 status on interrupt*/
	
	NVIC_PRI7_R                        = 3 << 21                       ;    /* set interrupt IRQ30 priority to 3 */
	NVIC_EN0_R                        |= (1<<30)                       ;    /*Enable PORTF Interrupt IRQ30 */
	
/*GPIOIBE_PORTF_R                   |= (1<<4)|(1<<0)                 ;      enable both edge triggering */ 
	
	

}

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPIOInterruptProcess         (void)
{
	while(1)
	{
	}

}

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : INTERRUPT FUNCTION 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPIOF_Handler         (void)
{
	 if (GPIOMIS_PORTF_R & 0x10)                                  /* check if interrupt causes by PF4/SW1*/
    {   
      GPIO_PORTF_PIN3_DATA_R           |= (1<<3)             ;
      GPIOICR_PORTF_R                  |= 0x10               ;  /* clear the interrupt flag */
    } 
   else if (GPIOMIS_PORTF_R & 0x01)                             /* check if interrupt causes by PF0/SW2 */
    {   
      GPIO_PORTF_PIN3_DATA_R           &= ~0x08              ;
      GPIOICR_PORTF_R                  |= 0x01               ;  /* clear the interrupt flag */
    }
	
}




/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void ADC_Init         (void)
{
	

	SYSCTL_RCGCGPIO_R                  |= (1UL<<4)                      ;    /*enable clock to port E*/
	RCGCADC_R                          |= (1UL<<0)                      ;    /*enable clock to ADC0*/
	GPIOAFSEL_PORTE_R                  |= (1UL<<3)                      ;    /*to enable alternate function from GPIO to PE3*/
	GPIO_PORTE_DEN_R                   &= ~(1UL<<3)                     ;    /*disable the digital functionality pf PE3*/
	GPIOAMSEL_PORTE_R                  |= (1UL<<3)                      ;    /*enable analog module AN0 of PE3*/
	ADCACTSS_ADC0_R                    &= ~(1UL<<3)                     ;    /*disable sample sequencer 3 during configuration*/
	ADCEMUX_ADC0_R                     &= ~(0xF000)                     ;    /*enable triggring the sampling through software*/
	ADCSSMUX3_ADC0_R                    = 0                             ;    /*get input from channel 0  */
	ADCSSCTL3_ADC0_R                   |= (1<<1)|(1<<2)                 ;    /*enable interrupt flag to be sit after conversion and end of sequence ???*/
	ADCACTSS_ADC0_R                    |= (1<<3)                        ;    /*enable sample sequencer 3 after configuration*/
	ADCPC_ADC0_R                        = 0x3                           ;    /*sit rate 250ksps*/
	ADCPSSI_ADC0_R                     |= (1UL<<3)                      ;    /*trigger sequencer to start by software*/
	
	/********************Iniitialize PF3 as a digital output pin */
	
	SYSCTL_RCGCGPIO_R                  |= 0x20                      ;    /*enable clock to port F*/
	GPIO_PORTF_DIR_R                   |= 0x08                      ;    /*set GREEN pin as a digital output pin*/
	GPIO_PORTF_DEN_R                   |= 0x08                      ;    /* Enable PF3 pin as a digital pin*/
	
}

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void ADC_Process         (void)
{
	unsigned int adc_value                           ;
	while(1)
	{
		ADCPSSI_ADC0_R      |= (1<<3)                  ;       /* Enable SS3 conversion or start sampling data from AN0 */ 
    while((ADCRIS_ADC0_R & 8) == 0)                ;       /* Wait untill sample conversion completed*/	
		adc_value            = ADCSSFIFO3_ADC0_R       ;       /* read adc coversion result from SS3 FIFO*/
		ADCDCISC_ADC0_R      = 8                       ;       /* clear coversion clear flag bit*/
		
		
		if(adc_value >= 2048)
			GPIO_PORTF_PIN3_DATA_R  = 0x00               ;        /* turn on green LED*/
	else if(adc_value < 2048)
	    GPIO_PORTF_PIN3_DATA_R  = 0x08               ;        /* turn off green LED*/
	}
	
}
/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCtrl_Init(void)
{
	volatile unsigned long ulLoop                      ;
	/*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
	SYSCTL_RCGCGPIO_R             |= 0x20              ;  /******** Enable clock for PORTF*/
	ulLoop                         = SYSCTL_RCGCGPIO_R ;  /*to halt for 3 time cycles which is amust in tiva */
	GPIO_PORTF_DIR_R               = 0x0E              ;  /* Configure ORTF Pin1, 2 and 3 digital output pins and pin 4,0 as input*/
	GPIO_PORTF_LOCK_R              = 0x4C4F434B        ;  /*unlockGPIOCR register*/
	GPIO_PORTF_CR_R                = 0x01              ;  /*Enable GPIOPUR register enable to commit*/
	GPIO_PORTF_PUR_R               = 0x11              ;  /*Enable Pull Up resistor PF4,PF0*/
	GPIO_PORTF_DEN_R               = 0x1F              ;  /**** Enable PORTF Pin1, 2 and 3 and 4 as a digital pins*/

    
    /*TODO : Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  


	/*TODO : Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers */


	

}


 
/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Blink_leds(void)
{
	/*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
	while (1) 
	{  


		if ((~(GPIO_PORTF_PIN4_DATA_R) & 0x10))      /* Monitored if the SW0 or SW4 has been pressed. */
		{
      GPIO_PORTF_PIN1_DATA_R   |= 0x02               ;
			GPIO_PORTF_PIN2_DATA_R   &= (~(0x04))          ;
		}
		if ((~(GPIO_PORTF_PIN0_DATA_R) & 0x01))
		{
			GPIO_PORTF_PIN1_DATA_R   &= ~(0x02)            ;
			GPIO_PORTF_PIN2_DATA_R   |= 0x04               ;
		}

	}
    
    /*TODO : Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  


	/*TODO : Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers */

}

/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DELAY(unsigned long x)
{

	/*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
	unsigned long j=0;
	for (j=0; j<x ; j++);
 
    /*TODO : Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  

	/*TODO : Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers */

}

/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
