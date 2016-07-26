#include "SingleFunctionCommandParser.h"

void SingleFunctionCommandParser::begin(SingleFunction* singleFunction) {
  _myFunction = singleFunction;
}

boolean SingleFunctionCommandParser::tryObey(String command){
  String _memonic = _myFunction->getMemonic();
  Serial.println(command.substring(0,_memonic.length()));
  if (_memonic.equals(command.substring(0,_memonic.length()))) {
    String wantsOnOrOff = command.substring(_memonic.length()+1,_memonic.length()+2);
    Serial.println(wantsOnOrOff);
    if (wantsOnOrOff.equals("1")) {
      _myFunction->setEnabled(true);
    } else if (wantsOnOrOff.equals("b")) {
      _myFunction->setBlink();
    } else {
      _myFunction->setEnabled(false);
    }
    return true;
  }
  return false;
};

