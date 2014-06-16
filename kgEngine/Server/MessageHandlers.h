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
		ChunkDataRequestAnswer( const sf::Vector2i& position, const Chunk& chunk )
		{
			m_message += std::to_string( position.x );
			m_message += standartSplitChar;
			m_message += std::to_string( position.y );
			m_message += standartSplitChar;
			m_message += std::move( chunk.toString() );
		}

		virtual std::string getMessage()
		{
			return m_message;
		}

		virtual int getID()
		{
			return MESSAGE_ID_SERVER::CHUNK_DATA_REQUEST_ANSWER;
		}
	};

	class ChunkDataRequestHandler : public nMessageHandler
	{
	public:

		virtual void handle( cCore& core, nNetworkManager& networkManger, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
		{
			auto seglist = aSplitString::function( std::get<3>( message ), standartSplitChar, aSplitString::operation::REMOVE );
			sf::Vector2i chunkPosition{ atoi( seglist.at( 0 ).c_str() ), atoi( seglist.at( 1 ).c_str() ) };

			networkManger.sendMessage(
				std::make_shared<ChunkDataRequestAnswer>( chunkPosition, core.getExtension<Server>()->getWorld().getChunk( chunkPosition )),
				std::get<0>( message ),
				//return message on port where it was recieved
				std::get<1>( message )
				);
		}

		virtual int getMessageHandlerID() const
		{
			return MESSAGE_ID_CLIENT::CHUNK_DATA_REQUEST;
		}

		virtual std::string info() const
		{
			return __CLASS__;
		}

	};
}
