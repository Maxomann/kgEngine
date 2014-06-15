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
		ChunkDataRequestAnswer( const Chunk& chunk )
			:m_message(chunk.toString())
		{}

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
			networkManger.sendMessage(
				std::make_shared<ChunkDataRequestAnswer>( core.getExtension<Server>()->getWorld().getChunk( { atoi( seglist.at( 0 ).c_str() ), atoi( seglist.at( 1 ).c_str() ) } ) ),
				std::get<0>( message ),
				//return message on port where it was recieved
				std::get<1>( message )
				);
		}
		//POSITION HINZUFÜGEn!!!!!!!!!!!!!
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
