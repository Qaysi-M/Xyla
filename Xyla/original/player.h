#pragma once

#include "entity.h"

#include "SFML/Graphics.hpp"

class Player : public Entity {

	int gold{ 0 };


public:


	void drawPlayer(sf::RenderWindow& windowView);

};