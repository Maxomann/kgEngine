//_______CHUNK_H_______//
#pragma once
#include"stdafx.h"
#include"SyncTime.h"
#include"PluginManagement.h"

namespace kg
{
	class sChunk
	{
	private:
		const int	m_chunkLayerId = -1;

	public:

		void saveToFile();

		void update();
	};
}
