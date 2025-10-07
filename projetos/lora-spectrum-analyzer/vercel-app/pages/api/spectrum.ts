// API endpoint to receive spectrum data from ESP32
import type { NextApiRequest, NextApiResponse } from 'next';

// In-memory storage (for demo - use database in production)
let latestSpectrumData: any = null;

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse
) {
  // Enable CORS
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');

  if (req.method === 'OPTIONS') {
    res.status(200).end();
    return;
  }

  if (req.method === 'POST') {
    // Receive data from ESP32
    try {
      const data = req.body;
      latestSpectrumData = {
        ...data,
        receivedAt: new Date().toISOString()
      };
      
      console.log('Received spectrum data:', {
        deviceId: data.deviceId,
        timestamp: data.timestamp,
        dataPoints: data.data?.length
      });
      
      res.status(200).json({ success: true, message: 'Data received' });
    } catch (error) {
      console.error('Error processing data:', error);
      res.status(500).json({ success: false, error: 'Failed to process data' });
    }
  } else if (req.method === 'GET') {
    // Send latest data to web page
    if (latestSpectrumData) {
      res.status(200).json(latestSpectrumData);
    } else {
      res.status(404).json({ error: 'No data available' });
    }
  } else {
    res.status(405).json({ error: 'Method not allowed' });
  }
}

