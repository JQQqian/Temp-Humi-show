#ifndef __BSP_USART_H__
#define __BSP_USART_H__
#include "stm32f10x.h"
#include "stdio.h"

void USART1_Config(void);
void USART2_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
   
#endif
