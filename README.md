# Robot Emoji OLED-ESP32

This repository contains an expressive animated robot face using ESP32 microcontroller and OLED display.




### 📂 Repository Structure

- `1. arduino_code.ino`    – ESP32 code for animated robot eyes
- `2. find_port.js`        – Notes for detecting ESP32 serial port
- `3. auto_run.js`         – Automated emotion demo sequence
- `4. server.js`           – Local server 
- `5. index.html`          – Frontend   
- `6. i2c_scanner.ino`     – I2C address scanner for OLED


### ✨ Features
- 👁️ Animated Eyes - Realistic blinking and eye movements
- 😊 6 Emotions - Happy, Sad, Angry, Surprised, Sleepy, and Wink
- 🎯 Auto Behaviors - Automatic blinking and random eye movements
- 🌐 Web Control - Control emotions from any browser
- 💻 Serial Commands - Send emotions via Serial Monitor
- ⚡ Real-time Response - Instant emotion changes


### 🛠️ Hardware Requirements

| Component | Specification | Quantity |
|-----------|--------------|----------|
| ESP32 Development Board | ESP32-WROOM-32 or similar | 1 |
| OLED Display | SSD1306 128x64 (I2C) | 1 |
| USB Cable | Micro USB or USB-C | 1 |
| Breadboard (Optional) | Standard size | 1 |
| Jumper Wires | Male-to-Female | 4 |


### 🔌 Connections

The OLED display is connected to ESP32 through suggested conections:

```
ESP32          OLED SSD1306
─────────────────────────────
3.3V     →     VCC
GND      →     GND
GPIO21   →     SDA
GPIO22   →     SCK
```


## PART A : Using only Arduino IDE

### 📦 Software Requirements

#### Arduino IDE Setup

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)
   - Install version 2.0 or higher

2. **Add ESP32 Board Support**
   - Open Arduino IDE
   - Go to `File` → `Preferences`
   - Add this URL to "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search for "ESP32" and install "esp32 by Espressif Systems"

3. **Install Required Libraries**
   
   Go to `Sketch` → `Include Library` → `Manage Libraries` and install:
   
   - **Adafruit SSD1306** (by Adafruit)
   - **Adafruit GFX Library** (by Adafruit)


### 🚀 Setup Steps

#### Step 1: Upload the Code

1. Open `arduino_code.ino` in Arduino IDE
2. Connect ESP32 to your computer via USB
3. Select board: `Tools` → `Board` → `ESP32 Dev Module`
4. Select correct COM port: `Tools` → `Port` → `COMx` (Windows) or `/dev/ttyUSB0` (Linux/Mac)
5. Click the **Verify** button (✓) to check for errors
6. Click the **Upload** button (→)
7. Wait for "Done uploading" message

#### Step 2: Test with Serial Monitor

1. Open Serial Monitor: `Tools` → `Serial Monitor`
2. Set baud rate to `115200`
3. You should see: "Robot Eyes Started!"

#### Step 3: Control Emotions

Type any of these commands in Serial Monitor:

- `HAPPY` - Smile with relaxed eyebrows
- `SAD` - Frown with drooping eyebrows
- `ANGRY` - Straight mouth with furrowed brows
- `SURPRISED` - Wide eyes with raised eyebrows
- `SLEEPY` - Half-closed eyes with "Zzz"
- `WINK` - Wink with a smile


### 📊 Display Information

The robot eyes will:

- ✨ Automatically blink every 3-5 seconds
- 👀 Look around randomly every 2-3 seconds
- 😊 Display the selected emotion
- 🎭 Animate eyebrows and mouth accordingly


### 🎨 Customization

#### Change Eye Positions

```cpp
int leftEyeX = 32;      // Move left eye
int rightEyeX = 96;     // Move right eye  
int eyeY = 32;          // Vertical position
```

#### Adjust Eye Sizes

```cpp
int eyeSize = 20;       // Eye width/height (try 15-25)
int pupilSize = 8;      // Pupil size (try 6-12)
```

#### Change Blink Frequency

