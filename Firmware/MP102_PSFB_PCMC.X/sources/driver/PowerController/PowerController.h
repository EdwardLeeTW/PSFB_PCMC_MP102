
#ifdef __PowerController
#define EXTERN  
#else
#define EXTERN extern
#endif

#define SysSwitch_OpenLoop  1   // 0:Disable Open-loop control 1:Enable Open-loop control

// PWM Module
#define SysConst_PWMPeriod  39992 //100KHz based on 500MHz
#define SysConst_Shift99p   (SysConst_PWMPeriod /2 * 0.99)
#define SysConst_Shift30p   (SysConst_PWMPeriod /2 * 0.30)
#define SysConst_Shift02p   (SysConst_PWMPeriod /2 * 0.02)

// Reference for Voltage Loop Compensator
#define VCOMP_VREF          3023 //

// Compensator Clamp Limits
#define VCOMP_MIN_CLAMP     SysConst_Shift02p
#define VCOMP_MAX_CLAMP     SysConst_Shift99p


EXTERN uint16_t PWMUpdateCount;
EXTERN uint16_t PhaseShifted;
EXTERN uint16_t SRdelay;
EXTERN uint16_t Output_Vref;

volatile uint16_t VMC_ControlObject_Initialize(void);
void VMC_Softstart(void);

