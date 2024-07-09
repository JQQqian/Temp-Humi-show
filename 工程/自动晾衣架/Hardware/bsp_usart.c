#include "bsp_usart.h"
#include "stm32f10x.h"
#define USART1_IRQn 37

static void USART1_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;

  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

static void USART2_NVIC_Configuration(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART1_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 设置 USART 结构体的各个成员，配置串口参数
    USART_InitStructure.USART_BaudRate = 115200;  // 波特率为 115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  // 数据位长度为 8 位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  // 停止位为 1 位
    USART_InitStructure.USART_Parity = USART_Parity_No;  // 不使用校验位
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 同时支持发送和接收
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // 不使用硬件流控制
    USART_Init(USART1, &USART_InitStructure);

    USART1_NVIC_Configuration();  // 配置 USART2 的中断向量表
    

}
void USART2_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 设置 USART 结构体的各个成员，配置串口参数
    USART_InitStructure.USART_BaudRate = 115200;  // 波特率为 115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  // 数据位长度为 8 位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  // 停止位为 1 位
    USART_InitStructure.USART_Parity = USART_Parity_No;  // 不使用校验位
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 同时支持发送和接收
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // 不使用硬件流控制
    USART_Init(USART2, &USART_InitStructure);

    USART2_NVIC_Configuration();  // 配置 USART2 的中断向量表
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);  // 使能接收中断
    USART_Cmd(USART2, ENABLE);  // 使能串口
}

void Usart_SendString(USART_TypeDef* pUSARTx, char* str){
    unsigned int k = 0;
    do{
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    }while(*(str + k) != '\0');
}

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch){
    USART_SendData(pUSARTx, ch);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
