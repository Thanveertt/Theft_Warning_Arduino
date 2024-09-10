#include <SoftwareSerial.h>
SoftwareSerial m(2, 3);    //rx 2 tx 3
volatile int call_stat=0;
volatile int message_stat=0;
void setup() 
{
m.begin(9600);              //gsm
Serial.begin(9600);
pinMode(5,INPUT);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(6, OUTPUT);
m.println("AT");
delay(2000);
}
void loop() 
{
  if(digitalRead(5))
  {
      digitalWrite(LED_BUILTIN, HIGH );
      delay(1000);
      digitalWrite(6,HIGH);
      delay(1000);
      if (call_stat==0)
      {
      call();
      }
      if (message_stat==0)
      {
      message();
      }
      }
      digitalWrite(LED_BUILTIN, LOW );
      delay(1000);
      digitalWrite(6, LOW );
      delay(1000);
}
