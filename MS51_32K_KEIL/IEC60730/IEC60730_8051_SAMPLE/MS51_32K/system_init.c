#include "NuMicro.h"
#include "IEC60730_CONTROL_PARAM.h"

/*-------------------------------------------*/
/*  init WKT                                 */
/*-------------------------------------------*/
void InitTimer1_WKT(void)
{
    WKCON = 0x02;                     //timer base 10k, Pre-scale = 1/16
    SFRS = 2;
    RWKH = 0xFC;
    SFRS = 0;
    RWKL = 0X00;                      //  if prescale is 0x00, never set RWK = 0xff
    ENABLE_WKT_INTERRUPT;                          // enable WKT interrupt

    set_WKCON_WKTR;                         // Wake-up timer run 
}
/*-------------------------------------------*/
/*                init timer0                */
/*-------------------------------------------*/
static void InitTimer0(void)
{
    ENABLE_TIMER0_MODE1;
    TIMER0_FSYS_DIV12;;

    TL0 = LOBYTE(65535 - ((24000000 / 1000000) * 10000 / 12)); //10ms
    TH0 = HIBYTE(65535 - ((24000000 / 1000000) * 10000 / 12));
    
    ENABLE_TIMER0_INTERRUPT;                       //enable Timer0 interrupt

    set_TCON_TR0;                                  //Timer0 run
}

/*-------------------------------------------*/
/*                timer0 isr                 */
/*-------------------------------------------*/
#if defined __ICC8051__   //iar use timer 0 interrupt define
#pragma vector=0x0B
    __interrupt void Timer0_ISR(void)
    {
#endif
			
#if defined __C51__             //keil use timer 0 interrupt define
 void Timer0_ISR(void) interrupt 1            /*interrupt address is 0x000B */        
 {
#endif

    _push_(SFRS);
  
    TL0 = LOBYTE(65535 - ((24000000 / 1000000) * 10000 / 12)); //10ms
    TH0 = HIBYTE(65535 - ((24000000 / 1000000) * 10000 / 12));  
    TF0 = 0;  //clear timer 0 interrupt flag
    CLASSB_HSCLOCK_INT();

    _pop_(SFRS);
}

#if defined __ICC8051__
#pragma vector=0x8B
__interrupt void WakeUp_Timer_ISR(void)
{
#endif
#if defined __C51__
void WakeUp_Timer_ISR(void)   interrupt 17      //ISR for self wake-up timer
{
#endif

			    _push_(SFRS);
         clr_WKCON_WKTR;
         clr_WKCON_WKTF;              //clear interrupt flag	    
         set_WKCON_WKTR;
         CLASSB_LSCLOCK_INT();         
				_pop_(SFRS);
}

uint8_t system_init(void)
{

    /* Init System, peripheral clock and multi-function I/O */
    /* Init UART0 for printf */
  #if defined __ICC8051__
    MODIFY_HIRC_24();
#endif
    #if defined __C51__
        MODIFY_HIRC(HIRC_24);
#endif    
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;                              // Important! use prinft function must set TI=1;
	  InitTimer0();
	  InitTimer1_WKT();
	    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    return 0;
}

uint16_t READ_bandgap(void)
{
		    uint16_t res; 
	uint8_t i;
/*Enable Bandgap */     
      ENABLE_ADC_BANDGAP;
		  /* IMPORTANT !!! multi channel convert must delay for ADC maocro ready */ 
      for (i=0;i<10;i++)
      _delay_();
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      AUXR1|=SET_BIT4;          /* ADC clock low speed */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(!(ADCCON0&SET_BIT7)); 
      res = (ADCRH<<4)|(ADCRL&0x0F);

      DISABLE_ADC;
	return res;
}

uint16_t READ_ADC_CH(void)
{
	    uint16_t res; 
	uint8_t i;
/*Enable channel 0 */ 
       ENABLE_ADC_CH0;
	  /* IMPORTANT !!! multi channel convert must delay for ADC maocro ready */ 
      for (i=0;i<10;i++)
      _delay_();
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      AUXR1|=SET_BIT4;          /* ADC clock low speed */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(!(ADCCON0&SET_BIT7)); 
      res = (ADCRH<<4)|(ADCRL&0x0F);

      DISABLE_ADC;
return res;
}