# 1 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
# 1 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino"
/*
HEART
*/

# 6 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino" 2
# 7 "/Users/vinni/Desktop/GIT/shdb18/heart/heart.ino" 2

// #include "data.ino"

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected

// empty heart
const byte emptyHeart[][8] = {
    {102,
     153,
     129,
     129,
     66,
     36,
     24,
     0}};

// Heartbeat animation
const byte heartbeat[][8] = {
    {102,
     153,
     129,
     129,
     66,
     36,
     24,
     0},
    {102,
     153,
     129,
     153,
     90,
     36,
     24,
     0},
    {102,
     153,
     189,
     189,
     126,
     36,
     24,
     0},
    {102,
     255,
     255,
     255,
     126,
     60,
     24,
     0}};

const byte waitingHeartBytes[][8] = {
    {102,
     129,
     129,
     129,
     66,
     36,
     24,
     0},
    {96,
     153,
     129,
     129,
     66,
     36,
     24,
     0},
    {102,
     152,
     128,
     129,
     66,
     36,
     24,
     0},
    {102,
     153,
     129,
     128,
     64,
     36,
     24,
     0},
    {102,
     153,
     129,
     129,
     66,
     32,
     16,
     0},
    {102,
     153,
     129,
     129,
     66,
     4,
     8,
     0},
    {102,
     153,
     129,
     1,
     2,
     36,
     24,
     0},
    {102,
     25,
     1,
     129,
     66,
     36,
     24,
     0},
    {6,
     153,
     129,
     129,
     66,
     36,
     24,
     0}};

const byte waitingHeartBytes2[][8] = {
    {68,
     17,
     128,
     1,
     64,
     4,
     16,
     0},
    {34,
     136,
     1,
     128,
     2,
     32,
     8,
     0}};

//Wating animation

// the setup routine runs once when you press reset:
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
