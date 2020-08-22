/*
 * Author       : Mohamed Ashraf
 * Date         : 8/21/2020 
 * Description  : baby monitoring
 *                - If the Baby cries, it should send a message that the baby is crying then stop the loop
 *                - if the baby moves more than 5 seconds, it should send a message that the baby is moving
 *                - by that we can be notified when the baby is awake, and check on him, then we need to reset
 */

#define SoundSensorPin      2
#define PIRMotionSensorPin  4
#define BuzzerPin           5

int SoundSensorValue = 0;
int PIRMotionSensorValue = 0;

void setup() {
  pinMode(SoundSensorPin,     INPUT);
  pinMode(PIRMotionSensorPin, INPUT);
  pinMode(BuzzerPin,     OUTPUT);
}

void loop() {
  SoundSensorValue = digitalRead(SoundSensorPin);
  PIRMotionSensorValue = digitalRead(PIRMotionSensorPin);

  if(SoundSensorValue == HIGH)
  {
    digitalWrite(BuzzerPin, HIGH);
  }
  else{
    digitalWrite(BuzzerPin, LOW);
  }

  
  if(PIRMotionSensorValue == HIGH)
  {
    delay(500);
    PIRMotionSensorValue = digitalRead(PIRMotionSensorPin);
    if(PIRMotionSensorValue == HIGH)
    {
      digitalWrite(BuzzerPin, HIGH);
    }
    else{
      digitalWrite(BuzzerPin, LOW);
    }
  }
}
