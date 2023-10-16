#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;

int gesture = 0;

float speed = 0;
float angle = 0;
int direction;

bool calm = false; 
bool happy = false; 
bool mad = false; 

void setup() {
  Wire.begin();
  Serial.begin(9600);
  servo.init(0x7f);
}

void loop() {
 while (Serial.available()) {
  gesture = Serial.read();
  }
   if (gesture == 1){
    calm = true;
    happy = false;
    mad = false;
  }
    if (gesture == 2){
    happy = true;
    mad = false;
    calm = false;
  }
    if (gesture == 3){
    mad = true;
    happy = false;
    calm = false;
  }

    //3 states
  if (calm){
   speed = 0.1;
  }
   if (happy){
   speed = 0.3;
  }
   if (mad){
   speed = 0.5;
  }
  
  angle = angle + speed * direction;
  if (angle>=90){
    direction= -1;
  }else if(angle <= 0){
    direction = 1;
  }

  if (gesture>0){
   servo.setAngle(1, angle);
   delay(1000);
   servo.setAngle(2, angle);
   delay(1000);
   servo.setAngle(3, angle);
   delay(1000);
   servo.setAngle(4, angle);
   delay(1000);
   servo.setAngle(5, angle);
   delay(1000);
   servo.setAngle(6, angle);
   delay(1000);
  }


  Serial.write(angle);
  delay(1000);

}
