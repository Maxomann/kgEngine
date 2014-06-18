#pragma once
#include "../stdafx.h"

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
			m_message += std::move( chunk.nToString() );
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
}
