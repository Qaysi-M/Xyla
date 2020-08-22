

#include "floor.h"



void Floor::createRoom(sf::VideoMode& userMode) {
	Room room;
	room.outlineVertices(userMode);
	Floor::rooms.push_back(room);

}