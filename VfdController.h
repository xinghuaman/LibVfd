#ifndef VfdController_h
#define VfdController_h

#include <AbstractVFD.h>

#define GENERICBUFSIZE 20

class VfdController {
	private:
		void nocomprende(const char* const command, const char* const cause, 
			AbstractVFD* vfd);
		static char buffer[];
	public:
		void obey(char command[], AbstractVFD* vfd);
};

#endif
