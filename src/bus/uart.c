#include"types.h"
#include "uart.h"
#include "cfg.h"
#include "flash.h"
#include <string.h>
#include "magentic.h"
#include "ad.h"
#include "timeslot.h"
#include "24l01.h"
#include "..\bc95\mcu_buffer.h"

/*********************************************************
//���ڳ���
***********************************************************/
extern FLASH_PARAMTER_t  FlashParamt;
extern RF_PARAMTER RfParamt;
extern SENSOR_SAMPLE_PARAMTER AxisZ1Pam;
extern SENSOR_SAMPLE_PARAMTER AxisX1Pam;
extern MAGNETIC_VALUE Magnetic;
extern SENSOR_TIME_PARAMTER  SenTime;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineX;
extern STABLE_BASELINE        OnStableBaseLineZ;
extern STABLE_BASELINE        OnStableBaseLineX;
extern EVENT_BUFF  EventBuff;
extern u8 DatCnt[2];
extern u16 PumpHigh;;
extern u8 TimeSlotMode;
extern u16 CheckNumRead;
extern u16 ConfigFlags;
extern u16 CheckNumWrite;
extern u16 AdMagenticFlags;
extern u16 TimeCommunicatFlag;
extern u16 HalfBaseLineFlag;
extern u16 ExtraFlags;
extern u16 CompFlags;
extern u8 OldBaseDayCnt;
extern u8 SystemState;
extern u8 AdStartCnt;
extern u8 EventBuffFlag;
extern u8 BaseLineRssi;
extern SNP_EVENT_t OnSaveBuff;
extern SNP_EVENT_t OffSaveBuff;
extern TIME_SLOT_PARMAT TimeSlot;
extern u16 RFM98FreqTbl[1][3];
extern SNP_UPLINE_PACKET_t UplinePacket;
extern int8 ComparRssi;
extern u16 ReportTime;
extern u8 SignalState;
extern u16 SetBaseLineZ;
extern u16 SetBaseLineX;
extern u16 DebugFlag;
extern u8 testflag;
extern u16 TempBaseX;
extern u16 TempBaseZ;
extern CLOCK_VALUE Clock;
extern SNP_SEN_CFG_ACK_PACKET_t SenAckPacket;
extern EVENT_SAVE_SYS  SaveEventFlash;
extern ON_BASELINE_BUFF BaseLineBuff;
extern u8 OffNumZ;
extern u8 OffNumX;
extern u8 TempBaseDayCnt;
extern u8 BasCountX;
extern u8 BasCountZ;
extern u16 TempBaseFlag;
extern u8 testZ;
extern u8 testX;
extern u8 BaseBuffZPtr;
extern u8 BaseBuffXPtr;
extern u16 FlashBaseBuffZ[BASE_BUFF_NUM];
extern u16 FlashBaseBuffX[BASE_BUFF_NUM];
//extern u8 CountTimePtr;
//extern u8 CountTime[50];
u8 RecBuf[RECNUM];
u8 Rindex = 0;
u8 NewLineOFF;
u8 DatCnt1[2];
u8 testflag = 0;
u8 testXZ;
//extern u8 SEN_XCO_DELAY;
//extern u8 RfDisableFlag;
//u8 Tap;
//int8 testSnr;
void UartInit()
{
  P5SEL|=(BIT6+BIT7);
  P5DIR |= BIT6;
  UCA1CTL0 = 0;
  UCA1CTL1 |= UCSSEL_2;// //����ΪUSRTģʽ������żЧ�飬8λ1ͣ���첽
   
 // UTCTL1|=SSEL1;//ѡ��1M//ѡ���ʱ��ԴΪSMCLK,
  UCA1BR0 = 0x41;// 0X04;
  UCA1BR1 = 0X03;//UCBRS1
  UCA1MCTL= 0x00;//0X3a; //���ò�����Ϊ9600    
      
  UCA1IFG &= ~UCTXIFG;
  UCA1CTL1 &= ~UCSWRST;
  UCA1IE |= UCRXIE; //�����ж�ʹ��     
}

/*******************************************************************
* ������ : Mcu_UartSendLR
* ����   : ���ͻس���0x0D �� ���з�0x0A
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   :
********************************************************************/
void Mcu_UartSendLR(void)
{
	UartSendByte(0x0D); //�س���
	UartSendByte(0x0A); //���з�
}


void UartSendByte(u8 data)
{
 UCA1TXBUF = data; 
   while(!(UCA1IFG & UCTXIFG));//�ȴ����ͽ���
}

void UartSendWByte(u16 data)
{
  u8 pData;
  pData=data>>8;
  UartSendByte(pData);
  pData=(u8)data;
  UartSendByte(pData);
}

/*******************************************************************************
* ������ : Mcu_UartSendAtCommand
* ����   : ����ATָ���
* ����   :
* ���   :
* ����   :
* ע��   :
*******************************************************************************/
void Mcu_UartSendAtCommand(char *cmd)
{
	UartSendStrings(cmd);
	Mcu_UartSendLR();
}


