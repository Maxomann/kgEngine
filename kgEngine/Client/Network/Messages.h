#pragma once
#include "../stdafx.h"

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
}