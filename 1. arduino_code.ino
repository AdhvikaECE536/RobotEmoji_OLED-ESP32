/*
 * SIMPLE ROBOT EYES - Beginner Friendly!
 * ESP32 with OLED Display (128x64)
 * 
 * WIRING (4 wires only!):
 * OLED VCC  →  ESP32 3.3V
 * OLED GND  →  ESP32 GND
 * OLED SDA  →  ESP32 GPIO21
 * OLED SCL  →  ESP32 GPIO22
 * 
 * LIBRARIES NEEDED (Install from Arduino IDE):
 * 1. Adafruit SSD1306
 * 2. Adafruit GFX Library
 * 
 * HOW TO INSTALL LIBRARIES:
 * Arduino IDE → Tools → Manage Libraries → Search for each library → Install
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup (don't change these)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Eye positions and sizes (you can adjust these!)
int leftEyeX = 32;      // Left eye center
int rightEyeX = 96;     // Right eye center  
int eyeY = 32;          // Both eyes Y position
int eyeSize = 20;       // Eye width/height
int pupilSize = 8;      // Pupil size

// Animation variables
int pupilX = 0;         // Where pupil looks (-5 to 5)
int pupilY = 0;
int blinkAmount = 0;    // How closed are eyes (0 = open, 20 = closed)
bool isBlinking = false;

// Timers
unsigned long lastBlink = 0;
unsigned long lastLook = 0;

// Emotions
String currentEmotion = "HAPPY";

void setup() {
  Serial.begin(115200);
  
  // Start the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display not found! Check wiring!");
    while(1); // Stop here if display not found
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Robot Eyes Ready!");
  display.display();
  delay(2000);
  
  Serial.println("Robot Eyes Started!");
  Serial.println("Type these commands:");
  Serial.println("  HAPPY");
  Serial.println("  SAD");
  Serial.println("  ANGRY");
  Serial.println("  SURPRISED");
  Serial.println("  SLEEPY");
  Serial.println("  WINK");
}

void loop() {
  unsigned long now = millis();
  
  // Check for serial commands
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase();
    
    if (command == "HAPPY" || command == "SAD" || command == "ANGRY" || 
        command == "SURPRISED" || command == "SLEEPY" || command == "WINK") {
      currentEmotion = command;
      Serial.print("Emotion: ");
      Serial.println(currentEmotion);
    }
  }
  
  // Auto blink every 3-5 seconds
  if (now - lastBlink > random(3000, 5000)) {
    isBlinking = true;
    lastBlink = now;
  }
  
  // Auto look around every 2-3 seconds
  if (now - lastLook > random(2000, 3000)) {
    pupilX = random(-5, 6);
    pupilY = random(-4, 5);
    lastLook = now;
  }
  
  // Update blink animation
  if (isBlinking) {
    blinkAmount += 5;
    if (blinkAmount >= 20) {
      delay(50); // Pause closed
      isBlinking = false;
    }
  } else if (blinkAmount > 0) {
    blinkAmount -= 5;
    if (blinkAmount < 0) blinkAmount = 0;
  }
  
  // Draw everything
  drawFace();
  
  delay(30);
}

void drawFace() {
  display.clearDisplay();
  
  // Draw based on emotion
  if (currentEmotion == "HAPPY") {
    drawEye(leftEyeX, eyeY, false);
    drawEye(rightEyeX, eyeY, false);
    drawHappyMouth();
    drawEyebrows(2, 2); // Relaxed
    
  } else if (currentEmotion == "SAD") {
    drawEye(leftEyeX, eyeY, false);
    drawEye(rightEyeX, eyeY, false);
    drawSadMouth();
    drawEyebrows(-3, 3); // Sad angle
    
  } else if (currentEmotion == "ANGRY") {
    drawEye(leftEyeX, eyeY, false);
    drawEye(rightEyeX, eyeY, false);
    drawAngryMouth();
    drawEyebrows(-5, -5); // Angry angle
    
  } else if (currentEmotion == "SURPRISED") {
    eyeSize = 25; // Bigger eyes
    drawEye(leftEyeX, eyeY, false);
    drawEye(rightEyeX, eyeY, false);
    drawSurprisedMouth();
    drawEyebrows(-7, -7); // Raised
    eyeSize = 20; // Reset
    
  } else if (currentEmotion == "SLEEPY") {
    blinkAmount = 15; // Half closed
    drawEye(leftEyeX, eyeY, false);
    drawEye(rightEyeX, eyeY, false);
    drawSleepyMouth();
    display.setCursor(80, 10);
    display.print("Z z");
    
  } else if (currentEmotion == "WINK") {
    drawEye(leftEyeX, eyeY, true); // Wink left
    drawEye(rightEyeX, eyeY, false);
    drawHappyMouth();
  }
  
  display.display();
}

void drawEye(int x, int y, bool wink) {
  int currentHeight = eyeSize - blinkAmount;
  if (wink) currentHeight = 2; // Closed for wink
  
  if (currentHeight < 2) currentHeight = 2;
  
  // Draw eye outline (rounded rectangle)
  display.drawRoundRect(x - eyeSize/2, y - currentHeight/2, 
                        eyeSize, currentHeight, 5, WHITE);
  
  // Draw pupil if eye is open enough
  if (currentHeight > 10) {
    int pX = x + pupilX;
    int pY = y + pupilY;
    
    // Keep pupil inside eye
    pX = constrain(pX, x - eyeSize/2 + 5, x + eyeSize/2 - 5);
    pY = constrain(pY, y - currentHeight/2 + 5, y + currentHeight/2 - 5);
    
    display.fillCircle(pX, pY, pupilSize/2, WHITE);
    
    // Add shine/highlight
    display.fillCircle(pX - 2, pY - 2, 2, BLACK);
  }
}

void drawEyebrows(int leftAngle, int rightAngle) {
  // Left eyebrow
  int lx1 = leftEyeX - 12;
  int lx2 = leftEyeX + 12;
  int ly1 = eyeY - 15 + leftAngle;
  int ly2 = eyeY - 15 - leftAngle;
  display.drawLine(lx1, ly1, lx2, ly2, WHITE);
  
  // Right eyebrow
  int rx1 = rightEyeX - 12;
  int rx2 = rightEyeX + 12;
  int ry1 = eyeY - 15 - rightAngle;
  int ry2 = eyeY - 15 + rightAngle;
  display.drawLine(rx1, ry1, rx2, ry2, WHITE);
}

void drawHappyMouth() {
  // Smile arc
  for (int i = -15; i <= 15; i++) {
    int x = 64 + i;
    int y = 55 - (i * i) / 30;
    display.drawPixel(x, y, WHITE);
  }
}

void drawSadMouth() {
  // Frown arc
  for (int i = -15; i <= 15; i++) {
    int x = 64 + i;
    int y = 52 + (i * i) / 30;
    display.drawPixel(x, y, WHITE);
  }
}

void drawAngryMouth() {
  // Straight line
  display.drawLine(50, 54, 78, 54, WHITE);
  display.drawLine(50, 55, 78, 55, WHITE);
}

void drawSurprisedMouth() {
  // Open circle
  display.drawCircle(64, 54, 5, WHITE);
}

void drawSleepyMouth() {
  // Small line
  display.drawLine(58, 54, 70, 54, WHITE);
}
