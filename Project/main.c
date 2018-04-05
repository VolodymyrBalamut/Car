#include "Lib.h"
int step = 0;
int count = 0;
void TIM4_IRQHandler(void)
{
		
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			//KeyPress(GetKey());
			if(step == 0) EngineAllForward();
			if(step == 1) EngineAllBack();
			if(step == 2) EngineAllStop();
			
			//refresh
			if(++count == 5){ // 5 sec
				if(++step == 3){
					step = 0;
				}
				count = 0;
			}
		}
}

int main(void)
{
	Initialization();
	
	int i;
	
	while(1)
	{
		/*Delay(10000000);
		EngineAllStop();
		Delay(10000000);
		EngineAllForward();
		Delay(10000000);
		EngineAllBack();
		Delay(10000000);
		EngineRightForward();
		Delay(10000000);
		EngineLeftForward();
		Delay(10000000);
		EngineRightBack();
		Delay(10000000);
		EngineLeftBack();*/
		;
	}
}