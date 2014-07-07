#include "../GUI/GuiElements.h"

namespace kg
{
	const std::string TileDrawingWindow::NO_BRUSH{ "NONE" };

	void ConnectToServerWindow::m_callback( const tgui::Callback& callback, cCore& core )
	{
		if( callback.widget == &*m_connectToServerWindow )
		{
			close();
		}
		if( callback.widget == &*m_ctsSendButton )
		{
			sf::IpAddress ip( sf::IpAddress( m_ctsIp->getText() ) );
			sf::Uint16 recievePortOnServer(
				std::atoi( m_ctsRecievePortOnServer->getText().toAnsiString().c_str() ) );
			sf::Uint16 recievePortOnClient(
				std::atoi( m_ctsRecievePortOnClient->getText().toAnsiString().c_str() ) );

			core.networkManager.clearConnections();

			core.networkManager.addConnection( ip, recievePortOnClient, recievePortOnServer );

			core.networkManager.sendMessage(
				std::make_shared<ConnectionRequest>( recievePortOnClient, recievePortOnServer ),
				ip,
				standartServerRecievePort );
		}
	}

	void ConnectToServerWindow::onClose( tgui::Gui& gui )
	{
		gui.remove( m_connectToServerWindow );

		//		not needed because objects are not registred in gui
		//		they are registred in m_connectToServerWindow
		// 		gui.remove( m_ctsIp );
		// 		gui.remove( m_ctsRecievePortOnServer );
		// 		gui.remove( m_ctsRecievePortOnClient );
		// 		gui.remove( m_ctsSendButton );
	}

	void ConnectToServerWindow::onInit( cCore& core, tgui::Gui& gui )
	{
		//ConnectToServerWindow
		m_connectToServerWindow = tgui::ChildWindow::Ptr( gui );
		m_connectToServerWindow->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_connectToServerWindow->setTitle( connectionMenuConnectItem );
		m_connectToServerWindow->setSize( 300, 200 );
		m_connectToServerWindow->keepInParent( true );
		m_connectToServerWindow->bindCallbackEx( std::bind(
			&ConnectToServerWindow::m_callback,
			this,
			std::placeholders::_1,
			std::ref( core ) ),
			tgui::ChildWindow::Closed );

		m_ctsIp = tgui::EditBox::Ptr( *m_connectToServerWindow );
		m_ctsIp->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_ctsRecievePortOnClient = tgui::EditBox::Ptr( *m_connectToServerWindow );
		m_ctsRecievePortOnClient->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_ctsRecievePortOnServer = tgui::EditBox::Ptr( *m_connectToServerWindow );
		m_ctsRecievePortOnServer->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_ctsSendButton = tgui::Button::Ptr( *m_connectToServerWindow );
		m_ctsSendButton->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );

		m_ctsIp->setText( sf::IpAddress::getPublicAddress().toString() );
		m_ctsIp->setSize( 300, 50 );

		m_ctsRecievePortOnClient->setText( "RecievePortOnClient" );
		m_ctsRecievePortOnClient->setSize( 300, 50 );
		m_ctsRecievePortOnClient->setPosition( 0, 50 );
		m_ctsRecievePortOnServer->setText( "RecievePortOnServer" );
		m_ctsRecievePortOnServer->setSize( 300, 50 );
		m_ctsRecievePortOnServer->setPosition( 0, 100 );

		m_ctsSendButton->setText( "Connect" );
		m_ctsSendButton->setPosition( 0, 150 );
		m_ctsSendButton->setSize( 300, 50 );
		m_ctsSendButton->bindCallbackEx( std::bind(
			&ConnectToServerWindow::m_callback,
			this,
			std::placeholders::_1,
			std::ref( core ) ),
			tgui::Button::LeftMouseClicked );
		//ConnectToServerWindow END
	}





	std::shared_ptr<Brush> TileDrawingWindow::getBrush()
	{
		if( m_subWindow )
			return m_subWindow->createBrush();
		else
			return nullptr;
	}

	void TileDrawingWindow::initExtensions( pPluginManager& pluginManager )
	{
		pluginManager.fillExtandable<TileDrawingWindow>( *this );

		for( const auto& el : m_extensions )
		{
			auto ptr = std::dynamic_pointer_cast< pGenericProviderInterface<TileDrawingOptionsWindow> >(el.second);
			if( ptr )
				m_subWindows[ptr->info()] = ptr;
		}
	}

	void TileDrawingWindow::onInit( cCore& core, tgui::Gui& gui )
	{
		m_tileDrawingWindow = tgui::ChildWindow::Ptr( gui );
		m_tileDrawingWindow->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_tileDrawingWindow->setTitle( editMenuTileItem );
		m_tileDrawingWindow->keepInParent( true );
		m_tileDrawingWindow->setSize( 300, 400 );

		m_subWindowSelectionBox = tgui::ComboBox::Ptr( *m_tileDrawingWindow );
		m_subWindowSelectionBox->load( resourceFolderPath + widgetFolderName + tguiConfigBlack );
		m_subWindowSelectionBox->setSize( 300, 20 );
		m_subWindowSelectionBox->bindCallbackEx( std::bind(
			&TileDrawingWindow::m_callback,
			this,
			std::placeholders::_1,
			std::ref( core ),
			std::ref( gui ) ),
			tgui::ComboBox::ItemSelected );
		m_subWindowSelectionBox->addItem( NO_BRUSH );
		m_subWindowSelectionBox->setSelectedItem( NO_BRUSH );

		for( const auto& el : m_subWindows )
			m_subWindowSelectionBox->addItem( el.first );
	}

	void TileDrawingWindow::onClose( tgui::Gui& gui )
	{
		if(m_subWindow)
			m_subWindow->onClose( gui );
		gui.remove( m_tileDrawingWindow );
	}

	void TileDrawingWindow::m_callback( const tgui::Callback& callback, cCore& core, tgui::Gui& gui )
	{
		std::string itemName = m_subWindowSelectionBox->getItem( callback.value );

		if( m_subWindow )
			m_subWindow->onClose( gui );

		if( itemName != NO_BRUSH )
		{
			m_subWindow = m_subWindows.at( callback.text )->create();
			m_subWindow->onInit( core, gui );
		}
		else
			m_subWindow = nullptr;
	}


	void StandartTileDrawingOptionsWindow::onInit( cCore& core, tgui::Gui& gui )
	{

	}

	std::string StandartTileDrawingOptionsWindow::info()
	{
		return "SingleBrush";
	}

	std::shared_ptr<Brush> StandartTileDrawingOptionsWindow::createBrush()
	{
		return std::make_shared<StandartBrush>();
	}

	void StandartTileDrawingOptionsWindow::onClose( tgui::Gui& gui )
	{
		//REPORT_ERROR_NOT_IMPLEMENTED;
	}

}
