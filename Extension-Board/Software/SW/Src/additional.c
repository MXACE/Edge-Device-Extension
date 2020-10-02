#include "main.h"
#include "additional.h"
#include "COM.h"

char Relay(char set, char state, char pos)
{
	static char Relays[6] = {0,0,0,0,0,0};
	{
		if(set)
		{
			Relays[pos] = state;
			switch(pos)
			{
				case 1:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, state);
					break;
				
				case 2:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, state);
					break;
				
				case 3:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, state);
					break;
				
				case 4:
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, state);
					break;
				
				case 5:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, state);
					break;
				
				case 6:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state);
					break;
			}
			return 0;
		}
		else
		{
			return Relays[pos];
		}
	}
}

char Led(char set, char state, char pos)
{
	static char Leds[8] = {0,0,0,0,0,0,0,0};
	{
		if(set)
		{
			Leds[pos] = state;
			switch(pos)
			{
				case 1:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, state);
					break;
				
				case 2:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, state);
					break;
				
				case 3:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, state);
					break;
				
				case 4:
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, state);
					break;
				
				case 5:
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, state);
					break;
				
				case 6:
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state);
					break;
				
				case 7:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, state);
					break;
				
				case 8:
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, state);
					break;
				
			}
			return 0;
		}
		else
		{
			return Leds[pos];
		}
	}
}

#define GREEN GPIO_PIN_12
#define RED GPIO_PIN_11
#define BLUE GPIO_PIN_8

char RGB(char set, char colors)
{
	static char RGBBuffer = 0;
	
	if(set)
	{
		RGBBuffer = colors;
		switch(colors)
		{
			case 0:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_RESET);
				break;
			
			case 1:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_SET);
				break;
			
			case 2:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_RESET);
				break;
			
			case 3:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_SET);
				break;
			
			case 4:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_RESET);
				break;
			
			case 5:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_SET);
				break;
			
			case 6:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_RESET);
				break;
			
			case 7:
				HAL_GPIO_WritePin(GPIOA, RED, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, BLUE, GPIO_PIN_SET);
				break;
		}
		return 0;
	}
	else
	{
		return RGBBuffer;
	}
}

void seg_reset(void);

void init_seg(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //LD
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); //PH
}


void seg(volatile char t, volatile char h, volatile char z, volatile char e, volatile char pointPos, volatile char doppelpunkt, volatile char apostroph)
{
	//seg_reset();
	
	//DIG 1, 1000   ------------------------------------------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET); //DIG 1
	//A-D
	if(t & 0x01)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); //A
	}
	if(t & 0x02)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); //B
	}
	if(t & 0x04)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); //C
	}
	if(t & 0x08)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); //D
	}
	if(pointPos == 4)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //DP
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); //DIG 1
	seg_reset();
	
	//DIG 2, 100   ------------------------------------------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); //DIG 2
	//A-D
	if(h & 0x01)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); //A
	}
	if(h & 0x02)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); //B
	}
	if(h & 0x04)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); //C
	}
	if(h & 0x08)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); //D
	}
	if(pointPos == 3)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //DP
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); //DIG 2
	seg_reset();
	
	//DIG 3, 10   ------------------------------------------------------------------
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET); //DIG 3
	//A-D
	if(z & 0x01)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); //A
	}
	if(z & 0x02)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); //B
	}
	if(z & 0x04)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); //C
	}
	if(z & 0x08)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); //D
	}
	if(pointPos == 2)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //DP
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET); //DIG 3
	seg_reset();
	
	//DIG 4, 1   ------------------------------------------------------------------
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); //DIG 1
	//A-D
	if(e & 0x01)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); //A
	}
	if(e & 0x02)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); //B
	}
	if(e & 0x04)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); //C
	}
	if(e & 0x08)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); //D
	}
	if(pointPos == 1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); //DP
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); //DIG 1
	seg_reset();
	
	if(doppelpunkt)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //doppelpunkt
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //doppelpunkt
	}
	if(apostroph)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //apostroph
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //apostroph
	}
	
}

void seg_reset()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); //A
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); //B
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); //C
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); //D
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DP
}

void UseSeg(char set, char t, char h, char z, char e, char pointPos, char doppelpunkt, char apostroph)
{
	static char st = 0,sh = 0,sz = 0,se = 0, spointPos = 0, sdoppelpunkt = 0, sapostroph = 0;
	if(set)
	{
		st = t;
		sh = h;
		sz = z; 
		se = e;
		spointPos = pointPos;
		sdoppelpunkt = doppelpunkt;
		sapostroph = apostroph;
	}
	else
	{
		seg(st, sh, sz, se, spointPos, sdoppelpunkt, sapostroph);
	}
}

