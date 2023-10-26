#include <Servo.h>
#include "PCA9685.h"
#include <Wire.h>
#include <BasicTimer.h>
  //NOTE: install Basic Timer library https://github.com/rtnate/arduino-BasicTimer

ServoDriver servo;
int gesture;

struct Appendage {

  float smoothingFactor = 0.9; //the higher the value, the most smoothly movement and direction will change
  float destinationAngle;
  float lastDestinationAngle;
  float currentAngle;
  int direction;
  int lastDirection;
  float tentacleSpeed;
  int stepPin;//
  int dirPin;//

  init(int _servoPin) {
  servoPin= _servoPin;
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
      ///might get some bugs here, like its 180.1 now, and it is supposed to come back to 179. suddenly the speed changes and it becomes 180.05, it will be stuck forever hahaha...
    }
    currentAngle = (currentAngle*smoothingFactor) + (destinationAngle* (1-smoothingFactor));
    //currentAngle = currentAngle * direction;
    //servo.setAngle(servoPin, currentAngle);
  }
} tentacleOne,tentacleTwo, tentacleThree, tentacleFour;


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
   servo.setAngle(tentacleOne.servoPin, tentacleOne.currentAngle);
   servo.setAngle(tentacleTwo.servoPin, tentacleTwo.currentAngle); //100 ms later run this
   servo.setAngle(tentacleThree.servoPin, tentacleThree.currentAngle); //100 ms later run this
   servo.setAngle(tentacleFour.servoPin, tentacleFour.currentAngle); //100 ms later run this


  }





