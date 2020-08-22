

#include "room.h"


void Room::outlineVertices(sf::VideoMode& userMode) {
	
	Room::width = 0.5 * userMode.width;
	Room::height = 0.5 * userMode.height;


	Room::setPosition(userMode);
	

}

void Room::setPosition(sf::VideoMode& userMode) {
	
	float px = (((float) userMode.width - Room::width)) / ((float) 2);

	Room::position = sf::Vector2f(px, 0.35 * 1000);

	
	
}



