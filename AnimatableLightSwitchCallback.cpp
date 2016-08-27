#include <AnimatableLightSwitchCallback.h>

void AnimatableLightSwitchCallback::addFunction(AnimatableFunction *function) {
	if (_numFunctions >= AnimatableLightSwitchCallbackNumFuncs -1) return;
	_functions[_numFunctions++]=function;
}

void AnimatableLightSwitchCallback::setLamp(int num, int state) {
	_functions[num]->setEnabled(state == LightSwitchCallback::ON ? true : false);
}

int AnimatableLightSwitchCallback::getNumFunctions() {
	return _numFunctions;
}

