#include "main.h"
#include "CMDHandler.h"
#include "COM.h"
#include "additional.h"

void CH_BUFFER(char alpha[1],char uart)
{
	char chooseuart = ((uart==6? 2:1)-1);
	static char BUFFER[50][2];
	char StringToSend[50];
	static uint8_t BufPos = 0;
	uint8_t CMDdone = 0;
	
	if(alpha[0] == ';')
	{
		BUFFER[BufPos][chooseuart] = '\0';
		CMDdone = 1;
	}
	else
	{
		BUFFER[BufPos][chooseuart] = alpha[0];
		
		BufPos++;
	}
	
	if(CMDdone)
	{
		char i;
		for(i = 0; i!= 50; i++)
		{
			StringToSend[i] = BUFFER[i][chooseuart]; 
		}
		
		CH_HANDLER(1,StringToSend,chooseuart);
		BufPos = 0;
		
		
		for(i = 0; i!= 50; i++)
		{
			BUFFER[i][chooseuart] = 0;
		}
	}
}

void CH_HANDLER(char set, char string[], char uart)
{
	static uint8_t rdy[2] = {0,0};
	static char COM_BUFFER[50];
	
	static char RS_setget[3]; //s e t . l e d . 1 . 1
	static char RS_what[50];		//0 1 2 . 4 5 6 . 8 . 10 11
	static char RS_add[4][50];
	int i = 0, ia = 0, ib = 0, ic = 0, id = 0, ie = 0;
	static char segValueEnd = 0;
	if(set)
	{
		switch(uart)
		{
			case 0:
				
				for(i = i; string[i] != '.' && string[i] != '\0' ; i++)
				{
					RS_setget[i] = string[i];
					
				}
				i++;
				
				for(i = i; string[i] != '.' && string[i] != '\0' ; i++)
				{
					RS_what[ia] = string[i];
					ia++;
				}
				i++;
				segValueEnd = i;
				for(i = i; string[i] != '.' && string[i] != '\0' ; i++)
				{
					RS_add[0][ib] = string[i];
					ib++;
				}
				segValueEnd = i - segValueEnd;
				i++;
				
				for(i = i; string[i] != '.' && string[i] != '\0' ; i++)
				{
					RS_add[1][ic] = string[i];
					ic++;
				}
				i++;
				
				for(i = i; string[i] != '.' && string[i] != '\0' ; i++)
				{
					RS_add[2][id] = string[i];
					id++;
				}
				i++;
				
				for(i = i; string[i] != '.' && string[i] != '\0' ; i++)
				{
					RS_add[3][ie] = string[i];
					ie++;
				}
				
				
				rdy[0] = 1;
			
				/*COM_TX("[COM RX]: ");
				COM_TX(string);
				COM_TX("\r\n");*/
				break;
			
			case 1:
				strcpy(COM_BUFFER, string);
				rdy[1] = 1;
				break;
		}
		for(i=0; i!=sizeof(*string); i++)
		{
			string[i] = 0;
		}
	}
	else
	{
		//RS
		if(rdy[0])
		{
			rdy[0] = 0;
			if(!(strcmp(RS_setget, "rdy")))
			{
				__nop();
			}
			if(!(strcmp(RS_setget, "BUTTON1")))
			{
				__nop();
			}
			if(!(strcmp(RS_setget, "BUTTON2")))
			{
				__nop();
			}
			if(!(strcmp(RS_setget, "BUTTON3")))
			{
				__nop();
			}
			if(!(strcmp(RS_what, "relay")))					//WHAT
			{
				char pos = RS_add[0][0] - 48;					//POS add0
				if(!(strcmp(RS_setget, "set"))) 									//SET
				{
					
					char state = RS_add[1][0] - 48;											//STATE add1
					Relay(1, state, pos);
				}
				else if(!(strcmp(RS_setget, "get"))) 							//GET
				{
					char ret[] = {'r','e','l','a','y','-',pos+48,'-',0,';'};
					ret[8] = (Relay(0,0,pos))+48;
					RS_TX(ret);
				}
			}
			if(!(strcmp(RS_what, "led")))						//WHAT
			{
				char pos = RS_add[0][0] - 48;					//POS add0
				if(!(strcmp(RS_setget, "set"))) 									//SET
				{
					
					char state = RS_add[1][0] - 48;											//STATE add1
					Led(1, state, pos);
				}
				else if(!(strcmp(RS_setget, "get"))) 							//GET
				{
					char ret[8] = {'l','e','d','-',pos+48,'-',0,';'};
					ret[6] = (Led(0,0,pos))+48;
					RS_TX(ret);
				}
			}
			if(!(strcmp(RS_what, "rgb")))						//WHAT
			{
				if(!(strcmp(RS_setget, "set"))) 								//SET
				{
					char rgbvalue = RS_add[0][0]-48;										//POS add0
					RGB(1,rgbvalue);
				}
				else if(!(strcmp(RS_setget, "get")))						//GET
				{
					char ret[6] = {'r','g','b','-',0,';'};
					ret[4] = (RGB(0,0))+48;
					RS_TX(ret);
				}
			}
			if(!(strcmp(RS_what, "segment")))				//WHAT
			{
				if(!(strcmp(RS_setget, "set")))									//SET
				{
					char SegData[4] = {RS_add[0][0]-48,RS_add[0][1]-48,RS_add[0][2]-48,RS_add[0][3]-48};
					switch(segValueEnd)
					{
						case 1:
							UseSeg(1,0,0,0,SegData[0],RS_add[1][0]-48,RS_add[2][0]-48,RS_add[3][0]-48);
							break;
						case 2:
							UseSeg(1,0,0,SegData[0],SegData[1],RS_add[1][0]-48,RS_add[2][0]-48,RS_add[3][0]-48);
							break;
						case 3:
							UseSeg(1,0,SegData[0],SegData[1],SegData[2],RS_add[1][0]-48,RS_add[2][0]-48,RS_add[3][0]-48);
							break;
						case 4:
							UseSeg(1,SegData[0],SegData[1],SegData[2],SegData[3],RS_add[1][0]-48,RS_add[2][0]-48,RS_add[3][0]-48);
							break;
					}
					
					//UseSeg(1,SegData[0],SegData[1],SegData[2],SegData[3],RS_add[1][0]-48,RS_add[2][0]-48,RS_add[3][0]-48);
				}
			}
			if(!(strcmp(RS_what, "temp")))				//WHAT
			{
				if(!(strcmp(RS_setget, "get")))									//SET
				{
					SendTemp(0,0);
				}
			}
			if(!(strcmp(RS_what, "showTemp")))				//WHAT
			{
				if(!(strcmp(RS_setget, "set")))									//SET
				{
					char status = RS_add[0][0]-48;										//POS add0
					localtemp(0,1/*,status*/);
					if(!status)
					{
						UseSeg(1,0,0,0,0,0,0,0);
					}
				}
			}
			if(!(strcmp(RS_what, "uart")))				//WHAT
			{
				if(!(strcmp(RS_setget, "set")))									//SET
				{
					ib = 0;
					char comBuffer[50];
					for(ia = 0; ia != 3; ia++)
					{
						for(i = 0; i != 50; i++)
						{
							comBuffer[ib] = RS_add[ia][i];
							if(RS_add[ia][i] != 0) ib++;
						}
					}
					COM_TX(comBuffer);
					COM_TX(";");
				}
			}

			for(i = 0; i != 50; i++)
			{
				RS_what[i] = 0;
				RS_add[0][i] = 0;
				RS_add[1][i] = 0;
				RS_add[2][i] = 0;
				RS_add[3][i] = 0;
				
			}
			for(i = 0; i != 3; i++)
			{
				RS_setget[i] = 0;
			}
		}
		//COM
		if(rdy[1])	
		{
			rdy[1] = 0;
		}
	}
}
