#include "Lib.h"

void Delay(int D)
{
	for(int i = 0; i < D; i++);
}

void ResetAll()
{
	/*GPIO_ResetBits(GPIOB,
	GPIO_Pin_0 |
	GPIO_Pin_1 |
	GPIO_Pin_2 |
	GPIO_Pin_3 |
	GPIO_Pin_4 |
	GPIO_Pin_5 |
	GPIO_Pin_6 |
	GPIO_Pin_7);*/
	GPIO_ResetBits(GPIOB,
		GPIO_Pin_12 |
		GPIO_Pin_13 |
		GPIO_Pin_14 |
		GPIO_Pin_15);
	
}

void EngineRightForward(void){
	ResetAll();
  GPIO_SetBits(GPIOB, RightForward);
}
void EngineLeftForward(void){
	ResetAll();
  GPIO_SetBits(GPIOB, LeftForward);
}
void EngineRightBack(void){
	ResetAll();
  GPIO_SetBits(GPIOB, RightBack);
}
void EngineLeftBack(void){
	ResetAll();
  GPIO_SetBits(GPIOB, LeftBack);
}

void EngineAllForward(void){
	ResetAll();
  GPIO_SetBits(GPIOB, Forward);
}
void EngineAllBack(void){
	ResetAll();
  GPIO_SetBits(GPIOB, Back);
}
void EngineAllStop(void){
	ResetAll();
}

int GetKey(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
		return 1;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
		return 4;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
		return 7;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))
		return 10;
		
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
		return 2;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
		return 5;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
		return 8;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))
		return 0;
		
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
		return 3;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
		return 6;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
		return 9;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))
		return 11;
	
	return 101;
}

void KeyPress(int key)
{
	
    switch (key)
			{
        case ForwardKEY: 
            EngineAllForward();
            break;  
        case BackKEY: 
            EngineAllBack();
            break;
        case RightKEY: 
            EngineRightForward();
            break;
       case LeftKEY: 
            EngineLeftForward();
            break;
        case StopKEY: 
            EngineAllStop();
            break;
        default:
					EngineAllStop();
    }
}


void Initialization(void)
{
	GPIOInitialization();
	TimerInitialization();
}

void GPIOInitialization(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef Ports;
	
	/*GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_Out_PP;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
  Ports.GPIO_Pin = GPIO_Pin_12 |
										GPIO_Pin_13 |
										GPIO_Pin_14;
  GPIO_Init(GPIOB, &Ports);*/
	
	/*GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_IPU;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
  Ports.GPIO_Pin = GPIO_Pin_6 |
										GPIO_Pin_7 |
										GPIO_Pin_8 |
										GPIO_Pin_9;
  GPIO_Init(GPIOB, &Ports);*/
	
	GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_Out_PP;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
  Ports.GPIO_Pin = 	GPIO_Pin_12 |
	                  GPIO_Pin_13 |
										GPIO_Pin_14 |
										GPIO_Pin_15;
  GPIO_Init(GPIOB, &Ports);
}

void TimerInitialization(void)
{
	TIM_TimeBaseInitTypeDef TimerStructure;
	NVIC_InitTypeDef NVICStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		
	
	TimerStructure.TIM_CounterMode = TIM_CounterMode_Down;		
	TimerStructure.TIM_Prescaler = FrequencyDivider;				
	TimerStructure.TIM_Period = InterruptionPeriod;					
	TIM_TimeBaseInit(TIM4, &TimerStructure);								
	
	
	NVICStructure.NVIC_IRQChannel = TIM4_IRQn;							
	NVICStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVICStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVICStructure);															 
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);							
	TIM_Cmd(TIM4, ENABLE);																	
}

/*void TIM4_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			KeyPress(GetKey());
		}
}*/
