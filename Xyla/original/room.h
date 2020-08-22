#pragma once


#include <iostream>

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>




	

class Room {
	friend class RoomCT;

	sf::Vector2f size{ sf::Vector2f(0,0) }; // size is a sf::vector2f(w,h) such that w & h is the width & of the room respectively.   

	const sf::Vector2f origin = sf::Vector2f(0, 0); // is the origin ( ie. (0,0) )

	int doors{ 0 };
	int enemies{ 0 };
	int golds{ 0 };
	int stairs{ 0 };

	sf::Vector2f vertices[4] = {origin, origin, origin, origin};
	
	float height{ 0 };
	float width{ 0 };
	sf::Vector2f position = origin; // upleft

public:

	void outlineVertices(sf::VideoMode& userMode);
	void setPosition(sf::VideoMode& userMode);



};