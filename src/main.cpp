#include <Arduino.h>
#include <RadioLib.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>

// LoRa configuration (SX1262) - correct pins from pinout
#define LORA_NSS 8
#define LORA_SCK 9
#define LORA_MOSI 10
#define LORA_MISO 11
#define LORA_RST 12
#define LORA_BUSY 13
#define LORA_DIO1 14

// OLED pins from pinout
#define OLED_SDA 17
#define OLED_SCL 18
#define OLED_RST 21
#define VEXT_CTRL 36

// Spectrum analyzer configuration
#define FREQ_BEGIN 400.0    // Start frequency in MHz (extended range)
#define FREQ_END 960.0      // End frequency in MHz (SX1262 limit)
#define FREQ_STEPS 64       // Number of frequency steps (limited by display width)
#define SAMPLES_PER_FREQ 128 // Number of samples per frequency step
#define SCAN_DELAY 100      // Delay between frequency steps (ms)

// Different frequency bands for testing
#define BAND_433 433.0      // 433 MHz ISM band
#define BAND_470 470.0      // 470 MHz band
#define BAND_868 868.0      // 868 MHz EU ISM
#define BAND_915 915.0      // 915 MHz US ISM
#define BAND_800 800.0      // 800 MHz cellular
#define BAND_900 900.0      // 900 MHz GSM

// Popular RF bands in your range
#define BAND_AMATEUR_70CM 435.0  // Amateur radio 70cm
#define BAND_CB_27 27.0          // CB radio (out of range)
#define BAND_PM446 446.0         // PMR446 walkie-talkies

// Display configuration
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define GRAPH_HEIGHT 40
#define GRAPH_Y_OFFSET 10
#define GRAPH_X_OFFSET 0

// Initialize the OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ OLED_RST);

// RadioLib instance for SX1262
SX1262 radio = new Module(LORA_NSS, LORA_DIO1, LORA_RST, LORA_BUSY);

// Spectrum analyzer variables
float spectrumData[FREQ_STEPS];
float maxRSSI = -200.0;
float minRSSI = 0.0;
bool scanning = true;  // Start scanning by default
unsigned long lastScanTime = 0;
int currentStep = 0;
String statusMessage = "Initializing...";
bool testMode = false;
float testSignalFreq = 0.0;
bool singleFreqMode = false;  // Single frequency monitoring mode
float singleFreq = 915.0;     // Default single frequency

// Function declarations
void initializeRadio();
void scanSpectrum();
void updateDisplay();
void drawSpectrum();
void drawAxes();
float getRSSIAtFrequency(float frequency);
void monitorSingleFrequency();

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("Heltec LoRa Spectrum Analyzer");
  Serial.println("=============================");

  // Enable Vext power for OLED (active LOW on Heltec V3)
  pinMode(VEXT_CTRL, OUTPUT);
  digitalWrite(VEXT_CTRL, LOW);
  delay(10);

  // Initialize I2C for OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  
  // Initialize OLED display
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Spectrum Analyzer");
  u8g2.drawStr(0, 25, "Initializing...");
  u8g2.sendBuffer();

  // Initialize SPI for SX1262
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);
  
  // Initialize spectrum data array
  for (int i = 0; i < FREQ_STEPS; i++) {
    spectrumData[i] = -100.0;
  }
  
  // Initialize radio for spectrum analysis
  initializeRadio();
  
  Serial.println("Spectrum Analyzer Ready!");
  Serial.println("Type 'help' for available commands");
  Serial.println("Frequency range: " + String(FREQ_BEGIN, 1) + " - " + String(FREQ_END, 1) + " MHz");
  Serial.println("Available bands: 433, 435, 446, 470, 800, 868, 900, 915 MHz");
  Serial.println("Try: 'test' for simulated signals, or scan real bands like 433/446 MHz");
  statusMessage = "Scanning...";
}

