#include <IRremote.h>

//1838
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

//L298N
int LeftIn1 = 2;//L298N In3
int LeftIn2 = 3;//L298N In4
int RightIn1 = 8;
int RightIn2 = 9;

//Time
unsigned long RefMillis = 0;
int Period = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(LeftIn1, OUTPUT);
  pinMode(LeftIn2, OUTPUT);
  pinMode(RightIn1, OUTPUT);
  pinMode(RightIn2, OUTPUT);

  Serial.println("Period0 Start -Init");
}

void loop() {
  //1838
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    //Serial.println(results.value);
    irrecv.resume(); // Receive the next value
  }

  //Time and Period //Overflow not considered
  switch (Period) {
  case 0:
    if (millis() >= RefMillis + 10000) {
      RefMillis = millis();
      Period = 1;
      Serial.println("Period1 Start");
    }
    break;
  case 1:
    if (millis() >= RefMillis + 10000) {
      RefMillis = millis();
      Period = 2;
      Serial.println("Period2 Start");
    }
    break;
  case 2:
    if (millis() >= RefMillis + 10000) {
      RefMillis = millis();
      Period = 0;
      Serial.println("Period0 Start");
    }
    break;
  default:
    RefMillis = millis();
    Period = 0;
    break;
  }

  //Action
  switch (Period) {
  case 0:
    digitalWrite(LeftIn1, LOW);
    digitalWrite(LeftIn2, HIGH);
    digitalWrite(RightIn1, LOW);
    digitalWrite(RightIn2, HIGH);
    break;
  case 1:
    digitalWrite(LeftIn1, HIGH);
    digitalWrite(LeftIn2, LOW);
    digitalWrite(RightIn1, LOW);
    digitalWrite(RightIn2, HIGH);
    break;
  case 2:
    digitalWrite(LeftIn1, LOW);
    digitalWrite(LeftIn2, HIGH);
    digitalWrite(RightIn1, HIGH);
    digitalWrite(RightIn2, LOW);
    break;
  }
}

/*L298N
ENA IN1 IN2 StateDisc
0   x   x   Stop
1   0   0   ForceStop
1   0   1   TurnForword
1   1   0   TurnBackword
1   1   1   ForceStop
*/

/*key code of my remoter
 * KEY    HEX
 * on/off FFA25D
 * menu   FFE21D
 * test   FF22DD
 * +      FF02FD
 * back   FFC23D
 * last   FFE01F
 * play   FFA857
 * next   FF906F
 * 0      FF6897
 * -      FF9867
 * C      FFB04F
 * 1      FF30CF
 * 2      FF18E7
 * 3      FF7A85
 * 4      FF10EF
 * 5      FF38C7
 * 6      FF5AA5
 * 7      FF42BD
 * 8      FF4AB5
 * 9      FF52AD
*/
