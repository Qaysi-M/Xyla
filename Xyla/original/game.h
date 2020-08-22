#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


#include "floor.h"

#include "roomCT.h"
#include "floorCT.h"
#include "player.h"



class Game {
	friend int main();
private:
	std::vector<Floor> floors;

	Player player;

	FloorCT floorCT;
	RoomCT roomCT;

public:
	
	Game();
	
	void createFloor();

};
 


