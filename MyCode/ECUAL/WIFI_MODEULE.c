/*
 * WIFI_MODEULE.c
 *
 * Created: 1/19/2022 2:30:25 PM
 *  Author: ahmed
 */ 
#include "WIFI_MODULE.h"


	uint8 wifi_Test[100] = "AT\r\n";
	uint8 wifi_Rst[100] = "AT+RST\r\n";
	uint8 wifi_information[100] = "AT+GMR\r\n";
	uint8 wifi_Enable_Echo[100] = "ATE1\r\n";
	uint8 wifi_Disable_Echo[100] = "ATE0\r\n";
	uint8 wifi_Networks_List[100] = "AT+CWLAP\r\n";
	uint8 wifi_Mode_client[100] = "AT+CWMODE=1\r\n";
	uint8 wifi_Mode_server[100] = "AT+CWMODE=2\r\n";
	uint8 wifi_Mode_client_server[100] = "AT+CWMODE=3\r\n";
	uint8 wifi_Transmission_Mode[100] = "AT+CIPMODE=0\r\n";
	uint8 wifi_Connect_Network[100] = "AT+CWJAP_DEF=\"psa2020\",\"rabbitelg@zma3030\"\r\n";
	uint8 wifi_Open_Socket[100] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";
	uint8 wifi_send_length[100] = "AT+CIPSEND=48";
	uint8 wifi_update[100] = "GET /update?api_key=O07F2RY16Y73FVMM&field1=70";

