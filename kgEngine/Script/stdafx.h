//_______STDAFX_H_______//

#pragma once

#ifndef KS_STDAFX
#define KS_STDAFX

#include<iostream>

#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<string>

#include<memory>
#include<thread>
#include<mutex>
#include<fstream>
#include<functional>
#include<memory.h>
#include<cassert>
#include<cctype>
#include <Algorithm/aException.h>
//#include<dirent.h>
//divide: struct dirent->d_type / DIRENT_CONST
//1=Folder
//2=File
#define DIRENT_CONST 16384

#include<cmath>

//To identify classes loaded over dll's
#define ABSTRACT

//To identify classes loaded over factory files
#define FACTORY

#endif //KS_STDAFX