#include <SoftwareSerial.h>
SoftwareSerial m(2, 3);//rx 2 tx 3
void setup() {
  // put your setup code here, to run once:
m.begin(9600);//gsm
Serial.begin(9600);
pinMode(4,INPUT);
pinMode(LED_BUILTIN, OUTPUT);
m.println("AT");
delay(2000);
}

void loop() {
  if(digitalRead(4))
  {
    Serial.println("Calling");
    m.println("ATD1234567890;");       //change 1234567890 to mobile number
    delay(5000);
      Serial.println("Message Sending");
      m.println("AT+CMGF=1");
      delay(1000);
      m.println("AT+CMGS=\"1234567890\"");        //change 1234567890 to mobile number
      delay(1000);
      m.println("Hello from GSM");
      m.write(26);                                                 // clr z
      Serial.println("Message connected");
      delay(5000);
       digitalWrite(LED_BUILTIN, HIGH );
        delay(1000);
        }
         digitalWrite(LED_BUILTIN, LOW );
}
