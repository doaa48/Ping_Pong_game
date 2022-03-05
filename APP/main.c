/*
 * main.c
 *
 *  Created on: Sep 28, 2021
 *      Author: dell
 */
#include"util/delay.h"
#include "../LIB/STDTYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/CHECK_ERROR.h"
#include "../MCAL/PORT_Driver/PORT_REG.h"
#include "../MCAL/PORT_Driver/PORT_Config.h"
#include "../MCAL/PORT_Driver/PORT_Private.h"
#include "../MCAL/PORT_Driver/PORT_Interface.h"
#include "../MCAL/DIO_Driver/DIO_REG.h"
#include "../MCAL/External_Interrupt_Driver/External_Interrupt_REG.h"
#include "../MCAL/External_Interrupt_Driver/External_Interrupt_Config.h"
#include "../MCAL/External_Interrupt_Driver/External_Interrupt_Private.h"
#include "../MCAL/External_Interrupt_Driver/External_Interrupt_Interface.h"
#include "../MCAL/GIE_Driver/GIE_REG.h"
#include "../MCAL/GIE_Driver/GIE_Interface.h"
#include "../MCAL/DIO_Driver/DIO_Interface.h"
#include "../HAL/LCD_Module/LCD_Config.h"
#include "../HAL/LCD_Module/LCD_Interface.h"

static u8 Check_State = 1;

/*Representation of Madrab on LCD*/
	u8 PING_Madrab[8]={ 0b00000011,
						0b00000011,
						0b00000011,
						0b00000011,
						0b00000011,
						0b00000011,
						0b00000011,
						0b00000011,
	                   };
/*Representation of Space on LCD*/
	u8 PING_Space[8]={ 0b00000000,
						0b00000000,
						0b00000000,
						0b00000000,
						0b00000000,
						0b00000000,
						0b00000000,
						0b00000000,
		                   };
/*Representation of Ball on LCD*/
	u8 PING_Ball[8]={ 0b00000000,
				      0b00000000,
				      0b00000100,
				      0b00001110,
				      0b00000100,
				      0b00000000,
				      0b00000000,
				      0b00000000,
					};

/*Function Prototype*/
void PingPongFunc();

int main(void)
{

	/*Port initialization*/
	PORT_VoidInit();

	/*LCD initialization*/
	LCD_VoidInit();

	/*Call function Back from main to MCAL layar*/
	SendAddress_Callback(PingPongFunc,1);

	/*Enable GIE for interrupt  */
	EXTI_VidEnableOrDisableGIE(ENABLE);

	/*External interrupt initialization */
	EXTI_voidEnableOrDisableInterruptPin_Prebuild();
	EXTI_VidControlSense_Prebuild();

	 /*Initial state of Madrab1*/
	 LCD_VoidCreateSpecialChar(PING_Madrab,0,0,0);

	 /*Initial state of Madrab2*/
	 LCD_VoidCreateSpecialChar(PING_Madrab,0,0,15);


	 /*Running of Ball During the LCD*/
	for(u8 i=1;i<=14;i++)
	 {
		 LCD_VoidCreateSpecialChar(PING_Ball,1,0,i);
		 _delay_ms(100);
		 LCD_VoidCreateSpecialChar(PING_Space,2,0,i);
	 }


	/* Checking if Ball hit Madrab or Not */
	 LCD_VoidClearDisplay();

		 if   (Check_State==0)
		 {
			LCD_VoidSendString("Player 1 Wins");
		 }
		 else if(Check_State==1)
	 	 {
	 		LCD_VoidSendString("Player 2 Wins");

	 	 }


	while(1)
	{

	}
	return 0;

}


void PingPongFunc()
{
	/*Changing the Position of Madrab on Each Entering ISR Up or Down*/

	LCD_VoidCreateSpecialChar(PING_Madrab,0,Check_State,15);
		if(Check_State==0)
		{
			Check_State=1;
		}
		else if(Check_State==1)
		{
			Check_State=0;
		}
	 LCD_VoidCreateSpecialChar(PING_Space,2,Check_State,15);

}
