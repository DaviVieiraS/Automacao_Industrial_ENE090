# LoRa Spectrum Analyzer

A real-time spectrum analyzer for the Heltec WiFi LoRa 32 V3 using the SX1262 radio module.

## Features

- **Real-time spectrum analysis** across configurable frequency ranges
- **Visual display** on the integrated OLED screen with spectrum visualization
- **Serial control interface** for frequency selection and scanning control
- **Multiple frequency bands** support (433, 470, 868, 915 MHz)
- **RSSI measurement** and visualization
- **Interactive controls** via serial commands
- **Web-based spectrum viewer** with real-time data visualization

## Project Structure

```
lora-spectrum-analyzer/
├── README.md                  # This file
├── firmware/                  # ESP32 firmware
│   ├── src/
│   │   ├── main.cpp          # Main spectrum analyzer code
│   │   └── wifi_spectrum.cpp # WiFi spectrum functionality
│   ├── include/
│   ├── lib/
│   ├── platformio.ini        # PlatformIO configuration
│   └── test/
└── vercel-app/               # Web interface
    ├── pages/
    │   ├── index.tsx         # Main web interface
    │   └── api/
    │       └── spectrum.ts   # API endpoint
    ├── package.json
    ├── next.config.js
    └── tsconfig.json
```

## Hardware Setup

This code is configured for the Heltec WiFi LoRa 32 V3 with the following pinout:

### LoRa Module (SX1262)
- NSS: GPIO 8
- SCK: GPIO 9
- MOSI: GPIO 10
- MISO: GPIO 11
- RST: GPIO 12
- BUSY: GPIO 13
- DIO1: GPIO 14

### OLED Display
- SDA: GPIO 17
- SCL: GPIO 18
- RST: GPIO 21
- VEXT Control: GPIO 36

## Firmware Setup

### Prerequisites
- PlatformIO IDE (VS Code extension recommended)
- Heltec WiFi LoRa 32 V3 board

### Installation

1. Navigate to the firmware directory:
```bash
cd firmware/
```

2. Build and upload:
```bash
platformio run --target upload
```

3. Open Serial Monitor at 115200 baud:
```bash
platformio device monitor
```

## Usage

### Basic Operation

1. **Upload the code** to your Heltec WiFi LoRa 32 V3
2. **Open Serial Monitor** at 115200 baud
3. **Type `help`** to see all available commands
4. **Start scanning** by typing `scan`

### Serial Commands

| Command | Description |
|---------|-------------|
| `help` | Show all available commands |
| `scan` | Start continuous spectrum scanning |
| `stop` | Stop spectrum scanning |
| `freq <MHz>` | Set specific frequency (e.g., `freq 915.5`) |
| `band868` | Set to 868 MHz band |
| `band915` | Set to 915 MHz band |
| `band433` | Set to 433 MHz band |
| `band470` | Set to 470 MHz band |
| `reset` | Reset spectrum data |
| `info` | Show current settings and status |

### Example Usage

```
> help
Available commands:
  scan - Start continuous scanning
  stop - Stop scanning
  freq <MHz> - Set specific frequency
  band868 - Set 868 MHz band
  band915 - Set 915 MHz band
  band433 - Set 433 MHz band
  band470 - Set 470 MHz band
  reset - Reset spectrum data
  info - Show current settings

> scan
Starting spectrum scan...

> freq 915.5
Set frequency to: 915.5 MHz

> info
=== Spectrum Analyzer Info ===
Frequency range: 860.0 - 920.0 MHz
Frequency steps: 64
Current step: 23
RSSI range: -120.5 to -85.2 dBm
Status: Ready to scan
```

## Web Interface

The project includes a Next.js web application for remote spectrum visualization.

### Setup

1. Navigate to the vercel-app directory:
```bash
cd vercel-app/
```

2. Install dependencies:
```bash
npm install
```

3. Run development server:
```bash
npm run dev
```

4. Deploy to Vercel:
```bash
vercel
```

### Features

- Real-time spectrum data visualization
- Interactive frequency charts
- Historical data analysis
- Responsive design for mobile and desktop

## Display Information

The OLED display shows:
- **Spectrum graph**: Real-time frequency vs. signal strength
- **Frequency range**: Current scanning range
- **Status message**: Current operation status
- **RSSI scale**: Signal strength reference
- **Current position**: Highlighted scanning position

## Configuration

