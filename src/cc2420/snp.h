

#ifndef _SNP_H_
#define _SNP_H_

#include "types.h"

//============================================================================================//

//



//============================================================================================//

//
// ���ṹ����.
//
//APָ���ջ��� SENָ�����
// �ṹԪ�ؼ䲻���(PAD)�κ��ֽ����ڶ���.
#pragma pack(1)
typedef struct _SNP_PHR_t   //����6
{
	u8		ucSize;			// ������
	u8		uiFcf;			// FCF ��ϵͳ��־�����ڽ�����ǰ����־�������������ܵĸ���ϵͳ��ֵ�̶�Ϊ0x8a
                #define  FCF_DEF       0x8a
	u8		SlotNum;		//
	u8		uiType;			// ������(Packet type).
		#define	SNP_PACKET_TYPE_SYNC		( 1u )		// ͬ����.  (AP-->SEN)	
                #define DOWN_CODE_SYNC	                ( 2  )
		#define	SNP_PACKET_TYPE_SEN_CFG		( 3u )		// ���ð�.(AP-->SEN)
		#define	SNP_DOWN_CODE_MODE		( 7u )		// ���³����.(AP--SEN) 
                #define SNP_SEND_BUS_STATE               ( 5 )        //���ͻ�������test
                #define SNP_SET_ALL_PUMP                 ( 6 )         //����Ƶ��
                #define SNP_SIGNAL_STATE                 ( 4)        // �ź�ǿ��״̬��
                #define CONFIG_TO_DOWN_CODE_MODE         ( 8)           //�������س�������
                #define SEND_EVENT_MANUAL                (9u)         //�ֶ������¼�
                #define TEST_DEMO_MODE                   ( 10 )      //����ģʽ
                #define VALUE_CHANGED                    ( 11 )
                #define VALUE_CHANGED_ACK                ( 12 )
                #define SAME_TIME_QUERY_MODE             ( 13 )
        //******************************************************
                #define RELEVANCE_BUS_REQUEST            ( 14 ) //   ����������
                #define RELEVANCE_BUS_ACK                 (15)  //  �������ش���ϢAP--��sen
                #define SIGNAL_RELEVANCE                  (16)  //�ź���������
                #define SIGNAL_RELEVANCE_ACK              (17)  //�ź���������ACK
                #define STATE_VALUE_CHANGED               (18)  //״̬�仯��Ϣ�ϴ�                                      
                #define DEBUG_MESSAGE                     (19)  //DEBUG ��Ϣ�ϴ�
                #define DEBUG_MESSAGE_ACK                 (20)  //DEBUG /״̬�仯��Ϣ ACK
                #define STATE_ACK                         (28)  //״̬��Ack(����sen)//
                #define SNP_PACKET_QUERY                  (23)  //��λѯ�ʰ�
                #define SNP_PACKET_QUERY_ACK              (24)
                #define AP_COMAND                         (31)  //�ֳֿ���AP����
        //*********************************************************************************8
                #define	SNP_PACKET_TYPE_STATE		( 0x21 )	// ״̬��.(SEN-->AP) 
                #define SNP_PHR_TYPE_UP_LINE            ( 0x31 )       //�������߰�  ����λ�ţ�ʱ��������ã���SEN-->AP��
                #define SNP_TIMESLOT_UP_LINE            ( 0x3D )    //�������߰�����λ��,ʱ���δ���ã�SEN-->AP��   
                #define SNP_DOWN_CODE_UP_LINE            ( 0x35) 
		#define SNP_PACKET_TYPE_SEN_A		(0x65 )        // ͣ�����ģʽ������������ģʽ�� (SEN-->AP)��SEN����ͣ��ON��OFF��AP              
		#define SNP_PACKET_TYPE_UF_DATA		( 0xD2u )	// ����SEN���������.  (AP-->SEN)
		#define	SNP_PACKET_TYPE_UF_ACK		( 0xD3u )	// ����SEN���� ��SNP_PACKET_TYPE_UF_DATA��Ӧ��.    (SEN-->AP)    
                #define SNP_TIMESLOT_UPLINE_ACK          ( 0x81)  //    AP����SENʱ��۰� ��SNP_TIMESLOT_UP_LINE ��Ӧ��
                #define SNP_CFG_SEN_ACK                 ( 0x85 )  //   SEN��AP ���ð���Ӧ�𣬣�SEN-->AP��,��SNP_PACKET_TYPE_SEN_CFG��Ӧ��
                #define	SNP_PACKET_TYPE_AP_ACK		( 0x6Eu )	// APӦ���.   (AP-->SEN)����SNP_PACKET_TYPE_SEN_A���� ��Ӧ��
                #define AD_TEST_DEMO                    ( 0x91 )  //ADֵ���ͣ����ԣ�
                #define RF_TEST_SYNC                     (0x92)
                #define RF_TEST_ACK                      ( 0x93 )
                #define RF_ALL_SYNC                       (0x94)                               //(0x90--0xA0) //�ֳ��豸��APͨѶ����

        u16		 uiDevId;		// (ϵͳ���Ͷ�ID)           
} SNP_PHR_t; 
#pragma pack()



