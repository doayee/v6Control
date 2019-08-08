/*******************************************************************************
 * File:                    browser_remote.ino                        
 * Date:                    31/07/2019                                   
 * Author:                  Thomas McQueen                                  
 * Target:                  Wifi Enabled Arduino (inc. ESP32, ESP8266)            
 * Copyright:               Doayee 2019                             
 * Description:             An Arduino example sketch to showcase the v6Control
 *                          library by creating a web-browser remote control
 ******************************************************************************/
/*******************************************************************************
 * Includes  
 ******************************************************************************/
#include <Arduino.h>
#include "v6Control.h"

/*******************************************************************************
 * Constants and definitionss                                            
 ******************************************************************************/
/*******************************************************************************
 * Globals                                                         
 ******************************************************************************/
const char* ssid     = "";
const char* password = "";

const char* v6_ip = "192.168.0.13";

const char* html_page = "<html>\n<head>\n<title>V6 Controller</title>\n<style>\nbody {\n\tfont: 13px \"Lucida Sans Unicode\", \"Lucida Grande\", sans-serif;\n}\n</style>\n</head>\n<meta name=\"viewport\" content=\"width=device-width,height=device-height,initial-scale=1.0\"/>\n<body>\n<div width=100vh>\n  <form method=\'POST\'>\n    <div align=\"center\">Enter Channel Number </div>\n    <div align=\"center\">\n      <input type=\"text\" name=\"Channel\" class=\"field-long\"/>\n    </div>\n    <ul class=\"form-style-1\">\n      <li>\n        <div align=\"center\">\n          <input type=\"submit\" value=\"Submit\" />\n        </div>\n      </li>\n    </ul>\n  </form>\n  <form method=\'POST\'>\n    <ul class=\"form-style-1\">\n      <div align=\"center\">\n        <table width=\"200\" border=\"0\" class=\"form-style-1\">\n          <tr>\n            <td height=\"36\"><div align=\"center\"></div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"nav1\" value=\"Up\" />\n              </div></td>\n            <td><div align=\"center\"></div></td>\n          </tr>\n          <tr>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"nav2\" value=\"Left\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"nav3\" value=\"Ok\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"nav4\" value=\"Right\" />\n              </div></td>\n          </tr>\n          <tr>\n            <td height=\"45\"><div align=\"center\"></div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"nav5\" value=\"Down\" />\n              </div></td>\n            <td><div align=\"center\"></div></td>\n          </tr>\n        </table>\n        <p>\n          <input type=\"submit\" name=\"navA\" value=\"Home\" />\n        </p>\n        <table width=\"280\" border=\"0\">\n          <tr>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"nav6\" value=\"Back\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"nav7\" value=\"Guide\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"nav8\" value=\"Tv\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"nav9\" value=\"Info\" />\n            </div></td>\n          </tr>\n        </table>\n      </div>\n      <div align=\"center\">\n        <table width=\"200\" border=\"0\" class=\"form-style-1\">\n          <tr>\n            <td height=\"49\"><div align=\"center\">\n                <input type=\"submit\" name=\"num_1\" value=\"1\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_2\" value=\"2\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_3\" value=\"3\" />\n              </div></td>\n          </tr>\n          <tr>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_4\" value=\"4\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_5\" value=\"5\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_6\" value=\"6\" />\n              </div></td>\n          </tr>\n          <tr>\n            <td height=\"53\"><div align=\"center\">\n                <input type=\"submit\" name=\"num_7\" value=\"7\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_8\" value=\"8\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_9\" value=\"9\" />\n              </div></td>\n          </tr>\n          <tr>\n            <td height=\"53\"><div align=\"center\">\n                <input type=\"submit\" name=\"num_x\" value=\"x\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_0\" value=\"0\" />\n              </div></td>\n            <td><div align=\"center\">\n                <input type=\"submit\" name=\"num_other\" value=\" \" />\n              </div></td>\n          </tr>\n        </table>\n        <table width=\"280\" border=\"0\">\n          <tr>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"navB\" value=\"Red\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"navC\" value=\"Green\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"navD\" value=\"Yellow\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"navE\" value=\"Blue\" />\n            </div></td>\n          </tr>\n        </table>\n        <p>\n          <input type=\"submit\" name=\"play6\" value=\"Record\" />\n        </p>\n        <table width=\"200\" border=\"0\" class=\"form-style-1\">\n          <tr>\n            <td height=\"36\"><div align=\"center\"></div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"play1\" value=\"Play\" />\n            </div></td>\n            <td><div align=\"center\"></div></td>\n          </tr>\n          <tr>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"play2\" value=\"Rev\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"play3\" value=\"Pause\" />\n            </div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"play4\" value=\"Fwd\" />\n            </div></td>\n          </tr>\n          <tr>\n            <td height=\"45\"><div align=\"center\"></div></td>\n            <td><div align=\"center\">\n              <input type=\"submit\" name=\"play5\" value=\"Stop\" />\n            </div></td>\n            <td><div align=\"center\"></div></td>\n          </tr>\n        </table>\n        <p>&nbsp;</p>\n      </div>\n    </ul>\n  </form>\n</div>\n</body>\n</html>\n<style type=\"text/css\">\n.form-style-1 {\n\tmargin: 10px auto;\n\tmax-width: 400px;\n\tpadding: 2px 2px 2px 20px;\n\tfont: 13px \"Lucida Sans Unicode\", \"Lucida Grande\", sans-serif;\n}\n.form-style-1 li {\n\tpadding: 0;\n\tdisplay: block;\n\tlist-style: none;\n\tmargin: 2px 0 0 0;\n}\n.form-style-1 label {\n\tmargin: 0 0 3px 0;\n\tpadding: 0px;\n\tdisplay: block;\n\tfont-weight: bold;\n}\n.form-style-1 input[type=text], .form-style-1 input[type=password], textarea, select {\n\tbox-sizing: border-box;\n\t-webkit-box-sizing: border-box;\n\t-moz-box-sizing: border-box;\n\tborder: 1px solid #BEBEBE;\n\tpadding: 7px;\n\tmargin: 0px;\n\t-webkit-transition: all 0.30s ease-in-out;\n\t-moz-transition: all 0.30s ease-in-out;\n\t-ms-transition: all 0.30s ease-in-out;\n\t-o-transition: all 0.30s ease-in-out;\n\toutline: none;\n}\n.form-style-1 input[type=text]:focus, .form-style-1 input[type=password]:focus, .form-style-1 textarea:focus, .form-style-1 select:focus {\n\t-moz-box-shadow: 0 0 8px #88D5E9;\n\t-webkit-box-shadow: 0 0 8px #88D5E9;\n\tbox-shadow: 0 0 8px #88D5E9;\n\tborder: 1px solid #88D5E9;\n}\n.form-style-1 .field-long {\n\twidth: 100px;\n\n}\n.form-style-1 input[type=submit], .form-style-1 input[type=button] {\n\tbackground: #4B99AD;\n\tborder: none;\n\tcolor: #fff;\n\tpadding-top: 2px;\n\tpadding-right: 15px;\n\tpadding-bottom: 2px;\n\tpadding-left: 15px;\n}\n.form-style-1 .required {\n\tcolor: red;\n}\n/* Smartphones (portrait and landscape) ----------- */\n@media only screen and (min-device-width : 320px) and (max-device-width : 480px) {\n/* Styles */\n}\n\n/* Smartphones (landscape) ----------- */\n@media only screen and (min-width : 321px) {\n/* Styles */\n}\n\n/* Smartphones (portrait) ----------- */\n@media only screen and (max-width : 320px) {\n/* Styles */\n}\n\n/* iPads (portrait and landscape) ----------- */\n@media only screen and (min-device-width : 768px) and (max-device-width : 1024px) {\n/* Styles */\n}\n\n/* iPads (landscape) ----------- */\n@media only screen and (min-device-width : 768px) and (max-device-width : 1024px) and (orientation : landscape) {\n/* Styles */\n}\n\n/* iPads (portrait) ----------- */\n@media only screen and (min-device-width : 768px) and (max-device-width : 1024px) and (orientation : portrait) {\n/* Styles */\n}\n\n/* Desktops and laptops ----------- */\n@media only screen and (min-width : 1224px) {\n/* Styles */\n}\n\n/* Large screens ----------- */\n@media only screen and (min-width : 1824px) {\n/* Styles */\n}\n\n/* iPhone 4 ----------- */\n@media only screen and (-webkit-min-device-pixel-ratio : 1.5), only screen and (min-device-pixel-ratio : 1.5) {\n/* Styles */\n}\n</style>\n";
/*************************************************************************************
 * Object Definitions
 ************************************************************************************/
