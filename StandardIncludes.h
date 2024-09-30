#ifndef STANDARDINCLUDES_H
#define STANDARDINCLUDES_H

//include standard headers
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cinttypes>
#include <stdio.h>
#include <thread>
#include <map>

//project headers
#include "Singleton.h"

//OS Specific includes and defines 
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); }
#define GetCurrentDir _getcwd
#else 
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
using namespace std;

#endif // !1
