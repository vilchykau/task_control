#include "platform.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void platform_sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#endif
}
