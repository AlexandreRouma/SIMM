/*
 * File:    ReadWrite.ino
 * Date:    23/09/2017
 * Author:  Alexandre Rouma (@WhatsTheGeekYT twitter)
 */

 // IMPRORTANT: This library requires an
 // Arduino MEGA and TimerThree to work

#include <SIMM.h>

void setup() {
  SIMM.begin();         // Initialize the SIMM RAM
  Serial.begin(115200); // Initialize the UART

  // Write the data to RAM
  SIMM.write(0, 0, 'T');
  SIMM.write(0, 1, 'E');
  SIMM.write(0, 2, 'S');
  SIMM.write(0, 3, 'T');

  // Read back the data
  Serial.write(SIMM.read(0, 0));
  Serial.write(SIMM.read(0, 1));
  Serial.write(SIMM.read(0, 2));
  Serial.write(SIMM.read(0, 3));
}

void loop() {

}
