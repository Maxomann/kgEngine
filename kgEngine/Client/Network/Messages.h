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

	class SetTileRequest : public nMessage
	{
		sf::Vector2i m_chunkPosition;
		sf::Vector2i m_tilePosition;
		int m_tileID;

	public:
		SetTileRequest( const sf::Vector2i& chunkPositionInChunks, const sf::Vector2i& tilePositionRelativeToChunk, const int tileID )
			:m_chunkPosition( chunkPositionInChunks ),
			m_tilePosition( tilePositionRelativeToChunk ),
			m_tileID(tileID)
		{ }

		virtual std::string getMessage()
		{
			return std::to_string( m_chunkPosition.x ) +
				standartSplitChar +
				std::to_string( m_chunkPosition.y ) +
				standartSplitChar +
				std::to_string( m_tilePosition.x ) +
				standartSplitChar +
				std::to_string( m_tilePosition.y ) +
				standartSplitChar +
				std::to_string( m_tileID );
		}

		virtual int getID()
		{
			return MESSAGE_ID_CLIENT::SET_TILE_REQUEST;
		}

	};
}
