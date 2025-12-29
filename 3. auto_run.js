const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

// Connect to ESP32 on COM8
const port = new SerialPort({
  path: 'COM8',
  baudRate: 115200
});

// Parser to read line-by-line
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

// When connection opens
port.on('open', () => {
  console.log('✅ Connected to robot on COM8!');
  console.log('Waiting 2 seconds for ESP32 to initialize...\n');
});

// When we receive data from ESP32
parser.on('data', (data) => {
  console.log('🤖 Robot says:', data);
});

// Function to send emotions
function setEmotion(emotion) {
  port.write(emotion + '\n', (err) => {
    if (err) {
      console.log('❌ Error:', err.message);
    } else {
      console.log('📤 Sent:', emotion);
    }
  });
}

// Demo sequence - send emotions after 2 seconds
setTimeout(() => {
  console.log('Starting emotion demo...\n');
  
  setEmotion('HAPPY');
  
  setTimeout(() => setEmotion('SURPRISED'), 3000);
  setTimeout(() => setEmotion('WINK'), 6000);
  setTimeout(() => setEmotion('ANGRY'), 9000);
  setTimeout(() => setEmotion('SLEEPY'), 12000);
  setTimeout(() => setEmotion('SAD'), 15000);
  setTimeout(() => setEmotion('HAPPY'), 18000);
  
  setTimeout(() => {
    console.log('\n✨ Demo complete! Press Ctrl+C to exit.');
  }, 20000);
  
}, 2000);
