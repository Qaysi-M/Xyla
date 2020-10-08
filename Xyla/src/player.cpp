
#include "precompiled.h"
#include "player.h"
#include "mathematics.h"
#include "game.h"
#include "room.h"
#include "floor.h"

void Player::setPosition(Room& room){
	Player::room = &room;
	std::srand(time(0));
	float px = Xyla::rand((int)(room.position.x + room.unit), (int)(room.position.x + room.width - room.unit - 1));  //leave a space for wall on left and right of size room.unit
	float py = Xyla::rand((int)(room.position.y + room.unit), (int)(room.position.y + room.height - room.unit - 1)); //leave a space for wall on left and right of size room.unit


	Player::position = Xyla::floor(sf::Vector2f(px, py), (int)room.unit, sf::Vector2f(room.position.x, room.position.y), 5);
	sf::Vector2i pRePosition = Xyla::getRelativePosition(Player::position, room.position, room.unit);
	room.roomMatrix[pRePosition.y][pRePosition.x] = CreatureType::Player;

	std::cout << "player position is " << Xyla::print(Player::position) << std::endl;
	std::cout << "player pRePosition is " << Xyla::print(pRePosition) << std::endl;
	
}

void Player::setDirection(Game& game, Direction direction) {
	Floor& floor = game.floors.at(game.currentFloor);

	if (Player::inDoor != nullptr && Player::inDoor->neighborDirection == direction) {
		Room& room1 = floor.rooms.at(game.currentRoom);
		Player::closeDoor(room1, Xyla::getRelativePosition(Player::position, room1.position, room1.unit));
		game.currentRoom = Player::inDoor->neighborRoom;
		Room& room2 = floor.rooms.at(game.currentRoom);
		Player::openDoor(room2, Xyla::getRelativePosition(Player::position, room2.position, room2.unit));
	}
	{
		Room& room = floor.rooms.at(game.currentRoom);
		Player::direction = direction;
		sf::Vector2i tRePosition = room.getNeighbor(Xyla::getRelativePosition(Player::position, room.position, room.unit), direction);
		Player::scan(room, tRePosition);
	}

}

void Player::scan(Room& room, sf::Vector2i position) {
	switch (room.roomMatrix[position.y][position.x]){
		case CreatureType::Wall :
			std::cout << "you cannot move bc of wall" << std::endl;
			break;
		
		case CreatureType::None : 
			{
				std::cout << "you can move bc of None" << std::endl;
				Player::move(room, Xyla::getRelativePosition(Player::position, room.position, room.unit), position);
			}	
			break;
		case CreatureType::Gold : 
			{ 
				std::cout << "you can eat gold" << std::endl;
				Player::eatGold(room, position);
				Player::move(room, Xyla::getRelativePosition(Player::position, room.position, room.unit), position);
				
			}
			break;
		case CreatureType::Enemy :
			{	
				std::cout << "you cannot move becuase there is an enemy" << std::endl;
			}
			break;
		
		case CreatureType::Door :
			{
				std::cout << "you can move bc of door" << std::endl;
				Player::move(room, Xyla::getRelativePosition(Player::position, room.position, room.unit), position);
				Player::openDoor(room, position);
			}
			break;

		default:
			break;
	}

	

	for (int i = 0; i < (int)((room.height) / room.unit); ++i) {
		for (int j = 0; j < (int)((room.width) / room.unit); ++j) {
			std::cout << (int)room.roomMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void Player::move(Room& room, sf::Vector2i a, sf::Vector2i b) {
	room.roomMatrix[a.y][a.x] = CreatureType::None;
	room.roomMatrix[b.y][b.x] = CreatureType::Player;
	Player::position = Xyla::getGeneralPosition(b, room.position, room.unit, 5);
	
	if (Player::inDoor != nullptr) {
		room.roomMatrix[a.y][a.x] = CreatureType::Door;
		Player::inDoor = nullptr;
	}
	
}



void Player::eatGold(Room& room,sf::Vector2i gRePosition) {
	sf::Vector2f goldPosition = Xyla::getGeneralPosition(gRePosition, room.position, room.unit, 5);
		for (std::list<Gold>::iterator i = room.golds.begin(); i != room.golds.end(); ++i) {
			if ( goldPosition == (i)->position) {
				Player::golds.push_back(*i);
				room.golds.erase(i);
				break;
			}
		}
}

void Player::openDoor(Room& room, sf::Vector2i dRePosition) {
	sf::Vector2f doorPosition = Xyla::getGeneralPosition(dRePosition, room.position, room.unit);

	for (auto& door : room.doors) {
		if (doorPosition == door.position) {
			Player::inDoor = &door;
			break;
		}
	}
}

void Player::closeDoor(Room& room, sf::Vector2i dRePosition) {
	Player::inDoor == nullptr;
	room.roomMatrix[dRePosition.y][dRePosition.x] = CreatureType::Gold;

}

void Player::setAction(Game& game, Action action) {
	Room* room = &game.floors.at(game.currentFloor).rooms.at(game.currentRoom);
	switch (action){
		case Action::weildWeapon:
			{
				if (Player::inDoor != nullptr && Player::inDoor->neighborDirection == Player::direction)
					room = &game.floors.at(game.currentFloor).rooms.at(Player::inDoor->neighborRoom);
			
				sf::Vector2i pRePosition = Xyla::getRelativePosition(Player::position, room->position, room->unit);
				std::cout << "pre = " << Xyla::print(pRePosition) << std::endl;
					
				sf::Vector2i eRePosition = room->getNeighbor(pRePosition, Player::direction);
				if (room->roomMatrix[eRePosition.y][eRePosition.x] == CreatureType::Enemy) {
					Player::hitEnemy(*room, eRePosition);
				}
			
			}
			break;
	default:
		break;
	}

}

void Player::hitEnemy(Room& room, sf::Vector2i eRePosition) {
	sf::Vector2f enemyPosition = Xyla::getGeneralPosition(eRePosition, room.position, room.unit, 5);
	
	for (std::list<Enemy>::iterator i = room.enemies.begin(); i != room.enemies.end();) {
		if (enemyPosition == i->position) {
			(i->health)--;
			std::cout << "health is " << i->health << std::endl;
			
			if (i->health == 0) {
				room.enemies.erase(i++);
				room.roomMatrix[eRePosition.y][eRePosition.x] = CreatureType::None;
			}
			else { ++i; }
			
		}
		else { ++i; }
	
	}
	
}

