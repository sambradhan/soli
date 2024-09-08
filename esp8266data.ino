#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "SAMBRADHAN 5557";             // Your Network SSID
const char* password = "Sambradhan123";

WiFiClient client;

unsigned long myChannelNumber = 2534900;         // Your ThingSpeak Channel Number
const char * myWriteAPIKey = "40UHWE1MCAKETKYP"; // Your ThingSpeak Write API Key

void setup() {
  Serial.begin(9600);
  delay(10);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println();

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available from Arduino Uno
    String data = Serial.readStringUntil('\n'); // Read data from Arduino Uno
    Serial.println("Received data from Arduino: " + data);

    // Parse the received data
    float mlxTemp = 0.0;
    int bpm = 0;
    int mlxIndex = data.indexOf("MLX:");
    int bpmIndex = data.indexOf("BPM:");
    if (mlxIndex != -1 && bpmIndex != -1) { // Check if both MLX and BPM values are found
      mlxTemp = data.substring(mlxIndex + 4, bpmIndex).toFloat(); // Extract MLX temperature
      bpm = data.substring(bpmIndex + 4).toInt(); // Extract BPM
      Serial.print("Received MLX Temperature: ");
      Serial.print(mlxTemp); // Print received MLX temperature
      Serial.println("*C");
      Serial.print("Received BPM: ");
      Serial.println(bpm); // Print received BPM
      uploadToThingSpeak(mlxTemp, bpm);
    } else {
      Serial.println("Invalid data format received from Arduino.");
    }
  }
}

void uploadToThingSpeak(float mlxTemp, int bpm) {
  ThingSpeak.setField(1, mlxTemp); // Set MLX temperature in field 1
  ThingSpeak.setField(2, bpm);     // Set BPM in field 2

  // Write to ThingSpeak
  int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("Error sending data to ThingSpeak, HTTP status code: ");
    Serial.println(status);
  }
}
