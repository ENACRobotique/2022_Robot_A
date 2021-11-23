#include <Arduino.h>
#include <Metro.h>

#include "odometry.h"

Metro odometryCtrl = Metro(10);

void setup()
{
  Odometry::init();

  Serial.begin(9600);
  while (!Serial) {;}
}

void loop()
{
  if(odometryCtrl.check())
  {
    Serial.printf("motor1: %f\n", Odometry::speed_motor1());
    Serial.printf("motor2: %f\n", Odometry::speed_motor2());
    Serial.printf("wheel1: %f\n", Odometry::speed_wheel1());
    Serial.printf("wheel2: %f\n", Odometry::speed_wheel2());
  }

}