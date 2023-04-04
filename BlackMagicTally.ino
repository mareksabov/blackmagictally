/*****************
  Tally light ESP32 for Blackmagic ATEM switcher

  Version 2.0

  A wireless (WiFi) tally light for Blackmagic Design
  ATEM video switchers, based on the M5StickC ESP32 development
  board and the Arduino IDE.

  For more information, see:
  https://oneguyoneblog.com/2020/06/13/tally-light-esp32-for-blackmagic-atem-switcher/

  Based on the work of Kasper Skårhøj:
  https://github.com/kasperskaarhoj/SKAARHOJ-Open-Engineering

******************/

#include <M5StickC.h>
#include <WiFi.h>
#include <SkaarhojPgmspace.h>
#include <ATEMbase.h>
#include <ATEMstd.h>

IPAddress clientIp(192, 168, 0, 61);        	// IP address of the ESP32
IPAddress switcherIp(192, 168, 0, 60);	      // IP address of the ATEM switcher
ATEMstd AtemSwitcher;

// http://www.barth-dev.de/online/rgb565-color-picker/
#define GRAY  0x2104 //   32   32   32
#define GREEN 0x0200 //   0    64   0
#define RED   0xF800 //   255  0    0
#define ORANGE 0xFDC0 //  255  187  0
#define BLUE 0x059F //    0    179  255

const char* ssid = "wifiSSID";
const char* password =  "wifiPassword";

int cameraNumber = 0;
int startCameraNumber = 1;
int maxCameraNumber = 8;

int ledPin = 10;

int PreviewTallyPrevious = 1;
int ProgramTallyPrevious = 1;


void setup() {

  Serial.begin(9600);

  // Start the Ethernet, Serial (debugging) and UDP:
  WiFi.begin(ssid, password);

  drawLabel(BLUE, BLACK, HIGH);

  cameraNumber = startCameraNumber;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // initialize the M5StickC object
  M5.begin();

  pinMode(ledPin, OUTPUT);  // LED: 1 is on Program (Tally)
  digitalWrite(ledPin, HIGH); // off

  // Initialize a connection to the switcher:
  AtemSwitcher.begin(switcherIp);
  AtemSwitcher.serialOutput(0x80);
  AtemSwitcher.connect();
}

void loop() {

  // Check for packets, respond to them etc. Keeping the connection alive!
  AtemSwitcher.runLoop();

  // Changing camera number when btn A is pressed
  M5.update();

  bool cameraNumberChanged = false;
  if (M5.BtnA.wasReleasefor(500)){
    cameraNumber++;

    if(cameraNumber > maxCameraNumber)
      cameraNumber = startCameraNumber;

    cameraNumberChanged = true;

    drawLabel(ORANGE, GRAY, HIGH);
    delay(50);
  }

  //Tally light functionality
  int ProgramTally = AtemSwitcher.getProgramTally(cameraNumber);
  int PreviewTally = AtemSwitcher.getPreviewTally(cameraNumber);

  if ((ProgramTallyPrevious != ProgramTally) || (PreviewTallyPrevious != PreviewTally) || cameraNumberChanged) { // changed?

    if ((ProgramTally && !PreviewTally) || (ProgramTally && PreviewTally) ) { // only program, or program AND preview
      drawLabel(RED, BLACK, LOW);
    } else if (PreviewTally && !ProgramTally) { // only preview
      drawLabel(GREEN, BLACK, HIGH);
    } else if (!PreviewTally || !ProgramTally) { // neither
      drawLabel(BLACK, GRAY, HIGH);
    }

  }

  ProgramTallyPrevious = ProgramTally;
  PreviewTallyPrevious = PreviewTally;
}

void drawLabel(unsigned long int screenColor, unsigned long int labelColor, bool ledValue) {
  digitalWrite(ledPin, ledValue);
  M5.Lcd.fillScreen(screenColor);
  M5.Lcd.setTextColor(labelColor, screenColor);
  M5.Lcd.drawString(String(cameraNumber), 15, 40, 8);
}