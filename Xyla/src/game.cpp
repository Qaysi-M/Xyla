#include "precompiled.h"

#include "mathematics.h"
#include "game.h"


Game::Game() {
	 	

}

int Game::createFloor(sf::VideoMode& userMode) {
	Floor floor;
	floor.createDungen(userMode);
	floor.seperateRooms(userMode);
	floor.setLivingAndDungenRooms(userMode);
	floor.allRooms = floor.mergeSort(floor.allRooms);
	

	floor.constructDelauneyTrangulation(floor.allRooms);
	floor.adjacencyListDT = floor.adjacencyList;
	floor.constructEdges(floor.adjacencyListDT, floor.edgesDT);
	
	floor.constructMST(floor.allRooms[0], floor.allRooms);
	floor.constructEdges(floor.adjacencyListMST, floor.edgesMST);

	floor.addEdgesToMSTFromDT();
	floor.createHallways(userMode, floor.edgesMST);

	floor.createGolds();
	floor.createEnemies();
	floor.createDoors();
	int id = Game::floorHighestId++;

	Game::floors.insert({id, floor});

	return id;
}

void Game::setStartingRoom() {
	srand(time(0));
	int i = Xyla::rand(0, Game::floors.at(currentFloor).livingRooms.size() - 1); // choose a rand room
	Game::currentRoom = Game::floors.at(currentFloor).livingRooms[i];
}

void Game::initiatePlayer() {
	Floor& floor = Game::floors.at(Game::currentFloor);
	Room& room = floor.rooms.at(currentRoom);
	Game::player.initiatePosition(room.position, room.size, room.unit);
	Game::player.setPosition(room);
}

void Game::startGame(sf::VideoMode& userMode) {
	Game::currentFloor = Game::createFloor(userMode); //create a floor

	Game::setStartingRoom();
	Game::initiatePlayer();


}

void Game::onTick() {
	Room& room = Game::floors.at(Game::currentFloor).rooms.at(currentRoom);
	room.moveEnemy(Game::player);
}