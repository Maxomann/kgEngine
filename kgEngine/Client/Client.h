//_______CLIENT_______//

#pragma once
#include "stdafx.h"
#include "Network/Messages.h"
#include "World/World.h"
#include "Drawing/Animation.h"
#include "GUI/GuiManager.h"

namespace kg
{
	class Client : public cCoreExtension
	{
		sf::RenderWindow m_window;

		GuiManager m_guiManager;
		Camera m_camera;
		World m_world;

		aDataByIdentifierFile m_config_file;

	public:
		Client( pPluginManager& pluginManger );

		World& getWorld();

		void frame( cCore& core );

		virtual std::string info() const;

		static const char config_file_path[];
	};
}
