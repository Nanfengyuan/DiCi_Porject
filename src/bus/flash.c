#include "types.h"
#include "flash.h"

/******************************************************************
//Flash��д������ʱ���ø���
*******************************************************************/

u16 CheckNumWrite;
u16 CheckNumRead;

void EraseSectorFlashB()
{
  /*   u8 *p0;
      _DINT();
      WDTCTL = WDTPW + WDTHOLD;        
      FCTL2 = FWKEY + FSSEL_1 + FN3 ;//ѡ��ʱ��Դ����Ƶ
      FCTL3 = FWKEY;//���LOCK
      while(FCTL3 & BUSY);//�������æ����ȴ�
      FCTL1 = FWKEY + ERASE;//ʹ�ܶβ���  
      p0 = (u8 *)SegmentB;//��ֵǿ��ת����ָ��
      *p0 = 0;            //����������ַд0������д�룬������������
      FCTL1 = FWKEY;
      FCTL3 = FWKEY + LOCK; 
      while(FCTL3 & BUSY);
      _EINT();                       //�����ж�
      WDTCTL = WDT_ARST_1000 ; */
} 

void EraseSectorFlashC( void )
{
   u8 *Erase_address;   
  Erase_address  = (u8 *)SegmentC;   
  FCTL1 = FWKEY + ERASE;  
  FCTL3  = FWKEY;   
  *Erase_address = 0;   
  FCTL1 = FWKEY;    
  FCTL3 = FWKEY + LOCK; 
  WDTCTL = WDT_ARST_1000 ;
}

u16 FlashWriteB(u8 *Datain,u8 count)
{
  u8 i;
  u8 *Flash_ptr, *p0;     
  u16 AddNum;
  AddNum = 0;
  Flash_ptr = (u8 *)SegmentB;
  _DINT();
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *(u16 *)Flash_ptr = 0;   
  FCTL1 = FWKEY+WRT;    
  while(FCTL3 & BUSY);     
  for(i=0;i<count;i++)
    { 
      while(FCTL3 & BUSY);   
      AddNum += *Datain; 
      *Flash_ptr++ = *Datain++;    
    }
   p0 = (u8 *)CHECK_NUM_ADDRESS;
  *p0++ = (u8)AddNum;
  *p0 = (u8)(AddNum>>8);
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
  while(FCTL3 & BUSY);   
  _EINT();
   WDTCTL = WDT_ARST_1000 ; 
  return  AddNum;   
}

void FlashReadB(u8 *Dataout,u8 count)
{
  u8 i;
  u8 *p0;
  p0 = (u8 *)SegmentB;
  _DINT();
  for(i=0;i<count;i++)
  { *Dataout++ = *p0++; }
  _EINT();
   WDTCTL = WDT_ARST_1000 ; 
}


void EraseSectorFlash( u32 Address)
{
 
} 

void FlashWrite(u32 Address, u8 *Datain,u16 count)
{
  u16 i;
  u8 *Flash_ptr;     
  Flash_ptr = (u8 *)Address;
  _DINT();
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *(u32 *)Flash_ptr = 0;   
  FCTL1 = FWKEY+WRT;  
  while(FCTL3 & BUSY);   
  for(i=0;i<count;i++)
    { 
      while(FCTL3 & BUSY);   
      *Flash_ptr++ = *Datain++; 
    }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
  while(FCTL3 & BUSY);   
  _EINT();
   WDTCTL = WDT_ARST_1000 ; 
}

void FlashRead(u32 Address, u8 *Dataout,u16 count)
{
   u16 i;
  u8 *p0;
  p0 = (u8 *)Address;
  _DINT();
  for(i=0;i<count;i++)
  { *Dataout++ = *p0++; }
  _EINT();
   WDTCTL = WDT_ARST_1000 ; 
}