//AP����SEN����ռ��ͬ����ʱ�䣩  AP-->SEN  ��Ӧ SNP_PACKET_TYPE_SEN_CFG��
typedef struct _SNP_CFG_PACKET_t //����16
{
	SNP_PHR_t	sPhr;
        u8		AllTimeSlotNum;	// 1�������ڰ���С���ڸ�����1��С����Ϊ250ms��
        u8              Hour;      //ʱ
        u8              Minute;    //��
        u8              Second;     //�룬
        u8              Msec;   //����
        u8              TimeSlotNum;  //С���ڼ���ֵ
	u16		uiDestId;		// 	SEN�����뱾��IDƥ��ʱ, ִ��'uiCmd'���������.
	u16		uiCmd;			// ��������, ��4λΪ�����12λΪ����
		#define SNP_CMD_PUMP_bm			        ( 1u )		// ����ͨ���ţ�Ƶ�ʣ�
		#define SNP_CMD_SEN_RECAL			( 2u )		// /��λ	
                #define SNP_CMD_ENTER_UF                        (3u )          // ���س���                
                #define  SNP_CMD_SEND_BUS                        ( 5 )
                #define  SNP_CMD_SET_BASELINE                    (6) //���û�ֵ
                #define REST_COMMEND                              7
                #define SNP_SET_TIMESLOT                         (8) //����Ƶ��
                #define  SNP_BASELINE_GET                         (9)
                #define SET_SETBASE_X                             (10)  //���û�ֵX
                #define SER_SETBASE_Z                           (4u)   //���û�ֵZ
                #define SET_RF_POWER                             (11)
                #define SET_OFF_BASELINE                         (12)    
                #define SET_ID                                   (13)
                #define SET_NEW_PUMP                              (14) //���������
        u8              Parmet;
        u8              CheckNumLow; 
        u8              CheckNumHigh;
        
} SNP_CFG_PACKET_t;


typedef struct  _SNP_SET_PUMP_CFG_t
{
  SNP_PHR_t	  sPhr;
  u16             Pump;
  u16             SenID[8];
  u8              Reserved1;
  u8              CheckNumLow;
  u8              CheckNumHigh;
}SNP_SET_PUMP_CFG_t;
//APͬ����  AP-->SEN  //����SENУ׼ʱ�䣬������������  ��ӦSNP_PACKET_TYPE_SYNC��
typedef struct _SNP_SYNC_PACKET_t   //����21
{
	SNP_PHR_t	sPhr;
        u8		AllTimeSlotNum;	// ��ʱ��۸����������������������12�ı���
        u8              Hour;      //ʱ
        u8              Minute;    //��
        u8              Second;     //�룬
        u8              Msec;   //���붨��ֵ�� ֵΪ0,1,2,3��  0 ����0ms��1����250ms��2���� 500ms��3����750ms  
        u8              TimeSlotNum;  //��ǰʱ���
        u8              StartWorkTime;  //  SEN��ʼ������ʱ��(��λ Сʱ)
        u8              StopWorkTime;   //  SEN����������ʱ�䣨��λ Сʱ��
        u8              CfgBox;
        u8              SystemParameter[2];	//15 16λ
        u8              CheckNumLow;
        u8              CheckNumHigh;
} SNP_SYNC_PACKET_t;

//SEN Ӧ�������ӦSNP_CFG_SEN_ACK����
typedef struct _SNP_SEN_CFG_ACK_PACKET_t  //����8
{
  SNP_PHR_t	sPhr;
   u16		uiCmd;	  //AP���ð�������ش�
   u8           CheckNumLow;
   u8           CheckNumHigh;
}SNP_SEN_CFG_ACK_PACKET_t;


