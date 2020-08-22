/*
 * Author       : Mohamed Ashraf
 * Date         : 8/21/2020 
 * Description  : baby monitoring
 *                - If the Baby cries, it should send a message that the baby is crying then stop the loop
 *                - if the baby moves more than 5 seconds, it should send a message that the baby is moving
 *                - by that we can be notified when the baby is awake, and check on him, then we need to reset
 */

#include <SoftwareSerial.h>


#define SoundSensorPin      3
#define PIRMotionSensorPin  4
#define LedPin              13

int   SoundSensorValue      = 0;
int   PIRMotionSensorValue  = 0;
bool  isCrying              = false;
bool  isMoving              = false;
bool  notReset              = true;

String   phone_number1 = "+ZZxxxxxxxxxx";    //change ZZ with country code and xxxxxxxxxxx with phone number to sms

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(8, 9); //SIM800L Tx & Rx is connected to Arduino #8 & #9


void setup() {

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  pinMode(SoundSensorPin,     INPUT);
  pinMode(PIRMotionSensorPin, INPUT);
  pinMode(LedPin,             OUTPUT);
  digitalWrite(LedPin,        LOW);
  sendSMS("the device reset", phone_number1);

}

void loop() {
  
  checkTheBabeyOnce();  

}


// Sending SMS via Sim800
void sendSMS(String message, String number) 
{ 
  String mnumber = "AT + CMGS = \""+number+"\"";
  mySerial.print("AT+CMGF=1\r");             
  delay(80);
  mySerial.println(mnumber);                                    
  delay(80);
  mySerial.println(message);       
  delay(80);
  mySerial.println((char)26);                       
  delay(80);
  mySerial.println();
  delay(100);
  Serial.print("sending message to");                                
}


bool checkCrying()
{
  SoundSensorValue = digitalRead(SoundSensorPin);
  if(SoundSensorValue == HIGH)
  {
    return true;
  }
  else{
    return false;
  }
}

void sendCryingMessage()
{
  digitalWrite(LedPin, HIGH);
  sendSMS("the baby is crying", phone_number1); 
}

bool checkMotion()
{
  PIRMotionSensorValue = digitalRead(PIRMotionSensorPin);
  if(PIRMotionSensorValue == HIGH)
  {
    delay(5000);
    PIRMotionSensorValue = digitalRead(PIRMotionSensorPin);
    if(PIRMotionSensorValue == HIGH)
    {
      return true;
    }
    else{
      return false;
    }
  }
}

void sendMotionMessage()
{
  digitalWrite(LedPin, HIGH);
  sendSMS("the baby is moving", phone_number1);
}

void checkTheBabeyOnce()
{
  while(notReset)
  {
    isCrying = checkCrying();
    isMoving = checkMotion();
  
    if(isCrying)
    {
      sendCryingMessage();
      notReset = false;
    }
    if(isMoving)
    {
      sendMotionMessage();
    }
  }
}