```cpp
// In loop(), find this line:
if (now - lastBlink > random(3000, 5000)) {
// Change 3000 (min) and 5000 (max) milliseconds
```


### 📖 How It Works
1. **Initialization**: ESP32 starts up and initializes the OLED display
2. **Animation Loop**: Main loop runs continuously at 30 FPS (every 30ms)
3. **Auto Behaviors**:
    - Random blinks trigger every 3-5 seconds
    - Pupils move to random positions every 2-3 seconds
4. **Serial Listening**: ESP32 constantly checks for incoming serial commands
5. **Command Processing**: When emotion command received (e.g., "HAPPY"), it updates `currentEmotion` variable
6. **Display Update**: Each frame, `drawFace()` renders eyes, eyebrows, and mouth based on current emotion
7. **Repeat**: Loop continues indefinitely, creating smooth animations

 
---

## PART B: Using Node.js (Web Control)

### 🌐 What's Different?

Part B adds **remote control** via web browser! You can:
- 🖱️ Click emotion buttons from any device on your network
- 🎮 Control multiple robots from one interface
- 🔄 Test all emotions quickly with automated sequences

### 📦 Additional Requirements

- **Node.js** (version 14 or higher)
  - Download from [nodejs.org](https://nodejs.org/)
- **npm** (comes with Node.js)

### 🔧 Installation

1. **Install Node.js**
- Go to https://nodejs.org
- Download the LTS version (v24.12.0)
- Open Terminal (Mac/Linux) or Command Prompt (Windows)
- Type: node --version (You should see something like v24.12.0)

2. **Install VS Code (Code Editor)**
- Go to https://code.visualstudio.com
- Download and install

3. **Create your first project folder**
- Open Terminal > New Terminal
- On the top right-corner of the terminal window, click on the drop-down beside the `+` icon
- Select Command Prompt (Windows)
- Type
  
  ```bash
  # After " C:\Users\YourName> ", type the following
  mkdir my-project                              # creates folder
  cd my-project                                 # opens the folder

  Now, it should be in the form " C:\Users\YourName\my-project> "

  npm init -y                                   # initialize a Node.js project
  # A package.json file will be created

  npm install @serialport/parser-readline       # to process raw binary data from a serial port
  ```

### 📁 Project Structure for Node.js

```
my-project/
├── server.js                 # Node.js server
├── find_port.js              # Port detection utility
├── public/                   # Web interface folder
│   └── index.html            # Control panel webpage
├── package.json
├── auto_run.js               # Automated demo script
└── node_modules/
```


### 🚀 Setup Steps

1. **Create `find-port.js`**
   Open the `find-port.js` file in VS code

2. **Plug in your ESP32**
   Connect your ESP32 to your computer via USB cable.

3. **Run the script**
   
   ```bash
   # Run after " C:\Users\YourName\my-project> "

   node find-port.js


   **You should see something like:**
   
   Available ports:
   - COM3
   Manufacturer: Silicon Labs

   ```

4. **Update Server Configuration & Upload `index.html`**

   Open `server.js` and update the COM port (if needed):

   ```js
   const esp32 = new SerialPort({
     path: 'COM8',  // ← Change this to your port
     baudRate: 115200
   });
   ```
   
   Also upload the `index.html` file by creating `public/index.html` (After C:\Users\YourName\my-project> )
   

5. **Upload Updated Arduino Code**
   Upload the `arduino_code.ino` code to ESP32 and close the IDE window

6. **Start the Server**
   
   ```bash
   # Run after " C:\Users\YourName\my-project> "

   node server.js


   **You should see something like:**
   
   ✅ ESP32 Weather Station connected on COM8
   🌐 Weather Control Server running at http://localhost:3000
   Open this URL in your browser!
   ```

7. **Open the Web Interface**

   Open your browser and go to:
   ```
   http://localhost:3000
   ```

**Bonus: Automated Demo**

Want to see all emotions automatically? Try this:

1. Create `auto_run.js` with the provided code
2. Update COM port if needed
3. Run:
    
    ```bash
    node auto_run.js
    ```
    
This will cycle through all emotions every 3 seconds.

### 📖 How It Works
1. **Arduino Code**: ESP32 runs animation loop and listens for serial commands
2. **Node.js Server**: Connects to ESP32 and hosts web interface
3. **Web Interface**: User clicks emotion buttons in browser
4. **HTTP Request**: Browser sends emotion to Node.js server
5. **Serial Communication**: Server forwards command to ESP32
6. **Display Update**: ESP32 draws new emotion on OLED


### 🐛 Troubleshooting

#### Display Not Working
- ✅ Verify wiring connections
- ✅ Try 5V instead of 3.3V for OLED VCC
- ✅ Check I2C address (should be `0x3C`, sometimes `0x3D`)
- ✅ Run I2C scanner to detect OLED address

#### Serial Port Issues
- ✅ Make sure Arduino IDE Serial Monitor is **closed**
- ✅ Verify correct COM port in code
- ✅ Check if ESP32 is properly connected
- ✅ Try unplugging and replugging ESP32
- ✅ Install CH340/CP2102 drivers if needed

#### Server Won't Start
- ✅ Check Node.js is installed: `node --version`
- ✅ Install dependencies: `npm install`
- ✅ Verify port 3000 isn't already in use
- ✅ Check firewall settings

#### Web Page Won't Load
- ✅ Make sure server is running (`node server.js`)
- ✅ Check console for error messages
- ✅ Try `http://127.0.0.1:3000` instead
- ✅ Verify `public/index.html` exists

#### Robot Not Responding to Commands
- ✅ Confirm Arduino code is uploaded
- ✅ Check Serial Monitor shows "Robot Eyes Started!"
- ✅ Verify baud rate is 115200
- ✅ Make sure only ONE program is connected to serial port

#### "Error: Opening COM port" Error
- ✅ **Close Arduino IDE Serial Monitor!**
- ✅ Check if another program is using the port
- ✅ Restart your computer if port is stuck


---

## 🎓 Learning Outcomes

- 🖥️ **I2C Communication** - Connect sensors and displays
- 🎨 **Graphics Programming** - Draw shapes and animations
- 📡 **Serial Communication** - UART data transfer
- 🌐 **Web Servers** - Express.js and HTTP APIs
- 🔌 **Full-Stack IoT** - Hardware + Software integration
- 🎭 **Animation Techniques** - Timing and smooth movements
- 💻 **Node.js Development** - JavaScript on server side

---

## 🚀 Future Enhancements

### Easy Additions

- 🎨 More emotions (love, confused, embarrassed)
- 🌈 RGB LED for emotion colors
- 🔊 Speaker for sound effects
- 📱 Mobile app instead of web page

### Intermediate

- 👂 Microphone for voice control
- 🎯 Servo motors to physically move eyes
- 📷 Camera for face tracking
- 🤖 Multiple emotion transitions

### Advanced

- 🧠 AI emotion detection from images
- 🗣️ Text-to-speech responses
- 🌐 MQTT for remote control over internet
- 🎮 Game integration (eyes react to game events)

--- 

## 🎯 Quick Command Reference

### Serial Monitor Commands

```
HAPPY
SAD
ANGRY
SURPRISED
SLEEPY
WINK
```

### Web API Endpoints

```
GET http://localhost:3000/emotion/HAPPY
GET http://localhost:3000/emotion/SAD
GET http://localhost:3000/emotion/ANGRY
GET http://localhost:3000/emotion/SURPRISED
GET http://localhost:3000/emotion/SLEEPY
GET http://localhost:3000/emotion/WINK
```

--- 

## 📄 License

This project is open source and available for educational purposes. 

---

## 👤 Author

[@AdhvikaECE536](https://github.com/AdhvikaECE536)

---

## 🙏 Acknowledgments
Special thanks to GMR Airports Ltd for proving me the environment to learn, explore and grow. 

---

**Note**: This is a learning project. It uses open-source libraries and public APIs. Feel free to experiment and modify the code!


---

Made with ❤️ using ESP32
