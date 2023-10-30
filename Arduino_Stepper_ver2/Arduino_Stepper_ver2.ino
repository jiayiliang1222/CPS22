#include <FlexyStepper.h>

//X:Right
//Y:Left
//Z:Outward
//A:Inward
//+ 顺时针clockwise
//- 逆时针counterclockwise

int gesture = 1; 

const int LED_PIN = 13;
const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_Z_STEP_PIN = 4;
const int MOTOR_A_STEP_PIN = 12;

const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_DIR_PIN = 6;
const int MOTOR_Z_DIR_PIN = 7;
const int MOTOR_A_DIR_PIN = 13;

const int STEPPERS_ENABLE_PIN = 8;

FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;
FlexyStepper stepperA;

float X_speed;//formal parameters
float Y_speed;
float Z_speed;
float A_speed;

float X_acceleration;
float Y_acceleration;
float Z_acceleration;
float A_acceleration;

int X_steps = 0; //run one motor
int Y_steps = 0;
int Z_steps = 0;
int A_steps = 0;


int valueFromProcessing;

int totalStepsX = 0;
int totalStepsY = 0;
int totalStepsZ = 0;
int totalStepsA = 0;

bool calm = false; 
bool happy = false; 
bool sad = false; 
bool mad = false;

int calm_ = 0; 
int happy_ = 0; 
int sad_ = 0; 
int mad_ = 0;

// int calmWhile = 0; //别写bool
// int happyWhile = 0; 
// int sadWhile = 0; 
// int madWhile = 0; 

// long stepsX;//run all motors
// long stepsY;
// long stepsZ;
// long stepsA;

// long stepsX_;
// long stepsY_;
// long stepsZ_;
// long stepsA_;



void setup() 
{
  pinMode(LED_PIN, OUTPUT);   
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);       
  Serial.begin(9600);

  stepperX.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
  stepperY.connectToPins(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
  stepperZ.connectToPins(MOTOR_Z_STEP_PIN, MOTOR_Z_DIR_PIN);
  stepperA.connectToPins(MOTOR_A_STEP_PIN, MOTOR_A_DIR_PIN);

  digitalWrite(STEPPERS_ENABLE_PIN, LOW);    
}



void loop() 
{
  /* while (Serial.available()) {
        String receivedStr = Serial.readStringUntil('\n');  // Read the incoming data until newline
    
        //Split the received string based on commas
        int commaIndex1 = receivedStr.indexOf(',');
        int commaIndex2 = receivedStr.indexOf(',', commaIndex1 + 1);
        
        X_speed = receivedStr.substring(0, commaIndex1).toInt();
        X_acceleration = receivedStr.substring(commaIndex1 + 1, commaIndex2).toInt();
        X_steps = receivedStr.substring(commaIndex2 + 1).toInt();

    }*/
    if (Serial.available()>0) {
     String receivedString = Serial.readStringUntil('\n');
     if (receivedString.length() > 0) {
       gesture = receivedString.toInt();
       //X_steps = receivedString.toInt();
       //runJustTheXStepper(X_speed, X_acceleration, X_steps);
     }
    }
switch (gesture) {
        case 1:
            break;
        case 2:
           calm = true;
           happy = false;
           sad = false;
           mad = false;
    Z_speed = 75;
    A_speed = 75;

    Z_acceleration = 75;
    A_acceleration = 75;

    Z_steps = -100;
    A_steps = 100;

    runJustTheAStepper(A_speed, A_acceleration, A_steps); 
    runJustTheAStepper(A_speed, A_acceleration, -A_steps); 
    runJustTheZStepper(Z_speed, Z_acceleration, Z_steps);
    runJustTheZStepper(Z_speed, Z_acceleration, -Z_steps);                // 执行与 gesture == 1 相关的操作
            break;
        case 3:
          happy = true;
          mad = false;
          sad = false;
          calm = false;
    X_speed = 100;
    Y_speed = 100;

    X_acceleration = 100;
    Y_acceleration = 100;

    X_steps = 150;
    Y_steps = -150;

    runJustTheXStepper(X_speed, X_acceleration, X_steps);
    runJustTheXStepper(X_speed, X_acceleration, -X_steps);
    runJustTheYStepper(Y_speed, Y_acceleration, Y_steps); 
    runJustTheYStepper(Y_speed, Y_acceleration, -Y_steps);                 // 执行与 gesture == 2 相关的操作
            break;
        case 4:
          mad = false;
          happy = false;
          sad = true;
          calm = false;
          
    A_speed = 50;
    A_acceleration = 50;

    A_steps = 75;

    runJustTheAStepper(A_speed, A_acceleration, A_steps);
    runJustTheAStepper(A_speed, A_acceleration, -A_steps);    // 执行与 gesture == 3 相关的操作
            break;
        case 5:
          mad = true;
          happy = false;
          sad = false;
          calm = false;
          
    Z_speed = 150;
    A_speed = 150;

    Z_acceleration = 150;
    A_acceleration = 150;

    Z_steps = -199;
    A_steps = 199;

    runJustTheZStepper(Z_speed, Z_acceleration, Z_steps);
    runJustTheZStepper(Z_speed, Z_acceleration, -Z_steps);

    runJustTheAStepper(A_speed, A_acceleration, A_steps); 
    runJustTheAStepper(A_speed, A_acceleration, -A_steps);      // 执行与 gesture == 4 相关的操作
            break;
        default:
            break;
    }
}


