#include "../nNetworkManger.h"

static std::mutex networkMutex;

void kg::nNetworkManager::m_networkRecieverFunction( ConnectionContainer& connections, MessageContainer& messages, bool& shouldTerminate )
{
	while( !shouldTerminate )
	{
		//std::cout << "Ich empfange Narchichten" << std::endl; //// to test if the thread works
		networkMutex.lock();
		for( auto& el : connections )
		{
			std::tuple<sf::IpAddress, sf::Uint16, int, std::string> info;
			sf::Packet packet;

			auto status = el.second.second.receive( packet, std::get<0>( info ), std::get<1>( info ) );
			if( status == sf::Socket::Done )
			{
				//sf::UdpSocket::recieve gives a wrong port
				std::get<1>( info ) = el.second.second.getLocalPort();

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
	std::thread thread( &m_networkRecieverFunction, std::ref( m_connectionContainer ), std::ref( m_messageContainer ), std::ref( m_terminateNetworkThread ) );
	thread.detach();
}

NETWORK_API void kg::nNetworkManager::initExtensions()
{
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
		m_messageHandler[std::get<2>( el )]->handle( core, el);
		recievedData->pop();
	}

	m_messageContainer.swap();
}

NETWORK_API void kg::nNetworkManager::addConnection( const sf::IpAddress& ip, sf::Uint16 port )
{
	networkMutex.lock();

	auto& el = m_connectionContainer[port];
	el.first.push_back( ip );
	el.second.bind( port );
	el.second.setBlocking( false );

	networkMutex.unlock();
}

NETWORK_API void kg::nNetworkManager::sendMessage( std::shared_ptr<nMessage> message, const sf::IpAddress& to, sf::Uint16 onPort )
{
	m_senderSocket.send( message->toPacket(), to, onPort );
}

NETWORK_API kg::nNetworkManager::~nNetworkManager()
{
	m_terminateNetworkThread = true;
	while( !networkMutex.try_lock() )
		;
	networkMutex.unlock();
}