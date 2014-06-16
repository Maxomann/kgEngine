//_______MESSAGE_HANDLERS_CLIENT_______//

#pragma once
#include "stdafx.h"

namespace kg
{
	class ChunkDataRequest : public nMessage
	{
		sf::Vector2i m_position;

	public:
		ChunkDataRequest( const sf::Vector2i& position )
			:m_position( position )
		{ }

		virtual std::string getMessage()
		{
			return std::to_string( m_position.x ) + standartSplitChar + std::to_string( m_position.y );
		}

		virtual int getID()
		{
			return MESSAGE_ID_CLIENT::CHUNK_DATA_REQUEST;
		}

	};

	class ChunkDataRequestAnswerHandler : public nMessageHandler
	{
	public:

		virtual void handle( cCore& core, nNetworkManager& networkManger, std::tuple<sf::IpAddress, sf::Uint16, int, std::string>& message ) const
		{
			/*std::string chunkX;
			std::string chunkY;

			int pos = 0;
			while( std::get<3>( message ).at( pos ) != standartSplitChar )
			{
				chunkX.push_back( std::get<3>( message ).at( pos ) );
				pos++;
			}
			while( std::get<3>( message ).at( pos ) != standartSplitChar )
			{
				chunkY.push_back( std::get<3>( message ).at( pos ) );
				pos++;
			}*/

			std::cout << std::get<3>( message ) << std::endl;
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