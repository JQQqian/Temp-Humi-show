#include "stm32f10x.h" 
#include "Delay.h"
#include "DHT11.h"
void DHT11_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}
static void DHT11_Mode_IPU(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
static void DHT11_Mode_Out_PP(void){
    GPIO_InitTypeDef GPIO_InitStructure;;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
static uint8_t Read_Byte(void){
    uint8_t i,temp=0;
    for(i=0;i<8;i++){
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET);
        Delay_us(40);
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET){
            while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET);
            temp |=(uint8_t)(0x01 << (7-i));
        }else{
            temp &= (uint8_t) ~ (0x01<<(7-i)); 
        }
    }
    return temp;
}
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data){
    DHT11_Mode_Out_PP();
    DHT11_DATA_OUT(LOW);
    Delay_ms(18);
    DHT11_DATA_OUT(HIGH);
    Delay_us(30);

    DHT11_Mode_IPU();
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET){
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET);

        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET);

        DHT11_Data -> humi_int = Read_Byte();
        DHT11_Data ->humi_deci = Read_Byte();
        DHT11_Data -> temp_int = Read_Byte();
		DHT11_Data -> temp_deci = Read_Byte();
		DHT11_Data -> check_sum= Read_Byte();

        DHT11_Mode_Out_PP();
        DHT11_DATA_OUT(HIGH);

        if (DHT11_Data -> check_sum == DHT11_Data -> humi_int + DHT11_Data -> humi_deci + DHT11_Data -> temp_int + DHT11_Data -> temp_deci){
			return SUCCESS;
        }else{
            return ERROR;
        }
    }else{
        return ERROR;
    } 
}