### Frequency Range
Default range: 860.0 - 920.0 MHz
- Modify `FREQ_BEGIN` and `FREQ_END` in the code
- Ensure range is within SX1262 capabilities (150-960 MHz)

### Scanning Parameters
- `FREQ_STEPS`: Number of frequency bins (default: 64)
- `SCAN_DELAY`: Delay between frequency steps in ms (default: 50)
- `SAMPLES_PER_FREQ`: Samples per frequency (default: 128)

### Display Settings
- `GRAPH_HEIGHT`: Height of spectrum graph (default: 40 pixels)
- `GRAPH_Y_OFFSET`: Vertical offset of graph (default: 10 pixels)

## Testing the Spectrum Analyzer

### 1. Basic Functionality Test
```bash
# Upload code and open serial monitor
# Type 'help' to verify command interface works
# Type 'info' to check initial settings
```

### 2. Frequency Setting Test
```bash
# Test individual frequency setting
freq 915.0
freq 868.0
freq 433.0

# Test band selection
band915
band868
band433
```

### 3. Scanning Test
```bash
# Start scanning
scan

# Monitor serial output for frequency/RSSI readings
# Check OLED display for spectrum visualization

# Stop scanning
stop
```

### 4. Signal Detection Test
To test signal detection:
1. Use another LoRa device to transmit on a known frequency
2. Set the analyzer to scan that frequency range
3. Observe increased RSSI values at the transmission frequency

### 5. Display Test
Verify the OLED display shows:
- Spectrum bars with varying heights
- Frequency markers at bottom
- RSSI scale on left side
- Status messages at bottom
- Current scanning position highlighted

## Troubleshooting

### Radio Initialization Failed
- Check SPI connections
- Verify pin assignments match your hardware
- Ensure proper power supply

### No Signal Detection
- Check antenna connection
- Verify frequency range is correct
- Test with known RF source
- Check if radio is in correct mode

### Display Issues
- Verify I2C connections
- Check VEXT power control
- Ensure proper initialization sequence

### Serial Communication Issues
- Verify baud rate is 115200
- Check USB connection
- Try different serial terminal

## Technical Details

### Radio Configuration
- **Mode**: FSK (Frequency Shift Keying) for better spectrum analysis
- **Bandwidth**: 250 kHz
- **Data Shaping**: None (for raw spectrum analysis)
- **Frequency Range**: 150-960 MHz (SX1262 specification)

### Spectrum Analysis Method
1. **Frequency Sweep**: Step through frequency range in defined increments
2. **RSSI Measurement**: Read signal strength at each frequency
3. **Data Visualization**: Display as bar chart on OLED
4. **Real-time Update**: Continuously update display with new measurements

### Performance Characteristics
- **Scan Time**: ~3.2 seconds for full 64-step scan (50ms per step)
- **Frequency Resolution**: ~0.94 MHz per step (60 MHz / 64 steps)
- **RSSI Range**: Typically -120 to -40 dBm
- **Update Rate**: Continuous real-time scanning

## Safety and Legal Considerations

⚠️ **Important**: 
- Ensure you have proper authorization to operate radio equipment
- Check local regulations for frequency usage
- This device is for educational and testing purposes
- Do not interfere with licensed radio services

## Dependencies

### Firmware
- **RadioLib**: For SX1262 radio control
- **U8g2**: For OLED display control
- **Arduino**: Core framework
- **ESP32**: Platform support

### Web Application
- **Next.js**: React framework
- **TypeScript**: Type safety
- **Recharts**: Data visualization
- **Vercel**: Deployment platform

## IIoT Context

This project demonstrates key IIoT concepts from the ENE090 course:

### IoT Architecture Layers
- **Perception Layer**: SX1262 radio sensor for RF spectrum sensing
- **Edge Layer**: ESP32 local processing and OLED visualization
- **Network Layer**: WiFi connectivity for remote monitoring
- **Application Layer**: Next.js web interface for data visualization

### Communication Technologies
- **LoRa**: LPWAN technology for wide-area spectrum analysis
- **WiFi**: Local network connectivity for data transmission
- **Serial**: Direct device communication and debugging

### Practical Applications
- **Spectrum monitoring**: Real-time RF environment awareness
- **Interference detection**: Identify unauthorized or interfering signals
- **Network planning**: Analyze spectrum occupancy before deployment
- **Predictive maintenance**: Monitor RF equipment health and performance

## License

This project is provided as-is for educational and testing purposes. Please ensure compliance with local radio regulations.

---

**Developed for Automação Industrial (ENE090) - UFJF**

