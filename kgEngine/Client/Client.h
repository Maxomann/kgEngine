//_______CLIENT_______//

#pragma once
#include "stdafx.h"
#include "Network/Messages.h"
#include "World/World.h"
#include "Drawing/Animation.h"

namespace kg
{
	class Client : public cCoreExtension
	{
		sf::RenderWindow m_window;

		Camera m_camera;
		World m_world;

		aDataByIdentifierFile m_config_file;

	public:
		Client();

		World& getWorld();

		void frame( cCore& core );

		virtual std::string info() const;

		static const char config_file_path[];
	};
}
