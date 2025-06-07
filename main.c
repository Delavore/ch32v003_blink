#include "debug.h"


#define LED_PIN (4)
#define LED_SHIFT    (LED_PIN * 4)
#define LED_MASK     (0b1111 << LED_SHIFT)
#define LED_CONFIG   (0b0011 << LED_SHIFT)

void USARTx_CFG2(void)
{
    // PD5 - TX PD6 - RX
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;
   RCC->APB2PCENR |= RCC_APB2Periph_USART1;
    // RCC->APB2PCENR |= RCC_APB2Periph_AFIO;  // alternative function

    // TX 
    // Output mode, speed 30mhz
    GPIOD->CFGLR &= ~GPIO_CFGLR_MODE5;  
    GPIOD->CFGLR |= GPIO_CFGLR_MODE5_0 | GPIO_CFGLR_MODE5_1; 

    // multeplexed PP, full duplex
    GPIOD->CFGLR &= ~GPIO_CFGLR_CNF5;
    GPIOD->CFGLR |= GPIO_CFGLR_CNF5_1;


    // RX 
    GPIOD->CFGLR &= ~GPIO_CFGLR_MODE6;  // input mode\

    // floating input, full duplex
    GPIOD->CFGLR &= ~GPIO_CFGLR_CNF6;
    GPIOD->CFGLR |= GPIO_CFGLR_CNF6_0;  

    USART1->BRR = 
 


   


    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

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
