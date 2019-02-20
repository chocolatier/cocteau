#include <SharpIR.h>
#include <Servo.h> 

#define HIGH_SPEED 1000
#define LOW_SPEED 200
#define IR A0 // IR Analog Pin
#define MODEL 1080 // IR Sensor Model

SharpIR SharpIR(IR, MODEL);

Servo panServo;   
Servo tiltServo;   

// Note: The Documentation calls S1,S2 E1 and E2. 
// Not sure why that is. I've named them S1, S2
// for speed control.
int M1 = 4;     //Motor 1
int S1 = 5;     //M1 Speed

int M2 = 7;     //Motor 2
int S2 = 6;     //M2 Speed

int dist; // The Distance sensed by the IR Sensor
int on_precipie;


void setup(void) 
{ 
  Serial.begin(9600);
  panServo.attach(8);
  tiltServo.attach(7);
} 
 
void loop(void) 
{
  
//  dist = SharpIR.distance();  
//  on_precipie = digitalRead(2); 
//
//  if (dist < 15 & !on_precipie){
//    stop();
//    
//    } else {
//    setSpeedHigh();
//    moveForward();      
//    }

  panServo.write(110);
  tiltServo.write(30);

  delay(1000);

  panServo.write(90);
  tiltServo.write(40);

  delay(10000);

}

void moveForward() {
  digitalWrite(M1,HIGH);    
  digitalWrite(M2,HIGH); 
}

void setSpeedHigh() {
   analogWrite (S1,HIGH_SPEED);
   analogWrite (S2,HIGH_SPEED); 
 }


void writePan(int angle) {
    panServo.write(angle);
  }

void writeTilt(int angle) {
    tiltServo.write(angle);
  }


void turnLeft() {
   analogWrite (S1,0);
   analogWrite (S2,HIGH_SPEED); 
   moveForward();
  }

void turnRight() {
   analogWrite (S1,HIGH_SPEED);
   analogWrite (S2,0); 
   moveForward();
  }

void stop() {
   analogWrite (S1,0);
   analogWrite (S2,0); 
}

void setSpeedLow() {
   analogWrite (S1,LOW_SPEED);
   analogWrite (S2,LOW_SPEED); 
 }
