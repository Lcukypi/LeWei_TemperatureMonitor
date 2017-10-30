#include "test.h"
#include "bsp_esp8266.h"
#include "bsp_SysTick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "bsp_dht11.h"
#include "./ds18b20/bsp_ds18b20.h"
#include "bsp_led.h" 
#include "./Beep/bsp_beep.h"  

volatile uint8_t ucTcpClosedFlag = 0;
uint8_t uc, ucDs18b20Id [ 8 ];

/**
  * @brief  ESP8266 ��Sta Tcp Client��͸��
  * @param  ��
  * @retval ��
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{
	uint8_t ucStatus;
	
	char cStr [ 100 ] = { 0 };
	char cStr1 [ 200 ] = { 0 };
	char cStr2 [ 200 ] = { 0 };
	
	printf("\r\n this is a ds18b20 test demo \r\n");
	
	while( DS18B20_Init() )	
		printf("\r\n no ds18b20 exit \r\n");
	
	printf("\r\n ds18b20 exit \r\n");
	
	DS18B20_ReadId ( ucDs18b20Id  );           // ��ȡ DS18B20 �����к�
	
	printf("\r\nDS18B20�����к��ǣ� 0x");

	for ( uc = 0; uc < 8; uc ++ )             // ��ӡ DS18B20 �����к�
	 printf ( "%.2x", ucDs18b20Id [ uc ] );
	
  printf ( "\r\n�������� ESP8266 ......\r\n" );

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test ();
	
	ESP8266_Net_Mode_Choose ( STA );

  while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
	ESP8266_Enable_MultipleId ( DISABLE );
	
	while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
	while ( ! ESP8266_UnvarnishSend () );
	
	printf ( "\r\n���� ESP8266 ���\r\n" );
	
	
	while ( 1 )
	{		
		
		if(DS18B20_GetTemp_MatchRom ( ucDs18b20Id ))
		{
			sprintf ( cStr, "%.1f", DS18B20_GetTemp_MatchRom ( ucDs18b20Id ));
		}
		else
			sprintf ( cStr, "Read DHT11 ERROR!\r\n" );

		printf ( "\r\n��ȡ�����к��������¶ȣ� " );  
		printf ( "%s\n", cStr );                                             //��ӡ��ȡ DS18B20 ��ʪ����Ϣ

		sprintf ( cStr1, "{\"method\": \"update\",\"gatewayNo\": \"01\",\"userkey\": \"47f49923403b4b18aaf8836d5d54dc65\"}&^!" );
		sprintf ( cStr2, "{\"method\":\"upload\",\"data\":[{\"Name\":\"temperature\",\"Value\":\"%s\"}]}&^!", cStr );

		ESP8266_SendString ( ENABLE, cStr1, 84, Single_ID_0 );               //���� DS18B20 ��ʪ����Ϣ�������������
		Delay_ms ( 2000 );
		ESP8266_SendString ( ENABLE, cStr2, 70, Single_ID_0 );               //���� DS18B20 ��ʪ����Ϣ�������������
		Delay_ms ( 2000 );
		
		if ( ucTcpClosedFlag )                                             //����Ƿ�ʧȥ����
		{
			ESP8266_ExitUnvarnishSend ();                                    //�˳�͸��ģʽ
			
			do ucStatus = ESP8266_Get_LinkStatus ();                         //��ȡ����״̬
			while ( ! ucStatus );
			
			if ( ucStatus == 4 )                                             //ȷ��ʧȥ���Ӻ�����
			{
				printf ( "\r\n���������ȵ�ͷ����� ......\r\n" );
				
				while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
				
				while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
				
				printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );

			}
			
			while ( ! ESP8266_UnvarnishSend () );		
			
		}

	}
	
		
}


