#include "stm32f10x.h" 

__IO uint8_t usart_value = 0;//接收一个字节数据的变量
uint8_t len = 0;             //接收数据的数组当前下标   
uint8_t num[20];           //存放接收一次数据包的数组
uint8_t Flag = 0;  		   //接收到数据之后Flag=1
static uint8_t f = 0;      //从0xA5开始接收0x5A结束

void DEBUG_USART_IRQHandler(void){
    if(USART_GetITStatus(USART2,USART_IT_RXNE)){
        usart_value = USART_ReceiveData(USART2);
        if(usart_value == 0xA5){
            f = 1;
        }
        if(f == 1){
            num[len] = usart_value;
            len++;
        }
    }
    if(len == 8 && usart_value == 0x5A){
        Flag = 1;
        len = 0;
        f = 0;
    }else if(len > 8){
        f = 0;
        len = 0;
    }
    USART_ClearFlag(USART2,USART_FLAG_RXNE)
}
