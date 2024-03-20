/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33CK64MP102
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
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
#include "mcc_generated_files/system.h"
#include "sources/os/os.h"
#include "PowerController.h"

/*
                         Main application
 */
int main(void)
{
    // initialize VCOMP controller
    VMC_ControlObject_Initialize();
    
    // initialize the device
    SYSTEM_Initialize();
    
    // OS
    OS_Init();
    OS_Scheduler_RunForever();
    
    while (1)
    {
        // Add your application code
    }
    return 1; 
}

#if 0 // Moved to PowerController.c
#define SysSwitch_OpenLoop  1
#define SysConst_PWMPeriod  39992 //100KHz based on 500MHz
#define SysConst_Shift99p   (SysConst_PWMPeriod /2 * 0.99)
#define SysConst_Shift30p   (SysConst_PWMPeriod /2 * 0.30)
#define SysConst_Shift02p   (SysConst_PWMPeriod /2 * 0.02)

uint16_t PWMUpdateCount = 0;
uint16_t PhaseShifted = SysConst_Shift02p;
uint16_t SRdelay = 0x320;


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADCAN0Interrupt ( void )
{
    uint16_t valchannel_AN0;
    //Read the ADC value from the ADCBUF
    valchannel_AN0 = ADCBUF0;

#if (SysSwitch_OpenLoop == 1)
    // For PWM Boundary Test
    if(PWMUpdateCount <= 2)
    {
        //0~2
        PhaseShifted = SysConst_Shift99p;
        SRdelay = 0x320;
    }
    else
    {
        //3~5
        PhaseShifted = SysConst_Shift02p;
        SRdelay = 0x320;
    }
    PG1TRIGA = PhaseShifted;
    //PG2TRIGA = SRdelay;
    if(PWMUpdateCount >= 5) PWMUpdateCount = 0;
    else PWMUpdateCount++;
#endif

    //clear the channel_AN0 interrupt flag
    IFS5bits.ADCAN0IF = 0;
}
#endif

/**
 End of File
*/

