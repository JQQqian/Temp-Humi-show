#include "stm32f10x.h" 

void PWM_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 || GPIO_Pin_1 || GPIO_Pin_2 || GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 2000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 720-1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef  TIM_OCInitStructure1;
    TIM_OCStructInit(&TIM_OCInitStructure1);
    TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure1.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure1);

    TIM_OCInitTypeDef  TIM_OCInitStructure2;
    TIM_OCStructInit(&TIM_OCInitStructure2);
    TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure2.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure2);

    TIM_OCInitTypeDef  TIM_OCInitStructure3;
    TIM_OCStructInit(&TIM_OCInitStructure3);
    TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure3.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure3);

    TIM_OCInitTypeDef  TIM_OCInitStructure4;
    TIM_OCStructInit(&TIM_OCInitStructure4);
    TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure4.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure4);
}

void PWM_SetCompare1(uint16_t Compare){
        TIM_SetCompare1(TIM2, Compare);
}

void PWM_SetCompare2(uint16_t Compare){
        TIM_SetCompare2(TIM2, Compare);
}

void PWM_SetCompare3(uint16_t Compare){
        TIM_SetCompare3(TIM2, Compare);
}

void PWM_SetCompare4(uint16_t Compare){
        TIM_SetCompare4(TIM2, Compare);
}
