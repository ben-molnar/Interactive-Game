#include <Adafruit_CircuitPlayground.h>

const byte switchPin = 7;
const byte buttonPin1 = 4;
const byte buttonPin2 = 5;

volatile bool switchFlag = false;
volatile bool buttonFlag = true;

int delayLED = 1500; //time delay between LEDs turning on and off
int multiplier = 2; //value the delay divides by when the player completes the current level
int LED = -1; //value that stores which LED is being turned on or off
int LEDnum = -1; //index for the while loop, which is reset if the player presses a button

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(10);

  attachInterrupt(digitalPinToInterrupt(switchPin), hardMode, CHANGE); //creates an interrupt for the hardmode feature
  attachInterrupt(digitalPinToInterrupt(buttonPin1), button1, FALLING); //creates an interrupt for one of the buttons
  attachInterrupt(digitalPinToInterrupt(buttonPin2), button2, FALLING); //creates an interrupt for the other button
}

void loop() 
{
  for(int i = 0; i < 10; ++i) //turns the LEDs off
  {
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
  }

  while(buttonFlag)//repeats until one of the buttons is pressed
  {
    CircuitPlayground.setPixelColor(LEDnum, 100, 100, 100); //turns the specific LED on
    LED = LEDnum; //sets the LED to the index value
    delay(delayLED);//delay by the however long the delayLED variable is, which depends on how far the player has progressed
    CircuitPlayground.setPixelColor(LEDnum, 0, 0, 0); //turns the specific LED off
    LED = -1;//sets the LED value to a value that represents no LED since no LED is on
    delay(delayLED);//delay by the however long the delayLED variable is, which depends on how far the player has progressed
    if(LEDnum < 10)//checks if the last LED is on or not, and if it's not, then the index value increases by 1
    {
      LEDnum++;
    }
    else//resets the index value to 0 for the first LED value
    {
      LEDnum = 0;
    }
  }
}

void button1()
{
  LEDnum = -1;
  buttonFlag = !buttonFlag;
  Serial.println("button 1 pressed");
  if(LED == 2)
  {
    delayLED = delayLED / multiplier; //decreases the delay between the the LEDs are turned on and off

    for(int i = 0; i < 10; ++i)//makes all of the LEDs green since the player pressed the button with the correct LED on
    {
      CircuitPlayground.setPixelColor(i, 0, 150, 0);
    }
    delay(200000); //give a long enough delay for the player to react and get ready
  }
  else
  {
    delayLED = 1500; //reset the time the LEDs are on and off
    CircuitPlayground.playTone(100, 500);
    for(int i = 0; i < 10; ++i)//makes all of the LEDs red since the player did not press the button with the correct LED on
    {
      CircuitPlayground.setPixelColor(i, 150, 0, 0);
    }
    delay(200000); //give a long enough delay for the player to react and get ready
  }
  buttonFlag = !buttonFlag;
  for(int i = 0; i < 11; ++i)//turns the LEDs off to start the next round
  {
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
  }
}

void button2()
{
  LEDnum = -1;
  buttonFlag = !buttonFlag;
  Serial.println("button 2 pressed");
  if(LED == 7)
  {
    delayLED = delayLED / multiplier;

    for(int i = 0; i < 10; ++i)//makes all of the LEDs green since the player pressed the button with the correct LED on
    {
      CircuitPlayground.setPixelColor(i, 0, 150, 0);
    }
    delay(200000); //give a long enough delay for the player to react and get ready
  }
  else
  {
    delayLED = 1500; //reset the time the LEDs are on and off
    CircuitPlayground.playTone(100, 500);
    for(int i = 0; i < 10; ++i) //makes all of the LEDs red since the player did not press the button with the correct LED on
    {
      CircuitPlayground.setPixelColor(i, 150, 0, 0);
    }
    delay(200000); //give a long enough delay for the player to react and get ready
  }
  buttonFlag = !buttonFlag;
  for(int i = 0; i < 11; ++i)//turns the LEDs off to start the next round
  {
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
  }
}

void hardMode() //hardmode starts off by default, the player has to turn it on every time they start
{
  switchFlag = !switchFlag;
  if(switchFlag)
  {
    Serial.println("Hard mode is now on.");
    multiplier = multiplier * 2;//increases the number the delay is divided by
  }
  else
  {
    Serial.println("Hard mode is now off.");
    multiplier = multiplier / 2;//decreases the number the delay is divided by
  }
}
