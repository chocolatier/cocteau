#include <SharpIR.h>
#include <Servo.h> 

#define HIGH_SPEED 1000
#define LOW_SPEED 200

#define IR A0 // IR Analog Pin
#define MODEL 1080 // IR Sensor Model

#define PANPIN 8
#define TILTPIN 9


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


bool explore = true; // Whether the rover explores or not

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

      case STOP: {
          explore = false;
          break;
        }
      
      case EXPLORE: {
        explore = true;
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
int on_precipie; // Whether It's on a precipie. 

unsigned long backward_time = 0;
unsigned long turn_time = 0;

bool turn_dir = false;

void setup(void) 
{ 
//  Serial.begin(9600);
  panServo.attach(PANPIN);
  tiltServo.attach(TILTPIN);
  writePan(90);
  delay(1000);
  writeTilt(60);
} 

void loop(void) 
{
//
  

  if (explore){
    dist = SharpIR.distance();  
    on_precipie = digitalRead(2); 
    Serial.println(on_precipie);
    Serial.println(dist);

    if (millis() - backward_time < 5000){
        moveBackward();
      }
    else if (on_precipie){
        moveBackward();
        backward_time = millis();
      }
    else if (dist < 10){
        moveBackward();
        backward_time = millis() - 2500;
      }
    else if (dist < 20) {
        if (millis() - turn_time > 20000) {
            turn_dir = !turn_dir;
            turn_time = millis();
          }
        if (turn_dir) {
          turnLeft();
        } else {
          turnRight();  
        }

      } else {
        moveForward();  
      }

  } else {
      stop1();
  }
    
//  read_serial();

}

void moveForward() {
  digitalWrite(M1,HIGH);    
  digitalWrite(M2,HIGH); 
}

void moveBackward() {
  digitalWrite(M1,LOW);    
  digitalWrite(M2,LOW); 
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
  digitalWrite(M1,HIGH);  
  digitalWrite(M2,HIGH);  }

void turnRight() {
  analogWrite (S1,HIGH_SPEED);
  analogWrite (S2,0); 
  digitalWrite(M1,HIGH);  
  digitalWrite(M2,HIGH);  
  
  }

void stop1() {
  analogWrite (S1,0);
  analogWrite (S2,0); 
}

void setSpeedLow() {
  analogWrite (S1,LOW_SPEED);
  analogWrite (S2,LOW_SPEED); 
}
