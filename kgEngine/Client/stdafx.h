//_______STDAFX_H_______//

#pragma once

#ifndef C_STDAFX
#define C_STDAFX

#ifndef CLIENT_API_EX
#define CLIENT_API __declspec(dllexport)

#else
#define CLIENT_API __declspec(dllimport)
#endif

#include <Plugin/pPluginManager.h>
#include <Core/cCoreExtension.h>
#include <Core/cCore.h>
#include <Algorithm/aFile.h>
#include <Algorithm/aString.h>
#include <Algorithm/aCallbacks.h>
#include <Core/SharedData.h>
#include <Network/nNetworkManger.h>

#include <array>
#include <locale>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/system.hpp>

#include <TGUI/TGUI.hpp>

#endif