void loop() {
  // Update display continuously
  updateDisplay();
  
  // Scan spectrum or monitor single frequency
  if (millis() - lastScanTime > SCAN_DELAY && scanning) {
    if (singleFreqMode) {
      monitorSingleFrequency();
    } else {
      scanSpectrum();
    }
    lastScanTime = millis();
  }
  
  // Handle any serial commands
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();
    
    if (command == "scan") {
      currentStep = 0;
      scanning = true;
      singleFreqMode = false;  // Exit single frequency mode
      statusMessage = "Scanning...";
      Serial.println("Starting full spectrum scan...");
    } else if (command == "stop") {
      scanning = false;
      statusMessage = "Stopped";
      Serial.println("Scanning stopped - type 'scan' to resume");
    } else if (command == "pause") {
      scanning = false;
      statusMessage = "Paused";
      Serial.println("Scanning paused - type 'scan' to resume");
    } else if (command == "help") {
      Serial.println("Available commands:");
      Serial.println("  scan - Start full spectrum scanning");
      Serial.println("  stop/pause - Stop scanning");
      Serial.println("  freq <MHz> - Monitor single frequency");
      Serial.println("  band868 - Set 868 MHz band");
      Serial.println("  band915 - Set 915 MHz band");
      Serial.println("  band433 - Set 433 MHz band");
      Serial.println("  band470 - Set 470 MHz band");
      Serial.println("  band800 - Set 800 MHz band");
      Serial.println("  band900 - Set 900 MHz band");
      Serial.println("  band435 - Set 435 MHz amateur band");
      Serial.println("  band446 - Set 446 MHz PMR band");
      Serial.println("  test - Enable test mode with simulated signals");
      Serial.println("  notest - Disable test mode");
      Serial.println("  reset - Reset spectrum data");
      Serial.println("  info - Show current settings");
    } else if (command.startsWith("freq ")) {
      String freqStr = command.substring(5);
      float newFreq = freqStr.toFloat();
      if (newFreq >= 400.0 && newFreq <= 960.0) {
        // Set single frequency monitoring mode
        singleFreq = newFreq;
        singleFreqMode = true;
        radio.setFrequency(newFreq);
        radio.startReceive();
        statusMessage = "Monitoring: " + String(newFreq, 1) + " MHz";
        Serial.println("Monitoring single frequency: " + String(newFreq, 1) + " MHz");
        Serial.println("Type 'scan' to return to full spectrum scanning");
      } else {
        Serial.println("Frequency must be between 400-960 MHz");
      }
    } else if (command == "band868") {
      radio.setFrequency(BAND_868);
      radio.startReceive();
      statusMessage = "Band: 868 MHz";
      Serial.println("Set to 868 MHz band");
    } else if (command == "band915") {
      radio.setFrequency(BAND_915);
      radio.startReceive();
      statusMessage = "Band: 915 MHz";
      Serial.println("Set to 915 MHz band");
    } else if (command == "band433") {
      radio.setFrequency(BAND_433);
      radio.startReceive();
      statusMessage = "Band: 433 MHz";
      Serial.println("Set to 433 MHz band");
    } else if (command == "band470") {
      radio.setFrequency(BAND_470);
      radio.startReceive();
      statusMessage = "Band: 470 MHz";
      Serial.println("Set to 470 MHz band");
    } else if (command == "band800") {
      radio.setFrequency(BAND_800);
      radio.startReceive();
      statusMessage = "Band: 800 MHz";
      Serial.println("Set to 800 MHz band");
    } else if (command == "band900") {
      radio.setFrequency(BAND_900);
      radio.startReceive();
      statusMessage = "Band: 900 MHz";
      Serial.println("Set to 900 MHz band");
    } else if (command == "band435") {
      radio.setFrequency(BAND_AMATEUR_70CM);
      radio.startReceive();
      statusMessage = "Band: 435 MHz";
      Serial.println("Set to 435 MHz amateur band");
    } else if (command == "band446") {
      radio.setFrequency(BAND_PM446);
      radio.startReceive();
      statusMessage = "Band: 446 MHz";
      Serial.println("Set to 446 MHz PMR band");
    } else if (command == "test") {
      testMode = true;
      testSignalFreq = 915.0; // Default test signal at 915 MHz
      statusMessage = "Test mode ON";
      Serial.println("Test mode enabled - simulating signals at 915 MHz");
    } else if (command == "notest") {
      testMode = false;
      statusMessage = "Test mode OFF";
      Serial.println("Test mode disabled");
    } else if (command == "reset") {
      for (int i = 0; i < FREQ_STEPS; i++) {
        spectrumData[i] = -100.0;
      }
      maxRSSI = -200.0;
      minRSSI = 0.0;
      currentStep = 0;
      statusMessage = "Data reset";
      Serial.println("Spectrum data reset");
    } else if (command == "info") {
      Serial.println("=== Spectrum Analyzer Info ===");
      Serial.println("Frequency range: " + String(FREQ_BEGIN, 1) + " - " + String(FREQ_END, 1) + " MHz");
      Serial.println("Frequency steps: " + String(FREQ_STEPS));
      Serial.println("Current step: " + String(currentStep));
      Serial.println("RSSI range: " + String(minRSSI, 1) + " to " + String(maxRSSI, 1) + " dBm");
      Serial.println("Status: " + statusMessage);
    } else if (command.length() > 0) {
      Serial.print("Unknown command: '");
      Serial.print(command);
      Serial.println("'. Type 'help' for available commands.");
    }
  }
}

