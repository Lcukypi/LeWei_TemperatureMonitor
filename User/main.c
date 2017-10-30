/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   WF-ESP8266 WiFiģ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "test.h"
#include "bsp_dht11.h"
#include "./ds18b20/bsp_ds18b20.h"
#include "bsp_led.h" 
#include "./Beep/bsp_beep.h" 
 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main ( void )
{
	/* ��ʼ�� */
  USARTx_Config ();                                                              //��ʼ������1
	SysTick_Init ();                                                               //���� SysTick Ϊ 1ms �ж�һ�� 
	ESP8266_Init ();                                                               //��ʼ��WiFiģ��ʹ�õĽӿں�����
	DHT11_Init ();

	
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );                          //��ӡ����������ʾ��Ϣ
	
	printf("macBEEP_ON started\n");
	macBEEP_ON();
	printf("macBEEP_ON fineshed\n");
//	Delay_ms ( 2000 );
//	macBEEP_OFF();
//	Delay_ms ( 2000 );
	
	LED3_ON;
//	Delay_ms ( 2000 );

	
  ESP8266_StaTcpClient_UnvarnishTest ();
	
	
  while ( 1 );
	
	
}


/*********************************************END OF FILE**********************/
