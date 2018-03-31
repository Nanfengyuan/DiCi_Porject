/*
 * common.h
 *
 *  Created on: 2016-8-29
 *      Author: user
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//#include <msp430.h>


//NBIOT���ݷ��ͷ�ʽ
#define  UDP_LOCAL_PORT "4567"
#define  UDP_SERVER_IP_PORT  	"114.115.144.122,4567"			//UDP:Զ�̷�����IP��ַ�Ͷ˿ں�
//#define  CDP_SERVER_IP_PORT  	"114.115.144.122,5683"			//COAP:Զ�̷�����IP��ַ�Ͷ˿ں�,˽�е�iot
//#define  CDP_SERVER_IP_PORT  	"180.101.147.115,5683"			//COAP:Զ�̷�����IP��ַ�Ͷ˿ںţ�����iot
#define  CDP_SERVER_IP_PORT  	"120.26.200.64"			//COAP:Զ�̷�����IP��ַ�Ͷ˿ںţ�����iot

//uart����buffer��С
#define  UART0_BUFFER_SIZE	512 	//���崦��NBIOTģ��ATָ����ջ������ͷ��ͻ������ĳ���
#define  UART1_BUFFER_SIZE	512  	//���崦��������õȽ��ջ������ͷ��ͻ������ĳ���

//��ص�ѹ�ɼ���Ϣ
#define  BATTERY_WAIT_TIME  		500000			//�ڲɼ���ѹ֮ǰ��Ҫ��ǰ�򿪷�ѹ��·��Ĭ��ʱ�䵥λΪuS
#define  BATTERY_THRESHOLD_UP  		2293			// (4.2v/3) / 2.5v * 4095 = 2293���൱��4.2V��Ӧ��ADֵΪ2293
#define  BATTERY_THRESHOLD_DOWN  	1692			// (3.1v/3) / 2.5v * 4095 = 1692���൱��3.1V��Ӧ��ADֵΪ1692�������ѹֵ��ʵ���������
#define  BATTERY_STEP_RANGE  	    (BATTERY_THRESHOLD_UP - BATTERY_THRESHOLD_DOWN)	// AD��Чֵ��Χ

//NBIOT��ز���
#define  API_OPEN_REPEAT_NUMBER  	3		//������Σ�ʧ��֮�� ͣ��N��ʱ��֮���������ԣ����������ڳ���-�ѵ磬Ҳ���ܽ�����һ��
#define  API_CLOSE_REPEAT_NUMBER  	3		//������Σ�ʧ��֮�� ͣ��N��ʱ��֮���������ԣ����������ڳ���-�ѵ磬Ҳ���ܽ�����һ��
#define  API_SEND_REPEAT_NUMBER  	3		//������Σ�ʧ��֮�� ͣ��N��ʱ��֮���������ԣ����������ڳ���-�ѵ磬Ҳ���ܽ�����һ��
#define  API_RECV_REPEAT_NUMBER  	3		//������Σ�ʧ��֮�� ͣ��N��ʱ��֮���������ԣ����������ڳ���-�ѵ磬Ҳ���ܽ�����һ��

//ʱ�����
#define  TIMER_REPEAT_NBIOT_REGISTER	3600 	//��λ�룺1Сʱ=60����x60��
#define  TIMER_REPEAT_NBIOT_RECV		3		//��λ�룺3
#define  COUNT_REPEAT_NBIOT_RECV		10		//���Զ�ȡ10�Σ����ʱ��ΪTIMER_REPEAT_RECV
#define  TIMER_KEY_PUSH_DELAY			10		//��λ�룺10,��������10��

//ATָ����ظ������Ĵ���(�̶�)
#define  NBIOT_RESET_DELAYTIME  	1000	//�ڲ���ATָ����ִ����ظ������Ĵ�����Ĭ��ʱ�� = (0.3S * N)S
#define  AT_DEFAULT_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NRB_REPEAT_NUMBER  		3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_AT_REPEAT_NUMBER  		3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_CCLK_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NCONFIG_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_CFUN_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_CSQ_REPEAT_NUMBER  		3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_CGATT_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_CEREG_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NSOCR_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NSOST_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NSORF_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NMGS_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���
#define  AT_NMGR_REPEAT_NUMBER  	3		//�ڲ���ATָ����ִ����ظ������Ĵ���

#endif /* COMMON_H_ */
