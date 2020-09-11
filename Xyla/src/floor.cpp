#include "precompiled.h"

#include "floor.h"



void Floor::createRoom(sf::VideoMode& userMode) {
	Room room;
	room.outlineVertices(userMode);
	room.createGold();
	room.createEnemies();
	Floor::rooms.push_back(room);

}