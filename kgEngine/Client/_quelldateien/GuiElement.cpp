#include "../GUI/GuiElement.h"

namespace kg
{


	void NonStaticGuiElement::close()
	{
		m_shouldClose = true;
	}

	bool NonStaticGuiElement::shouldClose() const
	{
		return m_shouldClose;
	}

}
