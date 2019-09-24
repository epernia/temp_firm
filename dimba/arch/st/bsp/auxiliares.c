#include "auxiliares.h"
#include "cubemx.h"


uint32_t
GPIO_ReadPin(uint32_t GPIO_Port, uint16_t GPIO_Pin)
{
	GPIO_TypeDef* GPIOx;

	 switch(GPIO_Port)
	 {
		 case GPIO_A:
			 GPIOx = GPIOA;
			 break;
		 case GPIO_B:
			 GPIOx = GPIOB;
			 break;
		 case GPIO_C:
			 GPIOx = GPIOC;
			 break;
		 case GPIO_D:
			 GPIOx = GPIOD;
			 break;
		 case GPIO_E:
			 GPIOx = GPIOE;
			 break;
		 case GPIO_F:
			 GPIOx = GPIOF;
			 break;
		 case GPIO_G:
			 GPIOx = GPIOG;
			 break;
		 case GPIO_H:
			 GPIOx = GPIOH;
			 break;
		 default:
			 break;
	 }

	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

void
GPIO_WritePin(uint32_t GPIO_Port, uint16_t GPIO_Pin, uint32_t Pin_State)
{
	GPIO_TypeDef* GPIOx;

	 switch(GPIO_Port)
	 {
		 case GPIO_A:
			 GPIOx = GPIOA;
			 break;
		 case GPIO_B:
			 GPIOx = GPIOB;
			 break;
		 case GPIO_C:
			 GPIOx = GPIOC;
			 break;
		 case GPIO_D:
			 GPIOx = GPIOD;
			 break;
		 case GPIO_E:
			 GPIOx = GPIOE;
			 break;
		 case GPIO_F:
			 GPIOx = GPIOF;
			 break;
		 case GPIO_G:
			 GPIOx = GPIOG;
			 break;
		 case GPIO_H:
			 GPIOx = GPIOH;
			 break;
		 default:
			 break;
	 }

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, Pin_State);
}

void
GPIO_TogglePin(uint32_t GPIO_Port, uint16_t GPIO_Pin)
{
	GPIO_TypeDef* GPIOx;

	 switch(GPIO_Port)
	 {
		 case GPIO_A:
			 GPIOx = GPIOA;
			 break;
		 case GPIO_B:
			 GPIOx = GPIOB;
			 break;
		 case GPIO_C:
			 GPIOx = GPIOC;
			 break;
		 case GPIO_D:
			 GPIOx = GPIOD;
			 break;
		 case GPIO_E:
			 GPIOx = GPIOE;
			 break;
		 case GPIO_F:
			 GPIOx = GPIOF;
			 break;
		 case GPIO_G:
			 GPIOx = GPIOG;
			 break;
		 case GPIO_H:
			 GPIOx = GPIOH;
			 break;
		 default:
			 break;
	 }

	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}

void
gpioConfig(uint32_t GPIO_Port, uint16_t GPIO_Pin, uint32_t Mode)
{
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	 GPIO_TypeDef* GPIOx;

	 switch(GPIO_Port)
	 {
		 case GPIO_A:
			 __HAL_RCC_GPIOA_CLK_ENABLE();
			 GPIOx = GPIOA;
			 break;
		 case GPIO_B:
			 __HAL_RCC_GPIOB_CLK_ENABLE();
			 GPIOx = GPIOB;
			 break;
		 case GPIO_C:
			 __HAL_RCC_GPIOC_CLK_ENABLE();
			 GPIOx = GPIOC;
			 break;
		 case GPIO_D:
			 __HAL_RCC_GPIOD_CLK_ENABLE();
			 GPIOx = GPIOD;
			 break;
		 case GPIO_E:
			 __HAL_RCC_GPIOE_CLK_ENABLE();
			 GPIOx = GPIOE;
			 break;
		 case GPIO_F:
			 __HAL_RCC_GPIOF_CLK_ENABLE();
			 GPIOx = GPIOF;
			 break;
		 case GPIO_G:
			 __HAL_RCC_GPIOG_CLK_ENABLE();
			 GPIOx = GPIOG;
			 break;
		 case GPIO_H:
			 __HAL_RCC_GPIOH_CLK_ENABLE();
			 GPIOx = GPIOH;
			 break;
		 default:
			 break;
	 }
		
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins :  */
	GPIO_InitStruct.Pin  = GPIO_Pin;
	GPIO_InitStruct.Mode = Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	if(Mode != GPIO_MODE_INPUT)
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
