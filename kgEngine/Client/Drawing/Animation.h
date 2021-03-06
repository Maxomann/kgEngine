//_______ANIMATION_______//

#pragma once
#include "../stdafx.h"
#include "../Settings/AnimationSettings.h"

namespace kg
{
	class Animation
	{
		// Reference to options for controlling the Animation.
		const AnimationSettings& m_settings;

		// The currently active frame.
		unsigned int             m_frame = 0;
		// The currently active state.
		unsigned int             m_state = 0;

		// true to run.
		bool                     m_run;

		// The time in frame.
		sf::Clock                m_timeInFrame;

	public:

		// Constructor Animation starts by default Animation must not exceed the lifetime of settings.
		//
		// @author	Kay
		// @date	07.08.2014
		//
		// @param	settings	Options for controlling the operation.
		// @param	start   	(Optional) true to start. false if animation should not start.
		Animation( const AnimationSettings& settings, bool start = true );

		// Runs this object.
		//
		// @author	Kay
		// @date	07.08.2014
		void                     run();

		// Stops this object.
		//
		// @author	Kay
		// @date	07.08.2014
		void                     stop();

		// Resets the given resetState.
		//
		// @author	Kay
		// @date	07.08.2014
		//
		// @param	resetState	(Optional) true to reset state.
		void                     reset( bool resetState = false );

		// returns false if frame not available.
		//
		// @author	Kay
		// @date	07.08.2014
		//
		// @param	id	The identifier.
		//
		// @return	true if it succeeds, false if it fails.
		bool                     setFrame( int id );

		// returns false if state not available.
		//
		// @author	Kay
		// @date	07.08.2014
		//
		// @param	id	The identifier.
		//
		// @return	true if it succeeds, false if it fails.
		bool                     setState( int id );

		// Applies the given toSprite.
		//
		// @author	Kay
		// @date	07.08.2014
		//
		// @param [in,out]	toSprite	to sprite.
		void                     apply( sf::Sprite& toSprite );

		// Frames this object.
		//
		// @author	Kay
		// @date	07.08.2014
		void                     frame();

		// Gets the settings.
		//
		// @author	Kay
		// @date	07.08.2014
		//
		// @return	The settings.
		const AnimationSettings& getSettings()const;
	};

	typedef std::map<int, Animation> AnimationByIdMap;
}
