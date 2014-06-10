#include "../cCoreExtension.h"

namespace kg
{
	bool cCore::shouldClose()
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
				ptr->frame( networkManger, *this );
			}
		}
	}

	void cCore::close()
	{
		m_shouldClose = true;
	}
}