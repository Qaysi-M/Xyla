
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

void Room::setPosition(sf::VideoMode& userMode) {
	Room::position = Xyla::getCenterPosition(sf::Vector2f(1920, 1080), Room::size);

}

void Room::outlineVertices(sf::VideoMode& userMode) {
	Room::setSize(Xyla::floor(sf::Vector2f(userMode.width * 0.50, userMode.height * 0.5), Room::unit));
	Room::setRoomMatrix();
	Room::setPosition(userMode);

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



void Room::createGold() {

	std::srand(time(0));
	int b = (((int)Room::width) / Room::unit + ((int)Room::height) / Room::unit)/3;
	int goldNumber = (int)Xyla::rand(0, b);
	
	
	std::srand(time(0) + 11);
	for (int i = 0; i <= goldNumber; ++i) {
		Gold gold;
		gold.setPosition(Room::position, Room::size, Room::unit);
		sf::Vector2i goldPosition = Xyla::getRelativePosition(gold.position, Room::position, Room::unit);
		Room::golds.push_back(gold);
		Room::roomMatrix[goldPosition.y][goldPosition.x] = CreatureType::Gold;
	}

}

void Room::createEnemies() {
	std::srand(time(0) + (int) CreatureType::Enemy);
	int b = (((int)Room::width) / Room::unit + ((int)Room::height) / Room::unit) / 6;
	int enemyNumber = (int)Xyla::rand(0, b);
	for (int i = 0; i <= enemyNumber; ++i) {
		Enemy enemy;
		enemy.setPosition(Room::position, Room::size, Room::unit);
		sf::Vector2i enemyPosition = Xyla::getRelativePosition(enemy.position, Room::position, Room::unit);
		if (Room::roomMatrix[enemyPosition.y][enemyPosition.x] == CreatureType::None) {
			Room::enemies.push_back(enemy);
			Room::roomMatrix[enemyPosition.y][enemyPosition.x] = CreatureType::Enemy;
		}
		else{
			--i;
		}
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

			sf::Vector2i nextMove = it->nextMove(Room::roomMatrix, Xyla::getRelativePosition(it->position, Room::position, Room::unit),
				Xyla::getRelativePosition(player.position, Room::position, Room::unit));
			if (roomMatrix[nextMove.y][nextMove.x] != CreatureType::Player) {
				sf::Vector2i rePosition = Xyla::getRelativePosition(it->position, Room::position, Room::unit);
				roomMatrix[rePosition.y][rePosition.x] = CreatureType::None;
				it->position = Xyla::getGeneralPosition(nextMove, Room::position, Room::unit, 5);
				roomMatrix[nextMove.y][nextMove.x] = CreatureType::Enemy;
			}
			else {
				if (--player.health == 0)
					break;
			}

		}

}