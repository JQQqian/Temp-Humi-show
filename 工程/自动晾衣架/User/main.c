#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "DHT11.h"
#include "PWM.h"
#include "Servo.h"
#include "Key.h"

DHT11_Data_TypeDef DHT11_Data;
uint8_t KeyNum;			//定义用于接收键码的变量
float Angle;	

int main(void){
    LED_Init();
    Key_Init();
    OLED_Init();
    DHT11_GPIO_Config();
    Servo_Init();
    OLED_ShowString(1,1,"Temperature:");
    OLED_ShowString(2,1,"Humidity:");
    OLED_ShowString(3,1,"Angle:");
    while(1){
        if(Read_DHT11(&DHT11_Data) == SUCCESS){
            OLED_ShowNum(1,13,DHT11_Data.humi_int,2);
            OLED_ShowString(1,15,".");
            OLED_ShowNum(1,16,DHT11_Data.humi_deci,1);
            OLED_ShowNum(2,10,DHT11_Data.temp_int,2);
            OLED_ShowString(2,12,".");
            OLED_ShowNum(2,13,DHT11_Data.temp_deci,1);
            if(DHT11_Data.humi_int >= 50){
                Angle = 180;
                Servo_SetAngle(Angle);
                LED2_ON();
                Delay_ms(1000);
            }else{
                Angle = 0;
                Servo_SetAngle(Angle);
                LED2_OFF();
                Delay_ms(1000);
            }
        }
        KeyNum = Key_GetNum();
        if(KeyNum == 1){
            if(Angle == 0){
                Angle = 180;
            }else{
                Angle = 0;
            }
            Servo_SetAngle(Angle);
        }
        OLED_ShowNum(3,7,Angle,3);
    }
}
