#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

unsigned long channelID = YOUR_CHANNEL_ID;
const char* apiKey = "YOUR_API_KEY";

const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
    Serial.begin(9600);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Connected to Wi-Fi");
    
    ThingSpeak.begin(client);
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        int commaIndex = data.indexOf(',');
        if (commaIndex != -1) {
            String tempStr = data.substring(0, commaIndex);
            String heartbeatStr = data.substring(commaIndex + 1);
            
            float temperature = tempStr.toFloat();
            int heartbeat = heartbeatStr.toInt();
            
            Serial.println("Received data:");
            Serial.println("Temperature: " + String(temperature) + " F");
            Serial.println("Heartbeat: " + String(heartbeat) + " BPM");
            
            ThingSpeak.setField(1, temperature);
            ThingSpeak.setField(2, heartbeat);
            int status = ThingSpeak.writeFields(channelID, apiKey);
            
            if (status == 200) {
                Serial.println("Data sent to ThingSpeak successfully");
                
                // Call external Python script to retrieve data from ThingSpeak
                Serial.println("Calling Python script to retrieve data from ThingSpeak...");
                // Use the serial communication to run a Python script on the host machine
                Serial.println("thingSpeakRetrieval.py");
            } else {
                Serial.println("Failed to send data to ThingSpeak");
            }
        }
    }
}
