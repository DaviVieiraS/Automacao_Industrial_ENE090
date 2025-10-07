# LoRa Spectrum Analyzer - Web Dashboard

Real-time spectrum analyzer dashboard for viewing RF spectrum data from your ESP32/LoRa device.

## 🚀 Quick Start

### 1. Install Dependencies
```bash
cd vercel-app
npm install
```

### 2. Run Development Server
```bash
npm run dev
```
Open [http://localhost:3000](http://localhost:3000) in your browser.

### 3. Deploy to Vercel

#### Option A: Using Vercel CLI
```bash
npm install -g vercel
vercel login
vercel
```

#### Option B: Using Vercel Dashboard
1. Push code to GitHub
2. Go to [vercel.com](https://vercel.com)
3. Import your repository
4. Deploy!

## 📡 Configure ESP32

After deploying, update your ESP32 code with your Vercel URL:

```cpp
const char* API_ENDPOINT = "https://your-app.vercel.app/api/spectrum";
```

## 🎯 Features

- **Real-time Spectrum Display** - Live RF spectrum chart
- **Signal Peak Detection** - Shows strongest signals
- **Device Status** - Connection and update status
- **Responsive Design** - Works on desktop and mobile

## 🔧 API Endpoints

### POST `/api/spectrum`
Receive spectrum data from ESP32

**Request Body:**
```json
{
  "timestamp": 123456,
  "deviceId": "AA:BB:CC:DD:EE:FF",
  "freqBegin": 400.0,
  "freqEnd": 960.0,
  "freqSteps": 64,
  "data": [
    { "freq": 400.0, "rssi": -120.5 },
    { "freq": 408.75, "rssi": -118.2 }
  ]
}
```

### GET `/api/spectrum`
Get latest spectrum data for web page

## 📊 Technologies

- **Next.js** - React framework
- **Recharts** - Chart library
- **TypeScript** - Type safety
- **Vercel** - Hosting and serverless functions

## 🔐 Production Considerations

For production use, consider:

1. **Database** - Store data in Vercel KV, PostgreSQL, or MongoDB
2. **Authentication** - Protect API with API keys
3. **Rate Limiting** - Prevent abuse
4. **WebSockets** - For lower latency updates
5. **Data Retention** - Automatic cleanup of old data

## 📝 License

MIT

