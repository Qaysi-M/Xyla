#pragma once

#include "SFML/Graphics.hpp"

#include "room.h"

//creature is a player, enemy, or gold

class Creature {
	

public:
	const sf::Vector2f origin = sf::Vector2f(0, 0);
	sf::Vector2f position = origin; 
	sf::Vector2f size = sf::Vector2f(40, 40);

	float unit{ 40 };

	enum class Axis { x = 0, y = 1 };
	enum class Direction { negative = -1, positive = 1 };

public:

	void setPosition(Room& room);

	 







};