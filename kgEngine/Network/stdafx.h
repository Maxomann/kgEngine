#pragma once

#ifndef NETWORK_API_EX
#define NETWORK_API __declspec(dllexport)

#else
#define NETWORK_API __declspec(dllimport)

#endif