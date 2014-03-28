//_______NETWORK_IDENTIFICATION_CPP_______//

#pragma once
#include "nNetworkIdentification.h"

namespace kg
{
	nNetworkIdentification::nNetworkIdentification( sf::IpAddress ipAddress, sf::Uint32 port ) :
		m_ipAddress( ipAddress ),
		m_port( port )
	{ };

	sf::IpAddress nNetworkIdentification::getIpAddress()const
	{
		return m_ipAddress;
	};

	sf::Uint16 nNetworkIdentification::getPort()const
	{
		return m_port;
	};

	bool nNetworkIdentification::operator== (const nNetworkIdentification &toCompare)const
	{
		if( this->m_ipAddress == toCompare.getIpAddress() )
			if( this->m_port == toCompare.getPort() )
				return true;

		return false;
	};

	bool nNetworkIdentification::operator!= (const nNetworkIdentification &toCompare)const
	{
		if( !operator==(toCompare) )
			return true;
		else return false;
	};

	nNetworkIdentification& nNetworkIdentification::operator= (nNetworkIdentification const& rhs)
	{
		if( this != &rhs )
		{
			this->m_ipAddress = rhs.m_ipAddress;
			this->m_port = rhs.m_port;
		}
		return *this;
	};
	std::pair<sf::IpAddress, sf::Uint16> nNetworkIdentification::toPair()const
	{
		return std::make_pair( m_ipAddress, m_port );
	}

	std::string nNetworkIdentification::toString()const
	{
#pragma message("warning: NetworkIdentification::toString() uses sf::Ipaddress::toInteger() because Ipaddress::toString() causes debug assertion failure")
		return std::to_string( m_ipAddress.toInteger() ) + "-" + std::to_string( m_port );
	};
};//kg