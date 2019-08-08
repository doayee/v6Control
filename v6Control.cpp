/*******************************************************************************
 * File:                    v6Control.c           	           
 * Date:                    31/07/2019                                   
 * Author:                  Thomas McQueen                                  
 * Target:                  Wifi Enabled Arduino (inc. ESP32, ESP8266)            
 * Copyright:               Doayee 2019 		                          
 * Description:             A library for simple interaction with a
 *                          v6/TiVo box over the wireless network
 ******************************************************************************/
/*******************************************************************************
 * Includes  
 ******************************************************************************/
#include <Arduino.h>
#include "v6Control.h"

/*******************************************************************************
 * Constructors                                                      
 ******************************************************************************/

v6Client::v6Client(const char* ip, int port){
  _ip = ip;
  _port = port;
}

/*******************************************************************************
 * Command Functions - These functions all call processCommand() with the
 * relevant command for desired operation                                                          
 ******************************************************************************/

void v6Client::changeChannel(int c){
  String cmd = "SETCH ";
  cmd += c;

  processCommand(cmd);
}
void v6Client::playbackPlay(){
  processCommand(CMD_PLAYBACK_PLAY);
}
void v6Client::playbackPause(){
  processCommand(CMD_PLAYBACK_PAUSE);
}
void v6Client::playbackFwd(){
  processCommand(CMD_PLAYBACK_FWD);
}
void v6Client::playbackRev(){
  processCommand(CMD_PLAYBACK_REV);
}
void v6Client::playbackReplay(){
  processCommand(CMD_PLAYBACK_REPLAY);
}
void v6Client::playbackAdvance(){
  processCommand(CMD_PLAYBACK_ADVANCE);
}
void v6Client::playbackRecord(){
  processCommand(CMD_PLAYBACK_RECORD);
}
void v6Client::playbackStop(){
  processCommand(CMD_PLAYBACK_STOP);
}

void v6Client::subsOn(){
  processCommand(CMD_SUBS_ON);
}
void v6Client::subsOff(){
  processCommand(CMD_SUBS_OFF);
}
void v6Client::chUp(){
  processCommand(CMD_CH_UP);
}
void v6Client::chDown(){
  processCommand(CMD_CH_DN);
}
void v6Client::navUp(){
  processCommand(CMD_NAV_UP);
}
void v6Client::navDown(){
  processCommand(CMD_NAV_DOWN);
}
void v6Client::navLeft(){
  processCommand(CMD_NAV_LEFT);
}
void v6Client::navRight(){
  processCommand(CMD_NAV_RIGHT);
}
void v6Client::navOk(){
  processCommand(CMD_NAV_OK);
}
void v6Client::navHome(){
  processCommand(CMD_NAV_HOME);
}
void v6Client::navTv(){
  processCommand(CMD_NAV_TV);
}
void v6Client::navGuide(){
  processCommand(CMD_NAV_GUIDE);
}
void v6Client::navInfo(){
  processCommand(CMD_NAV_INFO);
}
void v6Client::navBack(){
  processCommand(CMD_NAV_BACK);
}
void v6Client::navRed(){
  processCommand(CMD_RED);
}
void v6Client::navGreen(){
  processCommand(CMD_GREEN);
}
void v6Client::navYellow(){
  processCommand(CMD_YELLOW);
}
void v6Client::navBlue(){
  processCommand(CMD_BLUE);
}

void v6Client::numericInput(int n){
  switch(n){
    case 0:
      processCommand(CMD_NUM_0);
      break;
    case 1:
      processCommand(CMD_NUM_1);
      break;
    case 2:
      processCommand(CMD_NUM_2);
      break;
    case 3:
      processCommand(CMD_NUM_3);
      break;
    case 4:
      processCommand(CMD_NUM_4);
      break;
    case 5:
      processCommand(CMD_NUM_5);
      break;
    case 6:
      processCommand(CMD_NUM_6);
      break;
    case 7:
      processCommand(CMD_NUM_7);
      break;
    case 8:
      processCommand(CMD_NUM_8);
      break;
    case 9:
      processCommand(CMD_NUM_9);
      break;
    case 99:
      processCommand(CMD_NUM_CLEAR);
      break;
  }

}
/*******************************************************************************
 * Name:   setSerialOutput(Stream *_s)     
 * Inputs: (Pointer to a) Stream Object e.g. Serial&                       
 * Return: none     
 * Notes:  Stores the the passed in pointer to a Stream (Serial) object in 
 * an assosicated arduino sketch so we can optionally output to serial monitor	    
 ******************************************************************************/
void v6Client::setSerialOutput(Stream *s){
  _serial = s;
}
/*******************************************************************************
 * Name:   connectClient()     
 * Inputs: None                     
 * Return: Integer success or failure code     
 * Notes:  Uses the Arduino WiFi library to establish a tcp connection to
 *         the IP and port specified at instantiation.	    
 ******************************************************************************/
int v6Client::connectClient(){
  if (!connect(_ip, _port)) {
        if(_serial) _serial->println("connection failed");
        return EXIT_FAILURE;
    }  
  return EXIT_SUCCESS;  
}
/*******************************************************************************
 * Name:   processCommand(String cmd)   
 * Inputs: String                     
 * Return: Integer success or failure code  
 * Notes:  Takes in a String that the v6/TiVo understands, prints it to the 
 * WiFiClient and waits for a response before printing it to serial
 ******************************************************************************/
int v6Client::processCommand(String cmd){
  //wait here until enough time has passed since the previous command
  while(millis() - _lastCommandTime < 200);

  //opens a tcp connection to the address specified at instantiation
  if(connectClient()){
    return EXIT_FAILURE;
  }

  //tell the user what is going on if they have set a serial output
  if(_serial) {
    _serial->print("Sending Command: ");
    _serial->println(cmd);
  }

  //send the command to the tcp socket using the Arduino WiFi library
  println(cmd);

  //wait for a response or timeout and tell the user if requested
  _lastCommandTime = millis();
  while (available() == 0) {
      if (millis() - _lastCommandTime > 5000) {
          if(_serial) _serial->println(">>> v6 Timeout !");
          stop();
          return EXIT_FAILURE;
      }
  }

  //read the response and output to serial if requested
  while(available()) {
      String line = readStringUntil('\r');
      if(_serial) _serial->print("Response: ");
      if(_serial) _serial->println(line);
  }

  //gracefully disconnect from the set top box
  stop();

  return EXIT_SUCCESS;

}
