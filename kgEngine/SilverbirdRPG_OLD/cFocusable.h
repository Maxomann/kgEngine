//_______FOCUSABLE_H_______//
#pragma once
#include"stdafx.h"

namespace kg
{
	class cFocusable
	{
	private:
		bool			m_isFocused = false;

	protected:
		//ATTENTION: position is where the CENTER of the camera will be
		//if you give the position of the sprite you want to render
		//make sure to NOT set the position of the camera to it's
		//upper left corner
		sf::Vector2i	m_position = sf::Vector2i( 0, 0 );
		float			m_rotationInDegree = 0.0f;

	public:
		//Don't call this!
		void			setFocus( const bool isFocused );

		sf::Vector2i	getPosition()const;
		float			getRotation()const;
		bool			isFocused()const;
	};
}
