//_______WORLD_H_______//
#pragma once
#include"stdafx.h"
#include"sChunkLayer.h"
#include"PluginManagement.h"
#include"SyncTime.h"

namespace kg
{
	class sWorld
	{
		PluginManagement*		r_pluginManagement;
		SyncTime*				r_syncTime;
		NetworkStringManager*	r_networkStringManager;

		std::map< int, sChunkLayer* >	m_chunkLayer;

	public:
		sWorld( PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager );
		~sWorld();

		sChunkLayer& getChunkLayer( const int id );

		void update();
	};
}
