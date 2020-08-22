#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>


#include "room.h"


class RoomCT {
	friend class Game;
private:
	
	std::vector<Room> rooms;



	sf::RectangleShape roomBorder;

public:
	RoomCT();
	

	void drawRoom(sf::RenderWindow& windowView, Room room);
	
	



};