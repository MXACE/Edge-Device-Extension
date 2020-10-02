#include <string.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Turn off the LEDs
  Serial.println("start;");
}
String s;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
    {
      s = Serial.readString();
      Serial.println(s);
    }
}
