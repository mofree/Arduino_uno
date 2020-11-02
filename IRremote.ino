#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    //Serial.println(results.value);
    irrecv.resume(); // Receive the next value
  }
}

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