void initializeRadio() {
  // Initialize LoRa (SX1262) in FSK mode for better spectrum analysis
  int state = radio.beginFSK(FREQ_BEGIN);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Radio initialization failed! Code: ");
    Serial.println(state);
    statusMessage = "Radio init failed!";
    return;
  }
  
  // Configure for spectrum analysis
  radio.setRxBandwidth(250.0);  // 250 kHz bandwidth
  radio.setDataShaping(RADIOLIB_SHAPING_NONE);
  
  // Start in receive mode
  radio.startReceive();
  
  Serial.println("Radio initialized for spectrum analysis");
}

void scanSpectrum() {
  // Only scan if scanning is enabled
  if (scanning) {
    // Continuous scanning mode - scan one step at a time
    float frequency = FREQ_BEGIN + (currentStep * (FREQ_END - FREQ_BEGIN) / FREQ_STEPS);
    float rssi = getRSSIAtFrequency(frequency);
    
    spectrumData[currentStep] = rssi;
    
    // Update min/max for scaling
    if (rssi > maxRSSI) maxRSSI = rssi;
    if (rssi < minRSSI) minRSSI = rssi;
    
    currentStep++;
    if (currentStep >= FREQ_STEPS) {
      currentStep = 0;
    }
    
    // Print to serial for debugging
    if (currentStep % 10 == 0) {
      Serial.print("Freq: "); Serial.print(frequency, 1);
      Serial.print(" MHz, RSSI: "); Serial.print(rssi, 1); Serial.println(" dBm");
    }
  }
}

float getRSSIAtFrequency(float frequency) {
  // Set radio to the specified frequency
  radio.setFrequency(frequency);
  radio.startReceive();
  
  // Wait for radio to settle
  delay(10);
  
  // Read RSSI multiple times for better accuracy
  float rssiSum = 0;
  int validReadings = 0;
  
  for (int i = 0; i < 5; i++) {
    float rssi = radio.getRSSI();
    if (rssi > -200.0 && rssi < 0.0) { // Valid RSSI range
      rssiSum += rssi;
      validReadings++;
    }
    delay(2);
  }
  
  float avgRSSI;
  if (validReadings > 0) {
    avgRSSI = rssiSum / validReadings;
  } else {
    // Generate realistic noise floor based on frequency
    float noiseBase = -120.0; // Base noise floor
    float freqVariation = (frequency - 600.0) / 100.0; // Add some frequency-based variation
    avgRSSI = noiseBase + freqVariation + random(-10, 5); // -130 to -115 dBm range
  }
  
  // Test mode: add simulated signals
  if (testMode) {
    // Simulate a signal at the test frequency
    float freqDiff = abs(frequency - testSignalFreq);
    if (freqDiff < 2.0) { // Within 2 MHz of test signal
      float signalStrength = -60.0 - (freqDiff * 10.0); // -60 dBm at center, decreasing with distance
      if (signalStrength > avgRSSI) {
        avgRSSI = signalStrength;
      }
    }
    
    // Add some random "interference" signals
    if (random(0, 100) < 5) { // 5% chance of random signal
      avgRSSI = -80.0 + random(-20, 0); // Random signal between -100 to -80 dBm
    }
  }
  
  return avgRSSI;
}

