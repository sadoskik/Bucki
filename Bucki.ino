/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */
// unsigned ints avoid the issues from micros() rolling back over every x minutes
unsigned int weapon = 13;
unsigned int fireTime;
unsigned int rechargeTime;
bool active;

unsigned int RECHARGE_DURATION = 8000000;//microseconds until the weapon can fire again
unsigned int FIRE_DURATION = 2000000;//microseconds the valve can be open
#include <SoftwareSerial.h>
SoftwareSerial BTSerial (2,3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Enter AT Commands");
  BTSerial.begin(9600);
  pinMode(weapon, OUTPUT);
  write(weapon, LOW);

  active = false;
  rechargeTime = micros();
  fireTime = micros();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if(BTSerial.available()){
    char command = BTSerial.read();
    Serial.write(command);
    
    if(command = 'F')
    {
      
      if(now - rechargeTime > RECHARGE_DURATION && !active)
      {
        Serial.write("FIRING!\n");
        fireTime = micros();
        write(weapon, HIGH);
        active = true;
      }
      else
      {
        Serial.write("Cannot fire because it is firing or hasn't recharged\n");
      }
    }
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }

  if(micros() - fireTime > FIRE_DURATION && active)
  {
    Serial.write("Max fire time reached\n");
    write(weapon, LOW);
    active = false;
    rechargeTime = micros();
  }
  else if(micros() - rechargeTime > RECHARGE_DURATION && !active)
  {
    Serial.write("Nothing here yet, maybe an LED indicator that it's ready to fire?\n");
  }
}
