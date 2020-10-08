#pragma once




#include "floor.h"

#include "roomCT.h"
#include "floorCT.h"
#include "player.h"
#include "playerCT.h"



class Game {
	friend int main();
	friend class Player;
private:
	std::unordered_map<int, Floor> floors;
	int floorHighestId{ 0 };

	int currentFloor;
	int currentRoom;
	Player player;

	PlayerCT playerCT;
	FloorCT floorCT;
	RoomCT roomCT;
	

public:
	Game();
	
	int createFloor(sf::VideoMode& userMode); // return the floorid

	void setStartingRoom();
	void initiatePlayer();
	void startGame(sf::VideoMode& userMode);

	void onTick();

};
 


