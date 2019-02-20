#include <SharpIR.h>

#define HIGH_SPEED 1000
#define LOW_SPEED 200
#define IR A0 // IR Analog Pin
#define MODEL 1080 // IR Sensor Model


SharpIR SharpIR(IR, MODEL);

int M1 = 4;     //Motor 1
int S1 = 5;     //M1 Speed

int M2 = 7;     //Motor 2
int S2 = 6;     //M2 Speed

int dist; // The Distance sensed by the IR Sensor
int on_precipie;


void setup(void) 
{ 
  Serial.begin(9600);
} 
 
void loop(void) 
{
  
  dist = SharpIR.distance();  
  on_precipie = digitalRead(2); 

  if (dist < 15 & !on_precipie){
    stop();
    
    } else {
    setSpeedHigh();
    moveForward();      
    }

}

void moveForward() {
  digitalWrite(M1,HIGH);    
  digitalWrite(M2,HIGH); 
}

void setSpeedHigh() {
   analogWrite (S1,HIGH_SPEED);
   analogWrite (S2,HIGH_SPEED); 
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
