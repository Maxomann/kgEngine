//#include "../Gui/GuiManager.h"
//
//namespace kg
//{
//
//	GuiManager::GuiManager( sf::RenderWindow& window )
//	{
//		if( !m_gui.setGlobalFont( resourceFolderPath + "DejaVuSans.ttf" ) )
//			REPORT_ERROR_FILEACCESS( resourceFolderPath + "DejaVuSans.ttf" + "could not be loaded" );
//	}
//
//	void GuiManager::passEvent( sf::Event& sfmlEvent )
//	{
//		m_gui.handleEvent( sfmlEvent );
//	}
//
//	void GuiManager::drawToWindow()
//	{
//		m_gui.draw();
//	}
//
//}