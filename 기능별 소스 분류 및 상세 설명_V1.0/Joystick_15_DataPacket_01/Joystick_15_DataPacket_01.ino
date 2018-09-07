//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
#include <SoftwareSerial.h>

SoftwareSerial bleSerial(A0, A1); // RX, TX
//-----------------------------------------------
void setup()
{
  Serial.begin(9600);
  bleSerial.begin(9600);
  Serial.println("Data Packet Test 01");

  for(int i = 2; i < 8; i++)
  {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }

  delay(500);

  bleSerial.print("atd");
  bleSerial.print("083a5c1f015b");
  bleSerial.print("\r");

  delay(500);
}

void loop()
{
  if(!digitalRead(2))
  {
    bleSerial.print("at+writeh0006");
    //
    bleSerial.print("f0");
    bleSerial.print("a1");
    bleSerial.print("64");
    bleSerial.print("64");
    bleSerial.print("64");
    bleSerial.print("78");
    bleSerial.print("01");
    bleSerial.print("46");
    //
    bleSerial.print("\r");
    delay(300);
  }
}

