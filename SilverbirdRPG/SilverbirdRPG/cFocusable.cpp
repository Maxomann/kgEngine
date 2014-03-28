//_______FOCUSABLE_CPP_______//
#pragma once
#include"cFocusable.h"

namespace kg
{
	void cFocusable::setFocus( const bool isFocused )
	{
		this->m_isFocused = isFocused;
	}
	sf::Vector2i cFocusable::getPosition()const
	{
		return m_position;
	}
	float cFocusable::getRotation()const
	{
		return m_rotationInDegree;
	}
	bool cFocusable::isFocused()const
	{
		return m_isFocused;
	}
}