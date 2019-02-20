#include <SharpIR.h>
#include <Servo.h> 

#define HIGH_SPEED 1000
#define LOW_SPEED 200

#define IR A0 // IR Analog Pin
#define MODEL 1080 // IR Sensor Model

#define PANPIN 8
#define TILTPIN 7


// Based on https://github.com/araffin/arduino-robust-serial/blob/master/arduino-board/slave.cpp
// See SERIALLICENSE for more details. 


#define  PANSERVO 0
#define  TILTSERVO 1
#define  STOP 2
#define  EXPLORE 3

void wait_for_bytes(int num_bytes, unsigned long timeout)
{
	unsigned long startTime = millis();
	//Wait for incoming bytes or exit if timeout
	while ((Serial.available() < num_bytes) && (millis() - startTime < timeout)){}
}

// NOTE : Serial.readBytes is SLOW
// this one is much faster, but has no timeout
void read_signed_bytes(int8_t* buffer, size_t n)
{
	size_t i = 0;
	int c;
	while (i < n)
	{
		c = Serial.read();
		if (c < 0) break;
		*buffer++ = (int8_t) c; // buffer[i] = (int8_t)c;
		i++;
	}
}

int16_t read_i16()
{
  int8_t buffer[2];
	wait_for_bytes(2, 100); // Wait for 2 bytes with a timeout of 100 ms
	read_signed_bytes(buffer, 2);
  return (((int16_t) buffer[0]) & 0xff) | (((int16_t) buffer[1]) << 8 & 0xff00);
}

int read_order(){
  return Serial.read();
}

void read_serial(){
  if (Serial.available() > 0) {
    int order_received = read_order();
    
    switch (order_received){
      case PANSERVO: {
        int angle = read_i16();
        writePan(angle);
        break;
      }

      case TILTSERVO: {
        int angle = read_i16();
        writeTilt(angle);
        break;
      }


    }

  }
}

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
  panServo.attach(PANPIN);
  tiltServo.attach(TILTPIN);
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

//  panServo.write(110);
//  tiltServo.write(30);
//
//  delay(1000);
//
//  panServo.write(90);
//  tiltServo.write(40);
//
//  delay(10000);

  read_serial();

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

