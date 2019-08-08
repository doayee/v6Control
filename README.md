# v6Control - A V6 / TiVo Controller library
This is a library for use with a Wifi-enabled Arduino (tested with ESP32 / ESP8266) in order to control a Virgin Media V6 or TiVo box on the local network directly from your microcontroller.

## Getting started
In order to get started you must enable Network Remote Control in your V6/TiVo device settings. NOTE: anyone with the network key can then control the set top box - only do this on totally trusted networks.

Install the library in your Arduino/Platformio IDE and include the library header like `#include "v6Control.h"` at the top of your sketch.

To interact with a set top box you need to create a v6Client object which is defined as part of the library. 
To do this write the line `v6Client my_v6(ip);` where `my_v6` can be any name you like and ip is a `const char*` of the set top boxes IP address.

Optionally enable printing of library debug and response messages from the set top box to the Arduino Serial Monitor by calling `my_v6.setSerialOutput(&Serial);` after creating the object.

You can then issue any command in the library and see the change on your TV. For example `v6.changeChannel(102);`. See the examples folder for a more comprehensive example.

## Examples
  * [change_channels.ino](https://github.com/doayee/v6Control/blob/master/Examples/change_channels/change_channels.ino)
  
   The most basic "Hello World" of this library. Showcases how to set up a connection and issue a command to the set top box

  * [numeric_input.ino](https://github.com/doayee/v6Control/blob/master/Examples/numeric_input/numeric_input.ino)
  
   As above but achieves its result by simulating pressing individual number keys.
  
  * [browser_remote.ino](https://github.com/doayee/v6Control/blob/master/Examples/browser_remote/browser_remote.ino)
  
   A feature rich example which uses your microcontroller as a web server to host a webpage which has an interface for most functions of the library, which you can view on any device with a web browser.
   
## Full Command Function List
### Numeric Inputs
  * changeChannel(int c);
  * numericInput(int n);

### Playback States
  * playbackPlay();
  * playbackPause();
  * playbackFwd();
  * playbackRev();
  * playbackReplay();
  * playbackAdvance();
  * playbackRecord();
  * playbackStop();
 
### Navigation Buttons
  * navUp();
  * navDown();
  * navLeft();
  * navRight();
  * navOk();
  * navHome();
  * navTv();
  * navGuide();
  * navInfo();
  * navBack();
  * navRed();
  * navGreen();
  * navYellow();
  * navBlue();
  
### Misc 
  * subsOn();
  * subsOff();
  
  * chUp();
  * chDown();

