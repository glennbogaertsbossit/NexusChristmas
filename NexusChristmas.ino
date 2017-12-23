// DATA_PIN 5 -> D1
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define NUM_LEDS 50
#define PIN 5
#define LIGHTLED 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_RGB + NEO_KHZ400);

const char* ssid = "WIFISSID";
const char* password = "WIFIPASSWORD";
int randNumber;
int LedBright[50][3];
int No_Leds[LIGHTLED] = {0, 0, 0, 0, 0};



WiFiServer server(80);

void setup() {
  strip.begin();
  strip.show();

  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to "); Serial.println(ssid);
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
 
  server.begin();

  randomSeed(analogRead(0));

  for(int i = 0; i < NUM_LEDS; i++) { 
    strip.setPixelColor(i, 255, 0, 0);
    strip.show();
    delay(5);
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
  }
  
  for (int i=0; i < 50; i++) {
    for (int j=0; j < 3; j++) {
      LedBright[i][j] = 0;
    }
  }
}

void loop() {
  boolean set=false;
  
  for (int i=0; i < 50; i++) {
    for (int j=0; j < 3; j++) {
      if(LedBright[i][j] > 0 && No_Leds[0] != i && No_Leds[1] != i && No_Leds[2] != i && No_Leds[3] != i && No_Leds[4] != i) {
        LedBright[i][j] = LedBright[i][j] - 1;
        set=true;
        
      }
    }
    if(set == true) {
      strip.setPixelColor(i, LedBright[i][0], LedBright[i][1], LedBright[i][2]);
      strip.show();
      set = false;
    }
    
  }
  delay(50);
  TCPServer();
}

void TCPServer () {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.print("New Block in Channel: ");
  Serial.println(request);
  client.flush();
  delay(1);
  int channel=request.toInt();

  randNumber = random(50);
  for (int i=0; i<LIGHTLED-1; i++) {
    No_Leds[i] = No_Leds[i+1];
  }
  No_Leds[4] = randNumber;
  
  if(channel == 0) {
    LedBright[randNumber][0] = 255;
    LedBright[randNumber][1] = 0;
    LedBright[randNumber][2] = 0;
  }
  if(channel == 1) {
    LedBright[randNumber][0] = 0;
    LedBright[randNumber][1] = 255;
    LedBright[randNumber][2] = 0;
  }
  if(channel == 2) {
    LedBright[randNumber][0] = 0;
    LedBright[randNumber][1] = 0;
    LedBright[randNumber][2] = 255;
  }
  strip.setPixelColor(randNumber, LedBright[randNumber][0], LedBright[randNumber][1], LedBright[randNumber][2]);
  strip.show();
}
   


