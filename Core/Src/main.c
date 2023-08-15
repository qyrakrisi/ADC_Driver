////////////////////////////////////////////////////////
  #include "stm32f407xx.h"
  #include <stdio.h>
  #include <stdint.h>


#define GPIOAEN      (1U << 0)
#define ADC1EN        (1U << 8)


uint32_t vlera_sensorit;


int  main(void)
{
		HAL_Init();

		RCC->AHB1ENR |=GPIOAEN;


		//analog mode pin 1 PA1
	    GPIOA->MODER |= (1U << 2);
	    GPIOA->MODER |= (1U << 3);

		RCC->APB2ENR |=ADC1EN;

		ADC1->SQR3 |= (1U << 0);


		ADC1->SQR1 &=~(1U << 20);
		ADC1->SQR1 &=~(1U << 21);
		ADC1->SQR1 &=~(1U << 22);
		ADC1->SQR1 &=~(1U << 23);


		ADC1->CR2 |=(1U << 0);



	while(1)
	{
		ADC1->CR2 |= (1U << 30);//start the conversion of regular channels.


		while(!(ADC1->SR &(1U << 1))){}

		vlera_sensorit = ADC1->DR;
		HAL_Delay(1);

	}
}
