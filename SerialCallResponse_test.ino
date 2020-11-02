int inByte = 0;         // incoming serial byte

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("OK!");
}

void loop() {
  // if we get a valid byte:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    // print
    Serial.print("ASCII码为：");Serial.println(inByte);
    Serial.print("收到的字符为：");Serial.println(char(inByte));
  }
}
