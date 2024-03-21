/* ********************************************************************************
 * 3p3z Controller Configuration Code Example
 * ********************************************************************************
 *
 * The following code example covers all user-defined configurations of the
 * control object 'VCOMP' required to run the recently configured controller.
 *
 * Please note:
 * This is no executable code and serves only as template for the integration into
 * a proprietary firmware project. You can copy & paste this entire code example
 * to your code project by clicking the 'Copy to Clipboard' above or pick specific
 * section by selecting a text section and pressing <CTRL>+'C'.
 *
 * Once code has been copied to user code, each setting has to be configured by
 * replacing the placeholders <[data type]> in each code line by your individual
 * configuration values.
 *
 * This code example only lists configurations of features which have been selected
 * in this tool. Enabling/disabling code generation options may also change the
 * contents of this code example. Unused options are EXCLUDED from this code example.
 *
 * ********************************************************************************/

#define __PowerController

// Standard Include Files
#include <stdint.h>                               // include standard integer data types
#include <stdbool.h>                              // include standard boolean data types
#include <stddef.h>                               // include standard definition data types

// 3p3z Controller Include Files
#include "VMC.h"                                // include 'VCOMP' controller header file
#include "PowerController.h"
#include "../../../mcc_generated_files/pin_manager.h"
#include "../../../mcc_generated_files/pwm.h"

volatile uint16_t VMC_ControlObject_Initialize(void)
{
    volatile uint16_t retval = 0;                 // Auxiliary variable for function call verification (initially set to ZERO = false)
    Output_Vref = 0;
    PhaseShifted = SysConst_Shift02p;
    SRdelay = 0x320;
    /* Controller Input and Output Ports Configuration */

     // Configure Controller Primary Input Port
    VMC.Ports.Source.ptrAddress = &ADCBUF0;   // Pointer to primary feedback source (e.g. ADC buffer register or variable)
    VMC.Ports.Source.Offset = 0;              // Primary feedback signal offset
    VMC.Ports.Source.NormScaler = 0;          // Primary feedback normalization factor bit-shift scaler
    VMC.Ports.Source.NormFactor = 0x7FFF;     // Primary feedback normalization factor fractional

    // Configure Controller Primary Output Port
    VMC.Ports.Target.ptrAddress = &PhaseShifted;     // Pointer to primary output target (e.g. SFR register or variable)
    VMC.Ports.Target.Offset = 0;              // Primary output offset value
    VMC.Ports.Target.NormScaler = 0;          // Primary output normalization factor bit-shift scaler
    VMC.Ports.Target.NormFactor = 0x7FFF;     // Primary output normalization factor fractional
 
    // Configure Control Reference Port
    VMC.Ports.ptrControlReference = &Output_Vref; // Pointer to control reference (user-variable)
  
    /* Controller Output Limits Configuration */

    // Primary Control Output Limit Configuration
    VMC.Limits.MinOutput = VCOMP_MIN_CLAMP;        // Minimum control output value
    VMC.Limits.MaxOutput = VCOMP_MAX_CLAMP;        // Maximum control output value
    
    /* Advanced Parameter Configuration */

    // Initialize User Data Space Buffer Variables
    VMC.Advanced.usrParam0 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam1 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam2 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam3 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam4 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam5 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam6 = 0;                 // No additional advanced control options used
    VMC.Advanced.usrParam7 = 0;                 // No additional advanced control options used

    /* Controller Status Word Configuration */

    VMC.status.bits.enabled = false;            // Keep controller disabled

    // Call Assembler Control Library Initialization Function
    retval = VMC_Initialize(&VMC);            // Initialize controller data arrays and number scalers

    return(retval);
}

/* 3p3z Control Loop Interrupt Service Routine for Controller Object 'VCOMP'
 * **************************************************************************************************
 * This code example of a interrupt service routine uses the tailored name label '_VCOMP'.
 * The Assembler library code sequences of controller data objects generated by PS-DCLD are optimized
 * for being called by a PWM interrupt for minimum response time. However, in some applications
 * it might be desired to call the control loop from other interrupt sources.
 * Using custom labels for interrupt routines allows using generic interrupt service routine
 * function calls in code, which can be mapped to specific interrupt sources by adding a #define
 * pre-compiler directive declaration to your code, like the following example:
 *
 *    #define _VCOMP_Interrupt    _PWM1Interrupt  // Define label for interrupt service routine function call
 *    #define _VCOMP_ISRIF        _PWM1IF         // Define label for interrupt flag bit
 *
 * **************************************************************************************************/
#include "../../../mcc_generated_files/cmp1.h"

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADCAN0Interrupt ( void )
{
#if (SysSwitch_OpenLoop == 1)
    //Read the ADC value from the ADCBUF
    uint16_t valchannel_AN0;
    valchannel_AN0 = ADCBUF0;
    
    CMP1_SetDACDataHighValue(3700); // Max 3980 
    
    // For PWM Boundary Jumping Test
    if(PWMUpdateCount <= 2)
    {
        //0~2
        PhaseShifted = SysConst_Shift99p;
        SRdelay = 0x320;
    }
    else
    {
        //3~5
        PhaseShifted = SysConst_Shift99p;
        SRdelay = 0x320;
    }
    PG1TRIGA = PhaseShifted;
    //PG2TRIGA = SRdelay;
    if(PWMUpdateCount >= 5) PWMUpdateCount = 0;
    else PWMUpdateCount++;
#else
    //VMC_Update(&VCOMP);         // Call control loop
    VMC_PTermUpdate(&VMC);        // Call P-Term control loop
#endif

    //clear the channel_AN0 interrupt flag
    IFS5bits.ADCAN0IF = 0;
}


//**********************************************************************************
// Download latest version of this tool here:
//      https://www.microchip.com/powersmart
//**********************************************************************************

// Simple Softstart
void VMC_Softstart(void)
{
    VMC.status.bits.enabled = true;           // Enable controller   
    if(Output_Vref < VCOMP_VREF)
    {
        Output_Vref+=10;
    }
    else
    {
        Output_Vref = VCOMP_VREF;
    }
}
