/*
 * File:    SIMM.cpp
 * Date:    23/09/2017
 * Author:  Alexandre Rouma (@WhatsTheGeekYT twitter)
 * Version: 1.1.0
 */
 
// Important: Keep in mind that CAS, RAS and WE are inverted, so when I write 0, it means enabled !
// This may help you understand better how it works. More info on the github repo.

#include "Arduino.h"
#include "SIMM.h"
#include <TimerThree.h>

SIMMClass SIMM;

void refreshRam() {
  for (int i = 0; i < 4096; i++) {
    PORTC = PORTC & B11011111;              // Enable CAS
    PORTC = PORTC & B01111111;              // Enable RAS
    PORTC = PORTC | B00100000;              // Disable CAS
    PORTC = PORTC | B10000000;              // Disable RAS
  }
}

void SIMMClass::begin(){
    cli();                                  // Disable interrupts while we set up everything

    Timer3.initialize(62000);               // Set Timer3 to fire every 62ms
    Timer3.attachInterrupt(&refreshRam);    // Attach Timer3 interrupt to the RAM refresh routine

    DDRL = 0b00000000;                      // Set PORTL (the data bus) to input
    DDRA = 0b11111111;                      // Set LB Address to output
    DDRC = 0b11111111;                      // Set HB Address and controls to output
    PORTA = 0b00000000;                     // Clear PORTA
    PORTC = 0b11100000;                     // Clear PORTC and set RAS, CAS and WE to HIGH (remember these three are inverted)

    _delay_us(200);                         // Wait 200 microseconds to be sure the RAM is ready
    for (uint8_t t = 0; t < 8; t++) {       // Initialize the RAM
        refreshRam();
    }

    sei();                                  // Re-enable interrupts
}

void SIMMClass::stop(){
    Timer3.detachInterrupt();
}

byte SIMMClass::read(uint16_t row, uint16_t column){
    byte data;                              // This is the buffer used for the data from the RAM

    cli();

    PORTA = row;                            // Write lower row address byte to PORTA
    PORTC = PORTC | (row >> 8);             // Write lower row address byte to PORTA
    PORTC = PORTC & B01111111;              // Enable RAS

    PORTA = column;                         // Write lower column address byte to PORTA
    PORTC = PORTC | (column >> 8);          // Write high column address byte to PORTA
    PORTC = PORTC & B11011111;              // Enable CAS

    PORTC = PORTC | B10000000;              // Disable RAS
    PORTC = PORTC | B00100000;              // Disable CAS

    data = PINL;                            // Read data from PORTL
    sei();

    return data;
}

void SIMMClass::write(uint16_t row, uint16_t column, byte data){
    cli();                                  // Disable interrupts while we write

    DDRL = B11111111;                       // Set PORTL as output;

    PORTA = row;                            // Write lower row address byte to PORTA
    PORTC = PORTC | (row >> 8);             // Write high row address byte to PORTA
    PORTC = PORTC & B01111111;              // Enable RAS

    PORTL = data;                           // Write our value to RAM

    PORTC = PORTC & B10111111;              // Enable WE

    PORTA = column;                         // Write lower column address byte to PORTA
    PORTC = PORTC | (column >> 8);          // Write high column address byte to PORTC

    PORTC = PORTC & B11011111;              // Strobe CAS. One clock cycle is enough for the ram to register !
    PORTC = PORTC | B00100000;

    PORTC = PORTC | B01000000;              // Disable WE
    PORTC = PORTC | B10000000;              // Disable RAS

    DDRL = B00000000;                       // Set PORTL back to input

    sei();                                  // Re-enable interrupts
}

void SIMMClass::readBlock(uint16_t row, uint16_t column, uint16_t length, byte array[]){
    for (uint16_t i = 0; i < length; i++){  // Cycle through addresses and fill up the array
        if (column >= 4096){
            column = 0;                     // If the column is greater or equal to 4096, increment
            row++;                          // the rows and set column back to 0
        }
        array[i] = read(row, column);       // Write the data to the array
        column++;                           // Increment the column
    }
}

void SIMMClass::writeBlock(uint16_t row, uint16_t column, byte array[]){
    uint16_t length = sizeof(array);        // Get the size of the array
    for (uint16_t i = 0; i < length; i++){  // Cycle through the array write the values to RAM
        if (column >= 4096){
            column = 0;                     // If the column is greater or equal to 4096, increment
            row++;                          // the rows and set column back to 0
        }
        write(row, column, array[i]);       // Write the data to RAM
        column++;                           // Increment the column
    }
}