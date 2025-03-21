#include "gps.h"

void event_UART(uint32_t event)
{
	
	/* to do
	switch (event) {		
		
		case (ARM_USART_EVENT_SEND_COMPLETE | ARM_USART_EVENT_TX_COMPLETE) : 	osSignalSet(tid_Thread_T, 0x01);
																																					break;
		
		default : break;

	}*/
}

void UART3_Init(){
	Driver_USART3.Initialize(event_UART);
	Driver_USART3.PowerControl(ARM_POWER_FULL);
	Driver_USART3.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_EVEN		|
							ARM_USART_FLOW_CONTROL_NONE,
							9600);
	Driver_USART3.Control(ARM_USART_CONTROL_TX,1);
	
}
void gps_init(){
	
	UART3_Init();
	
}
void gps_getData(float *lat, float *lon, char *h, char *m, float *s){
		char trame[70];
		Driver_USART3.Receive(trame,70);			//recoit les 70 charactères qui nous intéressent
		sscanf(&trame[6], ",%2c,", h);
		sscanf(&trame[8], ",%2c,", m);
		sscanf(&trame[10], ",%6f,", s);
		printf("toto");
		
		if (trame[18] !=','){			//vérifie que le 19 e caractère n'est pas une virgule (et donc qu'on a une valeur)
			sscanf(&trame[18], ",%9f,", lat);

		}
		if (trame[30] !=','){			//vérifie que le 19 e caractère n'est pas une virgule (et donc qu'on a une valeur)
			sscanf(&trame[30], ",%10f,", lon);
		}
	
}