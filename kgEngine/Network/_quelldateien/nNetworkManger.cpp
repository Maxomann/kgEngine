#include "../nNetworkManger.h"

static std::mutex networkMutex;

void kg::nNetworkManager::m_networkRecieverFunction( SocketMap& recievingSocketByPort, MessageContainer& messages, bool& shouldTerminate )
{
	while( !shouldTerminate )
	{
		//std::cout << "Ich empfange Narchichten" << std::endl; //// to test if the thread works
		networkMutex.lock();
		for( auto& el : recievingSocketByPort )
		{
			std::tuple<sf::IpAddress, sf::Uint16, int, std::string> info;
			sf::Packet packet;

			//std::get<1>( info ) will be filled with a random? value
			auto status = el.second.receive( packet, std::get<0>( info ), std::get<1>( info ) );
			if( status == sf::Socket::Done )
			{
				// sf::UdpSocket::recieve gives a wrong port
				// correct the port with the port the recievingSocket is bound to
				std::get<1>( info ) = el.second.getLocalPort();

				packet >> std::get<2>( info ) >> std::get<3>( info );
				messages.push_back( info );
			}
		}
		networkMutex.unlock();
	}
}

NETWORK_API kg::nNetworkManager::nNetworkManager()
{
	// launch network reciever thread
	// it will run until the application is closed
	std::thread thread( &m_networkRecieverFunction, std::ref( m_recievingSocketByPort ), std::ref( m_messageContainer ), std::ref( m_terminateNetworkThread ) );
	thread.detach();
}

NETWORK_API void kg::nNetworkManager::initExtensions( pPluginManager& pluginManager )
{
	pluginManager.fillExtandable<nNetworkManager>( *this );

	for( const auto& el : m_extensions )
	{
		auto ptr = std::dynamic_pointer_cast< kg::nMessageHandler >(el.second);
		if( ptr )
		{
			m_messageHandler[ptr->getMessageHandlerID()] = ptr;
		}
	}
}

NETWORK_API void kg::nNetworkManager::frame( cCore& core )
{
	auto recievedData = m_messageContainer.getContent();

	while( !recievedData->empty() )
	{
		std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& el = recievedData->front();
		m_messageHandler[std::get<2>( el )]->handle( core, el );
		recievedData->pop();
	}

	m_messageContainer.swap();
}

NETWORK_API void kg::nNetworkManager::addConnection( const sf::IpAddress& ip, sf::Uint16 recievePort, sf::Uint16 sendPort )
{
	networkMutex.lock();

	auto& recieveSocket = m_recievingSocketByPort[recievePort];
	recieveSocket.bind( recievePort );
	recieveSocket.setBlocking( false );

	auto& vec = m_connections[ip];
	bool found = false;
	for( const auto& el : vec )
	{
		if( el.first == recievePort )
		{
			if( el.second != sendPort )
				REPORT_ERROR_NETWORK( "Could not add connection" );
			else
			{
				found = true;
				break;
			}
		}
	}
	if( !found )
		vec.push_back( std::make_pair( recievePort, sendPort ) );

	networkMutex.unlock();
}

NETWORK_API void kg::nNetworkManager::sendMessage( std::shared_ptr<nMessage> message, const sf::IpAddress& to, sf::Uint16 onPort )
{
	m_sendSocket.send( message->toPacket(), to, onPort );
}

NETWORK_API kg::nNetworkManager::~nNetworkManager()
{
	m_terminateNetworkThread = true;
	while( !networkMutex.try_lock() )
		;
	networkMutex.unlock();
}

NETWORK_API void kg::nNetworkManager::spreadMessage( std::shared_ptr<nMessage> message )
{
	for( const auto& el : m_connections )
		if( el.second.size() > NULL )
			sendMessage( message, el.first, el.second.at( 0 ).second );
}

NETWORK_API sf::Uint16 kg::nNetworkManager::getSendPort( sf::IpAddress forIp, sf::Uint16 recievedOnPort )
{
	auto& vec = m_connections.at( forIp );
	for( const auto& el : vec )
		if( el.first == recievedOnPort )
			return el.second;

	REPORT_ERROR_NETWORK( "Not connected to Ip: " + forIp.toString() );
}

NETWORK_API void kg::nNetworkManager::clearConnections()
{
	m_connections.clear();
}