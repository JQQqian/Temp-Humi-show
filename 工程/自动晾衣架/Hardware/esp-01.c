#include "esp-01.h"
#include "bsp_usart.h"
#include "Delay.h" 

char RST[]="AT+RST\r\n";//重启  
char UART[]="AT+UART=115200,8,1,0,0\r\n";//波特率设置
char CWMODE[]="AT+CWMODE=2\r\n";//工作模式设置
char CIPMUX[]="AT+CIPMUX=1\r\n";//多连接模式设置
char CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";//开启服务器模式
char CIFSR[]="AT+CIFSR\r\n";//查询本机地址
char CWSAP[]="AT+CWSAP=\"text1\",\"11111111\",1,3,\r\n";//设置热点名称和密码

char Usart_Receive[50]={0}; 
unsigned char Usart_Cnt=0;
unsigned char Usart_Connect_Buf_Flag=0;
unsigned char  Usart_AT_flage;

// 清除USART接收缓冲区
void Clear_Usart_Receive(){
    unsigned char i=0;
    for(i=0;i<50;i++){
        Usart_Receive[i]=0;
    }
    Usart_Cnt=0;
    Usart_AT_flage=0;
}

// 配置ESP-01模块为多连接AP模式
void ManyConnect_AP(void){
    Usart_SendString(USART2,RST);
    Delay_ms(500);
    while(!Usart_AT_flage);
    if(strstr(Usart_Receive,"OK")){
        Usart_SendString(USART2,"RST\r\n");
        Clear_Usart_Receive();
    }
    Clear_Usart_Receive();

    Usart_SendString(USART2,UART);
    while(!Usart_AT_flage);
    if(strstr(Usart_Receive,"OK")){
        Usart_SendString(USART2,"UART\r\n");
        Clear_Usart_Receive();
    }

    Usart_SendString(USART2,CWMODE);
    while(!Usart_AT_flage);
    if(strstr(Usart_Receive,"OK")){
        Usart_SendString(USART2,"CWMODE\r\n");
        Clear_Usart_Receive();
    }

    Usart_SendString(USART2,CWSAP);
    while(!Usart_AT_flage);
    if(strstr(Usart_Receive,"OK")){
        Usart_SendString(USART2,"CWSAP\r\n");
        Clear_Usart_Receive();
    }
    
    Usart_SendString(USART2,CIPMUX);
    while(!Usart_AT_flage);
    if(strstr(Usart_Receive,"OK")){
        Usart_SendString(USART2,"CIPMUX\r\n");
        Clear_Usart_Receive();
    }

    Usart_SendString(USART2,CIPSERVER);
    while(!Usart_AT_flage);
    if(strstr(Usart_Receive,"OK")){
        Usart_SendString(USART2,"CIPSERVER\r\n");
        Delay_ms(50);
        Clear_Usart_Receive();
        Usart_Connect_Buf_Flag = 1;
    }

    Usart_SendString(USART2,CIFSR);
    Usart_SendString(USART1,Usart_Receive);
}
