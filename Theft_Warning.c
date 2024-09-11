#include <SoftwareSerial.h>

// Initialize SoftwareSerial to communicate with GSM module on pins 2 (RX) and 3 (TX)
SoftwareSerial m(2, 3); // RX pin 2, TX pin 3

// Define status flags to track if the call and message have been sent
volatile int call_stat = 0;
volatile int message_stat = 0;

void setup() 
{
  // Initialize the GSM and Serial communication
  m.begin(9600);               // Start GSM module communication at 9600 baud
  Serial.begin(9600);          // Start Serial monitor communication at 9600 baud for debugging
  
  // Configure pins
  pinMode(5, INPUT);           // Pin 5 for button input
  pinMode(LED_BUILTIN, OUTPUT); // Built-in LED as output (pin 13)
  pinMode(6, OUTPUT);          // Pin 6 as output (you can connect an additional LED or buzzer)
  
  // Send an AT command to check if the GSM module is ready
  m.println("AT");
  delay(2000);                 // Delay to give time for the GSM module to respond
}

void loop() 
{
  // PIR sensor connected to pin 5
  if (digitalRead(5) == HIGH) 
  {
    // Turn on the built-in LED
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    
    // Turn on pin 6 (could be connected to an external LED or buzzer)
    digitalWrite(6, HIGH);
    delay(1000);

    // Check if the call hasn't been made, and initiate the call
    if (call_stat == 0) 
    {
      call();  // Call the function to make the phone call
    }

    // Check if the message hasn't been sent, and send the message
    if (message_stat == 0) 
    {
      message();  // Call the function to send the SMS message
    }
  } 
  
  // Turn off the LEDs after actions are completed
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(6, LOW);
  delay(1000);
}

// Function to make the call
void call() {
  call_stat = 1;  // Set the flag indicating the call has been made
  Serial.println("Calling...");
  m.println("ATD1234567890;");  // Command to dial the number (replace with your actual phone number)
  delay(5000);  // Wait for 5 seconds to allow the call to go through
}

// Function to send the SMS message
void message() {
  message_stat = 1;  // Set the flag indicating the message has been sent
  Serial.println("Message Sending...");
  
  // Set GSM module to SMS mode (text mode)
  m.println("AT+CMGF=1");
  delay(1000);

  // Prepare to send an SMS to the given number (replace 1234567890 with your actual phone number)
  m.println("AT+CMGS=\"1234567890\"");
  delay(1000);
  
  // Send the actual message content
  m.println("Hello from GSM");
  
  // Send the special character (CTRL+Z, ASCII code 26) to indicate the end of the message
  m.write(26);
  
  Serial.println("Message Sent");
  delay(5000);  // Wait for 5 seconds to ensure the message is sent
}
