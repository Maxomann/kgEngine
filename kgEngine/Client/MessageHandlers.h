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
			return std::to_string( m_position.x ) + ";" + std::to_string( m_position.y );
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
			throw std::logic_error( "The method or operation is not implemented." );
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