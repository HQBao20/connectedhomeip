#pragma once
#include "LEDWidget.h"
#include "ColorWidget.h"

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
        void pwmPulseWidth(RgbColor_t rgbColor);
    private:
};