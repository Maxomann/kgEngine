//_______CLIENT_______//

#pragma once
#include "stdafx.h"
#include "MessageHandlers.h"
#include "ConfiguratedTexture.h"
#include "ResourceManagement.h"

namespace kg
{
	class Client : public cCoreExtension
	{
		sf::RenderWindow m_window;
		ResourceManagement m_resourceManagement;

		aDataByIdentifierFile m_config_file;

		sf::Sprite m_sprite;

	public:
		Client();

		void frame( cCore& core, nNetworkManager& networkManger );

		virtual std::string info() const;

		static const char config_file_path[];
	};
}
