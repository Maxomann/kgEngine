//_______CLIENT_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class Client : public cCoreExtension
	{
	public:

		virtual void frame( cCore& core, nNetworkManager& networkManger )
		{
			std::cout << "Client works" << std::endl;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
				core.close();
		}

		virtual std::string info() const
		{
			return "Build in CLIENT plugin";
		}

	};
}
