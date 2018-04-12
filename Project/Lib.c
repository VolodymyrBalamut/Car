#include "Lib.h"
//unsigned  int TIM_Pulse = 10;
/*
void setPulse(int tim_Pulse){
	TIM_Pulse = tim_Pulse;
}
*/
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
	
	TIM4->CCR1 = 0;  
	TIM4->CCR2 = 0; 
	TIM4->CCR3 = 0;  
	TIM4->CCR4 = 0;
}

void EngineRightForward(int TIM_Pulse){
	ResetAll();
	TIM4->CCR3 = TIM_Pulse;
  GPIO_SetBits(GPIOB, RightForward);
}
void EngineLeftForward(int TIM_Pulse){
	ResetAll();
	TIM4->CCR2 = TIM_Pulse;
  GPIO_SetBits(GPIOB, LeftForward);
}
void EngineRightBack(int TIM_Pulse){
	ResetAll();
	TIM4->CCR4 = TIM_Pulse;
  GPIO_SetBits(GPIOB, RightBack);
}
void EngineLeftBack(int TIM_Pulse){
	ResetAll();
	TIM4->CCR1 = TIM_Pulse;
  GPIO_SetBits(GPIOB, LeftBack);
}

void EngineAllForward(int TIM_Pulse){
	ResetAll();
	TIM4->CCR2 = TIM_Pulse;
	TIM4->CCR3 = TIM_Pulse;
  GPIO_SetBits(GPIOB, Forward);
}
void EngineAllBack(int TIM_Pulse){
	ResetAll();
	TIM4->CCR1 = TIM_Pulse;
	TIM4->CCR4 = TIM_Pulse;
  GPIO_SetBits(GPIOB, Back);
}
void EngineAllStop(void){
	ResetAll();
}

int GetKey(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
		return 1;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
		return 4;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))
		return 7;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
		return 10;
		
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
		return 2;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
		return 5;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))
		return 8;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
		return 0;
		
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
		return 3;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
		return 6;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))
		return 9;
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
		return 11;
	
	return 101;
}

void KeyPress(int key)
{
	
    switch (key)
			{
        case ForwardKEY: 
            EngineAllForward(50);
            break;  
        case BackKEY: 
            EngineAllBack(50);
            break;
        case RightForwardKEY: 
            EngineRightForward(50);
            break;
       case LeftForwardKEY: 
            EngineLeftForward(50);
            break;
			 case RightBackKEY: 
            EngineRightBack(50);
            break;
       case LeftBackKEY: 
            EngineLeftBack(50);
            break;
       case StopKEY: 
            EngineAllStop();
            break;
       default:
				 break;
					//EngineAllStop();
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
	
	//keyboard out port
	GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_Out_PP;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
  Ports.GPIO_Pin = KeyboardOutPorts;
  GPIO_Init(GPIOA, &Ports);
	
	//keyboard input port
	GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_IPU;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
  Ports.GPIO_Pin = KeyboardInPorts;
  GPIO_Init(GPIOA, &Ports);
	
	//engine ports
	GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_Out_PP;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
  Ports.GPIO_Pin = 	EnginePorts;
  GPIO_Init(GPIOB, &Ports);
	
	//pwm ports
  GPIO_StructInit(&Ports);
	Ports.GPIO_Mode = GPIO_Mode_AF_PP;
	Ports.GPIO_Pin = PWMPorts;
	Ports.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &Ports);
}

void TimerInitialization(void)
{
	TIM_TimeBaseInitTypeDef TimerStructure;
	TIM_OCInitTypeDef TimerPWM;
	NVIC_InitTypeDef NVICStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	

	TIM_TimeBaseStructInit(&TimerStructure);
	TimerStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TimerStructure.TIM_Prescaler = Keyboard_TIM_Prescaler;
	TimerStructure.TIM_Period = Keyboard_TIM_Period;
	TIM_TimeBaseInit(TIM2, &TimerStructure);
	

	TIM_TimeBaseStructInit(&TimerStructure);
	TimerStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TimerStructure.TIM_Prescaler = Engine_TIM_Prescaler;
	TimerStructure.TIM_Period = Engine_TIM_Period;
	TIM_TimeBaseInit(TIM3, &TimerStructure);
	
	TIM_TimeBaseStructInit(&TimerStructure);
  TimerStructure.TIM_Prescaler = PWM_TIM_Prescaler;
  TimerStructure.TIM_Period = PWM_TIM_Period;
  TimerStructure.TIM_ClockDivision = 0;
  TimerStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TimerStructure);
	
	TIM_OCStructInit(&TimerPWM);
  TimerPWM.TIM_Pulse = PWM_TIM_Pulse;
  TimerPWM.TIM_OCMode = TIM_OCMode_PWM2;
  TimerPWM.TIM_OutputState = TIM_OutputState_Enable;
  TimerPWM.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC1Init(TIM4, &TimerPWM);
	
	TimerPWM.TIM_Pulse = PWM_TIM_Pulse / 2;
  TIM_OC2Init(TIM4, &TimerPWM);
	
  TimerPWM.TIM_Pulse = PWM_TIM_Pulse / 3;
  TIM_OC3Init(TIM4, &TimerPWM);
	
	TimerPWM.TIM_Pulse = PWM_TIM_Pulse / 4;
	TIM_OC4Init(TIM4, &TimerPWM);
	
	NVICStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVICStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStructure.NVIC_IRQChannelSubPriority = 1;
	NVICStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStructure);
	
	NVICStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVICStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStructure.NVIC_IRQChannelSubPriority = 1;
	NVICStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);												
}
