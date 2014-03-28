//_______NETWORK_IDENTIFICATION_H_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class nNetworkIdentification
	{
	public:
		nNetworkIdentification( sf::IpAddress ipAddress, sf::Uint32 port );

		sf::IpAddress						getIpAddress()const;
		sf::Uint16							getPort()const;
		std::pair<sf::IpAddress, sf::Uint16>	toPair()const;
		std::string							toString()const;

		bool operator== (const nNetworkIdentification &toCompare)const;
		bool operator!= (const nNetworkIdentification &toCompare)const;

		nNetworkIdentification& operator= (nNetworkIdentification const& rhs);

	private:

		sf::IpAddress	m_ipAddress;
		sf::Uint16		m_port;
	};
};//kg