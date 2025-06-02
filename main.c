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


int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    GPIOConfig();
    GPIO_SetBits(GPIOC, GPIO_Pin_4);

    while(1)
    {


    }
}
