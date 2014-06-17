//_______CORE_______//

#pragma once
#include "stdafx.h"
#include "cResourceManagement.h"

namespace kg
{
	class cCore : public pExtendable
	{
		bool m_shouldClose = false;

	public:
		void frame();

		CORE_API bool shouldClose();
		CORE_API void close();


		nNetworkManager networkManager;
		cResourceManagement resourceManagement;
	};
}
