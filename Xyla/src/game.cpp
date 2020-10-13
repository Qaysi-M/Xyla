#include "precompiled.h"

#include "mathematics.h"
#include "game.h"


Game::Game() {
	 	

}

int Game::createFloor() {
	Floor floor;
	floor.createDungen();
	floor.seperateRooms();
	floor.setLivingAndDungenRooms();
	floor.setGameMatrix();
	floor.allRooms = floor.mergeSort(floor.allRooms);

	

	floor.constructDelauneyTrangulation(floor.allRooms);
	floor.adjacencyListDT = floor.adjacencyList;
	floor.constructEdges(floor.adjacencyListDT, floor.edgesDT);
	
	floor.constructMST(floor.allRooms[0], floor.allRooms);
	floor.constructEdges(floor.adjacencyListMST, floor.edgesMST);

	floor.addEdgesToMSTFromDT();
	floor.createHallways(floor.edgesMST);
	floor.createStair();
	floor.createGolds();
	floor.createEnemies();
	//floor.createDoors();
	int id = Game::floorHighestId;
	Game::floorHighestId++;
	
	Game::floors.insert({id, floor});
	

	return id;
}

void Game::setStartingRoom() {
	srand(time(0));
	int i = Xyla::rand(0, Game::floors.at(currentFloor).livingRooms.size() - 1); // choose a rand room
	Game::currentRoom = Game::floors.at(currentFloor).livingRooms[i];
	Game::floors.at(currentFloor).visitedRooms.push_back(Game::currentRoom);
}

void Game::initiatePlayer() {
	Floor& floor = Game::floors.at(Game::currentFloor);
	Room& room = floor.rooms.at(currentRoom);
	Game::player.initiatePosition(room.position, room.size, room.unit);
	Game::player.setPosition(floor, room);

	floor.printMatrix();
}

void Game::startGame() {
	Game::currentFloor = Game::createFloor(); //create a floor
	Game::setStartingRoom();
	Game::initiatePlayer();


}


void Game::changeFloor() {
	Game::currentFloor = Game::createFloor(); //create a floor
	Game::setStartingRoom();
	Game::initiatePlayer();
}

void Game::onTick() {
	Floor& floor = Game::floors.at(Game::currentFloor);
	Room& room = Game::floors.at(Game::currentFloor).rooms.at(currentRoom);
	floor.moveEnemy(Game::player, room);
}

void Game::onWait() {
	Game::player.didHit = false;

}

