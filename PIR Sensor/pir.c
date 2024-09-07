int LDR = 4;
void setup() 
  {
    Serial.begin(9600);
    pinMode(LDR, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
  }

void loop() 
  {
    int x = digitalRead(LDR);
    Serial.println(x);
    delay(1); 
    if (x==1)//NO LIGHT DETECTION
      {
        digitalWrite(LED_BUILTIN, HIGH );
        delay(1000);
      }
        else
        {
        digitalWrite(LED_BUILTIN, LOW );
       
      }
  }
