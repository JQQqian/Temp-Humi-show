#ifndef __ESP_01_H
#define __ESP_01_H
#include<string.h>

extern  char Usart_Receive[50];
extern unsigned char Usart_Cnt;
extern unsigned char  Usart_AT_flage;
extern unsigned char Usart_Connect_Buf_Flag;
void ManyConnect_AP(void);
void Clear_Usart_Receive(void);

#endif
