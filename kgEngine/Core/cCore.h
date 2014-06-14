//_______CORE_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class cCore : public pExtendable
	{
		bool m_shouldClose = false;

	public:
		void frame( nNetworkManager& networkManger );

		CORE_API bool shouldClose();
		CORE_API void close();
	};
}