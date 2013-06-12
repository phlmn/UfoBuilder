#include "Starter.h"
 
int main()
{
	// hide console in release mode
	#ifndef _DEBUG
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	#endif

	Starter starter;	
	starter.run();

	return 0;
}