void runJustTheXStepper(float X_speed_, float X_acceleration_, float steps_) 
{
  if (totalStepsX < 200 && totalStepsX > -200 ){
  stepperX.setSpeedInStepsPerSecond(X_speed_);
  stepperX.setAccelerationInStepsPerSecondPerSecond(X_acceleration_);
  stepperX.moveRelativeInSteps(steps_);
  totalStepsX += steps_;
  }
  }

void runJustTheYStepper(float Y_speed_, float Y_acceleration_, float steps_) 
{
  if (totalStepsY < 200 && totalStepsY > -200 ){
  stepperY.setSpeedInStepsPerSecond(Y_speed_);
  stepperY.setAccelerationInStepsPerSecondPerSecond(Y_acceleration_);
  stepperY.moveRelativeInSteps(steps_);
  totalStepsY += steps_;
  }
  }
void runJustTheZStepper(float Z_speed_, float Z_acceleration_, float steps_) 
{
  if (totalStepsZ < 200 && totalStepsZ > -200 ){
  stepperZ.setSpeedInStepsPerSecond(Z_speed_);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(Z_acceleration_);
  stepperZ.moveRelativeInSteps(steps_);
  totalStepsZ += steps_;
  }
  }
void runJustTheAStepper(float A_speed_, float A_acceleration_, float steps_) 
{
  if (totalStepsA < 200 && totalStepsA > -200 ){
  stepperA.setSpeedInStepsPerSecond(A_speed_);
  stepperA.setAccelerationInStepsPerSecondPerSecond(A_acceleration_);
  stepperA.moveRelativeInSteps(steps_);
  totalStepsA += steps_;
  }
  }

void runXYZASteppers(long stepsX,long stepsY,long stepsZ,long stepsA) 
{
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYZAWithCoordination(stepsX, stepsY, stepsZ,stepsA,speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);
}
void runXYZASteppers_(long stepsX,long stepsY,long stepsZ,long stepsA)  
{
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYZAWithCoordination(stepsX, stepsY, stepsZ, stepsA,speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);
}

