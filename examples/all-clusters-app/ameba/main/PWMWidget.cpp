#include <cstdio>
#include "LEDWidget.h"
#include "ColorWidget.h"
#include "PWMWidget.h"

#define PWM1 PA_25
#define PWM2 PA_26
#define PWM3 PA_30
#define PWM4 PA_12
#define PWM5 PA_13
#define TIME_SMOOTH 30000

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
    pwmout_pulsewidth_us(&pwmRed,255);
    pwmout_pulsewidth_us(&pwmBlue,255);
    pwmout_pulsewidth_us(&pwmGreen,255);
    pwmout_pulsewidth_us(&pwmWhite, 255);
    pwmout_pulsewidth_us(&pwmYellow, 255);
}

void PWMwidget::pwmPulseWidthCct(WyColor_t *wyColor)
{
    PWMwidget pwmwidget;
    printf("Current White: %d\n", wyColor->byCurrentWhite);
    printf("Current Yellow: %d\n", wyColor->byCurrentYellow);
    printf("Destination White: %d\n", wyColor->byDestinationWhite);
    printf("Destination Yellow: %d\n", wyColor->byDestinationYellow);

    while (pwmCctChangeSmooth(wyColor))
    {
        pwmout_pulsewidth_us(&pwmWhite, wyColor->byCurrentWhite);
        pwmout_pulsewidth_us(&pwmYellow, wyColor->byCurrentYellow);
        pwmwidget.setTimeSmooth(TIME_SMOOTH);
    }
}

void PWMwidget::pwmPulseWidthRgb(RgbColor_t *rgbColor)
{
    PWMwidget pwmwidget;
    printf("Current Red: %d\n", rgbColor->byCurrentRed);
    printf("Current Green: %d\n", rgbColor->byCurrentGreen);
    printf("Current Blue: %d\n", rgbColor->byCurrentBlue);
    printf("Destination Red: %d\n", rgbColor->byDestinationRed);
    printf("Destination Green: %d\n", rgbColor->byDestinationGreen);
    printf("Destination Blue: %d\n", rgbColor->byDestinationBlue);

    while (pwmRgbChangeSmooth(rgbColor))
    {
        pwmout_pulsewidth_us(&pwmRed, rgbColor->byCurrentRed);
        pwmout_pulsewidth_us(&pwmGreen, rgbColor->byCurrentGreen);
        pwmout_pulsewidth_us(&pwmBlue, rgbColor->byCurrentBlue);
        pwmwidget.setTimeSmooth(TIME_SMOOTH);
    }
}

void PWMwidget::setTimeSmooth(uint32_t wTime)
{
    while(wTime--)
    {
        
    }
}

bool PWMwidget::pwmCctChangeSmooth(WyColor_t *wyColor)
{
    bool bCheckChange = false;

    if (wyColor->byCurrentWhite > wyColor->byDestinationWhite)
    {
        wyColor->byCurrentWhite -= 1;
        bCheckChange = true;
        printf("White down: %d\n", wyColor->byCurrentWhite);
    }
    else if (wyColor->byCurrentWhite < wyColor->byDestinationWhite)
    {
        wyColor->byCurrentWhite += 1;
        bCheckChange = true;
        printf("White up: %d\n", wyColor->byCurrentWhite);
    }

    if (wyColor->byCurrentYellow > wyColor->byDestinationYellow)
    {
        wyColor->byCurrentYellow -= 1;
        bCheckChange = true;
        printf("Yellow down: %d\n", wyColor->byCurrentYellow);
    }
    else if (wyColor->byCurrentYellow < wyColor->byDestinationYellow)
    {
        wyColor->byCurrentYellow += 1;
        bCheckChange = true;
        printf("Yellow up: %d\n", wyColor->byCurrentYellow);
    }

    return bCheckChange;
}

bool PWMwidget::pwmRgbChangeSmooth(RgbColor_t *rgbColor)
{
    bool bCheckChange = false;

    if (rgbColor->byCurrentRed > rgbColor->byDestinationRed)
    {
        rgbColor->byCurrentRed -= 1;
        bCheckChange = true;
        printf("Red down: %d\n", rgbColor->byCurrentRed);
    }
    else if (rgbColor->byCurrentRed < rgbColor->byDestinationRed)
    {
        rgbColor->byCurrentRed += 1;
        bCheckChange = true;
        printf("Red up: %d\n", rgbColor->byCurrentRed);
    }

    if (rgbColor->byCurrentGreen > rgbColor->byDestinationGreen)
    {
        rgbColor->byCurrentGreen -= 1;
        bCheckChange = true;
        printf("Green down: %d\n", rgbColor->byCurrentGreen);
    }
    else if (rgbColor->byCurrentGreen < rgbColor->byDestinationGreen)
    {
        rgbColor->byCurrentGreen += 1;
        bCheckChange = true;
        printf("Green down: %d\n", rgbColor->byCurrentGreen);
    }

    if (rgbColor->byCurrentBlue > rgbColor->byDestinationBlue)
    {
        rgbColor->byCurrentBlue -= 1;
        bCheckChange = true;
        printf("Blue down: %d\n", rgbColor->byCurrentBlue);
    }
    else if (rgbColor->byCurrentBlue < rgbColor->byDestinationBlue)
    {
        rgbColor->byCurrentBlue += 1;
        bCheckChange = true;
        printf("Blue down: %d\n", rgbColor->byCurrentBlue);
    }

    return bCheckChange;
}
