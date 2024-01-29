# text1306
## A simple, lightweight library for displaying text on SSD1306 driven OLEDs.

text1306 is a small and straight-forward library to display text on displays driven by an ssd1306. The entire library is roughly 10kb in size (and hopefully smaller in the future), and should fit on most chips. It supports the standard ASCII palette.

## Install:
- Download .zip file. Import to Arduino IDE (Sketch -> Include Library -> Add .ZIP Library...)

## Documentation

`init()`
> Initialize text1306 object. Connects to the ssd1306 peripheral via the `0x3C` I2C device address (this is specifically for 128x64 displays).

`inverted(bool invert)`
> `invert` specifies whether the displays colors will be inverted. `false` will display a black background with white text, while `true` will display a white background with black text.

`write(int line, char * buffer)`
> Writes a `buffer` to the specified `line`. On a 128x64 display, there are 8 lines, beginning at the top of the display (line 0) to the bottom (line 7).

`clearLine(int line)`
> Clear the specified `line` of all text.

`clearAll()`
> Clear all lines of text, effectively resetting the display.

## To do
&#9744; Reduce font library size by removing empty characters.  
&#9744; Submit to Arduino Library repo for easier install.  
&#9744; Support 128x32 displays.