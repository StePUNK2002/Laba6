#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define TURN_API __declspec(dllexport)
#else
#define TURN_API __declspec(dllimport)
#endif

#include "windows.h"
class Turn
{
private:
	int size;
	HANDLE heaphandle;
	int* mass;
public:
	TURN_API Turn();
	TURN_API Turn(const Turn& turn);
	TURN_API void EjectionElemet();
	TURN_API int GetFirstEl();
	TURN_API int GetSize();
	TURN_API void WriteToFile();
	TURN_API Turn ReadFromFile();
	TURN_API void Push(int value);
	TURN_API ~Turn(); 
};