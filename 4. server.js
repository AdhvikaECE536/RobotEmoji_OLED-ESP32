const express = require('express');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const app = express();
const PORT = 3000;

// Connect to ESP32
const esp32 = new SerialPort({
  path: 'COM8',
  baudRate: 115200
});

const parser = esp32.pipe(new ReadlineParser({ delimiter: '\n' }));

esp32.on('open', () => {
  console.log('✅ ESP32 connected on COM8');
});

parser.on('data', (data) => {
  console.log('🤖 Robot:', data);
});

// Serve static files from 'public' folder
app.use(express.static('public'));

// API endpoint to send emotions
app.get('/emotion/:name', (req, res) => {
  const emotion = req.params.name.toUpperCase();
  
  esp32.write(emotion + '\n', (err) => {
    if (err) {
      res.json({ success: false, error: err.message });
    } else {
      console.log('📤 Sent:', emotion);
      res.json({ success: true, emotion: emotion });
    }
  });
});

// Start server
app.listen(PORT, () => {
  console.log('🌐 Server running at http://localhost:3000');
  console.log('Open this URL in your browser!');
});
