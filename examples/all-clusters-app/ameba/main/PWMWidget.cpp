#include <cstdio>
#include "LEDWidget.h"
#include "ColorWidget.h"
#include "PWMWidget.h"

#define PWM1 PA_25
#define PWM2 PA_26
#define PWM3 PA_30
#define PWM_PERIOD 255

pwmout_t pwmRed;
pwmout_t pwmGreen;
pwmout_t pwmBlue;

void PWMwidget::pwmInit(void)
{
    printf("PWM widget init!\n");
    pwmout_init(&pwmRed, PWM1);
    pwmout_init(&pwmBlue, PWM2);
    pwmout_init(&pwmGreen, PWM3);
    pwmout_period_us(&pwmRed, PWM_PERIOD);
    pwmout_period_us(&pwmBlue, PWM_PERIOD);
    pwmout_period_us(&pwmGreen, PWM_PERIOD);
    pwmout_pulsewidth_us(&pwmRed,0);
    pwmout_pulsewidth_us(&pwmBlue,255);
    pwmout_pulsewidth_us(&pwmGreen,255);s

    printf("Level Red: %d!\n", 0);
    printf("Level Green: %d!\n", 255);
    printf("Level Blue: %d!\n", 255);
}

void PWMwidget::pwmPulseWidth(RgbColor_t rgbColor)
{
    printf("RED: %d\n", rgbColor.byRed);
    printf("Blue: %d\n", rgbColor.byBlue);
    printf("GREEN: %d\n", rgbColor.byGreen);

    pwmout_pulsewidth_us(&pwmRed, rgbColor.byRed);
    pwmout_pulsewidth_us(&pwmBlue, rgbColor.byBlue);
    pwmout_pulsewidth_us(&pwmGreen, rgbColor.byGreen);
}