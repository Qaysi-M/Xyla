#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "SFML/Window.hpp"
#include "room.h"


class RoomCT {
	friend class Game;

private:
	sf::RectangleShape roomBorder;

public:
	void drawLivingRoom(sf::RenderWindow& windowView, Room& room);
#ifdef XYLA_DEBUG
	void drawDungenRoom(sf::RenderWindow& windowView, Room& room);
	void drawHallwayRoom(sf::RenderWindow& windowView, Room& room);
#endif // XYLA_DEBUG

	void drawDoors(sf::RenderWindow& windowView, Room& room);


	void drawGold(sf::RenderWindow& windowView, Room& room);
	void drawEnemy(sf::RenderWindow& windowView, Room& room);

	void drawStair(sf::RenderWindow& windowView, Room& room);
};