/*
// Wifi
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "YOUR_FIREBASE_HOST" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "YOUR_FIREBASE_AUTH"
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Define Firebase Data object
FirebaseData firebaseData;

// Root Path
String path = "/ESP8266_Device";

// SCREEN, DHT

#include "SPIFFS.h"
#include <JPEGDecoder.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 19    
#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define SCLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN   17
#define CS_PIN   5
#define RST_PIN 4

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

const String fileTemperature = "/temperature.jpg";
const String fileHumidity = "/humidity.jpg";

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

float prev_temp;
float prev_humidity;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  initDrawing();
  initWifi();
  
}

void loop() {

  delay(delayMS);
  
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    updateTemp(event.temperature);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    updateHumidity(event.relative_humidity);
  }
}

void updateTemp(float temp){
  if(prev_temp != temp){
    tft.fillRect(64, 0, 128, 64, WHITE);
    tft.setCursor(70, 24);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    String tempString = "";
    tempString += (int)temp;
    tempString += "C";
    tft.print(tempString);
    prev_temp = temp;

    Firebase.setDouble(firebaseData, path + "/Temperature/Data", temp);
  }
}

void updateHumidity(float humidity){
  if(prev_humidity != humidity){
    tft.fillRect(64, 64, 128, 128, WHITE);
    tft.setCursor(70, 88);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    String humidityString = "";
    humidityString += (int)humidity;
    humidityString += "%";
    tft.print(humidityString);
    prev_humidity = humidity;
    Firebase.setDouble(firebaseData, path + "/Humidity/Data", humidity);
  }
}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
*/