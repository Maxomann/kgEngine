#pragma once

#ifndef A_STDAFX
#define A_STDAFX

#ifndef SCRIPT_API_EX
#define ALGORITHM_API __declspec(dllexport)

#else
#define ALGORITHM_API __declspec(dllimport)

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
#include <map>
#include <fstream>
#include <functional>

#include <SFML/Graphics.hpp>

#include<dirent.h>
//divide: struct dirent->d_type / DIRENT_CONST
//1=Folder
//2=File
#define DIRENT_CONST 16384

#endif //A_STDAFX