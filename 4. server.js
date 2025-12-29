// including the express library & creating the web server "App"
const Express = require('express');
const App = Express();

const ServerPort = 3000;

// connecting to ESP32
const {SerialPort} = require('serialport');

const esp32 = new SerialPort({
  path : 'COM8',
  baudRate : 115200  
});

esp32.on('open', () => {
  console.log('esp32 connected');
});

// to get full-line data
const {ReadlineParser} = require('@serialport/parser-readline');
const Parser = esp32.pipe(new ReadlineParser({delimiter: '\n'}));

Parser.on('data',(data) => {
  console.log('Robot:', data);
});

// serve static files from the public folder & json files
App.use(Express.static('public'));
App.use(Express.json());

// API endpoint to send emotions
App.get('/emotion/:name', (req, res) => {
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
App.listen(ServerPort, () => {
  console.log('🌐 Server running at http://localhost:3000');
  console.log('Open this URL in your browser!');
});
