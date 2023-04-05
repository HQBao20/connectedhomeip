#include <cstdio>
#include "LEDWidget.h"
#include "ColorWidget.h"
#include "PWMWidget.h"

#define PWM1 PA_25
#define PWM2 PA_26
#define PWM3 PA_30
#define PWM4 PA_12
#define PWM5 PA_13

pwmout_t pwmRed;
pwmout_t pwmGreen;
pwmout_t pwmBlue;
pwmout_t pwmWhite;
pwmout_t pwmYellow;

void PWMwidget::pwmInit(void)
{
    printf("PWM widget init!\n");
    pwmout_init(&pwmRed, PWM1);
    pwmout_init(&pwmBlue, PWM2);
    pwmout_init(&pwmGreen, PWM3);
    pwmout_init(&pwmWhite, PWM4);
    pwmout_init(&pwmYellow, PWM5);
    pwmout_period_us(&pwmRed, PWM_PERIOD);
    pwmout_period_us(&pwmBlue, PWM_PERIOD);
    pwmout_period_us(&pwmGreen, PWM_PERIOD);
    pwmout_period_us(&pwmWhite, PWM_PERIOD);
    pwmout_period_us(&pwmYellow, PWM_PERIOD);
    // pwmout_pulsewidth_us(&pwmRed,0);
    // pwmout_pulsewidth_us(&pwmBlue,255);
    // pwmout_pulsewidth_us(&pwmGreen,255);
    pwmout_pulsewidth_us(&pwmWhite, 0);
    pwmout_pulsewidth_us(&pwmYellow, 0);

    printf("Pulse White: %d!\n", 0);
    printf("Pulse Yellow: %d!\n", 0);
}

void PWMwidget::pwmPulseWidth(WyColor_t wyColor)
{
    printf("White: %d\n", wyColor.byWhite);
    printf("Blue: %d\n", wyColor.byYellow);

    pwmout_pulsewidth_us(&pwmWhite, wyColor.byWhite);
    pwmout_pulsewidth_us(&pwmYellow, wyColor.byYellow);
}
