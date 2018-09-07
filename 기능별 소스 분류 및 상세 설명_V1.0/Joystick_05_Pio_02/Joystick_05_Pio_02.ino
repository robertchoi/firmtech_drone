//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("PIO Test 02");

  for(int i = 2; i < 8; i++)
  {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }
}

void loop()
{
  if(!digitalRead(2))
  {
    Serial.println("Press 2");
  }
  if(!digitalRead(3))
  {
    Serial.println("Press 3");
  }
  if(!digitalRead(4))
  {
    Serial.println("Press 4");
  }
  if(!digitalRead(5))
  {
    Serial.println("Press 5");
  }
  if(!digitalRead(6))
  {
    Serial.println("Press 6");
  }
  if(!digitalRead(7))
  {
    Serial.println("Press 7");
  }
}

