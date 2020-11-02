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
unsigned long RefTime = 0;

int cmd = 0;
int action = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(LeftIn1, OUTPUT);
  pinMode(LeftIn2, OUTPUT);
  pinMode(RightIn1, OUTPUT);
  pinMode(RightIn2, OUTPUT);

  Serial.println("-Init");
}

void loop() {
  //1838
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value

    RefTime = millis();
    action = 1;
  }
  else
  {
    if (millis() - RefTime >= 200)
    {
      action = 0;
    }
  }

  if (results.value == 16712445)
  {
    cmd = 1;
  }
  else if (results.value == 16750695)
  {
    cmd = 2;
  }
  else if (results.value == 16769055)
  {
    cmd = 3;
  }
  else if (results.value == 16748655)
  {
    cmd = 4;
  }
  else if (results.value == 4294967295)
  {
    cmd = cmd;
  }
  else
  {
    cmd = 0;
  } 

  if (action == 1) 
  {
    switch (cmd) {
      case 1:
        digitalWrite(LeftIn1, 0);
        digitalWrite(LeftIn2, 1);
        digitalWrite(RightIn1, 0);
        digitalWrite(RightIn2, 1);
        break;
      case 2:
        digitalWrite(LeftIn1, 1);
        digitalWrite(LeftIn2, 0);
        digitalWrite(RightIn1, 1);
        digitalWrite(RightIn2, 0);
        break;
      case 3:
        digitalWrite(LeftIn1, 1);
        digitalWrite(LeftIn2, 1);
        digitalWrite(RightIn1, 0);
        digitalWrite(RightIn2, 1);
        break;
      case 4:
        digitalWrite(LeftIn1, 0);
        digitalWrite(LeftIn2, 1);
        digitalWrite(RightIn1, 1);
        digitalWrite(RightIn2, 1);
        break;
    }
  }
  else
  {
    digitalWrite(LeftIn1, 1);
    digitalWrite(LeftIn2, 1);
    digitalWrite(RightIn1, 1);
    digitalWrite(RightIn2, 1);
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
