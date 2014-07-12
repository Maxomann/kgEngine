//_______GUI_MANAGER_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	class NonStaticGuiElement
	{
		bool m_shouldClose = false;

	public:
		void close()
		{
			m_shouldClose = true;
		};

		bool shouldClose()const
		{
			return m_shouldClose;
		}

		virtual void onClose( tgui::Container& container ) = 0;

		virtual void onInit( cCore& core, tgui::Container& container ) = 0;
	};

	template < class EXTENDED_TYPE, class SUB_WINDOW_TYPE >
	class ExtendableNonStaticGuiElement : public NonStaticGuiElement, public pExtendable
	{
	protected:
		std::map< std::string, std::shared_ptr<pGenericProviderInterface<SUB_WINDOW_TYPE>>> m_subWindows;
		std::shared_ptr<SUB_WINDOW_TYPE> m_activeSubWindow = nullptr;

	public:
		//NonStaticGuiElement
		virtual void onClose( tgui::Container& container ) = 0;
		virtual void onInit( cCore& core, tgui::Container& container ) = 0;

		virtual void initExtensions( pPluginManager& pluginManager )
		{
			pluginManager.fillExtandable<EXTENDED_TYPE>( *this );

			for( const auto& el : m_extensions )
			{
				auto ptr = std::dynamic_pointer_cast< pGenericProviderInterface<SUB_WINDOW_TYPE> >(el.second);
				if( ptr )
					m_subWindows[ptr->info()] = ptr;
			}
		}

		//static std::string info() has to be implemented in deriving class!
	};
}
