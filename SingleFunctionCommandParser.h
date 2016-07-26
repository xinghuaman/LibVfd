#ifndef SingleFunctionCommandParser_h
#define SingleFunctionCommandParser_h

#include "SingleFunction.h"

class SingleFunctionCommandParser {
  private:
    SingleFunction* _myFunction;
  public:
    void begin(SingleFunction* function);
    boolean tryObey(String command);
};
#endif
