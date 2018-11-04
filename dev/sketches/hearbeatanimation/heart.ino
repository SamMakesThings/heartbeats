

/*
HEART
*/

#include "OneButton.h"
#include "LedControl.h"
#include "heart.h"



/*
BUTTONS
*/

// constants won't change. They're used here to set pin numbers:
// const int buttonPin = 2;     // the number of the pushbutton pin
// const int ledPin =  7;       // the number of the LED pin

// variables will change:
// int buttonState = 0;         // variable for reading the pushbutton status

// Setup a new OneButton on pin A1.  
// keywords https://github.com/mathertel/OneButton/blob/master/keywords.txt
OneButton firstbutton(A1, true);
OneButton secondbutton(A2, true);
OneButton thirdbutton(A3, true);
    


/*
LED
*/

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected

unsigned long animation_ts;
bool animation_finished = true;
// Heart Animations are in heart.h

// the setup routine runs once when you press reset:
void setup()
{
 // enable the standard led on pin 13.
  pinMode(7, OUTPUT);      // sets the digital pin as output
  
  // link the doubleclick function to be called on a doubleclick event.   
  firstbutton.attachClick(turnLEDOne);
  secondbutton.attachClick(turnLEDTwo);
  thirdbutton.attachClick(turnLEDThree);
  // button2.attachClick(doubleclick);


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
  static int state = 0;

  if (millis() - animation_ts < 50) {
    return;
  }

  animation_ts = millis();

  switch (state) {
    case 0:
      lc.setIntensity(0, 1); // Set intensity levels
      lc.setIntensity(1, 1);
      drawImg(heartbeat[1]);
      state = 1;
      break;

    case 1:
      lc.setIntensity(0, 5); // Set intensity levels
      lc.setIntensity(1, 5);
      drawImg(heartbeat[2]);
      state = 2;
      break;

    case 2:
      lc.setIntensity(0, 7); // Set intensity levels
      lc.setIntensity(1, 7);
      drawImg(heartbeat[3]);
      state = 3;
      break;

    case 3:
      lc.setIntensity(0, 7); // Set intensity levels
      lc.setIntensity(1, 7);
      drawImg(heartbeat[3]);
      state = 4;
      break;

    case 4:
      lc.setIntensity(0, 0.4); // Set intensity levels
      lc.setIntensity(1, 0.4);
      drawImg(heartbeat[0]);
      animation_finished = true;

      state = 0;
      break;
  }
}

void waitingHeartAnimation()
{
  static int i = 0;
  if (millis() - animation_ts < 100) {
    return;
  }

  animation_ts = millis();

  lc.setIntensity(0, 0.01); // Set intensity levels
  lc.setIntensity(1, 0.01);
  int arrayLength = sizeof(waitingHeartBytes2) / sizeof(waitingHeartBytes2[0]);
  drawImg(waitingHeartBytes2[i]);
  if(++i == arrayLength) {
    i = 0;
    animation_finished = true;
  }
}


// ========== ANIMATIONLOGIC ========== //
// if animation in loop, then do that otherwise,
// basic animation

const int max_animations = 20;
int first_animation = 0;
int last_animation = 0;
int num_animations = 0;
boolean experience_started = false;

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
    return WAITING;
  }

  animation ret = animationEvents[first_animation];
  first_animation++;
  if (first_animation == max_animations) {
    first_animation = 0;
  }

  num_animations--;

  return ret;
}


void loop()
{

  // keep watching the push button:
  firstbutton.tick();
  secondbutton.tick();
  thirdbutton.tick();
  



  // ========== TRIGGERING ANIMATIONS ========== //
  int animationEventLength = sizeof(animationEvents) / sizeof(animationEvents[0]);
  static animation nextAnimation;

  if(animation_finished) {
    nextAnimation = pop_animation();
    animation_finished = false;
  }

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



// this function will be called when the button was pressed 2 times in a short timeframe.
void turnLEDOne() {
  Serial.write("startButton ");
  static int m = LOW;
  // reverse the LED 
  m = !m;
  digitalWrite(7, m);
  
  experience_started = true;
} // doubleclick

void turnLEDTwo() {
  Serial.write("beatButton ");
  push_animation(HEARTBEAT);
  static int m = LOW;
  // reverse the LED 
  m = !m;
  digitalWrite(7, m);
} // doubleclick

void turnLEDThree() {
  Serial.write("resetButton ");
  static int m = LOW;
  // reverse the LED 
  m = !m;
  digitalWrite(7, m);

  experience_started = false;
} // doubleclick
     