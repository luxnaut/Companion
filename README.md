# Companion
V.2

Companion No. 2 | OSC Comm. Device 
Created by luxnaut 
 
Companion No. 2 is the second iteration in the series of custom controllers designed to send detailed 9-DOF, color, light, and simple gesture data via OSC communication.  

***Note that Arduino has been known to have issues with USB-C adapters when uploading***

***Note that the ESPRESSIF hardware has been having issues on macOS Big Sur, additional help can be found here (https://github.com/espressif/arduino-esp32/issues/4408)***

Required hardware: 
-	Adafruit HUZZAH32 | https://www.adafruit.com/product/3405
-	Adafruit BNO055 (STEMMA QT or standard) | https://www.adafruit.com/product/4754
-	Adafruit APDS9960 | https://www.adafruit.com/product/3595
-	PermaProto Board OR Breadboard | https://www.adafruit.com/product/1609 or https://www.adafruit.com/product/64
-	Lithium Ion Battery OR LiPoly Battery | https://www.adafruit.com/product/354 or https://www.adafruit.com/product/258
-	Soldering Iron and Solder 
-	Solid Strand Wire 

**BEFORE SOLDERING TO PERMA BOARD** it is best practice to lay out the wiring you will be using to make sure everything fits comfortably. 

## Hardware

1	Unless purchased with headers, solder the male headers to your microcontroller and sensors. On the sensors, you need only to solder the	 Vin side of headers. 

2	Make sure to orient the board so that the USB port is close to the edge of the permaboard. Solder the HUZZAH to the board, making sure to leave two spaces available on the side with SDA and SCL and one on the side with 3V and GND.  

3	Wire and solder the positive and negative busses with 3V and GND 

4	Clip the headers on the other side to create a flush surface with the board. 

5	Solder the wires in place for the Vin, GND, SDA, and SCL connections of the first sensor on the “top” part of the perma board. It is perhaps easiest to solder them to the edge closest to the busses. 

6	Place and solder the sensor accordingly, test your connections, snip the headers, and then repeat for the second sensor. 
______

## Software

1	Install the USB driver (https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for your current OS 

2	Download the CNMAT OSC Arduino Library (https://github.com/CNMAT/OSC) by clicking “code”, then “download zip”. Go into the Arduino IDE, go to “sketch”, “include 
library”, and then “add zip library”. 

3	In the Arduino IDE, go to “Arduino”, “preferences”, and under “Additional Board Manager URLs” paste: 
 	 	 	 	 	 
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json 
 
Then go to “Tools”, “Board”, and then “Boards Manager”. Search for “ESP32” and install 

4	Go to “Tools”, “Manage Libraries”, and install the Adafruit “BNO055” sensor library and the Adafruit “APDS9960” sensor library. This may trigger a popup menu to download the Adafruit Unified Sensor Library; if so, click yes. If not, download it from here (https://github.com/adafruit/Adafruit_Sensor). 
______

## Working with the Companion

1	Connect to your chosen WiFi network. 

***Note that enterprise networks, or networks with restricted access may cause connection errors.***

2	In Arduino, enter the SSID, password, and IP address. Enter a port number for the outPort variable.	 

3	Double check your code settings (board, upload speed, and port are primarily at fault if there’s any upload problems) 

4	Open the serial monitor to confirm everything is uploaded correctly. 

5	Begin OSC communication in your preferred application with your chosen port number and IP on the current network. 

***License***

MIT License

Copyright (c) 2021 luxnaut

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

