//_______INPUT_HANDLER_H_______//
#pragma once
#include"stdafx.h"
#include"cWorld.h"
#include"cCamera.h"
#include"SyncTime.h"
#include"NetworkStringManager.h"

namespace kg
{
	ABSTRACT class cGameState
	{
	protected:
		////////Refs
		cWorld*					r_world;
		cCamera*				r_camera;
		SyncTime*				r_syncTime;
		NetworkStringManager*	r_networkStringManager;

	public:
		virtual ~cGameState();
		void init( cWorld& world, cCamera& camera, SyncTime& syncTime, NetworkStringManager& networkStringManager );
		virtual void init() = 0;

		//can return new gameState
		//else return nullptr
		virtual void update() = 0;
	};

	class StandartGameState : public cGameState
	{
	private:
		sf::Vector2i	m_camCenter;

	public:
		void init()
		{
			//r_camera->setZoom(0.5f);
			r_world->getChunkLayer()->initChunk( sf::Vector2i( 0, 0 ) );
		}
		void update()
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
				m_camCenter.y -= 2;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
				m_camCenter.y += 2;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
				m_camCenter.x -= 2;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
				m_camCenter.x += 2;
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Add ) )
				r_camera->zoom( 0.9f );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Subtract ) )
				r_camera->zoom( 1.1f );
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )
				r_camera->setZoom( 1.0f );

			r_camera->setCenter( m_camCenter );
		}
	};
}
