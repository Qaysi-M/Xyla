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
	
	/*
	std::cout << "livingrooms " << std::endl;
	for (auto& room : floor.livingRooms)
		std::cout << room << " , ";
	std::cout << std::endl;
	
	floor.constructConvexHull(floor.livingRooms);

	
	std::vector<int> vl = { 66, 46, 23, 62, 11 };
	std::vector<int> vr = { 60, 64, 33, 31, 43};

	floor.adjacencyList[66] = { 46, 62 };
	floor.adjacencyList[46] = { 23, 66 };
	floor.adjacencyList[23] = { 11, 46 };
	floor.adjacencyList[11] = { 62, 23 };
	floor.adjacencyList[62] = { 66, 11 };

	floor.adjacencyList[60] = { 64, 31 };
	floor.adjacencyList[64] = { 33, 60 };
	floor.adjacencyList[33] = { 43, 64 };
	floor.adjacencyList[43] = { 31, 33 };
	floor.adjacencyList[31] = { 60, 43 };
	

	//std::cout << floor.qtest(floor.rooms.at(11).center, floor.rooms.at(11).center, floor.rooms.at(66).center, floor.rooms.at(31).center) << std::endl;
	

	//floor.findBTandUT(vl, vr);
	
	floor.mergeDTs(vl, vr);
	*/
	floor.constructDelauneyTrangulation(floor.livingRooms);
	Game::floors.push_back(floor);
}

