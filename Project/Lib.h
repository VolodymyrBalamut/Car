#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // GPIO
#include "stm32f10x_rcc.h"              // RCC
#include "stm32f10x_tim.h"              // TIM
#include "misc.h"						// Framework

#define FrequencyDivider 8000;				
#define InterruptionPeriod 1;				
#define OutputPorts GPIO_Pin_14;
#define InputPorts GPIO_Pin_12;

//keyboard
#define ForwardKEY 1
#define BackKEY 2
#define RightKEY 3
#define LeftKEY 4
#define StopKEY 5

//output
#define Forward  GPIO_Pin_13 |  GPIO_Pin_14
#define Back     GPIO_Pin_12 |  GPIO_Pin_15
#define LeftForward     GPIO_Pin_13
#define LeftBack     GPIO_Pin_12
#define RightForward    GPIO_Pin_14
#define RightBack   GPIO_Pin_15

void Delay(int);
void ResetAll();
int GetKey(void);
void KeyPress(int);
void Initialization(void);
void GPIOInitialization(void);
void TimerInitialization(void);

void EngineRightForward(void);
void EngineRightBack(void);
void EngineLeftForward(void);
void EngineLeftBack(void);
void EngineAllForward(void);
void EngineAllBack(void);
void EngineAllStop(void);