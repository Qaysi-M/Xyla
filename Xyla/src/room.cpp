
#include "precompiled.h"

#include "mathematics.h"
#include "room.h"
#include "floor.h"
#include "creature.h"


void Room::setSize(sf::Vector2f size) {
	Room::size = size;
	Room::width = size.x;
	Room::height = size.y;
	
	Room::verteces[0] = Room::position;
	Room::verteces[1] = sf::Vector2f(Room::position.x + Room::width, Room::position.y);
	Room::verteces[2] = sf::Vector2f(Room::position.x, Room::position.y + Room::height);
	Room::verteces[3] = sf::Vector2f(Room::position.x + Room::width, Room::position.y + Room::height);

	Room::center = sf::Vector2f((Room::verteces[0].x + Room::verteces[1].x) / 2, (Room::verteces[0].y + Room::verteces[2].y) / 2);
	
}

void Room::setPosition(sf::Vector2f position) {
	Room::position = position;

	Room::verteces[0] = Room::position;
	Room::verteces[1] = sf::Vector2f(Room::position.x + Room::width, Room::position.y);
	Room::verteces[2] = sf::Vector2f(Room::position.x, Room::position.y + Room::height);
	Room::verteces[3] = sf::Vector2f(Room::position.x + Room::width, Room::position.y + Room::height);

	Room::center = sf::Vector2f((Room::verteces[0].x + Room::verteces[1].x) / 2, (Room::verteces[0].y + Room::verteces[2].y) / 2);
}

void Room::outlineVertices(sf::Vector2f position, sf::Vector2f size) {
	Room::setSize(size);
	Room::setPosition(position);
	Room::setRoomMatrix();

	

	int height = Room::roomMatrix.size();
	int width = Room::roomMatrix[0].size();
	for (int i = 0; i < width; ++i) { // set the up lower walls as a wall
		Room::roomMatrix[0][i] = CreatureType::Wall;
		Room::roomMatrix[height - 1][i] = CreatureType::Wall;
	}
	for (int i = 0; i < height; i++){
		Room::roomMatrix[i][0] = CreatureType::Wall;
		Room::roomMatrix[i][width - 1] = CreatureType::Wall;
	}
	                                                          

}

void Room::setRoomMatrix() {
	Room::roomMatrix.resize((int)((Room::height) / Room::unit));

	for (auto& row : Room::roomMatrix) {
		row.resize((int)((Room::width) / Room::unit) ); 
	}

	for (int i = 0; i < (int)((Room::height) / Room::unit); ++i) {
		for (int j = 0; j < (int)((Room::width) / Room::unit); ++j) {
			Room::roomMatrix[i][j] = CreatureType::Sand;
		}
	}

}

bool Room::isInhabitable(){
	if ((Room::position.x + Room::size.x - Room::unit) - (Room::position.x + Room::unit) > 0 &&
		(Room::position.y + Room::size.y - Room::unit) - (Room::position.y + Room::unit) > 0)
		return true;
	else
		return false;

}




void Room::createStair() {
	float px = Xyla::rand((int)(Room::position.x + Room::unit), (int)(Room::position.x + Room::size.x - Room::unit - 1));
	float py = Xyla::rand((int)(Room::position.y + Room::unit), (int)(Room::position.y + Room::size.y - Room::unit - 1));

	stair.position = Xyla::floor(sf::Vector2f(px, py), (int)Room::unit, sf::Vector2f(Room::position.x, Room::position.y), 5);

	sf::Vector2i stairRePosition = Xyla::getRelativePosition(stair.position, Room::position, Room::unit);
	Room::roomMatrix[stairRePosition.y][stairRePosition.x] = CreatureType::Stair;
}


sf::Vector2i Room::getNeighbor(sf::Vector2i cRePosition, Direction direction) {
	switch (direction){
		case Direction::up:
			return sf::Vector2i(cRePosition.x, cRePosition.y - 1);
		case Direction::down:
			return sf::Vector2i(cRePosition.x, cRePosition.y + 1);
		case Direction::left:
			return sf::Vector2i(cRePosition.x - 1, cRePosition.y);
		case Direction::right:
			return sf::Vector2i(cRePosition.x + 1, cRePosition.y);
			break;
	}
}
