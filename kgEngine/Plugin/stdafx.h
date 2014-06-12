#pragma once

#ifndef P_STDAFX
#define P_STDAFX

#ifndef PLUGIN_API_EX
#define PLUGIN_API __declspec(dllexport)

#else
#define PLUGIN_API __declspec(dllimport)

#endif

#ifdef _WIN32
#include<windows.h>
#endif // _WIN32
#include <unordered_map>
#include <memory>
#include <Algorithm/aException.h>
#include <string>
#include <tuple>

#endif //P_STDAFX