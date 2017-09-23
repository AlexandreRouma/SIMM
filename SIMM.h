/*
 * File:    SIMM.h
 * Date:    23/09/2017
 * Author:  Alexandre Rouma (@WhatsTheGeekYT twitter)
 * Version: 1.1.0
 */

class SIMMClass {
    public:
        void begin();
        void stop();
        byte read(uint16_t row, uint16_t column);
        void write(uint16_t row, uint16_t column, byte data);
        void readBlock(uint16_t row, uint16_t column, uint16_t length, byte array[]);
        void writeBlock(uint16_t row, uint16_t column, byte array[]);
};

extern SIMMClass SIMM;