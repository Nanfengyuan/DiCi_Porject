/*
 * buffer.h
 *
 *  Created on: 2016-8-15
 *      Author: user
 */

#ifndef MCU_BUFFER_H_
#define MCU_BUFFER_H_

#include "common.h"

//uart0 ���ջ�����
extern char   recv0_buf[UART0_BUFFER_SIZE];
extern char * recv0_ptr;
extern short  recv0_num;

//uart0 ���ͻ�����
extern char   send0_buf[UART0_BUFFER_SIZE];
extern char * send0_ptr;
extern short  send0_num;


/*******************************************************************
* ������ : Buffer_Uart0RecvClear
* ����   : ����UART0���ջ�����
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   : ��������СΪUART0_BUFFER_SIZE�ֽڣ��ͻ����޸�����
********************************************************************/
void Buffer_Uart0RecvClear(void);

/*******************************************************************
* ������ : Buffer_Uart0SendClear
* ����   : ����UART0���ͻ�����
* ����   : ��
* ���   : ��
* ����   : ��
* ע��   : ��������СΪUART0_BUFFER_SIZE�ֽڣ��ͻ����޸�����
********************************************************************/
void Buffer_Uart0SendClear(void);

#endif /* BUFFER_H_ */
