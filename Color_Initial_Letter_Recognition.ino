#include <M5Core2.h>
#include <M5GFX.h>
#include "FastLED.h"
#include "neuton.h"
M5GFX display;
#define NUM_LEDS 10
#define DATA_PIN 25
CRGB leds[NUM_LEDS];

int val;
int iteration;
const int Buffer_Size = 450;
float* Buffer = (float*) calloc(Buffer_Size, sizeof(float));   // allocate memory for pixel buffer with 0s
int j;
void setup(void)
{
  Serial.begin(115200);
  M5.begin();
  display.init();
  display.setFont(&fonts::Font4);
  if(!Buffer){
    Serial.println("Failed to allocate memory");
  }

  if (!display.touch())
  {
    display.setTextDatum(textdatum_t::middle_center);
    display.drawString("Touch not found.", display.width() / 2, display.height() / 2);
  }

  display.setEpdMode(epd_mode_t::epd_fastest);
  display.startWrite();
  FastLED.addLeds<SK6812, DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(20, 20, 20);
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show(); 
}

void loop(void)
{
  static bool drawed = false;
  lgfx::touch_point_t tp[3];

  int nums = display.getTouchRaw(tp, 3);
  if (nums)
  {
    display.convertRawXY(tp, nums);

    for (int i = 0; i < nums; ++i)
    {
      if ((tp[i].y*320 + tp[i].x) != val && iteration<Buffer_Size)
      {
        Buffer[iteration] = tp[i].y*320 + tp[i].x;
        val=Buffer[iteration];
        iteration++;
      }
    }
    display.display();

    display.setColor(display.isEPD() ? TFT_BLACK : TFT_WHITE);
    for (int i = 0; i < nums; ++i)
    {
      int s = tp[i].size + 3;
      switch (tp[i].id)
      {
      case 0:
        display.fillCircle(tp[i].x, tp[i].y, s);
        break;
      case 1:
        display.drawLine(tp[i].x-s, tp[i].y-s, tp[i].x+s, tp[i].y+s);
        display.drawLine(tp[i].x-s, tp[i].y+s, tp[i].x+s, tp[i].y-s);
        break;
      default:
        display.fillTriangle(tp[i].x-s, tp[i].y +s, tp[i].x+s, tp[i].y+s, tp[i].x, tp[i].y-s);
        break;
      }
      display.display();
    }
    drawed = true;
  }
  else if (drawed)
  {
    drawed = false;
    display.waitDisplay();
    display.clear();
    display.display();
    if (neuton_model_set_inputs(Buffer)==0){
      uint16_t index;
      float* outputs;
      if (neuton_model_run_inference(&index, &outputs) == 0){
        switch(index){
          case 0:
          Serial.println("A");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Aquamarine", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(195,5,221);
            leds[10-i].setRGB(195,5,221);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 1:
          Serial.println("B");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Blue", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(0, 0, 255);
            leds[10-i].setRGB(0, 0, 255);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 2:
          Serial.println("C");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Cyan", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(188,0,227);
            leds[10-i].setRGB(188,0,227);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 3:
          Serial.println("F");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Fluorescent Blue", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(110,0,51);
            leds[10-i].setRGB(110,0,51);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 4:
          Serial.println("G");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Green", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(255,0,0);
            leds[10-i].setRGB(255,0,0);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 5:
          Serial.println("I");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Indigo", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(0,75,130);
            leds[10-i].setRGB(0,75,130);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 6:
          Serial.println("L");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Lime", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(190,120,33);
            leds[10-i].setRGB(190,120,33);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 7:
          Serial.println("M");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Magenta", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(1,217,122);
            leds[10-i].setRGB(1,217,122);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 8:
          Serial.println("O");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Orange", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(80,254,0);
            leds[10-i].setRGB(80,254,0);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 9:
          Serial.println("P");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Pink", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(72,251,196);
            leds[10-i].setRGB(72,251,196);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 10:
          Serial.println("R");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Red", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(0,255,0);
            leds[10-i].setRGB(0,255,0);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 11:
          Serial.println("S");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Sky Blue", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(181,0,226);
            leds[10-i].setRGB(181,0,226);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 12:
          Serial.println("V");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Violet", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(38,155,182);
            leds[10-i].setRGB(38,155,182);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 13:
          Serial.println("W");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("White", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(255,255,255);
            leds[10-i].setRGB(255,255,255);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
          case 14:
          Serial.println("Y");
          for (int k = 0; k < nums; ++j){
            display.setCursor(16, 128 + j * 24);
            display.printf("Yellow", tp[j].x, tp[j].y);
          }
          display.display();
          for (int i = 0; i < NUM_LEDS/2; i++) {
            leds[i].setRGB(255,255,0);
            leds[10-i].setRGB(255,255,0);
            FastLED.show();
            delay(100);
          }
          delay(5000);
          for (int i=0;i<NUM_LEDS;i++){
            leds[i] = CRGB::Black;
          }
          FastLED.show();
          display.waitDisplay();
          display.clear();
          display.display();
          break;
      }
    }
   }
   iteration = val = 0;
   neuton_model_reset_inputs();
   free(Buffer);
   Buffer = (float*) calloc(Buffer_Size, sizeof(float));
   if (!Buffer)
    {
      Serial.println("Failed to allocate memory");
    }
  }
  vTaskDelay(1);
}
