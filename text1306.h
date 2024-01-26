#ifndef text1306_h
#define text1306_h

#include "Arduino.h"
#include "Wire.h"

class TextDisplay {
    public:
        TextDisplay();
        void init();
        void inverted(bool);
        void write(int, char*);
        void print(char *);
        void clearLine(int);
        void clearAll();
    private:
        void _writeChar(int, int, char);
        int _linePos;
        int _colPos;
};

#endif