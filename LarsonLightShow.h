#ifndef LarsonLightShow_h
#define CoutingLightShow_h

#include <AnimatableLightSwitchCallback.h>
#include <AnotherVFD.h>
#include <LarsonScanner.h>
#include <Arduino.h>

class LarsonLightShow {
  private:
    AnotherVFD* _vfd;
    boolean _enabled;
    LarsonScanner _scanner;
    AnimatableLightSwitchCallback _callback;

  public:
    void setVfd(AnotherVFD* vfd);
    void begin();
    void animate();
    void enable(boolean enabled);


};

#endif
