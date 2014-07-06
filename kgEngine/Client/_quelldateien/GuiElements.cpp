#include "../GUI/GuiElements.h"

namespace kg
{
	ConnectToServerWindow::ConnectToServerWindow( cCore& core, tgui::Gui& gui )
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
		gui.remove( m_ctsIp );
		gui.remove( m_ctsRecievePortOnServer );
		gui.remove( m_ctsRecievePortOnClient );
		gui.remove( m_ctsSendButton );
	}
}