WiFiServer server(80);
v6Client v6(v6_ip);

/*******************************************************************************
 * Functions
 ******************************************************************************/
/*******************************************************************************
 * Name:   void setup()
 * Inputs: None
 * Return: None
 * Notes:  Runs once at the start of the processor
 ******************************************************************************/
void setup(){
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
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

    server.begin();

    v6.setSerialOutput(&Serial);
}

/*******************************************************************************
 * Name:   void http200(WiFiClient _client, const char* _content)
 * Inputs: _client - instance of WiFiClient, _content - http response content
 * Return: None
 * Notes:  Sends a HTTP 200 response line by line to a client with the content 
 *         passed in, useful for redisplaying a page after a button press
 ******************************************************************************/
void http200(WiFiClient _client, const char* _content){
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  _client.println("HTTP/1.1 200 OK");
  _client.println("Content-type:text/html");
  _client.println();

  // the content of the HTTP response follows the header:
  _client.print(_content);
  // The HTTP response ends with another blank line:
  _client.println();
}
/*******************************************************************************
 * Name: parseAndExecute(String req)   
 * Inputs: String req, which is the entire contents of the POST request
 * Return: 
 * Notes:  
 ******************************************************************************/
void parseAndExecute(String req){

    if(req.startsWith("Channel")){
      req.remove(0,8);
      int num = req.toInt();
      v6.changeChannel(num);
    }

    else if(req.startsWith("num")){
      //standard format num_n=n
      req.remove(0,6);
      if(req.equals("x")){
        v6.numericInput(99); //press clear
      }
      else{
        int num = req.toInt();
        v6.numericInput(num); //press the number
      }
    }

    else if(req.startsWith("nav")){
      //standard format navX=String
      req.remove(0,5);

      if(req.equals("Up")) v6.navUp();
      else if(req.equals("Down")) v6.navDown();
      else if(req.equals("Left")) v6.navLeft();
      else if(req.equals("Right")) v6.navRight();
      else if(req.equals("Ok")) v6.navOk();
      else if(req.equals("Home")) v6.navHome();
      else if(req.equals("Tv")) v6.navTv();
      else if(req.equals("Guide")) v6.navGuide();
      else if(req.equals("Info")) v6.navInfo();
      else if(req.equals("Back")) v6.navBack();
      else if(req.equals("Red")) v6.navRed();
      else if(req.equals("Green")) v6.navGreen();
      else if(req.equals("Yellow")) v6.navYellow();
      else if(req.equals("Blue")) v6.navBlue();
    }

    else if(req.startsWith("play")){
      //standard format playX=String
      req.remove(0,6);

      if(req.equals("Play")) v6.playbackPlay();
      else if(req.equals("Pause")) v6.playbackPause();
      else if(req.equals("Fwd")) v6.playbackFwd();
      else if(req.equals("Rev")) v6.playbackRev();
      else if(req.equals("Stop")) v6.playbackStop();
      else if(req.equals("Record")) v6.playbackRecord();
    }

}
/*******************************************************************************
 * Name:   handleClient(WiFiClient _client)
 * Inputs: _client - instance of WiFiClient that we want to handle
 * Return: None
 * Notes:  Reads an inbound HTTP request header then acts on it accordingly
 ******************************************************************************/
