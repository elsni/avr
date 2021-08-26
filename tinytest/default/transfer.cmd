rem echo off
rem echo Programming: %1%
rem avrdude -c usbtiny -p attiny2313 -D -U flash:w:%1%
avrdude -c usbtiny -p attiny2313 -U flash:w:tinytest.hex
pause
