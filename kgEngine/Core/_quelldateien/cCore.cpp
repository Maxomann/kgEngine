#include "../cCoreExtension.h"

namespace kg
{
	CORE_API bool cCore::shouldClose()
	{
		return m_shouldClose;
	}

	void cCore::frame( nNetworkManager& networkManger )
	{
		for( auto& el : m_extensions )
		{
			auto ptr = std::dynamic_pointer_cast< kg::cCoreExtension >(el.second);
			if( ptr )
			{
				ptr->frame( *this, networkManger );
			}
		}
	}

	CORE_API void cCore::close()
	{
		m_shouldClose = true;
	}
}