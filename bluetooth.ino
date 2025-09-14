#define LED1 4  // LM35 connected to analog pin A0
#define LED2 5

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);  // Initialize serial communication
}
void loop() {
  if (Serial.available()){
    char a = Serial.read();
  Serial.println(a);
  if (a == 'A' || a =='a') {
    digitalWrite(LED1, HIGH);
    Serial.println("LED is ON");
  } else if (a == 'B'|| a =='b') {
    digitalWrite(LED1, LOW);
    Serial.println("LED is OFF");
  } else if (a == 'C' || a =='c') {
    digitalWrite(LED2, HIGH);
    Serial.println("LED is ON");
  } else if (a == 'D' || a=='d') {
    digitalWrite(LED2, LOW);
    Serial.println("LED is OFF");
  } 
  }
  // put your main code here, to run repeatedly:
}
