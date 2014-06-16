#pragma once

#ifndef CORE_STDAFX
#define CORE_STDAFX

#ifndef CORE_API_EX
#define CORE_API __declspec(dllexport)

#else
#define CORE_API __declspec(dllimport)

#endif

#include <Network/nNetworkManger.h>
#include <Plugin/pPluginManager.h>

#endif
