#pragma once
#include "LEDWidget.h"
#include "ColorWidget.h"
#include <stdint.h>
#include <stdbool.h>

#define PWM_PERIOD 255

struct pwmout_s {
    uint8_t pwm_idx;
    uint32_t period;//in us
    float pulse;//in us
};

typedef struct pwmout_s pwmout_t;

extern "C" void pwmout_init(pwmout_t* obj, PinName pin);
extern "C" void pwmout_period_us(pwmout_t* obj, int us);
extern "C" void pwmout_pulsewidth_us(pwmout_t* obj, int us);

class PWMwidget
{
    public:
        void pwmInit(void);
        void pwmPulseWidthCct(WyColor_t *wyColor);
        void pwmPulseWidthRgb(RgbColor_t *rgbColor);
        bool pwmCctChangeSmooth(WyColor_t *wyColor);
        bool pwmRgbChangeSmooth(RgbColor_t *rgbColor);
        void setTimeSmooth(uint32_t wTime);
    private:
};