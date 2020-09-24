#pragma once




#include "floor.h"

#include "roomCT.h"
#include "floorCT.h"
#include "player.h"
#include "playerCT.h"



class Game {
	friend int main();
private:
	std::vector<Floor> floors;

	Player player;

	PlayerCT playerCT;
	FloorCT floorCT;
	RoomCT roomCT;
	

public:
	Game();
	
	void createFloor(sf::VideoMode& userMode);
};
 


