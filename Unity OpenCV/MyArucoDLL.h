#pragma once


#include <stdexcept>
#include <windows.h>
#include <iostream>


#ifdef MYARUCO_EXPORTS  
#define MYARUCO_EXPORTS_API __declspec(dllexport)   
#else  
#define MYARUCO_EXPORTS_API __declspec(dllimport)   
#endif  


namespace MYARUCO
{
	MYARUCO_EXPORTS_API void Initialize();
	MYARUCO_EXPORTS_API BYTE * MyAruco();
	//MYARUCO_EXPORTS_API void FreeMem();
	MYARUCO_EXPORTS_API void TheEnd();
}