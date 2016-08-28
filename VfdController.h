#ifndef VfdController_h
#define VfdController_h

#include <AbstractVFD.h>
#include <CountingLightShow.h>
#include <LarsonScanner.h>
#include <FullVfdLightSwitchCallback.h>


class VfdController {
	private:
		AbstractVFD* _vfd;
		void nocomprende(const char* const command, const char* const cause);
		bool _isLightShowEnabled;
		CountingLightShow _show;
		LarsonScanner _scanner;
		FullVfdLightSwitchCallback _callback;


	public:
		void obey(char command[]);
		void enableLightShow(bool enabled);
		void animate();
		void begin(AbstractVFD* vfd);
};

#endif
