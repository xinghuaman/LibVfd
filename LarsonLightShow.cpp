#include "LarsonLightShow.h"

void LarsonLightShow::setVfd(AnotherVFD* vfd) {
	_vfd = vfd;
}

void LarsonLightShow::begin() {
	_callback.addFunction(&_vfd->_threezero);
	_callback.addFunction(&_vfd->_s);
	_callback.addFunction(&_vfd->_v);
	_callback.addFunction(&_vfd->_cd);
	_callback.addFunction(&_vfd->_N);
	_callback.addFunction(&_vfd->_p);
	_callback.addFunction(&_vfd->_dvd);
	_callback.addFunction(&_vfd->_pbc);
	_callback.addFunction(&_vfd->_mp3);
	_scanner.begin(_callback.getNumFunctions(), 0, 3, &_callback);
}

void LarsonLightShow::enable(boolean enabled) {
	_enabled = enabled;
}

void LarsonLightShow::animate() {
	if (!_enabled) return;
	_scanner.cycle();
}
