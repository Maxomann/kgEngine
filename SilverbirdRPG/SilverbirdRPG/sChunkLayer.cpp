#include "sChunkLayer.h"

namespace kg
{
	sChunkLayer::sChunkLayer( PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager )
		: r_pluginManagement( &pluginManagement ),
		r_networkStringManager( &networkStringManager ),
		r_syncTime( &syncTime )
	{
		//empty
	}
	sChunkLayer::~sChunkLayer()
	{
		for( const auto&el : m_chunks )
			delete el.second;
	}
	sChunk& sChunkLayer::getChunk( const sf::Vector2i position )
	{
		try
		{
			return *m_chunks.at( std::make_pair( position.x, position.y ) );
		}
		catch( std::exception )
		{
			auto chunk = new sChunk();
			m_chunks.insert( std::make_pair( std::make_pair( position.x, position.y ), chunk ) );
			return *chunk;
		}
	}
	void sChunkLayer::setActiveAreas( const std::vector<sf::IntRect> areas )
	{
		std::vector<std::vector<sf::Vector2i>*> activeChunkLists;

		for( const auto&area : areas )
		{
			std::vector<sf::Vector2i>* activeChunkList = new std::vector<sf::Vector2i>();

			for( int x = area.left; x < area.left + area.width; ++x )
				for( int y = area.top; y < area.top + area.height; ++y )
					activeChunkList->push_back( sf::Vector2i( x, y ) );

			activeChunkLists.push_back( activeChunkList );
		}

		std::list<sf::Vector2i> finalActiveChunkList;

		//merge lists to finalActiveChunkList
		for( const auto&el : activeChunkLists )
			for( const auto&chunkPosition : *el )
			{
				if( std::none_of( finalActiveChunkList.begin(), finalActiveChunkList.end(),
					[&chunkPosition]( const sf::Vector2i& vec )->bool
				{
					return vec == chunkPosition;
				}
					) )
				{
					finalActiveChunkList.push_back( chunkPosition );
				}
			}

		//speichere und lösche nicht in der liste vorhandene chunks
		for( const auto& pair : m_chunks )
		{
			if( std::none_of( finalActiveChunkList.begin(), finalActiveChunkList.end(),
				[&pair]( const sf::Vector2i& vec )->bool
			{
				return sf::Vector2i( pair.first.first, pair.first.second ) == vec;
			}
				) )
			{
				pair.second->saveToFile();
				delete pair.second;
				m_chunks.erase( pair.first );
			}
			//wenn chunk geladen und auf liste vorhanden
			else
			{
				//chunk von liste löschen
				finalActiveChunkList.erase( std::find( finalActiveChunkList.begin(), finalActiveChunkList.end(), sf::Vector2i( pair.first.first, pair.first.second ) ) );
			}
		}

		//neue chunks laden
		for( const auto& vec : finalActiveChunkList )
		{
			m_chunks.insert( std::make_pair( std::make_pair( vec.x, vec.y ), new sChunk() ) );
		}

		//elemente aus liste löschen
		for( auto list : activeChunkLists )
			delete list;
	}

	void sChunkLayer::update()
	{
		for( const auto&el : m_chunks )
			el.second->update();
	}
}