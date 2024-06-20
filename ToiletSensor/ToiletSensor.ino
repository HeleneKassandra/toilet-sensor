#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 4;  // the number of the pushbutton pin
#define ledPin 48   // the number of the LED pin
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, ledPin, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  //digitalWrite(LED_BUILTIN, LOW);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
      pixels.clear(); // Set all pixel colors to 'off'
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    // turn LED green:
    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  } else {
    // turn LED red:
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));

  }
  pixels.show(); 
  delay(DELAYVAL);
}
