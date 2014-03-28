//_______INPUT_HANDLER_CPP_______//
#pragma once
#include"cGameState.h"

namespace kg
{
	cGameState::~cGameState()
	{ }

	void cGameState::init( cWorld& world,
						   cCamera& camera,
						   SyncTime& syncTime,
						   NetworkStringManager& networkStringManager )
	{
		r_world = &world;
		r_camera = &camera;
		r_syncTime = &syncTime;
		r_networkStringManager = &networkStringManager;
	}
}