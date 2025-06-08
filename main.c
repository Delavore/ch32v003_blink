#include "debug.h"


#define LED_PIN (4)
#define LED_SHIFT    (LED_PIN * 4)
#define LED_MASK     (0b1111 << LED_SHIFT)
#define LED_CONFIG   (0b0011 << LED_SHIFT)

__attribute((interrupt("WCH-Interrupt-fast")))
void USART1_IRQHandler(void)
{
    // volatile uint16_t tmp = USART1->DATAR;  // DATAR has length 9: [8:0]

    const char greeting[] = "hello\n\r";
    
        
        int i = 0;
        while (greeting[i]) {
            USART_SendData(USART1, greeting[i]);
            // USART_SendData(USART1, '\n');
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            {   
                // waiting for sending finish 
            }
            i++;
        }
    
    volatile uint16_t tmp = USART1->DATAR;  // DATAR has length 9: [8:0]
    // USART1->STATR &= ~USART_STATR_RXNE;
}

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
    GPIOD->CFGLR &= ~GPIO_CFGLR_MODE6;  // input mode

    // floating input, full duplex
    GPIOD->CFGLR &= ~GPIO_CFGLR_CNF6;
    GPIOD->CFGLR |= GPIO_CFGLR_CNF6_0;  

    // USART1->BRR = (26 << 4) | 1; // 115200 when 48mhz
    USART1->BRR = (13 << 4) | 0; // 115200 when 24mhz

 USART1->CTLR1 |= USART_CTLR1_RXNEIE;  // enable rx interrupt (when we get 1 byte than flag int is rise)

     
    USART1->CTLR1 |= USART_CTLR1_TE | USART_CTLR1_RE;
    // USART1->CTLR1 = USART_CTLR1_M; // 0 - stands for 8bits word length
    USART1->CTLR1 |= USART_CTLR1_UE; 
    // USART1->CTLR2 = USART_CTLR2_STOP; // 00 - stands for 1 stop bit 

     NVIC_EnableIRQ(USART1_IRQn);
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