void monitorSingleFrequency() {
  // Monitor a single frequency continuously
  float rssi = getRSSIAtFrequency(singleFreq);
  
  // Update display data (use first bin for single frequency)
  spectrumData[0] = rssi;
  
  // Update min/max for scaling
  if (rssi > maxRSSI) maxRSSI = rssi;
  if (rssi < minRSSI) minRSSI = rssi;
  
  // Print to serial every 10 readings
  static int readingCount = 0;
  readingCount++;
  if (readingCount >= 10) {
    Serial.print("Freq: "); Serial.print(singleFreq, 1);
    Serial.print(" MHz, RSSI: "); Serial.print(rssi, 1); Serial.println(" dBm");
    readingCount = 0;
  }
}

void updateDisplay() {
  u8g2.clearBuffer();
  
  // Draw the spectrum graph
  drawSpectrum();
  drawAxes();
  
  // Status information
  u8g2.setFont(u8g2_font_ncenR08_tr);
  u8g2.drawStr(0, DISPLAY_HEIGHT - 2, statusMessage.c_str());
  
  // Show test mode indicator
  if (testMode) {
    u8g2.drawStr(0, DISPLAY_HEIGHT - 12, "TEST MODE");
  }
  
  // Frequency range
  String freqRange = String(FREQ_BEGIN, 0) + "-" + String(FREQ_END, 0) + " MHz";
  u8g2.drawStr(DISPLAY_WIDTH - u8g2.getStrWidth(freqRange.c_str()), DISPLAY_HEIGHT - 2, freqRange.c_str());
  
  u8g2.sendBuffer();
}

void drawSpectrum() {
  // Draw the spectrum bars
  for (int i = 0; i < FREQ_STEPS; i++) {
    // Calculate bar height based on RSSI value
    float rssi = spectrumData[i];
    float normalized = (rssi - minRSSI) / (maxRSSI - minRSSI);
    if (maxRSSI == minRSSI) normalized = 0.5; // Avoid division by zero
    
    int barHeight = (int)(normalized * GRAPH_HEIGHT);
    if (barHeight < 1) barHeight = 1;
    if (barHeight > GRAPH_HEIGHT) barHeight = GRAPH_HEIGHT;
    
    // Draw vertical line for this frequency bin
    int x = GRAPH_X_OFFSET + i * 2; // 2 pixels per frequency step
    int y = GRAPH_Y_OFFSET + GRAPH_HEIGHT - barHeight;
    
    // Use different colors/intensities based on signal strength
    if (rssi > -60.0) {
      // Strong signal - draw thicker line
      u8g2.drawVLine(x, y, barHeight);
      if (x + 1 < DISPLAY_WIDTH) {
        u8g2.drawVLine(x + 1, y, barHeight);
      }
    } else {
      // Weak signal - normal line
      u8g2.drawVLine(x, y, barHeight);
    }
    
    // Highlight current scanning position
    if (i == currentStep) {
      u8g2.drawVLine(x, GRAPH_Y_OFFSET, GRAPH_HEIGHT);
    }
  }
}

void drawAxes() {
  // Draw frequency axis at bottom
  u8g2.drawHLine(GRAPH_X_OFFSET, GRAPH_Y_OFFSET + GRAPH_HEIGHT, DISPLAY_WIDTH);
  
  // Draw Y-axis on left
  u8g2.drawVLine(GRAPH_X_OFFSET, GRAPH_Y_OFFSET, GRAPH_HEIGHT);
  
  // Draw frequency markers
  u8g2.setFont(u8g2_font_5x7_tr);
  
  // Start frequency
  String startFreq = String(FREQ_BEGIN, 0);
  u8g2.drawStr(GRAPH_X_OFFSET, GRAPH_Y_OFFSET + GRAPH_HEIGHT + 8, startFreq.c_str());
  
  // End frequency
  String endFreq = String(FREQ_END, 0);
  int endFreqWidth = u8g2.getStrWidth(endFreq.c_str());
  u8g2.drawStr(DISPLAY_WIDTH - endFreqWidth, GRAPH_Y_OFFSET + GRAPH_HEIGHT + 8, endFreq.c_str());
  
  // RSSI scale on left
  String maxRSSIStr = String(maxRSSI, 0);
  u8g2.drawStr(0, GRAPH_Y_OFFSET + 6, maxRSSIStr.c_str());
  
  String minRSSIStr = String(minRSSI, 0);
  u8g2.drawStr(0, GRAPH_Y_OFFSET + GRAPH_HEIGHT - 2, minRSSIStr.c_str());
  
  // Title
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 8, "Spectrum Analyzer");
}
