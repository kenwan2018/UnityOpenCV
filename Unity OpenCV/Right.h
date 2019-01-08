#pragma once


#include <stdexcept>
#include <windows.h>
#include <iostream>


#ifdef RIGHT_EXPORTS  
#define RIGHT_EXPORTS_API __declspec(dllexport)   
#else  
#define RIGHT_EXPORTS_API __declspec(dllimport)   
#endif  


namespace RIGHT
{
	RIGHT_EXPORTS_API void InitializeR();
	//MYARUCO_EXPORTS_API BYTE * MyAruco();
	RIGHT_EXPORTS_API BYTE * MyArucoR();
	//MYARUCO_EXPORTS_API void FreeMem();
	RIGHT_EXPORTS_API void TheEndR();
}