/* 
Author: George Linsdell
Date: 19/04/2022

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

@Author George Linsdell
@SPI Master Component.

Implemented Interfaces:

SCLK = 16/D13 = M_SCLK
MISO = 15/D12 = M_MISO
MOSI = 14/D11 = M_MOSI
M_SS1  = 12/D9  = M_SS1
M_SS2  = 11/D8  = M_SS2
*/


// inslude the SPI library:
#include <SPI.h>
#include "MCP_SPI_Master.h"

// Defin Static Pins described in comment header.
const int GLOBAL_SCLK = 13;
const int GLOBAL_MISO = 12;
const int GLOBAL_MOSI = 11;
const int GLOBAL_SS = 10;

const int M_SS1 = 9;
const int M_SS2 = 8;

//Where All SPI Devices may be treated the same, we can use static SPI configuration options.
const int SPI_SPEED_MAXIMUM = 20000000; //20 MHz
const int SPI_DATA_ORDER = MSBFIRST; //or LSBFIRST 
const int SPI_DATA_MODE = SPI_MODE0; //https://www.arduino.cc/en/reference/SPI

String response = "";
String inputString = "";         // a string to hold incoming data
boolean stringComplete;  // whether the string is complete
int iCommandLength ;



MCP_SPI_Master SPIController = MCP_SPI_Master();

void setup() {
  // set the slaveSelectPin as an output:
  SPISettings MySettings = SPISettings(SPI_SPEED_MAXIMUM,SPI_DATA_ORDER,SPI_DATA_MODE);
  Serial.begin(115200);
  inputString.reserve(32);
  
  pinMode(GLOBAL_MISO, OUTPUT);
  pinMode(GLOBAL_MOSI, OUTPUT);
  pinMode(M_SS1, OUTPUT);
  pinMode(M_SS2, OUTPUT);

  SPIController.Setup(MySettings);
  // initialize SPI:
  SPI.begin();
}

void loop() {
  //Interruptable Read Loop 
  
  if (stringComplete) {
      response =  ParseString() ;
      if (response.length() > 4) {
          String response = "ERROR!!"; //if a value longer than 32 is returned by the ParseString Function, we return an error to the client.
      }
      else {
          while (response.length() < 31){
            response = response + "z";
          }
      }
      inputString = "";
      stringComplete = false;
      Serial.println(response+"\n"); //Carriage return added here
      
  }
  else{
    ServiceActions();
  }
}

String ProcessSPICommand(String SPI_Message){
  Serial.println("Processing SPI command");
  return SPIController.SPIWriteRead(SPI_Message);
}

void ServiceActions(){
  ////Implement Service Actions Here.
  delay(1);
}

String ParseString(){
  if (inputString.substring(0,4) == "TEST"){
    response = ProcessSPICommand("GET_ID");
    Serial.println("SPI Processed");
    Serial.println(response);
    return response;
  }
  else if (inputString.substring(0,4) == "READ"){
    Serial.println("MOSI = " + String(GLOBAL_MOSI));
    Serial.println("MISO = " + String(GLOBAL_MISO));
    Serial.println("SlaveSelect = " + String(SPIController.SS));
    response = "readdone";
    return response;
  
  }
  else{
    return "NO_OP";
  }
}

void serialEvent() { //Serial Event Captures recieved serial commands
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    //if (SERIALDEBUG) {
    //  Serial.println(inputString);
    //}
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
     //Serial.print ("nl"); //Debug
      //digitalWrite(LED,LOW);
      delay(10);
      //digitalWrite(LED,HIGH);
      stringComplete = true;
    }
    else if (inChar == '\xfa') {
      //Serial.print ("CR"); //Debug
      //digitalWrite(LED,LOW);
      delay(15);
      //digitalWrite(LED,HIGH);
      stringComplete = true;
      }
  }

}
