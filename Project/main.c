#include "Lib.h"
int main(void)
{
	Initialization();
	
	int i;
	
	while(1)
	{
		Delay(10000000);
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
		EngineLeftBack();
	}
}