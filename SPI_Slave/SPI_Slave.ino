/* 
Author: George Linsdell
Date: 19/04/2022
@Author George Linsdell
@SPI Slave Component.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Implemented Interfaces:

Slave 1 - Arduino Nano
SCLK = 16/D13 = S1_SCLK => M_SCLK
MISO = 15/D12 = S1_MISO => M_MISO
MOSI = 14/D11 = S1_MOSI => M_MOSI
SS   = 13/D10 = S1_SS   => M_SS1
*/

// inslude the SPI library:
#include <SPI.h>
#include "MCP_SPI_Slave.h"

const String Version = "0.0.0.1";

// Defin Static Pins described in comment header.
const int GLOBAL_SCLK = 13;
const int GLOBAL_MISO = 12;
const int GLOBAL_MOSI = 11;
const int GLOBAL_SS = 10;

//PC => Serial interface
String response = "";
String command = "";         // a string to hold incoming data
boolean stringComplete;  // whether the string is complete
int iCommandLength ;

//Where All SPI Devices may be treated the same, we can use static SPI configuration options.
const uint32_t SPI_SPEED_MAXIMUM = 20000000; //20 MHz
const int SPI_DATA_ORDER = MSBFIRST; //or LSBFIRST 
const int SPI_DATA_MODE = SPI_MODE0; //https://www.arduino.cc/en/reference/SPI

String CommandBuffer [32]; //Support storing of 32 EventActions from SPI Master.

MCP_SPI_Slave SPIController = MCP_SPI_Slave();

void setup() {
  // set the slaveSelectPin as an output:
  Serial.begin(115200);
  SPISettings MySettings = SPISettings(SPI_SPEED_MAXIMUM,SPI_DATA_ORDER,SPI_DATA_MODE);
  SPIController.Setup(MySettings);
  stringComplete = false;
  attachInterrupt(digitalPinToInterrupt(SS),voidProcessSPICommand,LOW);
}

void voidProcessSPICommand(){
  command = SPIController.SPIRead();
  Serial.println("SPI Received");
  if (command == "GET_ID"){
        SPIController.SPIWrite(Version);
  }
  else {
    SPIController.SPIWrite("NO_OP");
  }
}

String ProcessSPICommand(){
  Serial.println("SPI Processing");
  command = SPIController.SPIRead();
  if (command == "GET_ID"){
        SPIController.SPIWrite(Version);
  }
  return "Complete";
}

void loop() {
    ServiceActions();
}

void ServiceActions(){
  delay (1);
}
