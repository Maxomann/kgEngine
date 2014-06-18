#include "../cCoreExtension.h"

namespace kg
{
	CORE_API bool cCore::shouldClose()
	{
		return m_shouldClose;
	}

	void cCore::frame()
	{
		networkManager.frame( *this );

		for( auto& el : m_extensions )
		{
			auto ptr = std::dynamic_pointer_cast< kg::cCoreExtension >(el.second);
			if( ptr )
			{
				ptr->frame( *this);
			}
		}
	}

	CORE_API void cCore::close()
	{
		m_shouldClose = true;
	}

	CORE_API void cCore::setServerIp( const sf::IpAddress& ip )
	{
		m_serverIp = ip;
	}

	CORE_API void cCore::setServerPort( const sf::Uint16& port )
	{
		m_serverPort = port;
	}

	CORE_API sf::IpAddress cCore::getServerIp() const
	{
		return m_serverIp;
	}

	CORE_API sf::Uint16 cCore::getServerPort() const
	{
		return m_serverPort;
	}

}