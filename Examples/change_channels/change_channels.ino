/*******************************************************************************
 * File:                    change_channels.ino                        
 * Date:                    31/07/2019                                   
 * Author:                  Thomas McQueen                                  
 * Target:                  Wifi Enabled Arduino (inc. ESP32, ESP8266)            
 * Copyright:               Doayee 2019                             
 * Description:             An Arduino example sketch to showcase the v6Control
 *                          library by connecting to a set top box 
 *                          and changing channels
 ******************************************************************************/
/*******************************************************************************
 * Includes  
 ******************************************************************************/
#include <Arduino.h>
#include "v6Control.h"

/*******************************************************************************
 * Globals                                                         
 ******************************************************************************/
const char* ssid     = "";
const char* password = "";

const char* v6_ip = "192.168.0.13";

/*************************************************************************************
 * Object Definitions
 ************************************************************************************/
v6Client v6(v6_ip);

/*************************************************************************************
 * Functions
 ************************************************************************************/
void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(5000);
      if(WiFi.status() != WL_CONNECTED) Serial.println("Connect timeout... Retrying!");
    }

  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  v6.setSerialOutput(&Serial);

}

void loop() {

  //continually alternate between the first two channels on the set top box
  v6.changeChannel(101);
  delay(5000);
  v6.changeChannel(102);
  delay(5000);
  

}
