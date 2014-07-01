//_______CAMERA_H_______//

#pragma once
#include"../stdafx.h"
/*#include"cFocusable.h"*/

namespace kg
{
	class SpriteBatch
	{
	public:
		SpriteBatch( void );
		~SpriteBatch( void );


		void display( bool reset = true, bool flush = true );
		void draw( const sf::Sprite &sprite );
		void draw( const sf::Texture *texture, const sf::Vector2f &position,
				   const sf::IntRect &rec, const sf::Color &color, const sf::Vector2f &scale,
				   const sf::Vector2f &origin, float rotation = 0 );

		void draw( const sf::Texture *texture, const sf::FloatRect &dest, const sf::IntRect &rec, const sf::Color &color );

		void flush();
		void setRenderStates( const sf::RenderStates &states );
		void setRenderTarget( sf::RenderTarget &rt );

	private:
		sf::RenderTarget *rt;
		sf::RenderStates state;
		std::vector<sf::Vertex> vertices;
		int count;
		int capacity;

		int create( const sf::Texture *texture );

	};



	//No check if the object is shown on screen is performed before drawing it
	//you have to check yourself by testing collision with the cameraReactangle
	class Camera
	{
	private:
		sf::Vector2i							m_finalSize;

		sf::View								m_View;

		// 		cFocusable*								m_focused = nullptr;
		// 		bool									m_focusRotation = false;

		//cannot be unordered_map because of drawing order
		std::map< int, std::vector<sf::Sprite*> >m_spritesToRender;

		SpriteBatch								m_spriteBatch;

	public:
		void init( const sf::Vector2u finalSize );

		//returns false if camera is focused on an object
		bool			setCenter( const sf::Vector2i position );
		sf::Vector2i	getCenter()const;
		void			moveCenter( const sf::Vector2i offset );

		//returns false if camera is focused and fucusRotation == true
		bool			setRotation( const float rotationInDegree );

		//zoomFactor != NULL
		void			zoom( const float zoomFactor );
		void			setZoom( const float zoom );
		float			getZoom()const;

		sf::Vector2i	getFinalSize()const;

		sf::FloatRect	getCameraRect()const;

		sf::Vector2i	getUpperLeftCorner()const;

		// 		bool			isFocused()const;
		// 		bool			isRotationFocused()const;
		//
		// 		void			focus( /*no const*/cFocusable& toFocus, const bool focusRotation = true );
		// 		//unfocuses the camera
		// 		void			free();

		//these draw functions don't acually draw the objects to the screen,
		//they just save a reference to them and draw them when Camera::display() is called
		//
		//If you give a Sprite without a zValue, it will be drawn last
		void			draw( sf::Sprite& toDraw, int zValue = TILE );
		void			draw( std::vector<sf::Sprite*>& toDraw, int zValue );

		void			display( sf::RenderTarget& renderTarget );

		static const int TILE = -999999999;
		static const int PREGROUND = 999999999;
	};

	class DrawableToCamera
	{
	public:
		virtual void draw( Camera& camera ) = 0;
	};
}
