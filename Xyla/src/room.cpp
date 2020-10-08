
#include "precompiled.h"

#include "mathematics.h"
#include "room.h"

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

void Room::outlineVertices(sf::VideoMode& userMode, sf::Vector2f position, sf::Vector2f size) {
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
			Room::roomMatrix[i][j] = CreatureType::None;
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


void Room::createGold() {
	if (Room::isInhabitable()) {
		std::srand(time(0) + (int)CreatureType::Gold);
		int b = (((int)Room::width) / Room::unit + ((int)Room::height) / Room::unit) / 10;
		int goldNumber = (int)Xyla::rand(0, b);

		std::srand(time(0) + 11);
		for (int i = 0; i <= goldNumber; ++i) {
			Gold gold;
			gold.initiatePosition(Room::position, Room::size, Room::unit);
			sf::Vector2i goldPosition = Xyla::getRelativePosition(gold.position, Room::position, Room::unit);
			Room::golds.push_back(gold);
			Room::roomMatrix[goldPosition.y][goldPosition.x] = CreatureType::Gold;
		}
	}
}

void Room::createEnemies() {
	if (Room::isInhabitable()) {
		std::srand(time(0) + (int)CreatureType::Enemy);
		int b = (((int)Room::width) / Room::unit + ((int)Room::height) / Room::unit) / 15;
		int enemyNumber = (int)Xyla::rand(0, b);
		for (int i = 0; i <= enemyNumber; ++i) {
			Enemy enemy;
			enemy.initiatePosition(Room::position, Room::size, Room::unit);
			sf::Vector2i enemyPosition = Xyla::getRelativePosition(enemy.position, Room::position, Room::unit);

			if (Room::roomMatrix[enemyPosition.y][enemyPosition.x] == CreatureType::None) {
				Room::enemies.push_back(enemy);
				Room::roomMatrix[enemyPosition.y][enemyPosition.x] = CreatureType::Enemy;
			}
			else {
				//--i;
			}
		}
	}
}



void Room::createDoors() {
	for (auto& door : Room::doors) {
		sf::Vector2i doorRePosition = Xyla::getRelativePosition(door.position, Room::position, Room::unit);
		Room::roomMatrix[doorRePosition.y][doorRePosition.x] = CreatureType::Door;
	}
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


void Room::moveEnemy(Player& player) {
		for (std::list<Enemy>::iterator it = Room::enemies.begin(); it != Room::enemies.end(); ++it) {
			std::cout << "enemy rp = " << Xyla::print(Xyla::getRelativePosition(it->position, Room::position, Room::unit)) << std::endl;
			std::cout << "player rp = " << Xyla::print(Xyla::getRelativePosition(player.position, Room::position, Room::unit)) << std::endl;
			sf::Vector2i nextMove = it->nextMove(Room::roomMatrix, Xyla::getRelativePosition(it->position, Room::position, Room::unit),
				Xyla::getRelativePosition(player.position, Room::position, Room::unit));
			//std::cout << "next move = " << Xyla::print(nextMove) << std::endl;
			if (roomMatrix[nextMove.y][nextMove.x] != CreatureType::Player ) {
				if (roomMatrix[nextMove.y][nextMove.x] == CreatureType::None){
					sf::Vector2i rePosition = Xyla::getRelativePosition(it->position, Room::position, Room::unit);
					roomMatrix[rePosition.y][rePosition.x] = CreatureType::None;
					it->position = Xyla::getGeneralPosition(nextMove, Room::position, Room::unit, 5);
					roomMatrix[nextMove.y][nextMove.x] = CreatureType::Enemy;
				}
			}
			else {
				if (--player.health == 0)
					break;
			}

		}

}