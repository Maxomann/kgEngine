#include "../Gui/GuiManager.h"

namespace kg
{


	GuiManager::GuiManager( sf::RenderWindow& window )
	{
		m_gui.setGlobalFont( resourceFolderPath + "DejaVuSans.ttf" );
	}

	void GuiManager::passEvent( sf::Event& sfmlEvent )
	{
		m_gui.handleEvent( sfmlEvent );
	}

	void GuiManager::drawToWindow()
	{
		m_gui.draw();
	}

}
