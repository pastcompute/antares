#include <arch/antares.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32_eval_spi_flash.h"

#include "misc.h"

void Usart1Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef USART_ClockInitStructure;
//enable bus clocks
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
//Set USART1 Tx (PA.09) as AF push-pull
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
 
//Set USART1 Rx (PA.10) as input floating
 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 
GPIO_Init(GPIOA, &GPIO_InitStructure);
 
USART_ClockStructInit(&USART_ClockInitStructure);
 
USART_ClockInit(USART1, &USART_ClockInitStructure);
 
USART_InitStructure.USART_BaudRate = 115200;
 
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No ;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 
//Write USART1 parameters
 
USART_Init(USART1, &USART_InitStructure);
 
//Enable USART1
 
USART_Cmd(USART1, ENABLE);
 
}

void mdelay(int n)
{
        int i = n*10;													/* About 1/4 second delay */
        while (i-- > 0) {
                asm("nop");													/* This stops it optimising code out */
        }
}

void SysTick_Handler()
{
    tmgr_tick();
}



int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
		
		Usart1Init();
		SysTick_Config(SystemCoreClock / 100);
		
		setvbuf(stdin, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		while(1)
		{
			printk("Hello world\n\r");
 			sleep_ticks(1000);
		}
}