#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // GPIO
#include "stm32f10x_rcc.h"              // RCC
#include "stm32f10x_tim.h"              // TIM
#include "misc.h"						// Framework

#define FrequencyDivider 8000;				
#define InterruptionPeriod 1000;				//1 time per second
#define OutputPorts GPIO_Pin_14;
#define InputPorts GPIO_Pin_12;

//keyboard
#define ForwardKEY 1
#define BackKEY 2
#define RightForwardKEY 3
#define LeftForwardKEY 4
#define RightBackKEY 5
#define LeftBackKEY 6
#define StopKEY 7

//output
#define Forward  GPIO_Pin_13 |  GPIO_Pin_14
#define Back     GPIO_Pin_12 |  GPIO_Pin_15
#define LeftForward     GPIO_Pin_13
#define LeftBack     GPIO_Pin_12
#define RightForward    GPIO_Pin_14
#define RightBack   GPIO_Pin_15

//-- Ports --//
#define KeyboardOutPorts GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0
#define KeyboardInPorts GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3

#define PWMPorts GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6

#define EnginePorts GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_15


#define PWM_TIM_Prescaler 8000
#define PWM_TIM_Period 100
#define PWM_TIM_Pulse 100


#define Keyboard_TIM_Prescaler 8000
#define Keyboard_TIM_Period 20

#define Engine_TIM_Prescaler 40000
#define Engine_TIM_Period 1000

void Delay(int);
void ResetAll();
int GetKey(void);
void KeyPress(int);
void Initialization(void);
void GPIOInitialization(void);
void TimerInitialization(void);

void EngineRightForward(int TIM_Pulse);
void EngineRightBack(int TIM_Pulse);
void EngineLeftForward(int TIM_Pulse);
void EngineLeftBack(int TIM_Pulse);
void EngineAllForward(int TIM_Pulse);
void EngineAllBack(int TIM_Pulse);
void EngineAllStop(void);

void PWMUp(void);
void PWMDown(void);

//void setPulse(int tim_Pulse);
//extern unsigned  int TIM_Pulse1;