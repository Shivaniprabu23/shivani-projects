// LM35 Temperature Sensor with Arduino
const int sensorPin = A5;
#define rLED 4 // LM35 connected to analog pin A0
#define gLED 5

void setup() {
  Serial.begin(9600);
  pinMode(rLED,OUTPUT);
  pinMode(gLED,OUTPUT); // Initialize serial communication
}

void loop() {
  // Read the analog value from LM35
  int sensorValue = analogRead(sensorPin);
  
  // Convert analog reading to voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1024.0);
  
  // Convert voltage to temperature in Celsius
  // LM35 outputs 10mV per degree Celsius
  float temperature = voltage * 100;
  
  // Display temperature on serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if(temperature>=35){
    digitalWrite(rLED,HIGH);
    delay(100);
    digitalWrite(rLED,LOW);
    delay(100);
  
    if(temperature>=36){
      digitalWrite(gLED,HIGH);
      delay(100);
      digitalWrite(gLED,LOW);
      delay(100);
    }
    else{
      digitalWrite(gLED,LOW);
    }
  }
  else{
    digitalWrite(rLED,LOW);
  }
  
  
  
  delay(1000); // Wait 1 second before next reading
}
