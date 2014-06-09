#pragma once

#ifndef PLUGIN_API_EX
#define PLUGIN_API __declspec(dllexport)

#else
#define PLUGIN_API __declspec(dllimport)

#endif