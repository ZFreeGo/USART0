/******************** (C) COPYRIGHT 2012 waveshare ********************
* File Name          : main.c
* Author             : waveshare.xuwenjie
* Version            : V1.0.0
* Date               : 29/10/2012
* Description        : 
************************************************************************/

#include <ioCC2530.h>
#include <string.h>

#define  uint  unsigned int
#define  uchar unsigned char

#define LED1 P0_1	
#define LED2 P0_0	

void Delay_ms(uint);
void initUART(void);
void UartSend_String(char *Data,int len);

char Txdata[20]; //存放"HELLO waveshare   "共20个字符串

/*******************************************************************************
* Function Name  : Delayms
* Description    : Delay ms.
* Input          : None
* Output         : None
* Return         : None
* Attention	 : None
*******************************************************************************/
void Delay_ms(uint n)
{
     uint i,j;
     for(i=0;i<n;i++)
     {
     for(j=0;j<1774;j++);
     }
}
/*******************************************************************************
* Function Name  : IO_Configuration
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void IO_Configuration()
{
	P0DIR |= 0x03;  //P0_1 P0_0定义为输出
        LED1 = 0;       //LED1灯熄灭 
          
        P1DIR |= 0x10;     //P1定义为输出
        P0_0 = 0;
        P1_4 = 0;
}


/*******************************************************************************
* Function Name  : InitUART
* Description    : Initialize UART
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void InitUART(void)
{ 
    PERCFG = 0x00;		      //位置1 P0口
    P0SEL = 0x0c;		      //P0_2,P0_3用作串口（外部设备功能）
    P2DIR &= ~0XC0;                   //P0优先作为UART0

    U0CSR |= 0x80;		      //设置为UART方式
    U0GCR |= 11;				       
    U0BAUD |= 216;		      //波特率设为115200
    UTX0IF = 0;                       //UART0 TX中断标志初始置位0
}

/*******************************************************************************
* Function Name  : UartSend_String
* Description    :  
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void UartSend_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void main(void)
{	
    CLKCONCMD &= ~0x40;               //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);          //等待晶振稳定为32M
    CLKCONCMD &= ~0x47;               //设置系统主时钟频率为32MHZ   
    IO_Configuration();
    InitUART();
    strcpy(Txdata,"\r\nHELLO waveshare  ");     //将发送内容copy到Txdata;
    while(1)
     {
         UartSend_String(Txdata,sizeof(Txdata)); //串口发送数据
         Delay_ms(500);                   //延时
         LED1=!LED1;                       //标志发送状态
     }
}