// APӦ����ṹ. ��Ӧ SNP_PACKET_TYPE_AP_ACK
typedef struct _SNP_AP_ACK_PACKET_t   //����14
{
        SNP_PHR_t	sPhr;  
	u16		SenID[5];		
        u8              CheckNumLow;
        u8              CheckNumHigh;
												
} SNP_AP_ACK_PACKET_t;

//******************************************************************************************************
//�����ID :a5 56   Ƶ�ʣ�6d 00

typedef struct _SNP_RELEVANCE_BUS_REQUEST_PACKET  //������������������  ��Ӧ���� RELEVANCE_BUS_REQUEST    �ѵ�ͨ  ������������� 77 a5 56 02 ff
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SNP_RELEVANCE_BUS_REQUEST_PACKET;

typedef struct _SNP_RELEVANCE_BUS_REQUEST_ACK_PACKET  //ap�ش����������������������� ACK�� ��Ӧ���� RELEVANCE_BUS_ACK
{
  SNP_PHR_t	sPhr;  
  u16           SenID;
  u8            Front; 
  u8            Behind;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SNP_RELEVANCE_BUS_REQUEST_ACK_PACKET;

typedef struct _SIGNAL_RELEVANCE_PACKET  // �ź��������������Ӧ���� SIGNAL_RELEVANCE
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SIGNAL_RELEVANCE_PACKET;

typedef struct _SIGNAL_RELEVANCE_ACK_PACKET  //�ź�����ACK��AP�ش�����Ӧ���� SIGNAL_RELEVANCE_ACK
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  int8          Rssi;
  int8          Snr;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SIGNAL_RELEVANCE_ACK_PACKET;

typedef struct  _STATE_VALUE_CHANGED_PACKET  // ״ֵ̬�ı��ϴ����� ��Ӧ���� STATE_VALUE_CHANGED   �ѵ�ͨ ������������� 66 a5 56 02 ff
{
   SNP_PHR_t	sPhr;  
   u16          AdValue;   //BIT15�� ON/OFF �¼�   0--14: ADֵ
   u8           Hour;      //ʱ
   u8           Minute;    //��
   u8           Second;     //��
   u8           Recived;
   u8           CheckNumLow;
   u8           CheckNumHigh;
}STATE_VALUE_CHANGED_PACKET;

typedef struct _DEBUG_MESSAGE_PACKET  //Debug ���ϴ��� ��Ӧ����  DEBUG_MESSAGE 
{
  SNP_PHR_t	sPhr;   
  u16           Value1;
  u16           Value2;
  u16           Value3;
  u16           Value4;
  u16           Value5; 
  u8           CheckNumLow;
  u8           CheckNumHigh;
}DEBUG_MESSAGE_PACKET;

typedef struct _DEBUG_MESSAGE_ACK_PACKET  // ״ֵ̬�ı� ��Debug ��Ack,  ��Ӧ���� DEBUG_MESSAGE_ACK
{
  SNP_PHR_t	sPhr;  
  u16           SenID; 
  u8            Type;  // Ϊ��������͵���Ӧ��־λ��STATE_VALUE_CHANGED �� DEBUG_MESSAGE
  u8            Recive;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}DEBUG_MESSAGE_ACK_PACKET;

typedef struct  _STATE_ACK_PACKET //STATE_ACK   ״̬��ACK������SEN��
{
  SNP_PHR_t	sPhr;
  u16           SenID; 
  u8            Recive1;
  u8            Recive2;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}STATE_ACK_PACKET;
//*********************************************************************************


typedef struct _SNP_TIME_QUERY_PACKET
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SNP_TIME_QUERY_PACKET;

typedef struct _SNP_AP_VALUE_ACK_PACKET  //16
{
  SNP_PHR_t	  sPhr;  
  u16             SenID;   
  u8              HourA;
  u8              MinuteA;
  u8              SecondA;
  u8              HourB;
  u8              MinuteB;
  u8              SecondB;
  u8              CheckNumLow;
  u8              CheckNumHigh;
}SNP_AP_VALUE_ACK_PACKET;


typedef struct _SNP_SIGNAL_STATE_PACKET_t
{
   SNP_PHR_t	sPhr;        //sPhr.uiType = 7  ������
   u16          BaselineZ;   //Z���ֵ
   u16          BaselineX;   //X���ֵ
   u8           DecZX;     //��ǰֵ���ֵ�� ��4λZ����4λX���
   u8           State;    // ״ֵ̬��AP�յ���״ֵ̬��ͬ��������
   u8           CheckNumLow;
   u8           CheckNumHigh;
}SNP_SIGNAL_STATE_PACKET_t;

// ״̬���� ���߰� �ṹ.  ��Ӧ SNP_PHR_TYPE_UP_LINE��SNP_TIMESLOT_UP_LINE��SNP_PACKET_TYPE_STATE��
typedef struct _SNP_UPLINE_PACKET_t  //����17
{
	SNP_PHR_t	sPhr;//ͬ��ͷ
        u8              PowerInt;    //��4λ��ص�ѹ����4λRF����
        u8              PowerFloat;
        u8              BaseChgNum;    //    
        u8              VersionLow;
        u8              VersionHigh;
        u8              CodeAdress;
        u16             AdValueZ;
        u16             AdValueX;
        u16             BaseZ;
        u16             BaseX;
        u16             ResendNum;
        u8              BaseAverageNum;
        u8              OnEventChgNum;
        u8              CheckNumLow;
        u8              CheckNumHigh;
} SNP_UPLINE_PACKET_t;

//�¼��� SEN-->AP ��Ӧ SNP_PACKET_TYPE_SEN_A ����λON��OFFʱ��SEN����״̬ʱ���AP
typedef struct _SNP_SEN_MODE_PACKET_t           //����16
{
	SNP_PHR_t	sPhr;   //6
        u8              Hour;      //ʱ
        u8              Minute;    //��
        u8              Second;     //�룬 ��BIT0--BIT6 Ϊ��ֵ��BIT7Ϊ��λON��OFF��־λ��BIT7=1 ΪON��BIT7=0 ΪOFF  
        u8              Day; //����
        u8              CheckNumLow;
        u8              CheckNumHigh;
} SNP_SEN_MODE_PACKET_t;

typedef struct _BUS_SEND_PACKET_t
{
  SNP_PHR_t	sPhr;
  u8            Day;
  u8            Hour;
  u8            Minute;
  u8            Second;
  u8            MaxDecZ;
  u8            MaxDecX;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}BUS_SEND_PACKET_t;


typedef struct _VALUE_CHG_PACKET_t
{
  SNP_PHR_t	sPhr;
  u8            Hour;
  u8            Minute;
  u8            Second;
  u8            temp;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}VALUE_CHG_PACKET_t;

typedef struct  _SNP_STATE_PACKET_t
{
  SNP_PHR_t	sPhr;  //��ͷ��ʾλΪ��0x21
  u8       VersionLow;
  u8       VersionHigh;
  u8       PowerInt;//  ��ص�ѹ
  u8       PowerFloat;
  u16      BaseLineZ;  //Z���ֵ
  u16      BaseLineX;  //X���ֵ
  u16      AdValueZ;  //Z�ᵱǰֵ
  u16      AdValueX;  //X�ᵱǰֵ
  u16      OnBaseLineZ; //Z��ONʱ��ʱ��ֵ
  u16      OnBaseLineX;//X��ONʱ��ʱ��ֵ
  u16      SendNum;   // �¼����ʹ���
  u16      ReSendNum;  //�¼��ش�����
  u8       BaseLineSaveNum;  //��ֵ�洢����
  u8       ReEventNum;   //����
  u8       CheckNumLow;
  u8       CheckNumHigh;
}SNP_STATE_PACKET_t;


typedef struct _SNP_UF_DOWN_CODE_PACKET_t  //��������
{
  SNP_PHR_t	sPhr;
  u16           SenID;
  u16           AllNum;
  u16           CurrentNum;
  u8            CodeData[32];
  u8       CheckNumLow;
  u8       CheckNumHigh;
}SNP_UF_DOWN_CODE_PACKET_t;


typedef struct _SNP_UF_ACK_PACKET_t  //�����ACK
{
	SNP_PHR_t	sPhr;
        u16      SavedBuffNum;
        u8       Type;
        u8       temp;
        u8       Data[32];
        u8       CheckNumLow;
        u8       CheckNumHigh;
} SNP_UF_ACK_PACKET_t;

typedef struct _AD_TEST_PACKET_t
{
  SNP_PHR_t	sPhr;
  u16           AdValueZ;
  u16           AdValueX;
  u8            PowerInt;
  u8            PowerFloat;
  u8            Rest;
  u8            recived;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}AD_TEST_PACKET_t;

typedef struct _RF_TEST_ACK_PACKET_t
{
  SNP_PHR_t	sPhr;
  int16         Snr;
  int16         Rssi;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}RF_TEST_ACK_PACKET_t;

#endif