
#include "precompiled.h"

#include "mathematics.h"
#include "room.h"

#include "creature.h"

void Room::setWidth(float width) {
	Room::width = width;
	Room::size.x = width;
}
void Room::setHeight(float height) {
	Room::height = height;
	Room::size.y = height;
}
void Room::setSize(sf::Vector2f size) {
	Room::size = size;
	Room::width = size.x;
	Room::height = size.y;
	
}

void Room::outlineVertices(sf::VideoMode& userMode) {
	Mathematics mathematics;
	Room::setWidth(0.5 * 1920);
	Room::setHeight(0.5 * 1080);
	
	Room::setSize(mathematics.floor(Room::size, 50));
	

	Room::setPosition(userMode);
	

}

void Room::setPosition(sf::VideoMode& userMode) {
	Mathematics mathematics;
	Room::position = mathematics.getCenterPosition(sf::Vector2f(1920, 1080), Room::size);

}


void Room::setGoldNumber() {
	Mathematics m;
	std::srand(time(0));
	int b = log2(((int)Room::width)/50 + ((int)Room::height)/50);

	Room::goldNumber = (int) m.rand(0, b);

}

void Room::createGold() {
	setGoldNumber();
	
	
	Mathematics m;
	std::srand(time(0)+11);
	
	for (int i = 0; i < Room::goldNumber; i++) {
		float px = m.Mathematics::rand((int)(Room::position.x), (int)(Room::position.x + Room::width));
		float py = m.Mathematics::rand((int)(Room::position.y), (int)(Room::position.y + Room::height));
		Room::gold.push_back( m.floor(sf::Vector2f(px, py), (int)Room::unit, sf::Vector2f(Room::position.x + 5, Room::position.y + 5)));
	}
	
	
}

