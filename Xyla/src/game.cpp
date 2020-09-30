#include "precompiled.h"


#include "game.h"


Game::Game() {
	 	

}

void Game::createFloor(sf::VideoMode& userMode) {
	Floor floor;
	floor.createDungen(userMode);
	floor.seperateRooms(userMode);
	floor.setLivingAndDungenRooms(userMode);
	floor.livingRooms = floor.mergeSort(floor.livingRooms);
	

	floor.constructDelauneyTrangulation(floor.livingRooms);
	floor.adjacencyListDT = floor.adjacencyList;
	floor.constructEdges(floor.adjacencyListDT, floor.edgesDT);
	
	floor.constructMST(floor.livingRooms[0]);
	floor.constructEdges(floor.adjacencyListMST, floor.edgesMST);

	floor.addEdgesToMSTFromDT();
	floor.createHallways();
	

	Game::floors.push_back(floor);
}

