#include <LiquidCrystal_I2C.h>

#define mq2_pin A0       // MQ2 Smoke Sensor
#define mq135_pin A1     // MQ135 Gas Sensor
#define buzzer 9         // Buzzer Pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, columns, rows

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(" Smoke & Gas ");
  lcd.setCursor(0, 1);
  lcd.print(" Detection Sys ");
  delay(2000);
  lcd.clear();
}

void loop() {
  int mq2_val = analogRead(mq2_pin);     // Smoke sensor reading
  int mq135_val = analogRead(mq135_pin); // Gas sensor reading

  Serial.print("MQ2 (Smoke): ");
  Serial.print(mq2_val);
  Serial.print(" | MQ135 (Gas): ");
  Serial.println(mq135_val);

  lcd.setCursor(0, 0);
  lcd.print("Smoke:");
  lcd.print(mq2_val);
  lcd.print("   "); // Clear leftover chars

  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(mq135_val);
  lcd.print("   ");

  // Danger level detection
  if (mq2_val > 450 || mq135_val > 400) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}
