#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "DHT11.h"
#include "esp-01.h"
#include "bsp_usart.h"
DHT11_Data_TypeDef DHT11_Data;

int main(void){
    char *PBuf;
    USART1_Config();
	USART2_Config();
    LED_Init();
    ManyConnect_AP();
    Clear_Usart_Receive();
    while(1){
        PBuf = strchr(Usart_Receive, '+');
        if((PBuf[0]=='+')&&(PBuf[1]=='I')&&(PBuf[2]=='P')&&(PBuf[3]=='D')
					 &&(PBuf[6]==',')&&((PBuf[9]>='0')&&(PBuf[9]<='9'))){
            if(PBuf[9]=='0'){
                LED1_OFF();
            }
            if(PBuf[9]=='1'){
                LED1_ON();
            }
            PBuf[10]='\r';
			PBuf[11]='\n';

            Usart_SendString(USART1,PBuf);
            Delay_ms(50);
            Clear_Usart_Receive();
        }
    }
}









//LED_Init();
    //OLED_Init();
    //DHT11_GPIO_Config();

    //OLED_ShowString(1,1,"Temperature:");
    //OLED_ShowString(2,1,"Humidity:");

    /*while(1){
        if(Read_DHT11(&DHT11_Data) == SUCCESS){
            OLED_ShowNum(1,13,DHT11_Data.humi_int,2);
            OLED_ShowString(1,15,".");
            OLED_ShowNum(1,16,DHT11_Data.humi_deci,1);
            OLED_ShowNum(2,10,DHT11_Data.temp_int,2);
            OLED_ShowString(2,12,".");
            OLED_ShowNum(2,13,DHT11_Data.temp_deci,1);
            if(DHT11_Data.temp_int >= 30){
                LED2_ON();
            }else{
                LED2_OFF();
            }
        }
    }*/