void UartSendStrings(char *str)
 {
     while(*str)
	 {
	  UartSendByte(*str); 
	  str++;
	 }
 } 

#pragma vector=USCI_A1_VECTOR
__interrupt void usart1_rx (void)
{ 
 // u8 i;
    //LPM3_EXIT;
    WDTCTL =  WDT_ARST_1000; 
    UCA1IFG &= ~UCRXIFG;
    *recv0_ptr = UCA1RXBUF;   //uart1���ն����ݲɼ������뻺��buffer
    recv0_ptr++;
    recv0_num++;
    if(UART0_BUFFER_SIZE <= recv0_num)
    {
      Buffer_Uart0RecvClear();    //������ݴ洢��֮��buffer�������´洢
    }
} 

//*********************************test*******************
char Pstr[6];
void UartSendNumber(u16 data)
{
  SplitNum(data ,Pstr);
  UartSendStrings(Pstr);   
  if(NewLineOFF == 0)  
  {UartSendStrings("\r\n");}
  memset(Pstr,0,sizeof(Pstr));   
  NewLineOFF = 0;
}


void SplitNum(u16 temp,char *pbuf)
{
  u16 DataH;
  u16 DataL;
 //u8 i;
  DataH=temp/10000;
  DataL=temp%10000;
  if(DataH>0)
 {
  *pbuf++=DataH+48;
  DataH=DataL/1000;
  DataL=DataL%1000;
  *pbuf++=DataH+48;
  DataH=DataL/100;
  DataL=DataL%100;
  *pbuf++=DataH+48;
  DataH=DataL/10;
  DataL=DataL%10;
  *pbuf++=DataH+48;
  *pbuf=DataL+48;
 }
 else
 {
  DataH=DataL/1000;
  DataL=DataL%1000;
  if(DataH>0)
  {
    *pbuf++=DataH+48;
    DataH=DataL/100;
    DataL=DataL%100;
     *pbuf++=DataH+48;
     DataH=DataL/10;
    DataL=DataL%10;
    *pbuf++=DataH+48;
    *pbuf=DataL+48;
  }
  else
  {
     DataH=DataL/100;
     DataL=DataL%100;
      if(DataH>0)
      {
        *pbuf++=DataH+48;
        DataH=DataL/10;
        DataL=DataL%10;
        *pbuf++=DataH+48;
        *pbuf=DataL+48;
      }
      else
      {
        DataH=DataL/10;
        DataL=DataL%10;
         if(DataH>0)
         {
            *pbuf++=DataH+48;
            *pbuf=DataL+48;
         }
         else
         {
           *pbuf=DataL+48;
         }
      }
  }
 } 
}

void UartSendNumberH(u16 data)
{
  SplitNumH(data ,Pstr);
  UartSendStrings(Pstr); 
  if(NewLineOFF == 0)  
  {UartSendStrings("\r\n");}
  memset(Pstr,0,sizeof(Pstr));
  NewLineOFF = 0;
}

void SplitNumH(u16 temp,char *pbuf)
{
  u8 DataH;
  DataH = temp>>12;
  if(DataH < 10)
    { *pbuf++ = DataH + 48; }
  else
    { *pbuf++ = DataH + 55; }
  temp &= 0x0fff;
  DataH = temp>>8;
  if(DataH < 10)
    { *pbuf++ = DataH + 48; }
  else
    { *pbuf++ = DataH + 55; }
  temp &= 0x00ff;
  DataH = temp>>4;
  if(DataH < 10)
    { *pbuf++ = DataH + 48; }
  else
    { *pbuf++ = DataH + 55; }
  temp &= 0x000f;
  DataH = temp;
  if(DataH < 10)
    { *pbuf++ = DataH + 48; }
  else
    { *pbuf++ = DataH + 55; }
}

void UartSendNumberH8(u8 data)
{
  SplitNumH8(data ,Pstr);
  UartSendStrings(Pstr); 
  if(NewLineOFF == 0)  
  {UartSendStrings("\r\n");}
  memset(Pstr,0,sizeof(Pstr));
  NewLineOFF = 0;
}

void SplitNumH8(u8 temp,char *pbuf)
{
  u8 DataH;
  DataH = temp>>4;
  if(DataH < 10)
    { *pbuf++ = DataH + 48; }
  else
    { *pbuf++ = DataH + 55; }
  temp &= 0x000f;
  DataH = temp;
  if(DataH < 10)
    { *pbuf++ = DataH + 48; }
  else
    { *pbuf++ = DataH + 55; }
}

/*******************************************************************************
* ������ : Mcu_UartSendDataWithLength
* ����   :  ����ָ�������ݳ��ȷ�������
* ����   :
* ���   :
* ����   :
* ע��   :
*******************************************************************************/
void Mcu_UartSendDataWithLength(char *data, unsigned short len)
{
	while(len)
	{
		while (!(UCA1IFG&UCTXIFG));           // USCI_A1 TX buffer ready?
		UCA1TXBUF = *data;                   // TX -> RXed character
		data++;
		len--;
	}
}

