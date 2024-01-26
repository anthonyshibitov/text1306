/*

    Font is 6x8

*/

#include "text1306.h"
#include "font.h"

TextDisplay::TextDisplay(){
    
}

void TextDisplay::init(){
    Wire.begin();
    Wire.setClock(400000);
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(0xAF);
    Wire.write(0x20);
    Wire.write(0x02);
    Wire.write(0xA0);
    Wire.endTransmission();

    _linePos = 7;
    _colPos = 0;
}

void TextDisplay::inverted(bool invert){
    if(!invert){
        Wire.beginTransmission(0x3C);
        Wire.write(0x80);
        Wire.write(0xA6);
        Wire.endTransmission();
    } else {
        Wire.beginTransmission(0x3C);
        Wire.write(0x80);
        Wire.write(0xA7);
        Wire.endTransmission();
    }
}

void TextDisplay::write(int line, char * buffer){
    char size = strlen(buffer);
    for(int i = 0; i < size; i++){
        _writeChar(line, i, buffer[i]);
    }
}

void TextDisplay::clearLine(int line){
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x10);
    int x = 0xB0 + line;
    Wire.write(x);
    Wire.endTransmission();

    for(int col = 0; col < 140; col++){
      Wire.beginTransmission(0x3C);
      Wire.write(0xC0);
      Wire.write(0x00);
      Wire.endTransmission();
    }
}

void TextDisplay::clearAll(){
  for(int currentPage = 0; currentPage < 8; currentPage++){
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x10);
    int x = 0xB0 + currentPage;
    Wire.write(x);
    Wire.endTransmission();
    for(int col = 0; col < 140; col++){
      Wire.beginTransmission(0x3C);
      Wire.write(0xC0);
      Wire.write(0x00);
      Wire.endTransmission();
    }
  }
}

void TextDisplay::_writeChar(int line, int col, char buffer){
    char fontBuffer[6];
    for(int i = 0; i < 6; i++){
        fontBuffer[i] = font[buffer][i];
    }

    col = col * 6;
    /* Add one pixel to account for misalignment. */
    col++;
    char columnLowerNibble = col & 0x0F;
    char columnHigherNibble = ((col & 0xF0) >> 4) + 0x10;
    int page = line + 0xB0;

    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(columnLowerNibble);
    Wire.write(columnHigherNibble);
    Wire.write(page);
    Wire.endTransmission();

    for(int i = 0; i < 6; i++){
        Wire.beginTransmission(0x3C);
        Wire.write(0xC0);
        Wire.write(fontBuffer[i]);
        Wire.endTransmission();
    }
}