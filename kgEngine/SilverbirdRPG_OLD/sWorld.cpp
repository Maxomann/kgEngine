#include "sWorld.h"

namespace kg
{
	sWorld::sWorld( PluginManagement& pluginManagement,
					SyncTime& syncTime,
					NetworkStringManager& networkStringManager )
					: r_pluginManagement( &pluginManagement ),
					r_syncTime( &syncTime ),
					r_networkStringManager( &networkStringManager )
	{
		//empty
	}
	sWorld::~sWorld()
	{
		for( const auto &el : m_chunkLayer )
			delete el.second;
	}
	sChunkLayer& sWorld::getChunkLayer( const int id )
	{
		try
		{
			return *m_chunkLayer.at( id );
		}
		catch( std::exception )
		{
			auto chunkLayer = new sChunkLayer( *r_pluginManagement,
											   *r_syncTime,
											   *r_networkStringManager );
			m_chunkLayer.insert( std::make_pair( id, chunkLayer ) );
			return *chunkLayer;
		}
	}
	void sWorld::update()
	{
		for( const auto&el : m_chunkLayer )
			el.second->update();
	}
}