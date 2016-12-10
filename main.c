#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <msp430f5529.h>

void main(void)
	{
			 WDTCTL = WDTPW | WDTHOLD;

			 P1SEL |=BIT1;
			 P2DIR &=~(BIT1); //set button to input
			 P2REN|=BIT1;     //enable pull-up resistor
			 P2OUT|=BIT1;
			 P2IE |=BIT1;     //enable interrupt on Port 2.1
			 P2IES |=BIT1;    //set as falling edge
			 

			 TA0CTL = TASSEL_1+MC_2+ID__8; //Timer A source ACLK

			 TA0CCTL0 = 0xC910;

			 _BIS_SR(LPM0_bits + GIE);  //enter LPM4 mode and enable global interrupt


	}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	static starttime = 0;
	volatile timediff = 0;
	volatile n = P1IN&BIT1;

	if(n != 0x02)
	{
	starttime = TA0CCR0;
	}

	if (n==0x02)
	{
		timediff = TA0CCR0 - starttime;
		if(timediff <= 0)
		{
			timediff = -1*timediff + 0xFFFF;
		}
		}
	}

}
