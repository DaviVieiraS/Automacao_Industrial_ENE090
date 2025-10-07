# Remote Real-Time Spectrum Plotting Guide

Complete guide to set up real-time spectrum data plotting on a Vercel web page.

## 🎯 Overview

This solution sends RF spectrum data from your ESP32 to a Vercel-hosted web page for real-time visualization.

## 📋 Architecture

```
┌─────────────┐         WiFi/HTTPS        ┌──────────────┐
│   ESP32     │ ──────────────────────────▶│    Vercel    │
│  LoRa SX1262│   POST /api/spectrum       │  Serverless  │
│             │                            │     API      │
└─────────────┘                            └──────┬───────┘
                                                  │
                                           GET /api/spectrum
                                                  │
                                                  ▼
                                          ┌──────────────┐
                                          │  Web Browser │
                                          │  Real-time   │
                                          │    Chart     │
                                          └──────────────┘
```

## 🚀 Step-by-Step Setup

### **Step 1: Deploy Vercel Web App**

1. **Install Vercel CLI:**
   ```bash
   npm install -g vercel
   ```

2. **Navigate to vercel-app directory:**
   ```bash
   cd vercel-app
   npm install
   ```

3. **Deploy to Vercel:**
   ```bash
   vercel login
   vercel
   ```

4. **Note your Vercel URL** (e.g., `https://your-app.vercel.app`)

### **Step 2: Configure ESP32**

1. **Update WiFi credentials** in `src/wifi_spectrum.cpp`:
   ```cpp
   const char* WIFI_SSID = "Your_WiFi_Name";
   const char* WIFI_PASSWORD = "Your_WiFi_Password";
   ```

2. **Update API endpoint** with your Vercel URL:
   ```cpp
   const char* API_ENDPOINT = "https://your-app.vercel.app/api/spectrum";
   ```

3. **Upload to ESP32:**
   ```bash
   # Option A: Use PlatformIO
   pio run --target upload --target monitor
   
   # Option B: Temporarily rename files
   # Rename main.cpp to main_backup.cpp
   # Rename wifi_spectrum.cpp to main.cpp
   # Then upload
   ```

### **Step 3: Test the Connection**

1. **Open Serial Monitor** (115200 baud)
2. **Check WiFi connection:**
   ```
   Connecting to WiFi...
   WiFi connected!
   IP: 192.168.1.xxx
   ```

3. **Verify data sending:**
   ```
   Data sent successfully, code: 200
   ```

4. **Open your Vercel URL** in browser
5. **You should see:**
   - 🟢 Connected status
   - Real-time spectrum chart
   - Device information
   - Peak signals

## 📊 Data Flow

### **ESP32 Sends:**
```json
{
  "timestamp": 123456,
  "deviceId": "AA:BB:CC:DD:EE:FF",
  "freqBegin": 400.0,
  "freqEnd": 960.0,
  "freqSteps": 64,
  "data": [
    { "freq": 400.0, "rssi": -120.5 },
    { "freq": 408.75, "rssi": -118.2 },
    ...
  ]
}
```

### **Web Page Displays:**
- Line chart of RSSI vs Frequency
- Connection status
- Device ID and frequency range
- Top 5 strongest signals
- Last update time

## 🔧 Advanced Options

### **Option 1: WebSocket (Lower Latency)**

For real-time updates with lower latency, use WebSockets:

**Pros:**
- Instant updates (no polling delay)
- Lower bandwidth usage
- Better for multiple clients

**Cons:**
- More complex setup
- Requires WebSocket server (e.g., Pusher, Ably, Socket.io)

### **Option 2: MQTT Broker**

Use MQTT for IoT-style communication:

**Pros:**
- Designed for IoT devices
- Very efficient
- Supports multiple subscribers

**Cons:**
- Requires MQTT broker (e.g., HiveMQ, CloudMQTT)
- Additional setup

### **Option 3: Firebase Realtime Database**

Use Firebase for instant synchronization:

**Pros:**
- Real-time synchronization
- Easy to set up
- Free tier available

**Cons:**
- Google account required
- Vendor lock-in

## 🎨 Customization Ideas

### **Enhance the Web Dashboard:**

1. **Waterfall Display** - Show spectrum over time
2. **Signal Recording** - Save interesting signals
3. **Alerts** - Notify when specific frequencies are detected
4. **Multiple Devices** - View multiple spectrum analyzers
5. **Historical Data** - Show past scans
6. **Export Data** - Download CSV/JSON
7. **Dark Mode** - Eye-friendly interface
8. **Mobile App** - React Native version

### **Enhance ESP32 Code:**

1. **Auto-reconnect** - Handle WiFi dropouts
2. **Compression** - Reduce data size
3. **Batching** - Send multiple scans at once
4. **Adaptive Rate** - Change update frequency
5. **Local Storage** - Buffer when offline

## 🐛 Troubleshooting

### **ESP32 Won't Connect to WiFi**
- Check SSID and password
- Ensure WiFi is 2.4GHz (not 5GHz)
- Check WiFi signal strength
- Try different access point

### **Data Not Appearing on Web Page**
- Check API endpoint URL is correct
- Verify ESP32 is sending data (check Serial Monitor)
- Check browser console for errors
- Try redeploying Vercel app

### **Slow Updates**
- Reduce `SEND_INTERVAL` in ESP32 code
- Reduce polling interval in web page
- Consider WebSocket solution

### **Connection Drops**
- Add auto-reconnect logic
- Increase WiFi power
- Use external antenna
- Check router settings

## 📈 Performance Tips

1. **Reduce Data Size:**
   - Send fewer frequency steps
   - Round RSSI values
   - Use compression

2. **Optimize Update Rate:**
   - 1 second is good balance
   - Faster = more bandwidth
   - Slower = less responsive

3. **Battery Life (if using battery):**
   - Deep sleep between scans
   - Reduce WiFi transmission power
   - Send data less frequently

## 🔐 Security Considerations

1. **API Authentication:**
   - Add API key to requests
   - Validate device ID
   - Rate limit requests

2. **HTTPS:**
   - Always use HTTPS (Vercel provides this)
   - Don't send sensitive data

3. **Data Privacy:**
   - Don't expose your WiFi password
   - Keep API endpoints private
   - Use environment variables

## 💾 Cost Considerations

### **Vercel Free Tier:**
- 100 GB bandwidth/month
- 100,000 function invocations/month
- **Sufficient for:**
  - 1 device sending every 1 second
  - ~2.6 million requests/month
  - Well within free limits!

### **If You Need More:**
- Vercel Pro: $20/month
- Or use free alternatives:
  - Netlify
  - Cloudflare Pages
  - Railway

## 📚 Next Steps

1. **Deploy and test** basic setup
2. **Customize dashboard** to your needs
3. **Add features** like signal alerts
4. **Optimize** for your use case
5. **Share** your spectrum data!

## 🎉 You're Done!

You now have a real-time RF spectrum analyzer accessible from anywhere in the world!

Visit your Vercel URL to see your spectrum data live! 📡📊

