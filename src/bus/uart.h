#ifndef UART_H
#define UART_H

#define RECNUM 4

void UartInit();
void UartSendByte(u8 data);
void UartSendStrings(char *str);
void UartSendWByte(u16 data);
void UartSendNumber(u16 data);
void SplitNum(u16 temp,char *pbuf);
void UartSendNumberH(u16 data);
void SplitNumH(u16 temp,char *pbuf);
void UartSendNumberH8(u8 data);
void SplitNumH8(u8 temp,char *pbuf);
void Mcu_UartSendLR(void);
void Mcu_UartSendAtCommand(char *cmd);
void Mcu_UartSendDataWithLength(char *data, unsigned short len);


/*******************************************************************************
* ������ : strnicmp
* ����   : �ַ��Ƚ�
* ����   :
* ���   :
* ����   :
* ע��   :
*******************************************************************************/
int strnicmp(const char *dst, const char *src, int count);

/*******************************************************************************
* ������ : itoi
* ����   : ����ת��Ϊ�ַ���
* ����   :
* ���   :
* ����   :
* ע��   :
*******************************************************************************/
void itoi(char *str, unsigned long num);

/*******************************************************************************
* ������ : itoc
* ����   : ��������ת��Ϊ�ַ�
* ����   : ichar����
* ���   :
* ����   : �ַ�
* ע��   :
*******************************************************************************/
char itoc(unsigned char ichar);

/*******************************************************************************
* ������ : Hex2Str
* ����   : 16������ת�����ַ���������AT+NSOST����
* ����   : ����: pSrc - Դ����ָ��
* ���   : ���: pDst - Ŀ���ַ���ָ��
* ����   :
* ע��   : �磺{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01"
*******************************************************************************/
void Hex2Str(char* pSrc, char* pDst, unsigned int nSrcLength);

/*******************************************************************************
* ������ : AsciiToHex
* ����   : ASCALL��ת�����ַ�
* ����   : unsigned char cNum  ASC-II�ַ���
* ���   : unsigned char HEX��
* ����   :
* ע��   : �磺{'A'} --> 0xA
*******************************************************************************/
unsigned char AsciiToHex(unsigned char cNum);

/*******************************************************************************
* ������ : StrToHex
* ����   : �ַ���ת��hex
* ����   : char *ptr�ַ��洢����unsigned short len���ݳ���
* ���   :
* ����   :
* ע��   : �磺"C8329BFD0E01" -->  {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
*******************************************************************************/
void StrToHex(char *ptr, unsigned short len);


/***********************************************************************
 *
 * ���ڴ洢�豸��Ϣ���豸����Ĳ��������޸�
 *
 ***********************************************************************/
typedef struct _DeviceStruct
{
  char mftID[2];		//����ID�ţ�mftID[0]=��K��=0x4B mftID[1]=��X��=0x58
  char devID[2];		//����ID�ţ�devID[0]=��0��=0x30 devID[1]=��1��=0x31
  char hwdVer[2];		//��·��Ӳ���汾�ţ�hwdVer[0]=��0��=0x31 hwdVer[1]=��1��=0x34
  char sftVer[2];		//��������汾�ţ�sftVer[0]=��0��=0x31 sftVer[1]=��1��=0x34
}DeviceStruct;

/***********************************************************************
 *
 * ���ڴ洢NBIOTͨ��ģ�������Ϣ������������ʽ���ź�ǿ�ȵ�
 *
 ***********************************************************************/
typedef struct _ModuleStruct
{
  char cgmr[18];		//NBIOTģ��̼��汾�ţ�����V100R100C10B657SP2
  char nband;			//NBIOT��Ӫ�̣�nband=��5��=�й����ţ� nband=��8��=�й��ƶ����й���ͨ�� nband=��0��=����
  char nccid[20];		//SIM�����ţ�����89860316482018310474
}ModuleStruct;

/***********************************************************************
 *
 * ���ڴ洢������������Ϣ�������¶ȡ�ʪ�ȵ� //�������ӣ�ʪ�ȡ���γ��λ����Ϣ��������������
 *
 ***********************************************************************/
typedef struct _SensorStruct
{
	struct
	{
		char csq[2];		//NBIOT�����ź�ǿ�ȣ�����csq=��14��,�ֽ�Ϊcsq[0]='1',csq[1]='4'
	}nbiot;

	struct
	{
		char charge;			//USB����״̬��charge=��0��û������USB�ߣ�charge=��1���Ѿ�����USB��
		char battery_rate[3];	//��ص�����battery[0]=����λ�� ��battery[1]=��ʮλ������battery[3]=����λ��
	}battery;

    struct
    {
		char mark;				//�¶ȷ��ţ�'+' ���� '-'
    	char data[4];			//�洢�¶ȣ�[0]-[3]�洢�¶ȣ�����"23.5"��"10.5",����Ϊ0.1��
    }temp;

    struct
    {
    	char data[4];			//�洢�¶ȣ�[0]-[3]ʪ�Ȱٷֱȣ�����Ϊ1%��,����40.5%
    }humidity;



}SensorStruct;

/***********************************************************************
 *
 * ���ڴ洢�豸������Ϣ���豸����λ���������ֱ�ӵĽ���Э��
 *
 ***********************************************************************/
typedef struct _ParameterStruct
{
    struct
    {
    	char temperature_up[5];		//�¶�������ֵ������"+50.0"
    	char temperature_down[5];	//�¶�������ֵ������"-20.0"
    	char cycle_up[5];			//�����¶�������ֵʱ���¶��ϴ����ڣ�����"00010"��10�����ϴ�һ��
    	char cycle_middle[5];		//���¶ȿ��Ʒ�Χ֮�ڣ��¶��ϴ����ڣ�����"00020"��20�����ϴ�һ��
    	char cycle_down[5];			//�����¶�������ֵʱ���¶��ϴ����ڣ�����"00010"��10�����ϴ�һ��
    }temp;
}ParameterStruct;



/***********************************************************************
 *
 * ���ڴ洢NBIOT�շ���Ϣ���豸��IoTƽ̨�Ľ���Э��
 *
 ***********************************************************************/
typedef struct _MessageStruct
{
	char	index[4];		//��¼������Ϣ���������������㡰0000��-��9999��

	DeviceStruct	device_info;

	ModuleStruct	module_info;

	ParameterStruct	param_info;

	SensorStruct	sensor_info;

}MessageStruct;


extern MessageStruct 	msg_buffer;
extern MessageStruct 	*msg;


#endif