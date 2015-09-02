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
  
  /*
vector<string> MsgHandler::explode(const string& str, const char& ch) {
    string next;
    vector<string> result;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}  
  */
  
void MsgHandler::hanldeHandshakeClock(String message) {
  int h = (getValue(message, ';', 0)).toInt();
  int mi = getValue(message, ';', 1).toInt();
  int sec = getValue(message, ';', 2).toInt();
  int da = getValue(message, ';', 3).toInt();
  int mo = getValue(message, ';', 4).toInt();
  int ye = getValue(message, ';', 5).toInt();

  
  //set time
  setTime(h,mi,sec,da,mo,ye);
}
  
String MsgHandler::getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
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

