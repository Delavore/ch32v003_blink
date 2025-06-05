#include "debug.h"


/* Global define */


/* Global Variable */
vu8 val;

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */

#define LED_PIN (4)
#define LED_SHIFT    (LED_PIN * 4)
#define LED_MASK     (0b1111 << LED_SHIFT)
#define LED_CONFIG   (0b0011 << LED_SHIFT)

void GPIOConfig(void)
{
   RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;

    GPIOC->CFGLR &= ~(0b1111 << (LED_PIN * 4));
    GPIOC->CFGLR |= (0b0011 << (LED_PIN * 4));
}
#define SW 0
#define HSE_ON 16
#define HSE_READY 17

void ClockStart() {
    RCC->CTLR |= (1 << 18);  // HSEBYP
    // Enable HSE
    RCC->CTLR |= 1 << HSE_ON;

    // Wait HSE to start
    while (!(RCC->CTLR & (1 << HSE_READY))) ;

    // Switch to HSE
    RCC->CFGR0 &= ~(0b11 << SW);
    RCC->CFGR0 |= (0b01 << SW);  // HSE
}


int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    Delay_Init();
   // SystemCoreClockUpdate();
    ClockStart(); 

   
    GPIOConfig();
    // GPIO_SetBits(GPIOC, GPIO_Pin_4);
    GPIOC->BSHR |= 1 << LED_PIN;
    while(1)
    {


    }
}
