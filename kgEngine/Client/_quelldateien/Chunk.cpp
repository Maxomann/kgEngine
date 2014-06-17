#include "../World/Chunk.h"

namespace kg
{

	Chunk::Chunk( cResourceManagement& resourceManagement, sf::Vector2i positionInPixel )
		:m_positionInPixel(positionInPixel)
	{
		//standart initialize fields
		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			m_tiles.push_back( std::vector<Tile>() );
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				m_tiles.at( x ).push_back(
					Tile(
					resourceManagement,
					0,
					sf::Vector2i( m_positionInPixel.x + x*tileSizeInPixel, m_positionInPixel.y + y*tileSizeInPixel ))
					);
			}
		}
	}

	void Chunk::draw( Camera& camera )
	{
		for( auto& el : m_tiles )
			for( auto& tile : el )
				tile.draw( camera );
	}

	void Chunk::nFromString( cResourceManagement& resourceManagement, const std::string& data )
{
		auto seglist = aSplitString::function( data, standartSplitChar, aSplitString::operation::REMOVE );

		for( int x = 0; x < chunkSizeInTiles; ++x )
		{
			for( int y = 0; y < chunkSizeInTiles; ++y )
			{
				auto& tile = m_tiles.at( x ).at( y );
				int id = atoi( seglist.at( x*chunkSizeInTiles + y ).c_str());
				if( id != tile.getID() )
					tile = Tile( resourceManagement, id, sf::Vector2i( m_positionInPixel.x + x*tileSizeInPixel, m_positionInPixel.y + y*tileSizeInPixel ) );
			}
		}
	}

	const Tile& Chunk::getTile( sf::Vector2i positionInTiles ) const
	{
		return m_tiles.at( positionInTiles.x ).at( positionInTiles.y );
	}

}
