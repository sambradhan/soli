#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize built-in LED pin
  
  // Start I2C communication for OLED display
  Wire.begin();
  
  // Initialize display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  mlx.begin();
}

void loop() {
  int temp = mlx.readObjectTempC();

  // Print temperature and heartbeat
  Serial.print("Temp: ");
  Serial.println(temp);
  
  int BPM = generateBPM(temp); // Generate BPM based on temperature
  
  Serial.print("Heartbeat: ");
  Serial.println(BPM);

  display.clearDisplay();
  
  // Print temperature on display
  display.setCursor(0, 25);
  display.println("Temp: ");
  display.setCursor(50, 25);
  display.println(temp);
  display.setCursor(65, 25);
  display.println("C");

  // Print heartbeat on display
  display.setCursor(0, 15);
  display.println("Heartbeat: ");
  display.setCursor(70, 15);
  display.println(BPM);
  display.setCursor(95, 15);
  display.println("BPM");

  display.display();
  delay(1000); // Send data every 10 seconds
}

int generateBPM(int temp) {
  const int tempThreshold = 35; // Temperature threshold to trigger random BPM generation
  const int minBPM = 60; // Minimum BPM value
  const int maxBPM = 100; // Maximum BPM value

  if (temp >= tempThreshold - 1 && temp <= tempThreshold + 1) {
    return random(minBPM, maxBPM + 1); // Random BPM between minBPM and maxBPM when temp is near the threshold
  } else {
    // Calculate BPM based on temperature or use default value
    // Replace this with your calculation logic
    return 0; // Default value if not near the threshold
  }
}
