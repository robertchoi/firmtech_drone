//-----------------------------------------------
//-----------------------------------------------
#include <SoftwareSerial.h>

#define OPERATION_STEP_0  0
#define OPERATION_STEP_1  1
#define OPERATION_STEP_2  2
#define OPERATION_STEP_3  3
#define OPERATION_STEP_4  4
#define OPERATION_STEP_5  5
#define OPERATION_STEP_6  6
#define OPERATION_STEP_7  7
#define OPERATION_STEP_8  8
#define OPERATION_STEP_9  9
#define OPERATION_STEP_10  10
#define OPERATION_STEP_11  11
#define OPERATION_STEP_12  12

SoftwareSerial bleSerial(A0, A1); // RX, TX
//-----------------------------------------------
String uartString = "";
unsigned int currentStep;
//-----------------------------------------------
void setup()
{
  Serial.begin(9600);
  bleSerial.begin(9600);

  for(int i = 2; i < 8; i++)
  {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }
  
  currentStep = 0;
}

void loop()
{
  switch(currentStep)
  {
    case OPERATION_STEP_0:
      Serial.println("Check Message Test 01");
      currentStep++;
    break;
    case OPERATION_STEP_1:
      if(!digitalRead(6))
      {
        Serial.println("Pressed Connect Button");
        bleSerial.print("atd");
        bleSerial.print("083a5c1f015b");
        bleSerial.print("\r");
        delay(300);
        uartString = "";
        currentStep++;
      }
    break;
    case OPERATION_STEP_2:
      if(bleSerial.available())
      {
        char inChar = bleSerial.read();
        uartString += inChar;
        //
        if( uartString.length() > 4
         && uartString.startsWith("\r\n")
         && uartString.endsWith("\r\n") )
        {
          currentStep++;
        }
      }
    break;
    case OPERATION_STEP_3:
      if(uartString.equals("\r\nOK\r\n"))
      {
        Serial.println("Received OK");
        delay(300);
        uartString = "";
        currentStep++;
      }
    break;
    case OPERATION_STEP_4:
      if(bleSerial.available())
      {
        char inChar = bleSerial.read();
        uartString += inChar;
        //
        if( uartString.length() > 4
         && uartString.startsWith("\r\n")
         && uartString.endsWith("\r\n") )
        {
          currentStep++;
        }
      }
    break;
    case OPERATION_STEP_5:
      if(uartString.startsWith("\r\nCONNECT "))
      {
        Serial.println("Received CONNECT");
        delay(300);
        uartString = "";
        currentStep++;
      }
    break;
    case OPERATION_STEP_6:
      if(bleSerial.available())
      {
        bleSerial.read();
      }
      
      if(!digitalRead(7))
      {
        Serial.println("Pressed Disconnect Button");
        bleSerial.print("ath");
        bleSerial.print("\r");
        delay(300);
        uartString = "";
        currentStep++;
      }
    break;
    case OPERATION_STEP_7:
      if(bleSerial.available())
      {
        char inChar = bleSerial.read();
        uartString += inChar;
        //
        if( uartString.length() > 4
         && uartString.startsWith("\r\n")
         && uartString.endsWith("\r\n") )
        {
          currentStep++;
        }
      }
    break;
    case OPERATION_STEP_8:
      if(uartString.equals("\r\nOK\r\n"))
      {
        Serial.println("Received OK");
        delay(300);
        uartString = "";
        currentStep++;
      }
    break;
    case OPERATION_STEP_9:
      if(bleSerial.available())
      {
        char inChar = bleSerial.read();
        uartString += inChar;
        //
        if( uartString.length() > 4
         && uartString.startsWith("\r\n")
         && uartString.endsWith("\r\n") )
        {
          currentStep++;
        }
      }
    break;
    case OPERATION_STEP_10:
      if(uartString.startsWith("\r\nDISCONNECT"))
      {
        Serial.println("Recieved DISCONNECT");
        delay(300);
        uartString = "";
        currentStep++;
      }
    break;
    case OPERATION_STEP_11:
      if(bleSerial.available())
      {
        char inChar = bleSerial.read();
        uartString += inChar;
        //
        if( uartString.length() > 4
         && uartString.startsWith("\r\n")
         && uartString.endsWith("\r\n") )
        {
          currentStep++;
        }
      }
    break;
    case OPERATION_STEP_12:
      if(uartString.startsWith("\r\nREADY"))
      {
        Serial.println("Recieved READY");
        delay(300);
        uartString = "";
        currentStep = OPERATION_STEP_1;
      }
    break;
  }
}

