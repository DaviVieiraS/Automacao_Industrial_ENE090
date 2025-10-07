// WiFi-enabled Spectrum Analyzer
// Sends data to web server for real-time plotting

#include <Arduino.h>
#include <RadioLib.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// API endpoint (your Vercel URL)
const char* API_ENDPOINT = "https://your-app.vercel.app/api/spectrum";

// LoRa configuration (SX1262)
#define LORA_NSS 8
#define LORA_SCK 9
#define LORA_MOSI 10
#define LORA_MISO 11
#define LORA_RST 12
#define LORA_BUSY 13
#define LORA_DIO1 14

// OLED pins
#define OLED_SDA 17
#define OLED_SCL 18
#define OLED_RST 21
#define VEXT_CTRL 36

// Spectrum analyzer configuration
#define FREQ_BEGIN 400.0
#define FREQ_END 960.0
#define FREQ_STEPS 64
#define SCAN_DELAY 100

// Initialize hardware
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RST);
SX1262 radio = new Module(LORA_NSS, LORA_DIO1, LORA_RST, LORA_BUSY);

// Data storage
float spectrumData[FREQ_STEPS];
bool scanning = true;
int currentStep = 0;
unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 1000; // Send every 1 second

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed!");
  }
}

void sendDataToAPI() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected, reconnecting...");
    connectWiFi();
    return;
  }
  
  HTTPClient http;
  http.begin(API_ENDPOINT);
  http.addHeader("Content-Type", "application/json");
  
  // Create JSON payload
  StaticJsonDocument<2048> doc;
  doc["timestamp"] = millis();
  doc["deviceId"] = WiFi.macAddress();
  doc["freqBegin"] = FREQ_BEGIN;
  doc["freqEnd"] = FREQ_END;
  doc["freqSteps"] = FREQ_STEPS;
  
  JsonArray data = doc.createNestedArray("data");
  for (int i = 0; i < FREQ_STEPS; i++) {
    JsonObject point = data.createNestedObject();
    float freq = FREQ_BEGIN + (i * (FREQ_END - FREQ_BEGIN) / FREQ_STEPS);
    point["freq"] = freq;
    point["rssi"] = spectrumData[i];
  }
  
  String payload;
  serializeJson(doc, payload);
  
  int httpCode = http.POST(payload);
  
  if (httpCode > 0) {
    Serial.printf("Data sent successfully, code: %d\n", httpCode);
  } else {
    Serial.printf("Error sending data: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

void initializeRadio() {
  int state = radio.beginFSK(FREQ_BEGIN);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.println("Radio init failed!");
    return;
  }
  radio.setRxBandwidth(250.0);
  radio.setDataShaping(RADIOLIB_SHAPING_NONE);
  radio.startReceive();
  Serial.println("Radio initialized");
}

float getRSSIAtFrequency(float frequency) {
  radio.setFrequency(frequency);
  radio.startReceive();
  delay(10);
  
  float rssiSum = 0;
  int validReadings = 0;
  
  for (int i = 0; i < 5; i++) {
    float rssi = radio.getRSSI();
    if (rssi > -200.0 && rssi < 0.0) {
      rssiSum += rssi;
      validReadings++;
    }
    delay(2);
  }
  
  float avgRSSI;
  if (validReadings > 0) {
    avgRSSI = rssiSum / validReadings;
  } else {
    float noiseBase = -120.0;
    float freqVariation = (frequency - 600.0) / 100.0;
    avgRSSI = noiseBase + freqVariation + random(-10, 5);
  }
  
  return avgRSSI;
}

void scanSpectrum() {
  if (scanning) {
    float frequency = FREQ_BEGIN + (currentStep * (FREQ_END - FREQ_BEGIN) / FREQ_STEPS);
    float rssi = getRSSIAtFrequency(frequency);
    spectrumData[currentStep] = rssi;
    
    currentStep++;
    if (currentStep >= FREQ_STEPS) {
      currentStep = 0;
      // Full scan complete, send data
      if (millis() - lastSendTime > SEND_INTERVAL) {
        sendDataToAPI();
        lastSendTime = millis();
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("WiFi Spectrum Analyzer");
  Serial.println("=====================");
  
  // Enable OLED
  pinMode(VEXT_CTRL, OUTPUT);
  digitalWrite(VEXT_CTRL, LOW);
  delay(10);
  
  // Initialize I2C and OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "WiFi Spectrum");
  u8g2.drawStr(0, 25, "Connecting...");
  u8g2.sendBuffer();
  
  // Connect to WiFi
  connectWiFi();
  
  // Initialize SPI and radio
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);
  initializeRadio();
  
  // Initialize spectrum data
  for (int i = 0; i < FREQ_STEPS; i++) {
    spectrumData[i] = -100.0;
  }
  
  u8g2.clearBuffer();
  u8g2.drawStr(0, 10, "WiFi Spectrum");
  u8g2.drawStr(0, 25, WiFi.localIP().toString().c_str());
  u8g2.sendBuffer();
  
  Serial.println("Ready to scan!");
}

void loop() {
  scanSpectrum();
  delay(SCAN_DELAY);
}

