#ifndef text1306_h
#define text1306_h

#include "Arduino.h"
#include "Wire.h"

class TextDisplay {
    public:
        TextDisplay();
        void init();
        void inverted(bool invert);
        void write(int line, char * buffer);
        void clearLine(int line);
        void clearAll();
    private:
        void _writeChar(int, int, char);
};

#endif