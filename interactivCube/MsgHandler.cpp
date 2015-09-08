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
void MsgHandler::checkInput() {


  while (serial->available() > 0) {

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

  if (message.startsWith("c;")) {
    sendConnectionHandshake();

  } else if (message.startsWith("hc;")) {
    hanldeHandshakeClock(message.substring(3));

    // clock mode design
  } else if (message.startsWith("cm_d;")) {
    handleClockDesign(message.substring(5));

    // temperature mode color 1
  } else if (message.startsWith("nlm_c1;")) {
    handleNightLightPrimColor(message.substring(7));
  }

  // presence mode person is present
  else if (message.startsWith("pm_p;")) {
    handlePresencePresent(message.substring(5));
  }

  // presence mode person is absent
  else if (message.startsWith("pm_a;")) {
    handlePresencePresent(message.substring(5));
  }
}

void MsgHandler::hanldeHandshakeClock(String message) {
  int h = getValue(message, ';', 0).toInt();
  int mi = getValue(message, ';', 1).toInt();
  int sec = getValue(message, ';', 2).toInt();
  int da = getValue(message, ';', 3).toInt();
  int mo = getValue(message, ';', 4).toInt();
  int ye = getValue(message, ';', 5).toInt();


  //set time
  setTime(h, mi, sec, da, mo, ye);
}

/**
* set incomming primary color in model
* message: "nlm_c1;r;g;b";
* input "r;g;b;"
*/
void MsgHandler::handleNightLightPrimColor(String message) {
  int r = getValue(message, ';', 0).toInt();
  int g = getValue(message, ';', 1).toInt();
  int b = getValue(message, ';', 2).toInt();

  model->setNightLightColor(Color(r, g, b));

}

/**
* receive clockdesign change
* message: "cm_d;x; (x: 0-4)
* input: "x;"
**/
void MsgHandler::handleClockDesign(String message) {
  int mode = getValue(message, ';', 0).toInt();
  model->setClockDesign(mode + 1);
}

/**
* receive person with id is present
* message: "pm_p;id;r;g;b
* input: id;r;g;b
*/
void MsgHandler::handlePresencePresent(String message) {
  long id = getValue(message, ';', 0).toInt(); // hope it works 
  int r = getValue(message, ';', 1).toInt();
  int g = getValue(message, ';', 2).toInt();
  int b = getValue(message, ';', 3).toInt();

  // TODO add person to model
}


/**
* receive person with id is absent
* message: "pm_p;id;
* input: id;
*/
void MsgHandler::handlePresentAbsent(String message) {
   
   long id = getValue(message, ';', 0).toInt(); // hope it works 

  // todo remove person from model 
}



String MsgHandler::getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}







void MsgHandler::sendConnectionHandshake() {
  sendMsg("c;arduino_started");
}


void MsgHandler::sendMsg(String msg) {
  serial->println(msg);

  debug->print("msg go out: ");
  debug->println(msg);

}


void MsgHandler::debugMsg(String msg) {
  serial->println("d;" + msg);
}


Stream* MsgHandler::getSerial() {
  return serial;
}

