#pragma once

#ifndef N_STDAFX
#define N_STDAFX


#ifndef NETWORK_API_EX
#define NETWORK_API __declspec(dllexport)

#else
#define NETWORK_API __declspec(dllimport)

#endif


#include <Algorithm/aContainer.h>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <SFML/Network.hpp>
#include <Plugin/pExtendable.h>


#endif //N_STDAFX