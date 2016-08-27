#ifndef AnimatableLightSwitchCallback_h
#define AnimatableLightSwitchCallback_h

#include <LightSwitchCallback.h>
#include <AnimatableFunction.h>

#define AnimatableLightSwitchCallbackNumFuncs 20

class AnimatableLightSwitchCallback : public LightSwitchCallback {
	private:
		AnimatableFunction* _functions[AnimatableLightSwitchCallbackNumFuncs];
		int _numFunctions;

	public:
		void addFunction(AnimatableFunction* function);
		virtual void setLamp(int num, int state);
		int getNumFunctions();
		
};

#endif