void moveXYZAWithCoordination(long stepsX, long stepsY, long stepsZ, long stepsA,float speedInStepsPerSecond, float accelerationInStepsPerSecondPerSecond)
{
  float speedInStepsPerSecond_X;
  float accelerationInStepsPerSecondPerSecond_X;
  float speedInStepsPerSecond_Y;
  float accelerationInStepsPerSecondPerSecond_Y;
  float speedInStepsPerSecond_Z;
  float accelerationInStepsPerSecondPerSecond_Z;
  float speedInStepsPerSecond_A;
  float accelerationInStepsPerSecondPerSecond_A;

  long absStepsX;
  long absStepsY;
  long absStepsZ;
  long absStepsA;
  long maxStep;
  long maxStep_;

  //
  // setup initial speed and acceleration values
  //
  speedInStepsPerSecond_X = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond;
  
  speedInStepsPerSecond_Y = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond;

  speedInStepsPerSecond_Z = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Z = accelerationInStepsPerSecondPerSecond;

  speedInStepsPerSecond_A = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_A = accelerationInStepsPerSecondPerSecond;


  //
  // determine how many steps each motor is moving
  //
  if (stepsX >= 0)
    absStepsX = stepsX;
  else
    absStepsX = -stepsX;
 
  if (stepsY >= 0)
    absStepsY = stepsY;
  else
    absStepsY = -stepsY;

  if (stepsZ >= 0)
    absStepsZ = stepsZ;
  else
    absStepsZ = -stepsZ;

  if (stepsA >= 0)
    absStepsA = stepsA;
  else
    absStepsA = -stepsA;

  maxStep = max(absStepsX, max(absStepsY,max(absStepsZ,absStepsA)));
  if (absStepsX == maxStep){
  maxStep_ = stepsX;
  }else if (absStepsY == maxStep){
  maxStep_ = stepsY;
  }else if (absStepsY == maxStep){
  maxStep_ = stepsZ;
  }else if (absStepsA == maxStep){
  maxStep_ = stepsA;
  }

  if (maxStep_ != 0)
  {
    float scalerX = (float)maxStep / (float) absStepsX;
    float scalerY = (float)maxStep / (float) absStepsY;
    float scalerZ = (float)maxStep / (float) absStepsZ;
    float scalerA = (float)maxStep / (float) absStepsA;

    speedInStepsPerSecond_X = speedInStepsPerSecond_X * scalerX;
    accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond_X * scalerX;
    speedInStepsPerSecond_Y = speedInStepsPerSecond_Y * scalerY;
    accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond_Y * scalerY;
    speedInStepsPerSecond_Z = speedInStepsPerSecond_Z * scalerZ;
    accelerationInStepsPerSecondPerSecond_Z = accelerationInStepsPerSecondPerSecond_Z * scalerZ;
    speedInStepsPerSecond_A = speedInStepsPerSecond_A * scalerA;
    accelerationInStepsPerSecondPerSecond_A = accelerationInStepsPerSecondPerSecond_A * scalerA;
  }
  
  //
  // setup the motion for the X motor
  //
  stepperX.setSpeedInStepsPerSecond(speedInStepsPerSecond_X);
  stepperX.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_X);
  stepperX.setTargetPositionRelativeInSteps(stepsX);

  //
  // setup the motion for the Y motor
  //
  stepperY.setSpeedInStepsPerSecond(speedInStepsPerSecond_Y);
  stepperY.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Y);
  stepperY.setTargetPositionRelativeInSteps(stepsY);

  //
  // setup the motion for the Y motor
  //
  stepperZ.setSpeedInStepsPerSecond(speedInStepsPerSecond_Z);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Z);
  stepperZ.setTargetPositionRelativeInSteps(stepsZ);

  stepperA.setSpeedInStepsPerSecond(speedInStepsPerSecond_A);
  stepperA.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_A);
  stepperA.setTargetPositionRelativeInSteps(stepsA);
  //
  // now execute the moves, looping until both motors have finished
  //
  while((!stepperX.motionComplete()) || (!stepperY.motionComplete())|| (!stepperZ.motionComplete())|| (!stepperA.motionComplete()))
  {
    stepperX.processMovement();
    stepperY.processMovement();
    stepperZ.processMovement();
    stepperA.processMovement();
  }
}


