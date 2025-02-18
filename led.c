// Utilisation Event UART en emission-reception

#define osObjectsPublic                     // define objects in main module
#include "Driver_SPI.h"
#include "Board_GLCD.h"                 // ::Board Support:Graphic LCD
#include "stm32f4xx_hal.h" 
#include "Board_LED.h"   
#include "cmsis_os.h"                   // CMSIS RTOS header file


extern ARM_DRIVER_SPI Driver_SPI1;

void configure_GPIO(void);


void mySPI_Thread (void const *argument);                             // thread function
osThreadId tid_mySPI_Thread;                                          // thread id
osThreadDef (mySPI_Thread, osPriorityNormal, 1, 0);                   // thread object
//void phare( uint32_t tab[]); 


//fonction de CB lancee si Event T ou R
void mySPI_callback(uint32_t event)
{
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osSignalSet(tid_mySPI_Thread, 0x01);
																							break;
		
		default : break;
	}
}

void Init_SPI(void){
	Driver_SPI1.Initialize(mySPI_callback);
	Driver_SPI1.PowerControl(ARM_POWER_FULL);
	Driver_SPI1.Control(ARM_SPI_MODE_MASTER | 
											ARM_SPI_CPOL1_CPHA1 |   // Choisir en fonction datasheet
//											ARM_SPI_MSB_LSB | 
											ARM_SPI_SS_MASTER_UNUSED |
											ARM_SPI_DATA_BITS(8), 1000000);
	Driver_SPI1.Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
}

int main (void){
	
	osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	// initialize peripherals here 
	
	Init_SPI();
	NVIC_SetPriority(SPI1_IRQn,2);
	LED_Initialize(); 
	tid_mySPI_Thread = osThreadCreate (osThread(mySPI_Thread), NULL);
	
	
	osKernelStart ();                         // start thread execution 
	
//	LED_On(1); 
//	LED_On(2);
//	LED_On(3);
//	LED_On(4);
	osDelay(osWaitForever);
	
}

void mySPI_Thread (void const *argument)
{
char tab[38]; // pour les phares
int nb_led  ; 
for(nb_led=0; nb_led<12; nb_led++)// create tab with for loop 
	{
		tab[1+nb_led*4]=0x33;
		tab[2+nb_led*4]=0x33;
		tab[3+nb_led*4]=0x33;
		tab[4+nb_led*4]=0x33;
//		tab[5+nb_led*4]=0xff;
//		tab[6+nb_led*4]=0xff;
//		tab[7+nb_led*4]=0xff;
//		tab[8+nb_led*4]=0xff;
		
	}
	
	while(1) {
	
	Driver_SPI1.Send(tab,38); 
	
	}
}
	


	
 


