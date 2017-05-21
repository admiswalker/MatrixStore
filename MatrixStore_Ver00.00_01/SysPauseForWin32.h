#pragma once

#ifdef _WIN32
	#include <windows.h>							//system("pause");用			
	#define SysPauseForWin32() system("pause")	//system("pause > NUL");
#else
	#define SysPauseForWin32() //空白を割り当てる．
#endif

// How to use this
//
// SysPauseForWin32();