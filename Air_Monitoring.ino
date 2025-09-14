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

  // Initialize DHT
  dht.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
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
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int gasValue = analogRead(gas);

  display.clearDisplay();

  if (isnan(h) || isnan(t)) {
    display.setCursor(0, 0);
    display.println("DHT Error");
    display.display();
    return;
  }

  // Show Temperature
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(t);
  display.cp437(true);
  display.write(167); // Degree symbol
  display.print("C");

  // Show Humidity
  display.setCursor(0, 16);
  display.print("Humidity: ");
  display.print(h);
  display.print("%");

  // Show Gas value
  display.setCursor(0, 32);
  display.print("Gas: ");
  display.print(gasValue);

  // Air quality status
  display.setCursor(0, 48);
  if (gasValue < 1200) {
    display.println("Air: Fresh");
    Serial.println("Fresh Air");
  } else {
    display.println("Air: Bad");
    Serial.println("Bad Air");
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C, Humidity: ");
  Serial.print(h);
  Serial.print(" %, Gas Value: ");
  Serial.println(gasValue);

  display.display();
  delay(4000);
}