//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("Adc Test 01");
}

void loop()
{
  unsigned int adc4 = analogRead(4);

  Serial.println(adc4);
  delay(500);
}

