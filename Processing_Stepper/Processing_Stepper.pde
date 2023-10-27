import processing.serial.*;
import controlP5.*;

Serial myPort;  // Create object from Serial class
ControlP5 cp5;


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
     .setSize(600, 50)
     .setRange(0, 2000)
     .setValue(0);
     
   myPort.write(800);
}

void draw() {
  background(200);
  //float Speed = cp5.getController("Speed").getValue();
  //float Acceleration = cp5.getController("Acceleration").getValue();
  background(200);
  float Step = cp5.getController("Step").getValue();
   text(Step,50,50);
   String message = "0";
 // String message = str(Step);
  myPort.write(message+ "\n"); // Send the message as a string
}
