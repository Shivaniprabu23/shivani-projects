#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT settings
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Gas sensor pin
int gas = 32;

void setup() {
  Serial.begin(115200);
  delay(1000); // give time for Serial to connect

  // Initialize DHT
  dht.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // stop here
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Intro screen
  display.setCursor(20, 20);
  display.println("Air Quality");
  display.setCursor(15, 35);
  display.println("Monitoring");
  display.display();
  delay(2000);
  display.clearDisplay();

  // Print serial header
  Serial.println("=== Air Quality Monitoring ===");
  Serial.println("Temperature (C) | Humidity (%) | Gas Value | Air Status");
  Serial.println("--------------------------------------------------------");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int gasValue = analogRead(gas);
  String airStatus;

  display.clearDisplay();

  if (isnan(h) || isnan(t)) {
    display.setCursor(0, 0);
    display.println("DHT Error");
    display.display();
    Serial.println("Sensor read error: DHT11 not responding.");
    delay(4000);
    return;
  }

  // Determine air quality
  if (gasValue < 1200) {
    airStatus = "Fresh";
  } else {
    airStatus = "Bad";
  }

  // Display on OLED
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(t);
  display.cp437(true);
  display.write(167); // Degree symbol
  display.print("C");

  display.setCursor(0, 16);
  display.print("Humidity: ");
  display.print(h);
  display.print("%");

  display.setCursor(0, 32);
  display.print("Gas: ");
  display.print(gasValue);

  display.setCursor(0, 48);
  display.print("Air: ");
  display.println(airStatus);
  display.display();

  // Print to Serial
  Serial.print(t, 1);
  Serial.print("             ");
  Serial.print(h, 1);
  Serial.print("           ");
  Serial.print(gasValue);
  Serial.print("        ");
  Serial.println(airStatus);

  delay(4000); // wait before next read
}