void handleClient(WiFiClient _client){
  int contentLength = 0;
  bool postWaiting = false;
  Serial.println("New Client.");           // print a message out the serial port
  String currentLine = "";                // make a String to hold incoming data from the client
  while (_client.connected()) {            // loop while the client's connected
    if (_client.available()) {             // if there's bytes to read from the client,
      char c = _client.read();             // read a byte, then
      Serial.write(c);                    // print it out the serial monitor
      if (c == '\n') {                    // if the byte is a newline character

        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request header
        if (currentLine.length() == 0) {
          if(postWaiting){
            //read in the post request, then act upon it
            Serial.println("Post Content:");
            delay(10);
            currentLine = "";
            for(int i = 0; i < contentLength; i++){
              c = _client.read();
              currentLine += c;
            }
            Serial.println(currentLine);
            postWaiting = false;
           
            parseAndExecute(currentLine);
          }
          //respond to any request with 200 OK and serve the page
          http200(_client, html_page); 
          break;  //leave the while loop to disconnect

        } else {    // as you got a newline, then clear currentLine:
          currentLine = "";
          }
      } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }

      //check to see if the client request is a POST so that we remember to process it beyond the header:
      if(currentLine.endsWith("POST /")) {
        postWaiting = true;
      }
      //figure out how much post content we need to read
      if (currentLine.endsWith("Content-Length: ")) {
        String len = "";
        while(c != '\r'){                 // read all the numbers that follow
          c = _client.read();             // read one byte, then
          Serial.write(c);                // write it to Serial
          len += c;                       // add it to the length String
        }
        contentLength = len.toInt();
      }
    }
  }
  // close the connection:
  _client.stop();
  Serial.println("Client Disconnected.");

}

void loop(){
 WiFiClient cli = server.available();   // listen for incoming clients on the webpage
 if (cli) handleClient(cli);
}
