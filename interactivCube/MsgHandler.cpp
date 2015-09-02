#include "MsgHandler.h"


MsgHandler::MsgHandler(Model* m) {
  model = m;
}


void MsgHandler::addDebugStream(Stream* debugStream) {
  debug = debugStream;
  debug->println("add debugStream");
}

void MsgHandler::init(Stream* s) {
  serial = s;
}

String message;
void MsgHandler::checkInput(){
  
  
  while(serial->available() > 0) {
    
    char msg = serial->read();
    
    if (msg == '*' || msg == '\n') {
      message += "\n";
	  
      // send to usb 
      //Serial.print("inc: ");
      //Serial.print(message);
	  
      // send back to phone (test only)
      //Serial1.print("all: ");
      //Serial1.println(message);
	  
      handle(message);

      // reset Message
      message = "";
    } 
    else {
      message += msg  ;
      //Serial.print("r: ");
      //Serial.println(msg);
    }
  }
}
  
  
void MsgHandler::hanldeHandshakeClock(String message) {
  char *cstr = new char[message.length() + 1];
  strcpy(cstr, message.c_str());
  char * pch;
  pch = strtok(cstr, ";");
  
  while (pch != NULL)
  {
    debug->println(pch);
  }
  
  
  
  // set time in model
  //setTime(h,mi,19,2,9,15);
}
  
  
  /**
 * handle incomming messages
 */
void MsgHandler::handle(String message) {
  debug->print("incomming message: ");
  debug->println(message);
  
  if (message.startsWith("c;")) {
    sendConnectionHandshake();
  } else if (message.startsWith("hc;")) {
    hanldeHandshakeClock(message.substring(3));
  }
}



void MsgHandler::sendConnectionHandshake() {
  sendMsg("c;arduino_started");
}


void MsgHandler::sendMsg(String msg) {
  serial->println(msg);
  
  debug->print("msg go out: ");
  debug->println(msg);
  
}

