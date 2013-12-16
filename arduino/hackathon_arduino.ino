#include <Adafruit_NeoPixel.h>

#define PIN 5
int wait_T=40; //This is the delay between moving back and forth and per pixel
int PixelCount=8; //Set this to the AMOUNT of Led's/Pixels you have or want to use on your strip And It can be used to tell where to Stop then return the eye at in the strip
int Pixel_Start_End=0; //Set this to where you want it to Start/End at

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int InputChar;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(19200);
  Serial.write("Program Started");
}

void loop() {
  
  if(Serial.available()) {
    InputChar = Serial.read(); 
  }
  switch (InputChar) {
    case '0':
     colorWipe(strip.Color(0, 0, 0), 0);
     break;
    case '1':
      Serial.write("Red");
      for(int i=1;i<10;i++) {
        //Example: CylonEyeUp(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
        CylonEyeUp(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait_T, PixelCount, Pixel_Start_End);
        delay(wait_T);
        //Example: CylonEyeDown(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait_T, PixelCount, Pixel_Start_End);
        CylonEyeDown(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait_T, PixelCount, Pixel_Start_End);
        delay(wait_T);
      }
      for(int i=1;i<5;i++) {
        colorWipe(strip.Color(50, 0, 0), 5);
        delay(wait_T);
        colorWipe(strip.Color(255, 0, 0), 5);
        delay(wait_T);
      } 
      break;
    case '2':
      Serial.write("Yellow");
      colorWipe(strip.Color(255, 255, 0), 250); // Yellow
      break;
    case '3':
      Serial.write("Green");
      colorWipe(strip.Color(0, 255, 0), 250); // Green
      break;

  }
  // Some example procedures showing how to display to the pixels:
  //rainbow(100);
  //rainbowCycle(100);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void CylonEyeUp(uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pStart) {
  for(int i=pStart; i<TotalPixels; i++) {
    strip.setPixelColor(i+1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);     //Center Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color

      strip.setPixelColor(i-2, strip.Color(0,0,0)); //Clears the dots after the 2rd color
    strip.show();
    //Serial.println(i); //Used For pixel Count Debugging
    delay(Delay);
  }
}

void CylonEyeDown(uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pEnd) {
  for(int i=TotalPixels-1; i>pEnd; i--) {
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);    //Center Dot Color
    strip.setPixelColor(i+1, Ct);  //Second Dot Color
      strip.setPixelColor(i+2, strip.Color(0,0,0)); //Clears the dots after the 2rd color
    
    strip.show();
    //Serial.println(i); //Used For pixel Count Debugging
    delay(Delay);
  }
}




