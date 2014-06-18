//_______MESSAGE_HANDLERS_CLIENT_______//

#pragma once
#include "../stdafx.h"
#include "../Client.h"
#include "../Network/Messages.h"

namespace kg
{

	class ChunkDataRequestAnswerHandler : public nMessageHandler
	{
	public:

		virtual void handle( cCore& core, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
		{
			auto& str = std::get<3>( message );

			std::string chunkX;
			std::string chunkY;

			while( str.at( 0 ) != standartSplitChar )
			{
				chunkX.push_back( str.at( 0 ) );
				str.erase( str.begin() );
			}
			str.erase( str.begin() );
			while( str.at( 0 ) != standartSplitChar )
			{
				chunkY.push_back( str.at( 0 ) );
				str.erase( str.begin() );
			}
			str.erase( str.begin() );

			core.getExtension<Client>()->getWorld().getChunk( core, sf::Vector2i( atoi( chunkX.c_str() ), atoi( chunkY.c_str() ) ) ).nFromString( core, str );
		}

		virtual int getMessageHandlerID() const
		{
			return MESSAGE_ID_SERVER::CHUNK_DATA_REQUEST_ANSWER;
		}

		virtual std::string info() const
		{
			return __CLASS__;
		}

	};

}
