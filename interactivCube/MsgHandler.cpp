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
  
  
  /**
 * handle incomming messages
 */
void MsgHandler::handle(String message) {
  debug->print("incomming message: ");
  debug->println(message);
  
  sendMsg(message);
}


void MsgHandler::sendMsg(String msg) {
  serial->println(msg);
  
  debug->print("msg go out: ");
  debug->println(msg);
  
}

