#include"encodersWithTimers.h"
#include "Arduino.h"
#include "HardwareTimer.h"

volatile uint32_t FrequencyMeasured, LastCapture = 0, CurrentCapture;
uint32_t input_freq = 0;
volatile uint32_t rolloverCompareCount = 0;

HardwareTimer *timer_coder_1 = new HardwareTimer(TIM3);
HardwareTimer *timer_coder_2 = new HardwareTimer(TIM8);

void InputCapture_IT_callback(void)
{
  CurrentCapture = timer_coder_1->getCaptureCompare(TIM_CHANNEL_1);
  /* frequency computation */
  if (CurrentCapture > LastCapture) {
    FrequencyMeasured = input_freq / (CurrentCapture - LastCapture);
  }
  else if (CurrentCapture <= LastCapture) {
    /* 0x1000 is max overflow value */
    FrequencyMeasured = input_freq / (0x10000 + CurrentCapture - LastCapture);
  }
  LastCapture = CurrentCapture;
  rolloverCompareCount = 0;
}

/* In case of timer rollover, frequency is to low to be measured set value to 0
   To reduce minimum frequency, it is possible to increase prescaler. But this is at a cost of precision. */
void Rollover_IT_callback(void)
{
  rolloverCompareCount++;

  if (rolloverCompareCount > 1)
  {
    FrequencyMeasured = 0;
  }

}

void timerEncoders::init(){
    //Manuel https://www.st.com/resource/en/reference_manual/rm0351-stm32l47xxx-stm32l48xxx-stm32l49xxx-and-stm32l4axxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf P1029
    //https://stm32duinoforum.com/forum/viewtopic_f_18_t_4024.html
    //Reference : https://github.com/stm32duino/wiki/wiki/HardwareTimer-library
    


    //Tim3 - B4 -> Coder 1 B
    //Tim3 - B5 -> Coder 1 A
    //Tim8 - A7 -> Coder 2 A
    //Tim8 - C7 -> Coder 2 B

    timer_coder_1->setMode(TIM_CHANNEL_1,TIMER_INPUT_CAPTURE_FALLING, PB4);
    timer_coder_1->setMode(TIM_CHANNEL_2,TIMER_INPUT_CAPTURE_RISING, PB5);
    //timer_coder_2->setMode(TIM_CHANNEL_1,TIMER_INPUT_CAPTURE_RISING, PB4)

    uint32_t PrescalerFactor = 1;
    timer_coder_1->setPrescaleFactor(PrescalerFactor);
    timer_coder_1->setOverflow(0x10000); // Max Period value to have the largest possible time to detect rising edge and avoid timer rollover

    timer_coder_1->attachInterrupt(TIM_CHANNEL_1, InputCapture_IT_callback);
    timer_coder_1->attachInterrupt(TIM_CHANNEL_2, InputCapture_IT_callback);
    timer_coder_1->attachInterrupt(Rollover_IT_callback);

    timer_coder_1->resume();



    //timEnc1.pause()
    //TIM3->regs.adv->CCMR1
    ////TIM_CCMR1_CC2S
    //TIM3->regs.adv->CCMR1 |= 0x0101;
    //TIM3->regs.adv->CCER  |= 0x0000;
    //TIM3->regs.adv->SMCR |= 0x0303; //(reads 8 clock cycles to make sure)
    //TIM3->regs.adv->CR1  |= 0x0001;
    //timEnc1.refresh(); 
    //timEnc1.resume();

    //timEnc2 = HardwareTimer (8);
    //timEnc2.pause();
    //TIM8->regs.adv->CCMR1 |= 0x0101;
    //TIM8->regs.adv->CCER  |= 0x0000;
    //TIM8->regs.adv->SMCR |= 0x0303; //(reads 8 clock cycles to make sure)
    //TIM8->regs.adv->CR1  |= 0x0001;
    //timEnc2.refresh(); 
    //timEnc2.resume();

    //TIM_CCMR1_CC1S
    
}
  
