#include "Lib.h"
int TIM_Pulse = 10;

void TIM2_IRQHandler(void)
{
		
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			KeyPress(GetKey());
		}
}
int step = 0;
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			if(step == 0) EngineAllForward(TIM_Pulse);
			if(step == 1) EngineAllBack(TIM_Pulse);
			if(step == 2) EngineAllStop();
			if(step == 3) EngineRightForward(TIM_Pulse);
			if(step == 4) EngineLeftForward(TIM_Pulse);
			if(step == 5) EngineRightBack(TIM_Pulse);
			if(step == 6) EngineLeftBack(TIM_Pulse);
			if(++step == 7) step = 0;
		if (TIM_Pulse < PWM_TIM_Period) TIM_Pulse+=10;
		else TIM_Pulse = 1;
	}
}

int main(void)
{
	Initialization();
	
	
	while(1)
	{
    /*if (TIM_Pulse < PWM_TIM_Period) TIM_Pulse++;
		else TIM_Pulse = 1;
	  Delay(1000000); */
	}
}