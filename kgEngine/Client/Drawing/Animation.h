//_______ANIMATION_______//

#pragma once
#include "../stdafx.h"
#include "../Settings/AnimationSettings.h"

namespace kg
{

	class Animation
	{
		const AnimationSettings& m_settings;

		unsigned int m_frame = 0;
		unsigned int m_state = 0;

		bool m_run;

		sf::Clock m_timeInFrame;

	public:
		//Animation starts by default
		Animation( const AnimationSettings& settings, bool start = true );

		void run();
		void stop();
		void reset( bool resetState = false );

		//returns false if frame not available
		bool setFrame( int id );
		//returns false if state not available
		bool setState( int id );

		void apply( sf::Sprite& toSprite );

		void frame();

		const AnimationSettings& getSettings()const;
	};

	typedef std::map<int, Animation> AnimationByIdMap;
}