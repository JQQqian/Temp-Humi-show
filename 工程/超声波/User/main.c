#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HC-SR04.h"

uint8_t flag;
uint32_t num;
uint32_t times;
uint32_t distance;

int main(void){
    HC_SR04_Init();
    OLED_Init();
    while(1){
         distance=0;
        for(int i=0;i<10;++i){              //每次取10次测距数据,取平均值减少误差
            GPIO_SetBits(GPIOA,GPIO_Pin_6);
            Delay_us(15);                   //根据说明书,需要提供至少10us的高电平
            GPIO_ResetBits(GPIOA,GPIO_Pin_6);
            Delay_ms(65);                   //根据说明书,每个周期至少需要等待60ms
            distance+=(times/5.8);          //根据说明书提供的公式,获取单位为mm的距离
        }
        distance/=10;
        OLED_ShowNum(2,1,distance,4);
    }
}

void TIM2_IRQHandler(void){
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
        num++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void EXTI9_5_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line9) != RESET){
        if(flag == 0){
            num = 0;
            flag = 1;
            TIM_SetCounter(TIM2, 0);
            TIM_Cmd(TIM2, ENABLE);
        }else{
            TIM_Cmd(TIM2, DISABLE);
            flag = 0;
            times = num;
            times = num*100+TIM_GetCounter(TIM2);
        }
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
}
