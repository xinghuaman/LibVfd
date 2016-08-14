#ifndef VfdController_h
#define VfdController_h

#include <AbstractVFD.h>

#define GENERICBUFSIZE 20

const char global_noparse[] PROGMEM  = "Does not parse!";
const char global_unkfunc[] PROGMEM  = "Unknown Function!";
const char global_sevenseg[] PROGMEM = "SevenSegmentEncoder";
const char global_nodig[] PROGMEM    = "It's not a digit!";
const char global_unknerr[] PROGMEM  = "Unknown Error!";

class VfdController {
	private:
		void nocomprende(const char* const command, const char* const cause, 
			AbstractVFD* vfd);
		static char buffer[];
	public:
		void obey(char command[], AbstractVFD* vfd);
};

#endif
