/* module banner */

#include <FreeRTOS.h>
#include <stm32f10x.h>
#include <partest.h>
#include <task.h>

#define mainGREEN_LED_TOGGLE (tskIDLE_PRIORITY + 1)
#define mainORANGE_LED_TOGGLE (tskIDLE_PRIORITY + 1) 

void vGreenToggleTask(void *pvParameters)
{
  int i;

  for(;;)
  {
    vParTestToggleLED(0);
    vTaskDelay( 3000 / portTICK_PERIOD_MS );
  }
}

void vOrangeToggleTask(void *pvParameters)
{
  for(;;)
  {
    vParTestToggleLED(1);
    vTaskDelay( 3000 / portTICK_PERIOD_MS );
  }
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	/* This function will get called if a task overflows its stack.   If the
	parameters are corrupt then inspect pxCurrentTCB to find which was the
	offending task. */

	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}

int main(void) 
{   
  vParTestInitialise(); 
  xTaskCreate( vGreenToggleTask, "GreenLedToggle", 128, NULL, mainGREEN_LED_TOGGLE, NULL );
  xTaskCreate( vOrangeToggleTask, "OrangeLedToggle", 128, NULL, mainORANGE_LED_TOGGLE, NULL );
  
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

