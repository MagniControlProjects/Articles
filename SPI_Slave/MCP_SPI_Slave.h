/* 
Author: George Linsdell
Date: 19/04/2022  
MCP SPI Slave Module
Copyright 2022 George Linsdell

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MCP_SPI_Slave_h
#define MCP_SPI_Slave_h

#include "Arduino.h"
#include <SPI.h>

class MCP_SPI_Slave {
  public:
    MCP_SPI_Slave();
    void Setup(
      SPISettings MySettings
      );
    void Setup(
      SPISettings MySettings,
      String StartString,
      String TerminationString,
      int Timeout
      );
    String SPIRead(
      );
    SPISettings MySettings;
    void SPIWrite(
      String  Message
      );
    String State;
    String Idle = "IDLE";
    String Processing = "PROCESSING";
    int StateTransitionTime;
    int Timeout;
  private:
    //Define Hardware Connections
    void ChangeState(
      String NewState
      );
    int CurrentStateTime(); 
    int SS;
    int MOSI;
    int MISO;
    String _StartString;
    String _TerminationString;
    String MessageIn;
    String MessageOut;
    String ReadBuffer;
    String WriteBuffer;

    //Memory Allocation for state report structure.
    String Message;
};

#endif
