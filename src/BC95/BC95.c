/*
 * brd_bc95.c
 *
 *  Created on: 2017-11-14
 *      Author: user
 */


#include "common.h"
#include "mcu_buffer.h"
#include "types.h"
#include "uart.h"
//#include "mcu_uart.h"
//#include "mcu_timer.h"
//#include "tool_utils.h"

/*******************************************************************
* ������ : Brd_Nbiot_PowerOn
* ����   : �򿪺��İ��Դ
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : Ӳ����λ
********************************************************************/
void Brd_Nbiot_PowerOn(void)
{
//ʹ��BC95��Դ��ʹ��MCU����ģʽ
	P5OUT |= BIT5;			//��BC95��Դ
}

/*******************************************************************
* ������ : Brd_Nbiot_PowerOff
* ����   : �رպ��İ��Դ
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : Ӳ����λ
********************************************************************/
void Brd_Nbiot_PowerOff(void)
{
//�ر�BC95��Դ������RX �� TX�ܽ�����ΪGPIO����͵�ƽ
	P5OUT &= ~BIT5;				//�ر�BC95��Դ
	UCA1CTL1 |= UCSWRST;		//���ô��ڽ��븴λ״̬������TX�ܽ���Ȼ�����3.3V��ѹ��Ӱ��BC95����
	P5SEL &= ~(BIT6 + BIT7);	//����RX �� TX�ܽ�ΪGPIOģʽ
	P5DIR |= (BIT6 + BIT7);		//GPIO����Ϊ �������
	P5OUT &= ~(BIT6 + BIT7);    //��� �͵�ƽ
}

/*******************************************************************
* ������ : delay_nms
* ����   : ʹ��delay_ms��������������ֵ����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : 
********************************************************************/
void delay_nms(int n)
{
  for(int i=0;i<n;i++)
  {
    delay_ms(1);
  }
}

/*******************************************************************
* ������ : Brd_Nbiot_Hdw_Reset
* ����   : ͨ��Reset�ܽŸ�λNBIOTģ��
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : Ӳ����λ
********************************************************************/
unsigned char Brd_Nbiot_Hdw_Reset(void)
{
	P4DIR |= BIT5;
	P4OUT |= BIT5;									//����Reset�ܽŵ�ƽ����λnbiotģ��
	delay_nms(NBIOT_RESET_DELAYTIME);				//��ʱ
	P4DIR |= BIT5;
	P4OUT &= ~BIT5;									//����Reset�ܽŵ�ƽ���˳���λ

    return 1;
}

