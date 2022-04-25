/* 
Author: George Linsdell
Date: 19/04/2022
MCP SPI Slave Module
Copyright 2022 George Linsdell

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Arduino.h"
#include <SPI.h>
#include "MCP_SPI_Slave.h"

//Instanciation method of class
MCP_SPI_Slave::MCP_SPI_Slave(){
}

void MCP_SPI_Slave::Setup(
      SPISettings MySettings
    ){
    MySettings = MySettings;
    _StartString = "8xx5";
    _TerminationString = "x85x";
    Timeout = 1000;
    MISO = 12;
    MOSI = 11;
    SS = 10;
    SPI.begin;
}

void MCP_SPI_Slave::Setup(
      SPISettings MySettings,
      String StartString = "8xx5",
      String TerminationString = "x85x",
      int Timeout = 1000 //Transactions should complete within a second else something went horribly wrong.
    ){
    MySettings = MySettings;
    State = Idle;
    _StartString = StartString;
    _TerminationString = TerminationString;
    MISO = 12;
    MOSI = 11;
    SS = 10;
    SPI.begin;
}

void MCP_SPI_Slave::ChangeState(String NewState){
  // Single Method to change the State as String.
  // TODO: Setter methods for each state / Swap for actual State Machine.
  State = NewState;
  StateTransitionTime = millis();
}

int MCP_SPI_Slave::CurrentStateTime(){
  // Returns the time since last state change in milliseconds.
  return millis() - StateTransitionTime;
}

String MCP_SPI_Slave::SPIRead () {
  //  send in the address and value via SPI:
    ChangeState(Processing);
    while (State == Processing){
      
      ReadBuffer = SPI.transfer16(0);
      //TODO Continue implementing the READ and Write logic for SPI Events.
      delay(100);
      // take the SS pin high to de-select the chip:
    }
    ChangeState(Idle);
    return ReadBuffer;
}

void MCP_SPI_Slave::SPIWrite (String Message) {
  //  send in the address and value via SPI:
    ChangeState(Processing);
    while (State == Processing){
      for (int i = 0; i <= Message.length(); i++) {
        ReadBuffer = SPI.transfer(byte(Message[i]));  
      }
      
      //TODO Continue implementing the READ and Write logic for SPI Events.
      delay(100);
      // take the SS pin high to de-select the chip:
    }
    ChangeState(Idle);
    return ReadBuffer;
}
