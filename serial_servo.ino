#include <Servo.h>
Servo servox;
Servo servoy;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servox.attach(2);
  servoy.attach(4);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()==2)
  {
    servox.write(Serial.read());
    servoy.write(Serial.read());
  }
  delay(10);
}
