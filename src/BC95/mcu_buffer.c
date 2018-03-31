/*
 * buffer.c
 *
 *  Created on: 2016-8-15
 *      Author: user
 */

#include "common.h"

//uart0 ���ջ�����
char   recv0_buf[UART0_BUFFER_SIZE];
char * recv0_ptr=recv0_buf;
short  recv0_num;

//uart0 ���ͻ�����
char   send0_buf[UART0_BUFFER_SIZE];
char * send0_ptr;
short  send0_num;


/*******************************************************************
* ������ : Buffer_Uart0RecvClear
* ����   : ����UART0���ջ�����
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   : ��������СΪUART0_BUFFER_SIZE�ֽڣ��ͻ����޸�����
********************************************************************/
void Buffer_Uart0RecvClear(void)
{
	unsigned short i = 0;

	for(i=0; i<UART0_BUFFER_SIZE; i++)
	{
		recv0_buf[i] = 0x00;
	}

	recv0_ptr = recv0_buf;
	recv0_num = 0;
}

/*******************************************************************
* ������ : Buffer_Uart0SendClear
* ����   : ����UART0���ͻ�����
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   : ��������СΪUART0_BUFFER_SIZE�ֽڣ��ͻ����޸�����
********************************************************************/
void Buffer_Uart0SendClear(void)
{
	unsigned short i = 0;

	for(i=0; i<UART0_BUFFER_SIZE; i++)
	{
		send0_buf[i] = 0x00;
	}

	send0_ptr = send0_buf;
	send0_num = 0;
}
