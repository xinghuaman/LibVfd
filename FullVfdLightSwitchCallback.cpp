#include <FullVfdLightSwitchCallback.h>

void FullVfdLightSwitchCallback::begin(AbstractVFD* vfd) {
	_vfd = vfd;
}

void FullVfdLightSwitchCallback::setLamp(int num, int state) {
	AnimatableFunction** funcs = _vfd->getFunctions();
	const int limit = _vfd->getNumFunctions();
	int count=0;
	int count1=-1;
	while ( (count1 < num) && (count < limit)) {
		if (funcs[count]->getRawType() == 0) {
			count1++;
		}
		count++;
	}
	if (count1!=num) return; // Is an Errorcondition, but I can't use exceptions.

	funcs[count]->setEnabled(state == LightSwitchCallback::ON ? true : false);
}

int FullVfdLightSwitchCallback::getNumFunctions() {
	int count = 0;
	AnimatableFunction** funcs = _vfd->getFunctions();
	const int limit = _vfd->getNumFunctions();
	for (int i=0; i<limit;i++) 
		if (funcs[i]->getRawType() == 0) 
			count++;
	return count;
}

