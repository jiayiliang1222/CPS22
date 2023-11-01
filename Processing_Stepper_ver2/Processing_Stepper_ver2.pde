import processing.serial.*;
import controlP5.*;
import oscP5.*;

OscP5 oscP5;  
Serial myPort;  // Create object from Serial class
ControlP5 cp5;

int Step = 0;
int totalStep = 0;
int totalStep_ = 0;
int gesture = 1;
int gesture_= 1;

String message;


boolean calm = false; 
boolean happy = false; 
boolean sad = false; 
boolean mad = false; 

void setup() {
  size(800, 400);
  cp5 = new ControlP5(this);
//  myPort = new Serial(this, "COM10", 9600);  // Replace "COM3" with your Arduino's port
  oscP5 = new OscP5(this, 12000);
  
  cp5.addSlider("totalStep")
     .setPosition(50, 250)
     .setSize(600, 100)
     .setRange(-200, 200)
     .setValue(0);
     }

void draw() {
  background(200);

  if (gesture_ != gesture)
  {
     String message = str(gesture) + "/n";
     println(gesture);
     gesture_ = gesture;
     println("message: " + message);
   //  myPort.write(message);
    }
    
    totalStep = int(cp5.getController("totalStep").getValue());
  if (totalStep_ != totalStep)
  {
     Step = totalStep-totalStep_;
     String message = str(Step);
     println("message: " + message);
     totalStep_ = totalStep;
    }
    text("Total Step: " + totalStep_, 50, 100);
}
void keyPressed() {
  if (key == '1') {
    println("1");
    myPort.write("1\n"); 
  }
   if (key == '2') {
    println("2");
    myPort.write("2\n"); 
  }
  if (key == '3') {
    println("3");
    myPort.write("3\n"); 
  }
  if (key == '4') {
    println("4");
    myPort.write("4\n"); 
  }
   if (key == '5') {
    println("5");
    myPort.write("5\n"); 
  }
}

void oscEvent(OscMessage theOscMessage) {  
  int oscArg = int(theOscMessage.get(0).floatValue()); 
//  println('1');
  gesture = oscArg;
}
