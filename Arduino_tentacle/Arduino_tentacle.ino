#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>
#include <BasicTimer.h>
  //NOTE: install Basic Timer library https://github.com/rtnate/arduino-BasicTimer

ServoDriver servo;


struct Appendage {
  init(int _servoPin) {
    servoPin = _servoPin;
  }
  
  void setAngle(float _angle) {
    destinationAngle = _angle;

    if (destinationAngle != lastDestinationAngle){
      destinationAngle = lastDestinationAngle;
    }
  }  

  void update() {

    if(currentAngle >= 180 || currentAngle <= 0) {  //we run this check first to make sure we don't send the servos out of bounds
      direction = direction * -1; 
    }
   
    currentAngle = (currentAngle*smoothingFactor) + (destinationAngle* (1-smoothingFactor));
    //currentAngle = currentAngle * direction;
    //servo.setAngle(servoPin, currentAngle);
  }
   
  float smoothingFactor = 0.9; //the higher the value, the most smoothly movement and direction will change
  float destinationAngle;
  float lastDestinationAngle;
  float currentAngle;
  int direction;
  int lastDirection;
  float tentacleSpeed;
  int servoPin;

  // void setAngle
  //   if (gesture>1){
  // angle = angle + speed * direction;
  // if (angle>=180){
  //   direction= -1;
  // }else if(angle <= 0){
  //   direction = 1;
  // }

} tentacleOne,tentacleTwo, tentacleThree, tentacleFour;

//remove these
int gesture = 1;
float angle = 0;
int direction;


/* tdj: create an enum to contain the gestures, so they can be referenced by name 
--create datatype to hold of user emotions
--create datatype to hold jellyfish human emotions
--create map to specify the reactions between them; i.e. is the jellyfish just a mirror, or something more? 
maybe it's calm when we're happy, and happy when we're calm (for instance)
*/

const int numberOfAnimalEmotions = 5;

enum Emotion { 

  CALM = 1,  //not an emotion, but useful
  HAPPY = 2,  //joyful
  MAD = 3, //angry
  SAD = 4,
  AFRAID = 5 //scared
};


struct animal {

  Emotion currentEmotion;
  float currentSpeed;
  float defaultSpeeds[4];
  void setEmotion(int _emotion) {
   currentEmotion = _emotion;
   currentSpeed = defaultSpeeds[_emotion];
  }
} jellyfish;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  servo.init(0x7f);


  tentacleOne.init(1);
  tentacleTwo.init(2);
  tentacleThree.init(3);
  tentacleFour.init(4);

  jellyfish.currentEmotion = CALM; //starting emotion
  jellyfish.defaultSpeeds[CALM] = 0.05;
  jellyfish.defaultSpeeds[HAPPY] = 0.15;
  jellyfish.defaultSpeeds[MAD] = 0.3;
}

void loop() {
 while (Serial.available()) {
  gesture = Serial.read();

  }

  jellyfish.setEmotion(gesture);

  //replace these calls with our new appendage code
   servo.setAngle(1, angle);
   servo.setAngle(2, angle); //100 ms later run this
   servo.setAngle(3, angle); //100 ms later run this
   servo.setAngle(4, angle); //100 ms later run this


  }





