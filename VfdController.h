#ifndef VfdController_h
#define VfdController_h

#include <AbstractVFD.h>
#include <LarsonLightShowBuilder.h>
#include <CountingLightShow.h>

#define VFDCONTROLLER_BUFFSIZE 20

class VfdController {
	private:
		AbstractVFD* _vfd;
		void nocomprende(const char* const command, const char* const cause);
		LarsonLightShowBuilder _builder;
		int compairType(AnimatableFunction* func, const char compairTo[]);
		bool _isLightShowEnabled;
		CountingLightShow _show;

	public:
		void obey(char command[]);
		void enableLightShow(bool enabled);
		void animate();
		void begin(AbstractVFD* vfd);
		VfdController* add2Show(SingleFunction* singleFunction);
};

#endif
