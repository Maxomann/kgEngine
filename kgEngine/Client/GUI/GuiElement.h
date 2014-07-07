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

		virtual void onClose( tgui::Gui& gui ) = 0;

		virtual void onInit( cCore& core, tgui::Gui& gui ) = 0;
	};
}
