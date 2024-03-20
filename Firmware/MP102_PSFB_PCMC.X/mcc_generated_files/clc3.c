/**
  CLC3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    clc3.c

  @Summary
    This is the generated driver implementation file for the CLC3 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides implementations for driver APIs for CLC3.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33CK64MP102
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB             :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "clc3.h"

/**
  Section: CLC3 APIs
*/

void CLC3_Initialize(void)
{
    // Set the CLC3 to the options selected in the User Interface

	CLC3CONL = 0x8080 & ~(0x8000);

    CLC3CONH = 0x00;

    CLC3SELL = 0x5000;

    CLC3GLSL = 0x2002;

    CLC3GLSH = 0x8008;

	
	CLC3_Enable();
}

void __attribute__ ((weak)) CLC3_PositiveEdge_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ((weak)) CLC3_NegativeEdge_CallBack(void)
{
    // Add your custom callback code here
}

void CLC3_PositiveEdge_Tasks ( void )
{
	if(IFS10bits.CLC3PIF)
	{
		// CLC3 PositiveEdge callback function 
		CLC3_PositiveEdge_CallBack();
		
		// clear the CLC3 interrupt flag
		IFS10bits.CLC3PIF = 0;
	}
}

void CLC3_NegativeEdge_Tasks ( void )
{
	if(IFS11bits.CLC3NIF)
	{
		// CLC3 NegativeEdge callback function 
		CLC3_NegativeEdge_CallBack();
		
		// clear the CLC3 interrupt flag
		IFS11bits.CLC3NIF = 0;
	}
}
bool CLC3_OutputStatusGet(void)
{
    return(CLC3CONLbits.LCOUT);

}
/**
 End of File
*/
