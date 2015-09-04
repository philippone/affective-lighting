#include "Model.h"


int Model::getMaxBrightness() {
  return maxBrightness;  
}


/**Clock Mode stuff begin**/
byte Model::getClockDesign() {
  return clockDesign;
}

/**Clock Mode stuff end**/




///// DEBUG ///////

boolean Model::isInDebug() {
  return debugMode;  
}


/**Debug Mode stuff begin**/

float Model::getDebugTmp() {
  return debug_tmp;
}


/**Debug Mode stuff end **/

