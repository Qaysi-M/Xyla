#pragma once
#include <iostream>

#include "room.h"



class Floor {
	friend int main();
	friend class Game;

	std::vector<Room> rooms;



public:
	void createRoom(sf::VideoMode& userMode);

};