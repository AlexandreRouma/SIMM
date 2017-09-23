/*
 * File:    ReadWrite.ino
 * Date:    23/09/2017
 * Author:  Alexandre Rouma (@WhatsTheGeekYT twitter)
 * Version: 1.1.0
 */

 // IMPRORTANT: This library requires an
 // Arduino MEGA and TimerThree to work

#include <SIMM.h>

void setup() {
  SIMM.begin();         // Initialize the SIMM RAM
  Serial.begin(115200); // Initialize the UART

  // Write the data to RAM
  byte dataIn[4] = { 'T', 'E', 'S', 'T' };
  SIMM.writeBlock(0, 0, dataIn);

  // Read back the data
  byte dataOut[4];
  SIMM.readBlock(0, 0, 4, dataOut);
  Serial.write(dataOut[0]);
  Serial.write(dataOut[1]);
  Serial.write(dataOut[2]);
  Serial.write(dataOut[3]);
}

void loop() {

}
