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
#include "MCP_SPI_Master.h"

//Instanciation method of class
MCP_SPI_Master::MCP_SPI_Master(){
}

void MCP_SPI_Master::Setup(SPISettings mySettings){
    mySettings = mySettings;
    MISO = 12;
    MOSI = 11;
    SS = 9;
    SPI.begin;
}

void MCP_SPI_Master::Setup(
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
    SS = 9;
    SPI.begin;
}


String MCP_SPI_Master::SPIWriteRead (String  SPI_Message) {
  // take the SS pin low to select the chip:
  SPI.beginTransaction(MySettings);
  digitalWrite(SS, HIGH);
  delay(100);
  //  send in the address and value via SPI:
  for (int i = 0 ; i <= SPI_Message.length(); i++){
    SPI.transfer(byte(SPI_Message[i]));
  }
  delay(100);
  ReadBuffer = SPI.transfer(0);
  // take the SS pin high to de-select the chip:
  digitalWrite(SS, LOW);
  return ReadBuffer;
}
