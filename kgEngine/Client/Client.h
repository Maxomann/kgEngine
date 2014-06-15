//_______CLIENT_______//

#pragma once
#include "stdafx.h"
#include "MessageHandlers.h"

namespace kg
{
	class Client : public cCoreExtension
	{
		sf::RenderWindow m_window;

		aDataByIdentifierFile m_config_file;

		bool send = true;

	public:
		Client();

		void frame( cCore& core, nNetworkManager& networkManger );

		virtual std::string info() const;

		static const char config_file_path[];
	};
}
