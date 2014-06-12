#pragma once

#ifndef A_STDAFX
#define A_STDAFX


#ifndef SCRIPT_API_EX
#define SCRIPT_API __declspec(dllexport)

#else
#define SCRIPT_API __declspec(dllimport)

#endif


#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <string>
#include <memory>
#include <queue>
#include <mutex>
#include <exception>


#endif //A_STDAFX