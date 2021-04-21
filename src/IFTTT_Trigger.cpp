/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/SIT210_Projects_NWS/IFTTT_Trigger/IFTTT_Trigger/src/IFTTT_Trigger.ino"
/*
 * Project IFTTT_Trigger
 * Description:  This is an SIT210 task, where the student is required to build firmware which enacts an IFTTT trigger.  This uses the Particle Argon, and my case, an
 * ultrasonic distance sensor, rather than a light sensor.  I will apply the same principles as through it was a light sensor
 * Author:  Matthew Gray
 * Date:  11 April 21
 */

// Give static names to the trigger and the echo

void setup();
float range_find();
void loop();
#line 11 "c:/SIT210_Projects_NWS/IFTTT_Trigger/IFTTT_Trigger/src/IFTTT_Trigger.ino"
#define trigpin D2
#define echopin D3

// Pulse calculation constant for cm

const unsigned int cm_calc = 58;

// Setup the global distance variable

double distance;

int quality_check = 10;

bool at_desk;

bool prev_at_desk;


// setup() runs once, when the device is first turned on.
void setup() {
  // Setup the trigger as an output, the echo as an input
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  // Initially set the trigger to low
  digitalWrite(trigpin, LOW);

   
}

float range_find() {

  unsigned long echo_pulse_width;
  double distance;

  // Trigger must be held high for 10 us for pulse

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  // Conduct the measurement of how long the echo was high.
  echo_pulse_width = pulseIn(echopin, HIGH);

  // Calculate the distance in centimeters.
  distance = echo_pulse_width / cm_calc ;

  return distance;
}

void loop() {
  // The core of your code will likely live here.

  distance = range_find();
  
  if ((distance >= 100) and (quality_check < 20)) quality_check++;
  
  if (quality_check == 20) at_desk = false;

  if ((distance <= 100) and (quality_check > 0)) quality_check--;

  if (quality_check == 0) at_desk = true;

  if (at_desk != prev_at_desk) 
  {
    if (at_desk == true) Particle.publish("at_desk", "true");
    if (at_desk == false) Particle.publish("at_desk", "false");
  }

  Particle.publish("quality_check", String(quality_check));
  prev_at_desk = at_desk;

  delay(2000);

  
}