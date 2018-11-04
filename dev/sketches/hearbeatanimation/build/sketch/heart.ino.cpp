#include <Arduino.h>
#line 1 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
#line 1 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
/*
HEART
*/

#include "LedControl.h"
#include "heart.h"

// #include "data.ino"

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected

// empty heart
const byte emptyHeart[][8] = {
    {B01100110,
     B10011001,
     B10000001,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000}};

// Heartbeat animation
const byte heartbeat[][8] = {
    {B01100110,
     B10011001,
     B10000001,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B10011001,
     B10000001,
     B10011001,
     B01011010,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B10011001,
     B10111101,
     B10111101,
     B01111110,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B11111111,
     B11111111,
     B11111111,
     B01111110,
     B00111100,
     B00011000,
     B00000000}};

const byte waitingHeartBytes[][8] = {
    {B01100110,
     B10000001,
     B10000001,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000},
    {B01100000,
     B10011001,
     B10000001,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B10011000,
     B10000000,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B10011001,
     B10000001,
     B10000000,
     B01000000,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B10011001,
     B10000001,
     B10000001,
     B01000010,
     B00100000,
     B00010000,
     B00000000},
    {B01100110,
     B10011001,
     B10000001,
     B10000001,
     B01000010,
     B00000100,
     B00001000,
     B00000000},
    {B01100110,
     B10011001,
     B10000001,
     B00000001,
     B00000010,
     B00100100,
     B00011000,
     B00000000},
    {B01100110,
     B00011001,
     B00000001,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000},
    {B00000110,
     B10011001,
     B10000001,
     B10000001,
     B01000010,
     B00100100,
     B00011000,
     B00000000}};

const byte waitingHeartBytes2[][8] = {
    {B01000100,
     B00010001,
     B10000000,
     B00000001,
     B01000000,
     B00000100,
     B00010000,
     B00000000},
    {B00100010,
     B10001000,
     B00000001,
     B10000000,
     B00000010,
     B00100000,
     B00001000,
     B00000000}};

//Wating animation

// the setup routine runs once when you press reset:
#line 153 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void setup();
#line 168 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void drawImg(byte byteArray[]);
#line 178 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void hearBeatAnimation();
#line 201 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void waitingHeartAnimation();
#line 214 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void emptyHeartAnimation();
#line 238 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void push_animation(enum animation an);
#line 251 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
animation pop_animation();
#line 270 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void loop();
#line 153 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  lc.shutdown(0, false); // Wake up displays
  lc.shutdown(1, false);
  lc.setIntensity(0, 1); // Set intensity levels
  lc.setIntensity(1, 1);
  lc.clearDisplay(0); // Clear Displays
  lc.clearDisplay(1);
}

//  Take values in Arrays and Display them

void drawImg(byte byteArray[])
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, byteArray[i]);
  }
}

// ========== HEARTANIMATIONS ========== //

void hearBeatAnimation()
{
  lc.setIntensity(0, 1); // Set intensity levels
  lc.setIntensity(1, 1);
  drawImg(heartbeat[1]);
  delay(50);

  lc.setIntensity(0, 5); // Set intensity levels
  lc.setIntensity(1, 5);
  drawImg(heartbeat[2]);
  delay(50);

  lc.setIntensity(0, 7); // Set intensity levels
  lc.setIntensity(1, 7);
  drawImg(heartbeat[3]);
  delay(100);

  lc.setIntensity(0, 0.4); // Set intensity levels
  lc.setIntensity(1, 0.4);
  drawImg(heartbeat[0]);
  delay(800);
}

void waitingHeartAnimation()
{
  lc.setIntensity(0, 0.1); // Set intensity levels
  lc.setIntensity(1, 0.1);
  int waitingDelay = 100;
  int arrayLength = sizeof(waitingHeartBytes2) / sizeof(waitingHeartBytes2[0]);
  for (int i = 0; i < arrayLength; i++)
  {
    drawImg(waitingHeartBytes2[i]);
    delay(waitingDelay);
  }
}

void emptyHeartAnimation()
{
  lc.setIntensity(0, 0.4); // Set intensity levels
  lc.setIntensity(1, 0.4);
  int arrayLength = sizeof(emptyHeart) / sizeof(emptyHeart[0]);
  for (int i = 0; i < arrayLength; i++)
  {
    drawImg(emptyHeart[i]);
  }
}

// ========== ANIMATIONLOGIC ========== //

// if animation in loop, then do that otherwise,
// basic animation



const int max_animations = 20;
int first_animation = 0;
int last_animation = 0;
int num_animations = 0;

animation animationEvents[max_animations];
void push_animation(enum animation an) {
  if(num_animations >= max_animations) {
    return;
  }

  animationEvents[last_animation] = an;
  last_animation++;
  if (last_animation == max_animations) {
    last_animation = 0;
  }
  num_animations++;
}

animation pop_animation() {
  if (num_animations == 0) {
    return EMPTY;
  }

  animation ret = animationEvents[first_animation];
  first_animation++;
  if (first_animation == max_animations) {
    first_animation = 0;
  }

  num_animations--;

  return ret;
}

// animation nextAnimation = WAITING;

// the loop routine runs over and over again forever:
void loop()
{

  // ========== TRIGGERING ANIMATIONS ========== //
  int animationEventLength = sizeof(animationEvents) / sizeof(animationEvents[0]);
  animation nextAnimation;
  /*if (animationEvents > 0)
  {
    nextAnimation = HEARTBEAT;
    // nextAnimation = animationEvents[0];
  } else {
    nextAnimation = WAITING;
  }*/

  nextAnimation = pop_animation();

  switch (nextAnimation)
  {
  case HEARTBEAT:
    hearBeatAnimation();
    break;
  case WAITING:
    waitingHeartAnimation();
    break;
  default:
    emptyHeartAnimation();
    break;
  }







}

