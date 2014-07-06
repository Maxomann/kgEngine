//_______GUI_MANAGER_______//

#pragma once
#include "../stdafx.h"

namespace kg
{
	class NonStaticGuiElement
	{
		bool m_shouldClose = false;
		
	protected:
		void close()
		{
			m_shouldClose = true;
		};

	public:
		bool shouldClose()const
		{
			return m_shouldClose;
		}

		virtual void onClose( tgui::Gui& gui ) = 0;
	};
}
