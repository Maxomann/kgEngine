//_______TESTPROJEKT_______//

#pragma once
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/system.hpp>

#include <TGUI/TGUI.hpp>

using namespace std;
using namespace sf;
using namespace tgui;

int main()
{
	RenderWindow window( VideoMode( 800, 600 ), "Testwindow" );
	sf::RectangleShape shape;
	shape.setSize( { 40, 100 } );

	sf::RectangleShape cursor;
	cursor.setSize( { 20, 20 } );
	cursor.setFillColor( sf::Color::Red );
	cursor.setPosition( { 20, 20 } );

	sf::View view( { 0, 0 }, { 800, 600 } );

	while( !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
	{
		window.clear();
		window.setView( view );
		window.draw( shape );
		window.setView( window.getDefaultView() );//wichtig!
		window.draw( cursor );
		window.display();
		view.move( { 0.001f, 0.001f } );
	}

	return 0;
}
