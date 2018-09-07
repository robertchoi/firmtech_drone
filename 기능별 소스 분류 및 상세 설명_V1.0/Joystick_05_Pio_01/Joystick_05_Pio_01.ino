//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("PIO Test 01");

  for(int i = 2; i < 8; i++)
  {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }
}

void loop()
{
  if(!digitalRead(6))
  {
    Serial.println("Press 6");
  }
}

