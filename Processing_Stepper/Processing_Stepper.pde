import processing.serial.*;
import controlP5.*;

Serial myPort;  // Create object from Serial class
ControlP5 cp5;
int lastStep = 0;
int totalStep = 0;
int totalStep_ = 0;

int intLastStep;
String message;

void setup() {
  size(800, 400);
  cp5 = new ControlP5(this);
  myPort = new Serial(this, "COM8", 9600);  // Replace "COM3" with your Arduino's port
  //cp5.addSlider("Speed")
  //   .setPosition(50, 50)
  //    .setSize(600, 50)
  //   .setRange(0, 150)
  //   .setValue(0);
  //cp5.addSlider("Acceleration")
  //   .setPosition(50, 150)
  //   .setSize(600, 50)
  //   .setRange(0, 200)
  //   .setValue(0);
  cp5.addSlider("Step")
     .setPosition(50, 250)
     .setSize(600, 100)
     .setRange(-200, 200)
     .setValue(0);
     
//   myPort.write(800);
}

void draw() {
  //float Speed = cp5.getController("Speed").getValue();
  //float Acceleration = cp5.getController("Acceleration").getValue();
  background(200);
  int step = int(cp5.getController("Step").getValue());

  if (lastStep != step)
  {
    lastStep = step;
    totalStep += lastStep;
    if (totalStep<= 200 && totalStep>=-200){
    intLastStep = int(lastStep);
    totalStep_ += intLastStep;
    message = str(intLastStep);
    //println("message: " + message);
    myPort.write(message+"\n");
    }
    else if (totalStep>200){
      intLastStep = 200-totalStep_;
      totalStep_ += intLastStep;
      totalStep = totalStep_;
      message = str(intLastStep);
      println("message: " + message);
      myPort.write(message+"\n");
    }
    else if (totalStep<-200){
      intLastStep = -totalStep_-200;
      totalStep_ += intLastStep;
      totalStep = totalStep_;
      message = str(intLastStep);
      println("message: " + message);
      myPort.write(message+"\n");
    }
    }
  
    text("Total Step: " + totalStep_, 50, 100);

//  println("intStep: " + intStep);
//  String message = "0";
//  println("message1: " + message);
//  println("message2: " + message);
 //// String message = str(Step);//error
  //myPort.write(message+ "\n"); 
}
