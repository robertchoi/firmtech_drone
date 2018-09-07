//-----------------------------------------------
//-----------------------------------------------
#include <SoftwareSerial.h>

SoftwareSerial bleSerial(A0, A1); // RX, TX
//-----------------------------------------------
unsigned char startBit = 0xf0;
unsigned char commandBit = 0xa1;
unsigned char roll = 100;
unsigned char pitch = 100;
unsigned char yaw = 100;
unsigned char throttle = 0;
unsigned char operationBit = 0x05;
unsigned char checkSum = 0;
//-----------------------------------------------
void checkThrottle()
{
  //throttle: 감소시 하강, 증가시 상승
  if(!digitalRead(3))
  {
    if(throttle > 59)
      throttle -= 20;
    else if(throttle > 3)
      throttle -= 4;
  }
  else if(!digitalRead(2))
  {
    if(throttle < 20)
      throttle = 20;
    else if(throttle < 181)
      throttle += 20;
  }
}

void checkPitch()
{
  //pitch: 증가시 전진, 감소시 후진
  unsigned int secondPitch = analogRead(5);

  if(secondPitch < 400)
    pitch = 50;
  else if(secondPitch > 600)
    pitch = 150;
  else
    pitch = 100;
}

void checkRoll()
{
  //roll: 증가시 오른쪽 이동, 감소시 왼쪽 이동
  unsigned int secondRoll = analogRead(4);

  if(secondRoll < 400)
    roll = 50;
  else if(secondRoll > 600)
    roll = 150;
  else
    roll = 100;
}

void checkYaw()
{
  //Yaw: 감소시 좌회전, 증가시 우회전
  if(!digitalRead(4))
    yaw = 50;
  else if(!digitalRead(5))
    yaw = 150;
  else
     yaw = 100;
}

void checkEmergency()
{
  //비상버튼 눌리면, 모터 회전 즉시 0으로 설정.
  if(!digitalRead(6))
  {
    throttle = 0;
    roll = 100;
    pitch = 100;
    yaw = 100;
  }
}

void sendDroneCommand()
{
  bleSerial.print("at+writeh0006");
  //
  bleSerial.print(String(startBit,HEX));
  bleSerial.print(String(commandBit,HEX));
  bleSerial.print(String(roll,HEX));
  bleSerial.print(String(pitch,HEX));
  bleSerial.print(String(yaw,HEX));
  //
  if(throttle < 0x10)
    bleSerial.print("0" + String(throttle,HEX));
  else 
    bleSerial.print(String(throttle,HEX));
  //
  bleSerial.print("0" + String(operationBit,HEX));
  //
  if(checkSum < 0x10)
    bleSerial.print("0" + String(checkSum,HEX));
  else 
    bleSerial.print(String(checkSum,HEX));
  //
  bleSerial.print("\r");
}

void checkCRC()
{
  checkSum = commandBit + roll + pitch + yaw + throttle + operationBit;
  checkSum = checkSum & 0x00ff;
}
//-----------------------------------------------
void setup()
{
  Serial.begin(9600);
  bleSerial.begin(9600);
  Serial.println("Data Packet Test 07");

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
  checkThrottle();
  checkPitch();
  checkRoll();
  checkYaw();
  checkEmergency();
  //
  checkCRC();
  //
  sendDroneCommand();
  delay(100);
}

