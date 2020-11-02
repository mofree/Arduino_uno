int di01 = 11;
int statebuffer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(di01, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(di01);
  if (state != statebuffer) {
    if (state) {Serial.println("检测到人体");}
    if (not state) {Serial.println("人体信号丢失");}
  }
  statebuffer = state;
}
