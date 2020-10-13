
#include "precompiled.h"
#include "player.h"
#include "mathematics.h"
#include "game.h"
#include "room.h"
#include "floor.h"

void Player::setPosition(Floor& floor, Room& room){
	Player::room = &room;
	std::srand(time(0));
	float px = Xyla::rand((int)(room.position.x + room.unit), (int)(room.position.x + room.width - room.unit - 1));  //leave a space for wall on left and right of size room.unit
	float py = Xyla::rand((int)(room.position.y + room.unit), (int)(room.position.y + room.height - room.unit - 1)); //leave a space for wall on left and right of size room.unit

	Player::position = Xyla::floor(sf::Vector2f(px, py), (int)room.unit, sf::Vector2f(room.position.x, room.position.y), 5);
	sf::Vector2i pRePosition = Xyla::getRelativePosition(Player::position, floor.origin, room.unit);
	floor.gameMatrix[pRePosition.y][pRePosition.x] = CreatureType::Player;
	//room.roomMatrix[pRePosition.y][pRePosition.x] = CreatureType::Player;

	//std::cout << "player position is " << Xyla::print(Player::position) << std::endl;
	//std::cout << "player pRePosition is " << Xyla::print(pRePosition) << std::endl;
	
}

void Player::setDirection(Game& game, Direction direction) {
	Floor& floor = game.floors.at(game.currentFloor);
	Room& room = floor.rooms.at(game.currentRoom);
	Player::direction = direction;
	sf::Vector2i tRePosition = room.getNeighbor(Xyla::getRelativePosition(Player::position, floor.origin, floor.unit), direction);
	Player::scan(game, room, tRePosition);
	
}


void Player::scan(Game& game, Room& room, sf::Vector2i position) {
	Floor& floor = game.floors.at(game.currentFloor);
	if (position.x >= 0 && position.y >= 0 && position.x <= floor.gameMatrix[0].size() - 1 && position.y <= floor.gameMatrix.size() - 1) {
		switch (floor.gameMatrix[position.y][position.x]) {
		case CreatureType::Wall:
			std::cout << "you cannot move bc of wall" << std::endl;
			break;

		case CreatureType::Sand:
		{
			std::cout << "you can move bc of Sand" << std::endl;
			Player::move(floor, room, Xyla::getRelativePosition(Player::position, floor.origin, floor.unit), position);
		}
		break;
		case CreatureType::Grass:
		{
			std::cout << "you can move bc of Grass" << std::endl;
			Player::move(floor, room, Xyla::getRelativePosition(Player::position, floor.origin, floor.unit), position);
		}
		break;
		case CreatureType::Gold:
		{
			std::cout << "you can eat gold" << std::endl;
			Player::eatGold(floor, room, position);
			Player::move(floor, room, Xyla::getRelativePosition(Player::position, floor.origin, floor.unit), position);

		}
		break;
		case CreatureType::Enemy:
		{
			std::cout << "you cannot move becuase there is an enemy" << std::endl;
		}
		break;

		case CreatureType::Door:
		{
			std::cout << "you can move bc of door" << std::endl;
			Player::move(floor, room, Xyla::getRelativePosition(Player::position, floor.origin, floor.unit), position);
			Player::openDoor(game, floor, position);
		}
		break;

		case CreatureType::Stair:
		{
			game.changeFloor();
		}
		break;

		default:
			break;
		}
	}
	
	for (int i = room.position.y/floor.unit; i < (int)((room.position.y + room.height) / room.unit); ++i) {
		for (int j = room.position.x/floor.unit; j < (int)((room.position.x + room.width) / room.unit); ++j) {
			std::cout << (int)floor.gameMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
}

void Player::move(Floor& floor, Room& room, sf::Vector2i a, sf::Vector2i b) {
	floor.gameMatrix[a.y][a.x] = CreatureType::Sand;
	floor.gameMatrix[b.y][b.x] = CreatureType::Player;
	Player::position = Xyla::getGeneralPosition(b, floor.origin, floor.unit, 5);
	
	if (Player::inDoor) {
		Player::closeDoor(floor, room, sf::Vector2i(a.x, a.y));
	}
	
	floor.scanForHallway(b);
}



void Player::eatGold(Floor& floor, Room& room,sf::Vector2i gRePosition) {
	sf::Vector2f goldPosition = Xyla::getGeneralPosition(gRePosition, floor.origin, room.unit, 5);
		for (std::list<Gold>::iterator i = room.golds.begin(); i != room.golds.end(); ++i) {
			if ( goldPosition == (i)->position) {
				Player::golds.push_back(*i);
				room.golds.erase(i);
				break;
			}
		}
}

void Player::openDoor(Game& game, Floor& floor, sf::Vector2i dRePosition) {
	Player::inDoor = true;
	game.currentRoom = floor.floorMatrix[dRePosition.y][dRePosition.x].back();
	floor.visitedRooms.push_back(game.currentRoom);

}

void Player::closeDoor(Floor& floor, Room& room, sf::Vector2i dRePosition) {
	floor.gameMatrix[dRePosition.y][dRePosition.x] = CreatureType::Door;
	Player::inDoor = false;

}

void Player::setAction(Game& game, Action action) {
	Floor& floor = game.floors.at(game.currentFloor);
	Room* room = &game.floors.at(game.currentFloor).rooms.at(game.currentRoom);
	switch (action){
		case Action::weildWeapon:
			{
			
			
				sf::Vector2i pRePosition = Xyla::getRelativePosition(Player::position, floor.origin, floor.unit);
				std::cout << "pre = " << Xyla::print(pRePosition) << std::endl;
					
				sf::Vector2i eRePosition = room->getNeighbor(pRePosition, Player::direction);
				if (floor.gameMatrix[eRePosition.y][eRePosition.x] == CreatureType::Enemy) {
					Player::hitEnemy(floor, *room, eRePosition);
				}
			
			}
			break;
	default:
		break;
	}

}

void Player::hitEnemy(Floor& floor, Room& room, sf::Vector2i eRePosition) {
	sf::Vector2f enemyPosition = Xyla::getGeneralPosition(eRePosition, floor.origin, floor.unit, 5);
	
	for (std::list<Enemy>::iterator i = room.enemies.begin(); i != room.enemies.end();) {
		if (enemyPosition == i->position) {
			(i->health)--;
			std::cout << "health is " << i->health << std::endl;
			didHit = true;
			
			if (i->health == 0) {
				room.enemies.erase(i++);
				floor.gameMatrix[eRePosition.y][eRePosition.x] = CreatureType::Sand;
			}
			else { ++i; }
			
		}
		else { ++i; }
	
	}
	
}

