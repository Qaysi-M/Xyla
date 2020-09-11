#pragma once



#include "room.h"




class Floor {
	friend int main();
	friend class Game;


	std::vector<Room> rooms;
	

	

public:

	void createRoom(sf::VideoMode& userMode);

};