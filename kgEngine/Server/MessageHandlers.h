//_______MESSAGE_HANDLERS_SERVER_______//

#pragma once
#include "stdafx.h"
#include "Server.h"

namespace kg
{
	class ChunkDataRequestAnswer : public nMessage
	{
		std::string m_message;

	public:
		ChunkDataRequestAnswer( Chunk& chunk )
		{
			for( int x = 0; x < Chunk::size.x; ++x )
			{
				for( int y = 0; y < Chunk::size.y; ++y )
				{
					//TODO
					chunk.getField( sf::Vector2i( x, y ) );
				}
			}
		}

		virtual std::string getMessage()
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual int getID()
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}
	};

	class ChunkDataRequestHandler : public nMessageHandler
	{
	public:

		virtual void handle( cCore& core, nNetworkManager& networkManger, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
		{
			std::stringstream stream( std::get<3>(message));
			std::string segment;
			std::vector<std::string> seglist;

			while( std::getline( stream, segment, '_' ) )
			{
				seglist.push_back( segment );
			}
			networkManger.sendMessage(
				std::make_shared<ChunkDataRequestAnswer>( core.getExtension<Server>()->getWorld().getChunk( { atoi( seglist.at( 0 ).c_str() ), atoi( seglist.at( 1 ).c_str() ) } ) ),
				std::get<0>( message ),
				//return message on port where it was recieved
				std::get<1>( message )
				);
		}

		virtual int getMessageHandlerID() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

		virtual std::string info() const
		{
			throw std::logic_error( "The method or operation is not implemented." );
		}

	};
}
