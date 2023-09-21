#pragma once

#ifdef  FRG_PLATFORM_WINDOWS
	#ifdef FRG_BUILD_DLL
		#define FRAGMENT_API __declspec(dllexport)
	#else
		#define FRAGMENT_API __declspec(dllimport)
	#endif
#else
	#error Fragment only supports Windows
#endif

#define BIT(x) (1 << x)