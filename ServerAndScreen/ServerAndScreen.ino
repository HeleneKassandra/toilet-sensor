/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/
#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 64 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int ledExclamation[] = {0,0,0,1,1,0,0,0,
                        0,0,0,1,1,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,1,1,0,0,0,
                        0,0,0,1,1,0,0,0,
                        0,0,0,1,1,0,0,0,
                        0,0,0,1,1,0,0,0,
                        0,0,0,1,1,0,0,0,};



// variables will change:
int timeSinceLastState = 0;  // variable for reading the pushbutton status

//BLECharacteristic *pCharacteristic;

// Callback class to handle characteristic write requests
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Received value: ");
      Serial.print(value[0]);
      timeSinceLastState = 0;
      pixels.clear(); // Set all pixel colors to 'off'

      if (value[0] == '0') {
        // The first NeoPixel in a strand is #0, second is 1, all the way up
        // to the count of pixels minus one.
        for (int i=0; i<NUMPIXELS; i++) { // For each pixel...
            // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
            // Here we're using a moderately green color:
            pixels.setPixelColor(i, pixels.Color(0, 30, 0));
        } 
      } else {
          // The first NeoPixel iint timeSinceLastState = 0; n a strand is #0, second is 1, all the way up
          // to the count of pixels minus one.
          for (int i=0; i<NUMPIXELS; i++) { // For each pixel...
              // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
              // Here we're using a moderately red color:
              pixels.setPixelColor(i, pixels.Color(30, 0, 0));
          }
        }
        
        pixels.show(); 
      
      Serial.println();
      Serial.println("*********");
    }
    }
  
};

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Long name works now");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic =
    pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
   timeSinceLastState++;
   pixels.clear();
   if(timeSinceLastState > 10){
    for (int i=0; i<NUMPIXELS; i++) {
      
      pixels.setPixelColor(i, pixels.Color(30*ledExclamation[i], 30*ledExclamation[i], 0));
    }
    pixels.show();
    }
}
