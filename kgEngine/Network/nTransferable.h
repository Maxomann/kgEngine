//_______TRANFERABLE_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class cResourceManagement;

	//Tranferable over the network
	class nNetworkSendable
	{
	public:
		virtual std::string nToString()const = 0;
	};

	class nNetworkConstructable
	{
	public:
		virtual void nFromString( cCore& resourceManagement, const std::string& data ) = 0;
	};
}