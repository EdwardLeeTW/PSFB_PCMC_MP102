/**
  CLC2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    clc2.c

  @Summary
    This is the generated driver implementation file for the CLC2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides implementations for driver APIs for CLC2.
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

#include "clc2.h"

/**
  Section: CLC2 APIs
*/

void CLC2_Initialize(void)
{
    // Set the CLC2 to the options selected in the User Interface

	CLC2CONL = 0x8082 & ~(0x8000);

    CLC2CONH = 0x00;

    CLC2SELL = 0x5020;

    CLC2GLSL = 0x808;

    CLC2GLSH = 0x8080;

	
	CLC2_Enable();
}

void __attribute__ ((weak)) CLC2_PositiveEdge_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ((weak)) CLC2_NegativeEdge_CallBack(void)
{
    // Add your custom callback code here
}

void CLC2_PositiveEdge_Tasks ( void )
{
	if(IFS7bits.CLC2PIF)
	{
		// CLC2 PositiveEdge callback function 
		CLC2_PositiveEdge_CallBack();
		
		// clear the CLC2 interrupt flag
		IFS7bits.CLC2PIF = 0;
	}
}

void CLC2_NegativeEdge_Tasks ( void )
{
	if(IFS11bits.CLC2NIF)
	{
		// CLC2 NegativeEdge callback function 
		CLC2_NegativeEdge_CallBack();
		
		// clear the CLC2 interrupt flag
		IFS11bits.CLC2NIF = 0;
	}
}
bool CLC2_OutputStatusGet(void)
{
    return(CLC2CONLbits.LCOUT);

}
/**
 End of File
*/
