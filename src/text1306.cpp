/*

  text1306

  anthony shibitov

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
    Wire.write(0xA0); //Segment remap disabled
    _flipped = false;
    Wire.endTransmission();
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
    if(line < 0 || line > 7)
      return;
    char size = strlen(buffer);
    if(_flipped == false){
      for(int i = 0; i < size && i <= 21; i++){
        _writeChar(line, i, buffer[i]);
      }
    } else {
      for(int i = 0; i < size && i <= 21; i++){
        _writeChar(line, i, buffer[i]);
      }
    }
}

void TextDisplay::clearLine(int line){
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x10);
    if(_flipped){
      line = 7 - line;
    }
    int x = 0xB0 + line;
    Wire.write(x);
    Wire.endTransmission();

    /* There's sometimes dead space on the righthand side. From corruption that
       is outside of the regular writing bounds, hence 5 loops for 128px wide */
    for(int outer = 0; outer < 5; outer++){
      Wire.beginTransmission(0x3C);
      Wire.write(0x40);
      /* Needs to be done in 16 byte bursts. I2C max buffer size is typically 32bytes for Wire.h */
      for(int col = 0; col < 30; col++){
        Wire.write(0x00);
      }
      Wire.endTransmission();
    }
}

void TextDisplay::clearAll(){
  for(int currentPage = 0; currentPage < 8; currentPage++){
    clearLine(currentPage);
  }
}

void TextDisplay::_writeChar(int line, int col, char buffer){
    char fontBuffer[6];
    for(int i = 0; i < 6; i++){
        if(_flipped){
          fontBuffer[i] = reverse(font[buffer][i]);
        } else {
          fontBuffer[i] = font[buffer][i];
        }
    }

    col = col * 6;
    /* Add one pixel to account for misalignment. */
    col++;
    char columnLowerNibble = col & 0x0F;
    char columnHigherNibble = ((col & 0xF0) >> 4) + 0x10;
    if(_flipped){
      line = 7 - line;
    }
    int page = line + 0xB0;

    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(columnLowerNibble);
    Wire.write(columnHigherNibble);
    Wire.write(page);
    Wire.endTransmission();

    Wire.beginTransmission(0x3C);
    Wire.write(0x40);
    for(int i = 0; i < 6; i++){
        Wire.write(fontBuffer[i]);
    }
    Wire.endTransmission();

}

void TextDisplay::flipDisplay(bool flip){
  if(flip == false){
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(0xA0);
    Wire.endTransmission();  
    _flipped = false;
  }
  else {
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(0xA1);
    Wire.endTransmission();
    _flipped = true;
  }
}

/* Credit: https://stackoverflow.com/a/2602885 */
unsigned char TextDisplay::reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}