/*
void runJustTheAStepper() 
{
  //
  // set the speed and acceleration rates for the stepper motor
  //
  stepperA.setSpeedInStepsPerSecond(100);
  stepperA.setAccelerationInStepsPerSecondPerSecond(100);

  //
  // Rotate the motor in the forward direction one revolution (200 steps). 
  // This function call will not return until the motion is complete.
  //
  stepperA.moveRelativeInSteps(200);

  //
  // now that the rotation has finished, delay 1 second before starting 
  // the next move
  //
  delay(1000);

  //
  // rotate backward 1 rotation, then wait 1 second
  //
  stepperA.moveRelativeInSteps(-200);
  delay(1000);

  //
  // This time speedup the motor, turning 10 revolutions.  Note if you
  // tell a stepper motor to go faster than it can, it just stops.
  //
  stepperA.setSpeedInStepsPerSecond(800);
  stepperA.setAccelerationInStepsPerSecondPerSecond(800);
  stepperA.moveRelativeInSteps(200 * 10);
  delay(2000);
}


void runBothXAndYSteppers() 
{
  long stepsX = -200 * 1;
  long stepsY = 200 * 1;
  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYWithCoordination(stepsX, stepsY, speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);

  //
  // turn one motor 5 revolutions, the other motor just 1
  //
  stepsX = -200 * 1;
  stepsY = 200 * 5;
  speedInStepsPerSecond = 500;
  accelerationInStepsPerSecondPerSecond = 500;
  moveXYWithCoordination(stepsX, stepsY, speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(3000);
}


void moveXYWithCoordination(long stepsX, long stepsY, float speedInStepsPerSecond, float accelerationInStepsPerSecondPerSecond)
{
  float speedInStepsPerSecond_X;
  float accelerationInStepsPerSecondPerSecond_X;
  float speedInStepsPerSecond_Y;
  float accelerationInStepsPerSecondPerSecond_Y;
  long absStepsX;
  long absStepsY;

  //
  // setup initial speed and acceleration values
  //
  speedInStepsPerSecond_X = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond;
  
  speedInStepsPerSecond_Y = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond;


  //
  // determine how many steps each motor is moving
  //
  if (stepsX >= 0)
    absStepsX = stepsX;
  else
    absStepsX = -stepsX;
 
  if (stepsY >= 0)
    absStepsY = stepsY;
  else
    absStepsY = -stepsY;


  //
  // determine which motor is traveling the farthest, then slow down the
  // speed rates for the motor moving the shortest distance
  //
  if ((absStepsX > absStepsY) && (stepsX != 0))
  {
    //
    // slow down the motor traveling less far
    //
    float scaler = (float) absStepsY / (float) absStepsX;
    speedInStepsPerSecond_Y = speedInStepsPerSecond_Y * scaler;
    accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond_Y * scaler;
  }
  
  if ((absStepsY > absStepsX) && (stepsY != 0))
  {
    //
    // slow down the motor traveling less far
    //
    float scaler = (float) absStepsX / (float) absStepsY;
    speedInStepsPerSecond_X = speedInStepsPerSecond_X * scaler;
    accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond_X * scaler;
  }

  
  //
  // setup the motion for the X motor
  //
  stepperX.setSpeedInStepsPerSecond(speedInStepsPerSecond_X);
  stepperX.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_X);
  stepperX.setTargetPositionRelativeInSteps(stepsX);


  //
  // setup the motion for the Y motor
  //
  stepperY.setSpeedInStepsPerSecond(speedInStepsPerSecond_Y);
  stepperY.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Y);
  stepperY.setTargetPositionRelativeInSteps(stepsY);


  //
  // now execute the moves, looping until both motors have finished
  //
  while((!stepperX.motionComplete()) || (!stepperY.motionComplete()))
  {
    stepperX.processMovement();
    stepperY.processMovement();
  }
}



void runXYZSteppers() 
{
  long stepsX = -200 * 1;
  long stepsY = 200 * 1;
  long stepsZ = -200 * 1;

  float speedInStepsPerSecond = 100;
  float accelerationInStepsPerSecondPerSecond = 100;
  moveXYZWithCoordination(stepsX, stepsY, stepsZ,speedInStepsPerSecond, accelerationInStepsPerSecondPerSecond);
  delay(1000);
}
void moveXYZWithCoordination(long stepsX, long stepsY, long stepsZ, float speedInStepsPerSecond, float accelerationInStepsPerSecondPerSecond)
{
  float speedInStepsPerSecond_X;
  float accelerationInStepsPerSecondPerSecond_X;
  float speedInStepsPerSecond_Y;
  float accelerationInStepsPerSecondPerSecond_Y;
  float speedInStepsPerSecond_Z;
  float accelerationInStepsPerSecondPerSecond_Z;
  long absStepsX;
  long absStepsY;
  long absStepsZ;
  long maxStep;
  long maxStep_;

  //
  // setup initial speed and acceleration values
  //
  speedInStepsPerSecond_X = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond;
  
  speedInStepsPerSecond_Y = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond;

  speedInStepsPerSecond_Z = speedInStepsPerSecond;
  accelerationInStepsPerSecondPerSecond_Z = accelerationInStepsPerSecondPerSecond;


  //
  // determine how many steps each motor is moving
  //
  if (stepsX >= 0)
    absStepsX = stepsX;
  else
    absStepsX = -stepsX;
 
  if (stepsY >= 0)
    absStepsY = stepsY;
  else
    absStepsY = -stepsY;

  if (stepsZ >= 0)
    absStepsZ = stepsZ;
  else
    absStepsZ = -stepsZ;

  maxStep = max(absStepsX, max(absStepsY,absStepsZ));
  if (absStepsX == maxStep){
  maxStep_ = stepsX;
  }else if (absStepsY == maxStep){
  maxStep_ = stepsY;
  }else if (absStepsY == maxStep){
  maxStep_ = stepsZ;
  }

  if (maxStep_ != 0)
  {
    float scalerX = (float)maxStep / (float) absStepsX;
    float scalerY = (float)maxStep / (float) absStepsY;
    float scalerZ = (float)maxStep / (float) absStepsZ;

    speedInStepsPerSecond_X = speedInStepsPerSecond_X * scalerX;
    accelerationInStepsPerSecondPerSecond_X = accelerationInStepsPerSecondPerSecond_X * scalerX;
    speedInStepsPerSecond_Y = speedInStepsPerSecond_Y * scalerY;
    accelerationInStepsPerSecondPerSecond_Y = accelerationInStepsPerSecondPerSecond_Y * scalerY;
    speedInStepsPerSecond_Z = speedInStepsPerSecond_Z * scalerZ;
    accelerationInStepsPerSecondPerSecond_Z = accelerationInStepsPerSecondPerSecond_Z * scalerZ;
  }
  
  //
  // setup the motion for the X motor
  //
  stepperX.setSpeedInStepsPerSecond(speedInStepsPerSecond_X);
  stepperX.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_X);
  stepperX.setTargetPositionRelativeInSteps(stepsX);


  //
  // setup the motion for the Y motor
  //
  stepperY.setSpeedInStepsPerSecond(speedInStepsPerSecond_Y);
  stepperY.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Y);
  stepperY.setTargetPositionRelativeInSteps(stepsY);

  //
  // setup the motion for the Y motor
  //
  stepperZ.setSpeedInStepsPerSecond(speedInStepsPerSecond_Z);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(accelerationInStepsPerSecondPerSecond_Z);
  stepperZ.setTargetPositionRelativeInSteps(stepsZ);


  //
  // now execute the moves, looping until both motors have finished
  //
  while((!stepperX.motionComplete()) || (!stepperY.motionComplete())|| (!stepperZ.motionComplete()))
  {
    stepperX.processMovement();
    stepperY.processMovement();
    stepperZ.processMovement();
  }
}
*/
