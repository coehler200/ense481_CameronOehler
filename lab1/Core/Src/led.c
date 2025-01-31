#include "led.h"
#include "main.h"

void led(){
	while(1){
		if(!HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin)){
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			HAL_Delay(50);
			while(!HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin));
		}
	}
}
