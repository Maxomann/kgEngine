#pragma once

#ifndef SCRIPT_API_EX
	#define SCRIPT_API __declspec(dllexport)

#else
	#define SCRIPT_API __declspec(dllimport)

#endif