/*******************************************************************
* ������ : Brd_Nbiot_AT_Reset
* ����   : ͨ��NRB���λģ��
* ����   : ��
* ���   :
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_AT_Reset(void)
{
	Buffer_Uart0RecvClear();						//���uart1���ջ�����
//	Mcu_UartSendAtCommand("AT+NRB");				//ͨ��UART0�������log��Ϣ
	Mcu_UartSendAtCommand("AT+NRB");				//����ATָ��

    return 1;
}

/*******************************************************************
* ������ : Mcu_BC95_AT_OK
* ����   : ����AT������OK������uart0���ں�BC95ģ��֮��ͨ���Ƿ�����
* ����   : ��
* ���   :
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ����AT������OK
********************************************************************/
unsigned char Brd_Nbiot_Snd_AT(void)
{
	unsigned short try_num = AT_AT_REPEAT_NUMBER;

    do
    {
    	Buffer_Uart0RecvClear();					//���uart1���ջ�����
//    	Mcu_UartSendAtCommand("AT");				//ͨ��UART0�������log��Ϣ
    	Mcu_UartSendAtCommand("AT");				//����ATָ��
//    	Mcu_TimerAStart();							//������ʱ���ȴ�ָ��ظ�
//    	__bis_SR_register(LPM3_bits + GIE);			//MCU����͹���˯��ģʽ
        delay_nms(2000);                                  //��ʱ500���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)			//��⵽OK����NBIOTģ���Ѿ��������������Է�������ATָ��
    	{
//    		Mcu_TimerAStop();
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Cgmr
* ����   : ��ȡNBIOTģ��̼��汾��
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cgmr(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
//    	Mcu_Uart1SendAtCommand("AT+CGMR");				//ͨ��UART0�������log��Ϣ
    	Mcu_UartSendAtCommand("AT+CGMR");				//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "SECURITY,") != NULL)		//���磺SECURITY,V100R100C10B657SP2
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Cgsn
* ����   : ��ȡNBIOTģ���IMEI��Ϣ
* ����   : ��
* ���   :
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cgsn(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

    do
    {
    	Buffer_Uart0RecvClear();				//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CGSN=1");	//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CGSN:") != NULL)	//����"+CGSN:"�ؼ��ֵ�λ�� +CGSN:863703034512546
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Nconfig
* ����   : ��ȡ�Ƿ�ģ���Զ�����
* ����   : ��
* ���   : autocnt=0 : û���Զ�����   1 ���ϵ��Զ�����
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Nconfig(unsigned char *autocnt)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();				//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+NCONFIG?");	//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+NCONFIG:AUTOCONNECT,FALSE") != NULL)
    	{
    		*autocnt = 0;
    		break;
    	}
    	else if(strstr(recv0_buf, "+NCONFIG:AUTOCONNECT,TRUE") != NULL)
    	{
    		*autocnt = 1;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Nband
* ����   : ��ȡģ���Ƶ��
* ����   : ��
* ���   : nband=0 : 850MHZ   1 ��900MHZ  2 ��800MHZ
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Nband(unsigned char *nband)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

    do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+NBAND?");			//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+NBAND:5") != NULL)
    	{
    		*nband = '5';									//�й�����
    		break;
    	}
    	else if(strstr(recv0_buf, "+NBAND:8") != NULL)
    	{
    		*nband = '8';									//�й��ƶ����й���ͨ
    		break;
    	}
    	else if(strstr(recv0_buf, "+NBAND:20") != NULL)
    	{
    		*nband = '0';								//ŷ����ʽ
    		break;
    	}

    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Cfun
* ����   : ȷ���Ƿ�ʶ��SIM�����Լ���Ƶ�Ƿ��
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cfun(void)
{
	unsigned short try_num = AT_CFUN_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CFUN?");				//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CFUN:1") != NULL)		//��Ƶģ���Ѿ��������������ҳɹ�ʶ��SIM��
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Cimi
* ����   : ��ȡSIM����IMSI
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cimi(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CIMI");				//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "460") != NULL)			//���磺460111108971472���й���IMSI��460��ͷ
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Nccid
* ����   : ��ȡSIM����ICCID����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Nccid(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+NCCID");				//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+NCCID:") != NULL)		//�ɹ���ȡiccid���룬����+NCCID:89860317492039393960
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Csq
* ����   : ��ȡ���������ź�
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ��API����ȡ�ź�ǿ��ֵ
********************************************************************/
unsigned char Brd_Nbiot_Get_Csq(void)
{
	unsigned short try_num = AT_CSQ_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();					//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CSQ");			//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CSQ:99,99") != NULL)	//û���������ź�
    	{

    	}
    	else if(strstr(recv0_buf, "+CSQ:") != NULL)	//�������ź�
    	{
			break;
    	}
    }while(--try_num);

    return try_num;
}


/*******************************************************************
* ������ : Brd_Nbiot_Get_Cgatt
* ����   : �ж��Ƿ��ŵ�����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cgatt(void)
{
	unsigned short try_num = AT_CGATT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CGATT?");			//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CGATT:1") != NULL)
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Cereg
* ����   : �ж��Ƿ�ע�ᵽ����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cereg(void)
{
	unsigned short try_num = AT_CEREG_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CEREG?");			//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CEREG:0,1") != NULL)
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Cscon
* ����   : �ж��ǵ�ǰ�豸������״̬
* ����   : ��
* ���   : cscon=0 : idle   1 ��connect
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cscon(unsigned char *cscon)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CSCON?");			//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CSCON:0,1") != NULL)
    	{
    		*cscon = 1;									//����connect״̬
    		break;
    	}
    	else if(strstr(recv0_buf, "+CSCON:0,0") != NULL)
    	{
    		*cscon = 0;									//����idle״̬���߻�û�е����ɹ�
    		break;
    	}
    }while(--try_num);

    return try_num;
}


/*******************************************************************
* ������ : Brd_Nbiot_Get_Cclk
* ����   : ��ȡ��ǰ����ʱ��
* ����   : ��
* ���   :
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cclk(void)
{
	unsigned short try_num = AT_CCLK_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+CCLK?");				//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "+CCLK:") != NULL)			//ʱ����Ϣ"yy/MM/dd,hh:mm:ss"���� +CCLK:17/11/15,07:10:04+32
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Get_Ncdp
* ����   : ��ȡ��ǰNCDP��Ϣ��IoTƽ̨��Ϣ
* ����   : ��
* ���   : <ip_addr>,<port>
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Ncdp(char *ncdp)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+NCDP?");				//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	ncdp = strstr(recv0_buf, "+NCDP:");				//����+NCDP:114.115.144.122,5683
    	if(ncdp != NULL)
    	{
    		ncdp = ncdp + 6;							//������+NCDP:���ؼ���
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Set_Nconfig
* ����   : ����ģ���ϵ��Զ�����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Nconfig(void)
{
	unsigned short try_num = AT_NCONFIG_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();								//���uart1���ջ�����
    	Mcu_UartSendAtCommand("AT+NCONFIG=AUTOCONNECT,TRUE");	//����ATָ��
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Set_Cgatt
* ����   : �ֶ����� ȥ������
* ����   : cgatt=0�� ȥ��  1 ������
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Cgatt(unsigned char cgatt)
{
	unsigned short try_num = AT_CGATT_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	if(cgatt == 0)
	{
		Mcu_UartSendAtCommand("AT+CGATT=0");			//����ATָ��
	}
	else
	{
		Mcu_UartSendAtCommand("AT+CGATT=1");			//����ATָ��
	}

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Set_Cfun
* ����   : �ֶ��� ���� �ر� ��Ƶ��·
* ����   : cfun=0�� �ر���Ƶ  1 ������Ƶ
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Cfun(unsigned char cfun)
{
	unsigned short try_num = AT_CFUN_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	if(cfun == 0)
	{
		Mcu_UartSendAtCommand("AT+CFUN=0");			//����ATָ��
	}
	else
	{
		Mcu_UartSendAtCommand("AT+CFUN=1");			//����ATָ��
	}

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Set_Ncdp
* ����   : ����
* ����   : ipaddrƽ̨��IP��ַ  ipportƽ̨�Ķ˿ں�
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Ncdp(char *ip_port)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;
	char cmd[64] = {0};

	strcpy(cmd, "AT+NCDP=");		    				//�����������AT+NCDP=119.23.233.222,5683
	strcat(cmd, ip_port);

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	Mcu_UartSendAtCommand(cmd);						//����ATָ��

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//����ʧ�ܷ���ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Crt_Nsocr
* ����   : ����UDP�ŵ�
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Crt_Nsocr(void)
{
	unsigned short try_num = AT_NSOCR_REPEAT_NUMBER;
	char cmd[64] = {0};

	strcpy(cmd, "AT+NSOCR=DGRAM,17,");		    		//��������
	strcat(cmd, UDP_LOCAL_PORT);
	strcat(cmd, ",1");

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	Mcu_UartSendAtCommand(cmd);						//����ATָ��

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//����ʧ�ܷ���ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Cls_Nsocl
* ����   : �ر�UDP�ŵ�
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   :
********************************************************************/
unsigned char Brd_Nbiot_Cls_Nsocl(void)
{
	unsigned short try_num = AT_NSOCR_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	Mcu_UartSendAtCommand("AT+NSOCL=0");				//����ATָ��

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//����ERROR,˵��udp�ŵ��Ѿ��ر���
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Snd_Nsost
* ����   : ͨ��UDP�ŵ���������
* ����   : data����ָ�룬len �û����ݳ���
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ����ǰ ��Ҫ��������ָ��
********************************************************************/
unsigned char Brd_Nbiot_Snd_Nsost(char *ip_port, char * data, unsigned short len)
{
	char cmd[64] = {0};
	char str[6]	 = {0};
	unsigned short try_num = AT_NSOST_REPEAT_NUMBER;

	itoi(str, len);										//����ת�����ַ���
	strcpy(cmd, "AT+NSOST=0,");		    				//�������� AT+NSOST=0,114.115.144.122,4567,3,303132
	strcat(cmd, ip_port);					//��������IP��ַ�Ͷ˿ں�
	strcat(cmd, ",");
	strcat(cmd, str);									//�������ݳ���
	strcat(cmd, ",");

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	UartSendStrings(cmd);							//����ATָ��
	Mcu_UartSendDataWithLength(data, len*2);		//��������
	Mcu_UartSendLR();									//���ͻس�

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//����ʧ�ܷ���ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Rcv_Nsorf
* ����   : ͨ��UDP�ŵ���ȡ����
* ����   : ��
* ���   : newdata=1 ��ȡ�������ݣ� newdata=0�Ѿ�û��������
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ������Ȼ�����recv0_buf��û�ж�����������
********************************************************************/
unsigned char Brd_Nbiot_Rcv_Nsorf(unsigned char *newdata)
{
	unsigned short try_num = AT_NSORF_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();									//���uart1���ջ�����
	Mcu_UartSendAtCommand("AT+NSORF=0,512");					//����AT+NSORFָ��,��ȡ����

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if( (recv0_buf[2] == '0') && (recv0_buf[3] == ',') )		//������� �س�+��0���� ������յ������ݣ����ͣ���0��=�ŵ���Ź̶�Ϊ0���������̶�����
    	{
    		*newdata = 1;
    		break;
    	}
    	else if( (recv0_buf[2] == 'O') && (recv0_buf[3] == 'K') )	//������� �س�+OK����û��������
    	{
    		*newdata = 0;
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)					//����ʧ�ܷ���ERROR
    	{
    		*newdata = 0;
    		try_num  = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Snd_Nmgs
* ����   : ͨ��coap�ŵ���������
* ����   : data����ָ�룬len �û����ݳ���
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ����ǰ ��Ҫ��������ָ��
********************************************************************/
unsigned char Brd_Nbiot_Snd_Nmgs(char * data, unsigned short len)
{
	char cmd[64] = {0};
	char str[6]	 = {0};
	unsigned short try_num = AT_NMGS_REPEAT_NUMBER;

	itoi(str, len);										//����ת�����ַ���
	strcpy(cmd, "AT+NMGS=");		    				//�����������AT+NMGS=11,48454C4C4F2C574F524C44
	strcat(cmd, str);									//�������ݳ���
	strcat(cmd, ",");

	Buffer_Uart0RecvClear();							//���uart1���ջ�����
	UartSendStrings(cmd);							//����ATָ��
	Mcu_UartSendDataWithLength(data, len*2);			//��������
	Mcu_UartSendLR();									//���ͻس�������AT+NMGSָ��,ͨ��coap�ŵ���������

//	Buffer_Uart0RecvClear();										//���uart1���ջ�����
//	Mcu_Uart1SendAtCommand("AT+NMGS=11,48454C4C4F2C574F524C44");	//ͨ��UART0���������������
//	Mcu_Uart0SendAtCommand("AT+NMGS=11,48454C4C4F2C574F524C44");	//����AT+NSORFָ��,��ȡ����

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//�����ɹ�����OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//����ʧ�ܷ���ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Brd_Nbiot_Rcv_Nmgr
* ����   : ͨ��COAP�ŵ���ȡ����
* ����   : ��
* ���   : newdata=1 ��ȡ�������ݣ� newdata=0�Ѿ�û��������
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ������Ȼ�����recv0_buf��û�ж�����������
********************************************************************/
unsigned char Brd_Nbiot_Rcv_Nmgr(unsigned char *newdata)
{
	unsigned short try_num = AT_NMGR_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();										//���uart1���ջ�����
	Mcu_UartSendAtCommand("AT+NMGR");								//����AT+NSORFָ��,��ȡ����

	do
    {
        delay_nms(2000);                                  //��ʱ50���룬�ڼ�ӵ����ص�'OK',�򷵻�ʣ���try_num
    	if( ('0' < recv0_buf[2]) && (recv0_buf[3] < '9') )			//������� ��һ����Ч����λ 0-9�ĳ�����Ϣ����ô������յ�����
    	{
    		*newdata = 1;
    		break;
    	}
    	else if( (recv0_buf[2] == 'O') && (recv0_buf[3] == 'K') )	//������� �س�+OK����û��������
    	{
    		*newdata = 0;
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)					//����ʧ�ܷ���ERROR
    	{
    		*newdata = 0;
    		try_num  = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Nbiot_Api_Open_Network
* ����   : ����Ƶ��ȷ��NBIOTģ��ע�ᵽ����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ȷ��ģ��ע�ᵽ������
********************************************************************/
unsigned char Nbiot_Api_Open_Network(void)
{
  unsigned short try_num = API_OPEN_REPEAT_NUMBER; 	//Ĭ�ϳ���3��
  unsigned char  status    = 0;
  unsigned char  autocnt   = 0;
  unsigned char  nband     = 0;
  unsigned char  i         = 0;

  do
  {
    //Ӳ����λNBIOTģ��-ͨ��AT+NRB��λ
    status = Brd_Nbiot_AT_Reset();
    if(status == 0)
      goto OPEN_ERROR;
    //ʹ��AT-OK����NBIOTģ��Ĵ����Ƿ�ͨ������
    status = Brd_Nbiot_Snd_AT();
    if(status == 0)
      goto OPEN_ERROR;
    //��ѯ�Ƿ��Զ�ע�����磬if-yes=��һ����if-no=����Ϊtrue + ����ģ��
    status = Brd_Nbiot_Get_Nconfig(&autocnt);
    if(status == 0)
      goto OPEN_ERROR;
    else
    {
      if(autocnt == 0)						//if-no=����Ϊtrue
      {
        status = Brd_Nbiot_Set_Nconfig();	//����Ϊ�ϵ��Զ�����
        if(status == 0)
          goto OPEN_ERROR;

          continue;							//����ģ��
      }
    }

    //��ѯ��ǰ��NCDP��Ϣ��if=���ò���=��һ����if!=���õĲ���= �����µ�NCDP + ����ģ��
    status = Brd_Nbiot_Set_Ncdp(CDP_SERVER_IP_PORT);
    if(status == 0)
      goto OPEN_ERROR;
    //��ѯ-�ȴ�NBIOTģ����ɶ�ȡSIM�ʹ���Ƶ����-ͨ��AT+CFUN?ָ���ȡ��if-fail=�����´�do-while��if-OK=��һ��
    status = Brd_Nbiot_Get_Cfun();
    if(status == 0)								//SIM��û��ʶ�𣬻���û�а�װSIM��
      goto OPEN_ERROR;
    //��ȡNBIOTģ����Ӫ������
    status = Brd_Nbiot_Get_Nband(&nband);
    if(status == 0)
      goto OPEN_ERROR;
    else
      msg->module_info.nband = nband;
    //��ȡNBIOTģ��Ĺ̼��汾��
    status = Brd_Nbiot_Get_Cgmr();
    if(status == 0)
      goto OPEN_ERROR;
    else	//��recv0_buf����ȡ�̼��汾��
    {
      for(i=0; i<18; i++)
        msg->module_info.cgmr[i] = recv0_buf[i+11];	//�������س�+SECURITY,���ؼ��֣��õ�V100R100C10B657SP2
    }
    //��ȡģ���IMEI����-ͨ��AT+CGSN=1ָ����
    status = Brd_Nbiot_Get_Cgsn();
    if(status == 0)
      goto OPEN_ERROR;

    //��ȡSIM����ICCID����-ͨ��AT+NCCIDָ����
    status = Brd_Nbiot_Get_Nccid();
    if(status == 0)
      goto OPEN_ERROR;
    else	//��recv0_buf����ȡSIM����ICCID��
    {
      for(i=0; i<20; i++)
        msg->module_info.nccid[i] = recv0_buf[i+9];	//�������س�+NCCID:���ؼ��֣��õ�89860317492039393960
    }

    //��ȡ��ǰNBIOT������ź�ǿ��-ͨ��AT+CSQָ����
    status = Brd_Nbiot_Get_Csq();
    if(status == 0)
      goto OPEN_ERROR;
    else	//��recv0_buf����ȡ�ź�ǿ��
    {
      if(recv0_buf[8] != ',')		//�ź�ǿ���п����Ǹ�λ��,+CSQ:14,99
      {
        msg->sensor_info.nbiot.csq[0] = recv0_buf[7];
        msg->sensor_info.nbiot.csq[1] = recv0_buf[8];
      }
      else
      {
        msg->sensor_info.nbiot.csq[0] = '0';
        msg->sensor_info.nbiot.csq[1] = recv0_buf[7];
      }
    }
    //��ѯ-�ȴ����ŵ�����-ͨ��AT+CGATT?ָ���ȡ��if-fail=�����´�do-while��if-OK=��һ��
    status = Brd_Nbiot_Get_Cgatt();
    if(status == 0)
      goto OPEN_ERROR;

    //��ѯ-�ȴ�ע�ᵽ����-ͨ��AT+CEGER?ָ���ȡ��if-fail=�����´�do-while��if-OK=��һ��
    status = Brd_Nbiot_Get_Cereg();
    if(status == 0)
      goto OPEN_ERROR;

    break;		//�ɹ�����������ã�����UDP�ŵ�

OPEN_ERROR:
    try_num--;
    
  }while(try_num);

  return try_num;  
}

/*******************************************************************
* ������ : Nbiot_Api_Close_Network
* ����   : ע��NBIOT���磬���ر���Ƶ����
* ����   : ��
* ���   : ��
* ����   : 0 : ʧ��   ���� ���ɹ�
* ע��   : ȷ��ģ�������͹���
********************************************************************/
unsigned char Nbiot_Api_Close_Network(void)
{
  unsigned char  status    = 0;
  unsigned short try_num = API_CLOSE_REPEAT_NUMBER; 	//Ĭ�ϳ���5��

  do
  {
    //�ر���Ƶ����-ͨ��AT+CFUN=0��������ʡ����
    status = Brd_Nbiot_Set_Cfun(0);
    if(status != 0)
      break;

  }while(--try_num);

    return try_num;
}

/*******************************************************************
* ������ : Nbiot_Api_Send_Message
* ����   : ͨ��NBIOTģ�鷢������
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   : ��
********************************************************************/
unsigned char Nbiot_Api_Send_Message()
{
  unsigned char  status    = 0;
  unsigned short try_num = API_SEND_REPEAT_NUMBER; 	//Ĭ�ϳ���5��

  char * chptr = (char *)(&msg_buffer);

  Hex2Str(chptr, send0_buf, sizeof(MessageStruct));	//hex ת���� string

  do
  {
    status = Brd_Nbiot_Snd_Nmgs(send0_buf, sizeof(MessageStruct));		//��������ݳ��ȣ���Ҫcoap��������=����AT+NMGSָ�������
    if(status != 0)
      break;
  }while(--try_num);

  return try_num;
}

/*******************************************************************
* ������ : Nbiot_Api_Recv_Message
* ����   : ͨ��NBIOTģ���������
* ����   : ��
* ���   : new=1�����յ������ݣ�new=0û�н��յ�����
* ����   : ��
* ע��   : ��
********************************************************************/
unsigned char Nbiot_Api_Recv_Message(unsigned char *new)
{
	unsigned char status  = 0;

	status = Brd_Nbiot_Rcv_Nmgr(new);	//if-��Ҫcoap��������=����AT+NMGRָ���������

    return status;
}

/*******************************************************************
* ������ : Nbiot_Api_Get_Csq
* ����   : ͨ��NBIOTģ���ȡ��ǰ�ź�ǿ��
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   : ��
********************************************************************/
unsigned char Nbiot_Api_Get_Csq(void)
{
	unsigned char status  = 0;

	status = Brd_Nbiot_Get_Csq();	//��ȡ��ǰNBIOT������ź�ǿ��-ͨ��AT+CSQָ����
	if(status != 0)					//��recv0_buf����ȡ��ǰʱ��
	{
		if(recv0_buf[8] != ',')		//�ź�ǿ���п����Ǹ�λ��,+CSQ:14,99
		{
			msg->sensor_info.nbiot.csq[0] = recv0_buf[7];
			msg->sensor_info.nbiot.csq[1] = recv0_buf[8];
		}
		else
		{
			msg->sensor_info.nbiot.csq[0] = '0';
			msg->sensor_info.nbiot.csq[1] = recv0_buf[7];
		}
	}

    return status;
}

/*******************************************************************************
* ������ : strnicmp
* ����   : �ַ��Ƚ�
* ����   :
* ���   :
* ����   :
* ע��   :
*******************************************************************************/
int strnicmp(const char *dst, const char *src, int count)
{
   char ch1, ch2;

   if(count != strlen(src))
	   return -1;

   do
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( --count && ch1 && (ch1 == ch2) );

   return (ch1 - ch2);
}

/*******************************************************************************
* ������ : itoi
* ����   : ����ת��Ϊ�ַ���
* ����   :
* ���   :
* ����   :
* ע��   :
*******************************************************************************/
void itoi(char *str, unsigned long num)
{
	char index[]="0123456789";
	char i = 0, j = 0;
    char temp;

    do
    {
        str[i++] = index[num%10];
        num /= 10;
    }while(num);

    str[i]='\0';

    for(j=0; j<=(i-1)/2; j++)
    {
        temp=str[j];
        str[j]=str[i-j-1];
        str[i-j-1]=temp;
    }
}

/*******************************************************************************
* ������ : itoc
* ����   : ��������ת��Ϊ�ַ�
* ����   : ichar����
* ���   :
* ����   : �ַ�
* ע��   :
*******************************************************************************/
char itoc(unsigned char ichar)
{
	char index[]="0123456789";

    return index[ichar%10];
}

/*******************************************************************************
* ������ : Hex2Str
* ����   : 16������ת�����ַ���������AT+NSOST����
* ����   : ����: pSrc - Դ����ָ��
* ���   : ���: pDst - Ŀ���ַ���ָ��
* ����   :
* ע��   : �磺{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01"
*******************************************************************************/
void Hex2Str(char* pSrc, char* pDst, unsigned int nSrcLength)
{
	int i = 0;
	const char tab[]="0123456789ABCDEF";	// 0x0-0xf���ַ����ұ�

	for (i = 0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];		// �����4λ
		*pDst++ = tab[*pSrc & 0x0f];	// �����4λ
		pSrc++;
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';
}

/*******************************************************************************
* ������ : AsciiToHex
* ����   : ASCALL��ת�����ַ�
* ����   : unsigned char cNum  ASC-II�ַ���
* ���   : unsigned char HEX��
* ����   :
* ע��   : �磺{'A'} --> 0xA
*******************************************************************************/
unsigned char AsciiToHex(unsigned char cNum)
{
	if(cNum>='0'&&cNum<='9')
	{
		cNum -= '0';
	}
	else if(cNum>='A'&&cNum<='F')
	{
		cNum -= 'A';
		cNum += 10;
	}
	else if(cNum>='a'&&cNum<='f')
	{
		cNum -= 'a';
		cNum += 10;
	}
	return cNum;
}

/*******************************************************************************
* ������ : StrToHex
* ����   : �ַ���ת��hex
* ����   : char *ptr�ַ��洢����unsigned short len���ݳ���
* ���   :
* ����   :
* ע��   : �磺"C8329BFD0E01" -->  {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
*******************************************************************************/
void StrToHex(char *ptr, unsigned short len)
{
	unsigned char n1  = 0;
	unsigned char n2  = 0;
	unsigned char num = 0;
	unsigned short i = 0;
	unsigned short index = 0;

	for(i=0; i<len; i++)
	{
		index = i << 1;				//index=i*2
		n1 = AsciiToHex(ptr[index]);
		n2 = AsciiToHex(ptr[index+1]);
		num = (n1<<4) + n2;
		ptr[i] = num;
	}
}
