#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int tempC;  // Temperature variable in Celsius
int tempF;  // Temperature variable in Fahrenheit
int heartbeat = 0;

void setup() {
  delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  mlx.begin();
}

void loop() {
  tempC = mlx.readObjectTempC();  // Read temperature in Celsius
  tempF = (int)(tempC * 1.8) + 32;  // Convert Celsius to Fahrenheit
  
  heartbeat = random(60, 101); // Generate a random heartbeat rate between 60 and 100 BPM
  
  display.clearDisplay();
  
  // Display temperature in Fahrenheit
  display.setFont();
  display.setCursor(5, 5);
  display.println("TEMP: " + String(tempF) + " F");
  
  display.setCursor(5, 20);
  display.println("HEARTBEAT: " + String(heartbeat) + " BPM");
  
  display.display();
  delay(3500);
}
