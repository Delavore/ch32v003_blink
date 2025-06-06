#include "debug.h"


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

#define RCC_SW_POS (0)

void ClockStart() {
    RCC->CTLR |= RCC_HSION;

    // Wait HSI to start
    while (!(RCC->CTLR & (RCC_HSIRDY))) ;

    // Before HSI is ON
    // RCC->CFGR0 &= ~RCC_PLLSRC;  // Transfer HSI to PLL

    RCC->CTLR |= RCC_PLLON;

    // Wait PLL to start
    while (!(RCC->CTLR & (RCC_PLLRDY))) ;

    // Switch to HSI
    RCC->CFGR0 &= ~(RCC_SW);
    RCC->CFGR0 |= (RCC_SW_1);  // 0b10 = PLL
}

int main(void)
{
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    // SystemCoreClockUpdate();
    ClockStart(); 
    // Delay_Init();

    GPIOConfig();
    //GPIO_SetBits(GPIOC, GPIO_Pin_4);
    GPIOC->BSHR |= 1 << LED_PIN;  // gpioc->bshr = 1 << Led_pin
    while(1)
    {


    }
}
