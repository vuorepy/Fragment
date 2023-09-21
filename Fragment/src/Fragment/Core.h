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

#ifdef HZ_ENABLE_ASSERTS
	#define FRG_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FRG_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FRG_ASSERT(x, ...)
	#define FRG_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)