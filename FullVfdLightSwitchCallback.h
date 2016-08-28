#ifndef FullVfdLightSwitchCallback_h
#define FullVfdLightSwitchCallback_h

#include <LightSwitchCallback.h>
#include <AnimatableFunction.h>
#include <AbstractVFD.h>

class FullVfdLightSwitchCallback : public LightSwitchCallback {
	private:
		AbstractVFD* _vfd;

	public:
		void begin(AbstractVFD* vfd);
		virtual void setLamp(int num, int state);
		int getNumFunctions();
		
};

#endif