void button()
{
	static char OldState[3] = {0,0,0};
	volatile char ButtonPressed[3] = {0,0,0};	
	char ButtonChanged[3] = {0,0,0};	
		
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))  // BUTTON 1
	{
		ButtonPressed[0] = 1;
	}
	else
	{
		ButtonPressed[0] = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5))	// BUTTON 2
	{
		ButtonPressed[1] = 1;
	}
	else
	{
		ButtonPressed[1] = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4))	// BUTTON 3
	{
		ButtonPressed[2] = 1;
	}
	else
	{
		ButtonPressed[2] = 0;
	}
	
	//Buttons Changed
	char i = 0;
	for(i = 0; i != 3; i++)
	{
		if(ButtonPressed[i] != OldState[i])
		{
			ButtonChanged[i] = 1;
		}
		else
		{
			ButtonChanged[i] = 0;
		}
	}
	
	//Save new button state
	for(i = 0; i != 3; i++)
	{
		OldState[i] = ButtonPressed[i];
	}
	
	if(ButtonPressed[0] && ButtonChanged[0])
	{
		RS_TX("BUTTON1;");
	}
	if(ButtonPressed[1] && ButtonChanged[1])
	{
		RS_TX("BUTTON2;");
	}
	if(ButtonPressed[2] && ButtonChanged[2])
	{
		RS_TX("BUTTON3;");
	}
}

void localtemp(uint32_t *temp, char set/*, char showtoseg*/)
{
	static unsigned int Counter = 0;
	static char ConnenctToSeg = 0;
	static uint32_t LastValues = 0;
	
	static char FirstTime = 1;
	
	float Calctemp = 0;
	char temparea = 0;
	float CelsiusKO = 0;
	
	/*if(set)
	{
		ConnenctToSeg = showtoseg;
	}
	else
	{*/
	
		if(FirstTime)
		{
			LastValues = temp[0];
			
			FirstTime = 0;
		}
		else
		{
			LastValues = (LastValues + temp[0])/2;
			
		}
		if(Counter >= 10000)
		{
			Counter = 0;
			//FirstTime = 1;
			
			if(LastValues >= 2817 && LastValues <= 3700) //0-25	
			{
				temparea = 1;
			}
			else if(LastValues >= 1663 && LastValues <= 2816) //25-50
			{
				temparea = 2;
			}
			else if(LastValues >= 819 && LastValues <= 1662) //50-75
			{
				temparea = 3;
			}
			else if(LastValues <= 818) //75-100
			{
				temparea = 4;
			}
			else
			{
				//RS_TX("TEMP ERROR");
			}
			
			switch(temparea)
			{
				case 1: 
					CelsiusKO = 0.0283;
					Calctemp = (3700 - LastValues)*CelsiusKO;
					break;
				
				case 2:
					CelsiusKO = 0.02168;
					Calctemp = (2816 - LastValues)*CelsiusKO + 25;
					break;
				
				case 3:
					CelsiusKO = 0.0296;
					Calctemp = (1662 - LastValues)*CelsiusKO + 50;
					break;
				case 4:
					CelsiusKO = 0.03056;
					Calctemp = (818 - LastValues)*CelsiusKO + 75;
					break;
			}
			
			long int iTemp = Calctemp * 1000;
			if(iTemp > 10000)
			{
				iTemp /= 10;
			}
				
			SendTemp(1,iTemp);
			
			/*if(ConnenctToSeg)
			{
				char newTemp[4] = {iTemp/1000%10,iTemp/100%10,iTemp/10%10,iTemp%10};
				UseSeg(1,newTemp[0],newTemp[1],newTemp[2],newTemp[3],3,0,0);
			}*/
		}
		else
		{
			Counter++;
		}
	//}
}

void SendTemp(char set, int iTemp)
{
	static char newTemp[10] = {'t','e','m','p','.',0,0,0,0,';'};
	
	if(set)
	{
		newTemp[5] = iTemp/1000%10+48;
		newTemp[6] = iTemp/100%10+48;
		newTemp[7] = iTemp/10%10+48;
		newTemp[8] = iTemp%10+48;
		//newTemp[4] = ';';
	}
	else
	{
		RS_TX(newTemp);
	}
}
