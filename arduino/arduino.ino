#define HIGH_SPEED 200
#define LOW_SPEED 100

int M1 = 4;     //Motor 1
int S1 = 5;     //M1 Speed

int M2 = 7;     //Motor 2
int S2 = 6;     //M2 Speed

void setup(void) 
{ 
  Serial.begin(9600);

} 
 
void loop(void) 
{
//  setSpeedHigh();
//  moveForward();
}

void moveForward() {
  digitalWrite(M1,HIGH);    
  digitalWrite(M2,HIGH); 
}

void setSpeedHigh() {
   analogWrite (S1,HIGH_SPEED);
   analogWrite (S2,HIGH_SPEED); 
 }


void setSpeedLow() {
   analogWrite (S1,LOW_SPEED);
   analogWrite (S2,LOW_SPEED); 
 }
