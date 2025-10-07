// Real-time Spectrum Analyzer Web Page
import { useEffect, useState } from 'react';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';

interface SpectrumDataPoint {
  freq: number;
  rssi: number;
}

interface SpectrumData {
  timestamp: number;
  deviceId: string;
  freqBegin: number;
  freqEnd: number;
  freqSteps: number;
  data: SpectrumDataPoint[];
  receivedAt: string;
}

export default function Home() {
  const [spectrumData, setSpectrumData] = useState<SpectrumData | null>(null);
  const [isConnected, setIsConnected] = useState(false);
  const [lastUpdate, setLastUpdate] = useState<Date | null>(null);

  useEffect(() => {
    // Poll for new data every 250ms for snappier updates
    const interval = setInterval(async () => {
      try {
        const response = await fetch('/api/spectrum');
        if (response.ok) {
          const data = await response.json();
          setSpectrumData(data);
          setIsConnected(true);
          setLastUpdate(new Date());
        } else {
          setIsConnected(false);
        }
      } catch (error) {
        console.error('Error fetching data:', error);
        setIsConnected(false);
      }
    }, 250);

    return () => clearInterval(interval);
  }, []);

  // Prepare data for chart
  const chartData = spectrumData?.data?.map(point => ({
    frequency: point.freq.toFixed(1),
    RSSI: point.rssi
  })) || [];

  // Auto-scale Y axis with padding
  const rssiValues = chartData.map(d => d.RSSI);
  const minRssi = rssiValues.length ? Math.min(...rssiValues) : -140;
  const maxRssi = rssiValues.length ? Math.max(...rssiValues) : -40;
  const padding = 5;

  return (
    <div style={{ padding: '20px', fontFamily: 'Arial, sans-serif' }}>
      <h1>LoRa Spectrum Analyzer</h1>
      
      {/* Status */}
      <div style={{ 
        padding: '10px', 
        marginBottom: '20px', 
        backgroundColor: isConnected ? '#d4edda' : '#f8d7da',
        border: `1px solid ${isConnected ? '#c3e6cb' : '#f5c6cb'}`,
        borderRadius: '5px'
      }}>
        <strong>Status:</strong> {isConnected ? '🟢 Connected' : '🔴 Disconnected'}
        {lastUpdate && (
          <span style={{ marginLeft: '20px' }}>
            Last Update: {lastUpdate.toLocaleTimeString()}
          </span>
        )}
      </div>

      {/* Device Info */}
      {spectrumData && (
        <div style={{ 
          padding: '10px', 
          marginBottom: '20px', 
          backgroundColor: '#e7f3ff',
          border: '1px solid #b3d9ff',
          borderRadius: '5px'
        }}>
          <strong>Device ID:</strong> {spectrumData.deviceId}<br />
          <strong>Frequency Range:</strong> {spectrumData.freqBegin} - {spectrumData.freqEnd} MHz<br />
          <strong>Resolution:</strong> {spectrumData.freqSteps} steps
        </div>
      )}

      {/* Spectrum Chart */}
      <div style={{ 
        backgroundColor: 'white', 
        padding: '24px', 
        borderRadius: '12px',
        boxShadow: '0 8px 24px rgba(0,0,0,0.08)'
      }}>
        <h2 style={{ marginTop: 0, marginBottom: 12 }}>RF Spectrum</h2>
        <ResponsiveContainer width="100%" height={400}>
          <LineChart data={chartData}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis 
              dataKey="frequency" 
              label={{ value: 'Frequency (MHz)', position: 'insideBottom', offset: -5 }}
              tick={{ fontSize: 10 }}
              interval={Math.floor(chartData.length / 10)}
            />
            <YAxis 
              label={{ value: 'RSSI (dBm)', angle: -90, position: 'insideLeft' }}
              domain={[minRssi - padding, maxRssi + padding]}
            />
            <Tooltip 
              formatter={(value: number) => [`${value.toFixed(1)} dBm`, 'RSSI']}
              labelFormatter={(label) => `Frequency: ${label} MHz`}
            />
            <Legend />
            <Line 
              type="monotone" 
              dataKey="RSSI" 
              stroke="#6c5ce7" 
              strokeWidth={2.5}
              dot={false}
              isAnimationActive={false}
            />
          </LineChart>
        </ResponsiveContainer>
      </div>

      {/* Signal Strength Indicators */}
      {spectrumData && (
        <div style={{ marginTop: '20px' }}>
          <h3>Peak Signals</h3>
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(200px, 1fr))', gap: '10px' }}>
            {spectrumData.data
              .filter(point => point.rssi > -100)
              .sort((a, b) => b.rssi - a.rssi)
              .slice(0, 5)
              .map((point, idx) => (
                <div key={idx} style={{
                  padding: '10px',
                  backgroundColor: '#f0f0f0',
                  borderRadius: '5px',
                  border: '1px solid #ddd'
                }}>
                  <strong>{point.freq.toFixed(1)} MHz</strong><br />
                  RSSI: {point.rssi.toFixed(1)} dBm
                </div>
              ))}
          </div>
        </div>
      )}

      {/* Instructions */}
      {!isConnected && (
        <div style={{
          marginTop: '20px',
          padding: '15px',
          backgroundColor: '#fff3cd',
          border: '1px solid #ffc107',
          borderRadius: '5px'
        }}>
          <h3>⚠️ No Data Received</h3>
          <p>Make sure your ESP32 device is:</p>
          <ul>
            <li>Connected to WiFi</li>
            <li>Configured with the correct API endpoint</li>
            <li>Scanning and sending data</li>
          </ul>
        </div>
      )}
    </div>
  );
}

