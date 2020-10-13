#pragma once

#include "SFML/Graphics.hpp"


#include "creature.h"



class Game;
class Room;
class Floor;
struct Door;
class Player : public Creature {
	friend int main();
	friend class PlayerCT;
	friend class Room;
	friend class Floor;
	friend class Game;

	std::vector<Gold> golds;
	int health = 10;

	Direction direction = Direction::none;
	bool isAlive = true;
	bool didHit = false;
	Room* room = nullptr;

	bool inDoor = false;
	
	


public:
	// First time the player is created
	void setPosition(Floor& floor, Room& room);
	
	void setDirection(Game& game, Direction);

	void scan(Game& game, Room& room, sf::Vector2i position);
	void move(Floor& floor, Room& room, sf::Vector2i a, sf::Vector2i b);//move player from a to be

	//remove the gold from room (roomMatrix)
	void eatGold(Floor& floor, Room& room, sf::Vector2i gRePosition);

	void openDoor(Game& game,Floor& floor,  sf::Vector2i dRePosition);
	void closeDoor(Floor& floor, Room& room, sf::Vector2i dRePosition);

	void setAction(Game& game, Action);

	//hits enemy and the return the life of the enemy
	void hitEnemy(Floor& floor, Room& room, sf::Vector2i eRePosition);

};
