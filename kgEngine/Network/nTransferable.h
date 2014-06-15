//_______TRANFERABLE_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	//Tranferable over the network
	class nNetworkSendable
	{
	public:
		virtual std::string toString()const=0;
	};

	class nNetworkConstructable
	{
	public:
		virtual void fromString( const std::string& data ) = 0;
	};

}