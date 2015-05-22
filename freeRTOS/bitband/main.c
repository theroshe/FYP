
#include <FreeRTOS.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <semphr.h>
#include <partest.h>
#include <task.h>

#define TASK_COUNT 8
#define USE_SEMAPHORE 1

//Delay that all tasks wait for
#define DELAY 0.5 / portTICK_PERIOD_MS 
 
#define PRIORITY (tskIDLE_PRIORITY + 1)
#define LED_PRIORITY (tskIDLE_PRIORITY + 1)

//Set up bitband SRAM regions
#define BITBAND_SRAM_REF 0x20000000
#define BITBAND_SRAM_BASE 0x22000000

//Macro to convert SRAM address
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32+(b*4))) 

//Set up bitband peripheral regions
#define BITBAND_PERI_REF 0x40000000
#define BITBAND_PERI_BASE 0x42000000

//Macro to convert PERI address
//#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32+(b*4))) 

//STM32 GPIO registers
/*typedef struct
{
  __IO uint32_t CRL;  //Control registers
  __IO uint32_t CRH;
  __IO uint32_t IDR;  //Data in
  __IO uint32_t ODR;  //Data out
  __IO uint32_t BSRR; //Bit set
  __IO uint32_t BRR;  //Bit read
  __IO uint32_t LCKR; //Lock
  } GPIO_TypeDef; */

#define PORTE GPIOE_BASE + 0x0c //Add offset to ODR. 1400 to 17FF
#define PERI(a,b) *((volatile unsigned int*) peri(a,b)) //Wrapper for peri()
  
//Binary semaphore to protect PORTD (a critical resource)
static SemaphoreHandle_t sem;

//Function version of the BITBAND_PERI macro.
//Being able to convert the address at runtime is quite nice
unsigned int* peri(unsigned int port, unsigned int pin)
{
  return ((BITBAND_PERI_BASE + (port-BITBAND_PERI_REF)*32+(pin*4)));
}

//Toggles selected pin using bit banding
void bitBandToggle(void * pvParameters)
{
  unsigned int value = 0;  
  unsigned int pin = *((unsigned int*) pvParameters);
  
  for(;;) {
    PERI(PORTE, pin) = value;
    value = !value;
    vTaskDelay(DELAY+1); //Include extra tick that the other task waits for
  }
}

//Toggles selected pin using conventional bit masking
void conventionalToggle(void * pvParameters)
{
  unsigned int value = 0;
  unsigned int pin = *((unsigned int*) pvParameters);
  pin = 1 << (pin);
  volatile unsigned int* port = PORTE;

  for(;;) {
    //Attempt to take semaphore
    if(USE_SEMAPHORE != 1 || xSemaphoreTake(sem, 0) == pdTRUE) {

      //Toggle pin
      GPIO_WriteBit(GPIOE, pin, ((value != 0) ? Bit_SET : Bit_RESET)); 
      value = !value;

      //Alternative method
      //*port = value;
      //value ^= pin;
      
      vTaskDelay(DELAY);
    
      //Release semaphore
      xSemaphoreGive(sem);
    }
    vTaskDelay(1); //Needs to wait a bit, or one task will hog the semaphore
  }
}


void vGreenToggleTask()
{
  int i;
  
  for(;;) {
    vParTestToggleLED(0);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

/*void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
  ( void ) pxTask;
  ( void ) pcTaskName;
  
  for( ;; );
  }*/

int main(void) 
{
  unsigned int pins[16];
  int i = 0;

  GPIO_InitTypeDef GPIO_InitStructure;

  //Create binary semaphore and initialise it
  sem = xSemaphoreCreateBinary();
  xSemaphoreGive(sem);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  //Set up LEDs
  vParTestInitialise();

  for(i = 0; i < TASK_COUNT; i++) {
    pins[i] = i;
    
    //Pins 0 - 3 use bit banding, 4-7 use conventional IO
    if(i < 4)
      xTaskCreate(bitBandToggle, "toggle", 32, &pins[i], PRIORITY, NULL);
    else
      xTaskCreate(conventionalToggle, "toggle", 32, &pins[i], PRIORITY, NULL);
    
  }

  //xTaskCreate(vGreenToggleTask, "ToggleLED", 64, NULL, LED_PRIORITY, NULL);
  vParTestToggleLED(0);

  vTaskStartScheduler();

  for( ;; );

  return 0;
} 

#ifdef  USE_FULL_ASSERT 

/** 
  * @brief  Reports the name of the source file and the source line number 
  *         where the assert_param error has occurred. 
  * @param  file: pointer to the source file name 
  * @param  line: assert_param error line source number 
  * @retval None 
  */ 
void assert_failed(uint8_t* file, uint32_t line) 
{ 
  /* User can add his own implementation to report the file name and line number, 
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */ 

  /* Infinite loop */ 
  while (1) 
  { 
  } 
} 

#endif 

