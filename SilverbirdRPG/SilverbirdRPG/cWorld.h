//_______WORLD_H_______//
#pragma once
#include"stdafx.h"
#include"NetworkStringManager.h"
#include"SyncTime.h"
#include"cChunkLayer.h"

namespace kg
{
	class cWorld
	{
	private:
		////////Refs
		kg::cCamera*						r_camera;
		PluginManagement*				r_pluginManagement;
		NetworkStringManager*			r_networkStringManager;
		SyncTime*						r_syncTime;

		cChunkLayer								m_chunkLayer;
		int										m_chunkLayerId = 0;

	public:
		cWorld( cCamera& camera, PluginManagement& pluginManagement, SyncTime& syncTime, NetworkStringManager& networkStringManager );

		cChunkLayer* getChunkLayer();
		int			getChunkLayerId()const;
		//Layer will be added automaticly
		void		setChunkLayerId( int layer );

		void		update();

		void		draw();
	};
}
