/*******************************************************************************
 * File:                    v6Control.h            	           
 * Date:                    31/07/2019                                   
 * Author:                  Thomas McQueen                                  
 * Target:                  Wifi Enabled Arduino (inc. ESP32, ESP8266)            
 * Copyright:               Doayee 2019 		                          
 * Description:             A library for simple interaction with a
 *                          v6/TiVo box over the wireless network
 ******************************************************************************/

#ifndef v6Control_h
#define v6Control_h

/*******************************************************************************
 * Module includes       
 ******************************************************************************/
#include <Arduino.h>
#include <Stream.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

/*******************************************************************************
 * System Wide Module definitions                                             
 ******************************************************************************/

#define CMD_PLAYBACK_PLAY     "KEYBOARD PLAY"
#define CMD_PLAYBACK_PAUSE    "KEYBOARD PAUSE"
#define CMD_PLAYBACK_FWD      "KEYBOARD FORWARD"
#define CMD_PLAYBACK_REV      "KEYBOARD REVERSE"
#define CMD_PLAYBACK_REPLAY   "KEYBOARD REPLAY"
#define CMD_PLAYBACK_ADVANCE  "KEYBOARD ADVANCE"
#define CMD_PLAYBACK_RECORD   "KEYBOARD RECORD"
#define CMD_PLAYBACK_STOP     "KEYBOARD STOP"

#define CMD_SUBS_ON           "KEYBOARD CC_ON"
#define CMD_SUBS_OFF          "KEYBOARD CC_OFF"

#define CMD_CH_UP             "KEYBOARD CHANNELUP"
#define CMD_CH_DN             "KEYBOARD CHANNELDOWN"

#define CMD_NAV_UP            "KEYBOARD UP"
#define CMD_NAV_DOWN          "KEYBOARD DOWN"
#define CMD_NAV_LEFT          "KEYBOARD LEFT"
#define CMD_NAV_RIGHT         "KEYBOARD RIGHT"
#define CMD_NAV_OK            "KEYBOARD SELECT"
#define CMD_NAV_HOME          "KEYBOARD TIVO"
#define CMD_NAV_TV            "KEYBOARD LIVETV"
#define CMD_NAV_GUIDE         "KEYBOARD GUIDE"
#define CMD_NAV_INFO          "KEYBOARD INFO"
#define CMD_NAV_BACK          "KEYBOARD EXIT"

#define CMD_RED               "KEYBOARD ACTION_A"
#define CMD_GREEN             "KEYBOARD ACTION_B"
#define CMD_YELLOW            "KEYBOARD ACTION_C"
#define CMD_BLUE              "KEYBOARD ACTION_D"

#define CMD_NUM_0             "KEYBOARD NUM0"
#define CMD_NUM_1             "KEYBOARD NUM1"
#define CMD_NUM_2             "KEYBOARD NUM2"
#define CMD_NUM_3             "KEYBOARD NUM3"
#define CMD_NUM_4             "KEYBOARD NUM4"
#define CMD_NUM_5             "KEYBOARD NUM5"
#define CMD_NUM_6             "KEYBOARD NUM6"
#define CMD_NUM_7             "KEYBOARD NUM7"
#define CMD_NUM_8             "KEYBOARD NUM8"
#define CMD_NUM_9             "KEYBOARD NUM9"
#define CMD_NUM_CLEAR         "KEYBOARD CLEAR"

/*******************************************************************************
 * Classes                                                 
 ******************************************************************************/
class v6Client : public WiFiClient {

public:
  v6Client(const char* ip, int port = 31339);
  void changeChannel(int c);

  void playbackPlay();
  void playbackPause();
  void playbackFwd();
  void playbackRev();
  void playbackReplay();
  void playbackAdvance();
  void playbackRecord();
  void playbackStop();

  void subsOn();
  void subsOff();
  void chUp();
  void chDown();
  void navUp();
  void navDown();
  void navLeft();
  void navRight();
  void navOk();
  void navHome();
  void navTv();
  void navGuide();
  void navInfo();
  void navBack();

  void navRed();
  void navGreen();
  void navYellow();
  void navBlue();

  void numericInput(int n);

  void setSerialOutput(Stream *s);
private:
  int connectClient();
  int processCommand(String cmd);

  Stream *_serial = NULL;
  unsigned long _lastCommandTime;

  const char* _ip = NULL;
  int _port;
};

#endif
