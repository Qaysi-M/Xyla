#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "SFML/Window.hpp"
#include "room.h"


class RoomCT {
	friend class Game;

private:
	sf::RectangleShape roomBorder;

public:
	void drawRoom(sf::RenderWindow& windowView, Room& room);
	void drawGold(sf::RenderWindow& windowView, Room& room);
	void drawEnemy(sf::RenderWindow& windowView, Room& room);
};