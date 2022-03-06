#include "HardwareEncoder.h"
#include "Arduino.h"

    
volatile uint32_t encoderCount;

void init() {
    
}
int get_pos_encoder() {
    HardwareTimer timer = HardwareTimer(TIM1);
}


static void update_encoder() {

}


/*

// call this from the systick interrupt every millisecond
// modified from the original code by dannyf
// at https://github.com/dannyf00/My-MCU-Libraries---2nd-try/blob/master/encoder1.c
void encoder1_read(void)
{
  volatile static uint8_t ABs = 0;
  ABs = (ABs << 2) & 0x0f; //left 2 bits now contain the previous AB key read-out;
  ABs |= (digitalRead(ENC_CLK) << 1) | digitalRead(ENC_DATA);
  switch (ABs)
  {
    case 0x0d:
      encoderCount++;
      break;
    case 0x0e:
      encoderCount--;
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(ENC_CLK, INPUT);
  pinMode(ENC_DATA, INPUT);
  pinMode(LEDPIN, OUTPUT);
  encoderCount = 10000;
#ifdef LIBMAPLE_CORE  
  systick_attach_callback(&encoder1_read);
#endif  
}

void loop()
{
  static uint32_t count;
  static uint32_t prevCount;
  count = encoderCount;
  if (count != prevCount)
  {
    prevCount = count;
    Serial.print("Count: ");
    Serial.println(count);
  }
}

#ifdef STM32DUINO_CORE
void HAL_SYSTICK_Callback()
{
  encoder1_read();
}
#endif
*/