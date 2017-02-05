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

char Txdata[20]; //���"HELLO waveshare   "��20���ַ���

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
	P0DIR |= 0x03;  //P0_1 P0_0����Ϊ���
        LED1 = 0;       //LED1��Ϩ�� 
          
        P1DIR |= 0x10;     //P1����Ϊ���
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
    PERCFG = 0x00;		      //λ��1 P0��
    P0SEL = 0x0c;		      //P0_2,P0_3�������ڣ��ⲿ�豸���ܣ�
    P2DIR &= ~0XC0;                   //P0������ΪUART0

    U0CSR |= 0x80;		      //����ΪUART��ʽ
    U0GCR |= 11;				       
    U0BAUD |= 216;		      //��������Ϊ115200
    UTX0IF = 0;                       //UART0 TX�жϱ�־��ʼ��λ0
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
    CLKCONCMD &= ~0x40;               //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);          //�ȴ������ȶ�Ϊ32M
    CLKCONCMD &= ~0x47;               //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ   
    IO_Configuration();
    InitUART();
    strcpy(Txdata,"\r\nHELLO waveshare  ");     //����������copy��Txdata;
    while(1)
     {
         UartSend_String(Txdata,sizeof(Txdata)); //���ڷ�������
         Delay_ms(500);                   //��ʱ
         LED1=!LED1;                       //��־����״̬
     }
}