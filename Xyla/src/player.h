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

	std::vector<Gold> golds;
	int health = 10;

	Direction direction = Direction::none;

	Room* room = nullptr;

	Door* inDoor = nullptr;
	
	


public:
	// First time the player is created
	void setPosition(Room& room);
	
	void setDirection(Game& game, Direction);

	void scan(Room& room, sf::Vector2i position);
	void move(Room& room, sf::Vector2i a, sf::Vector2i b);//move player from a to be

	//remove the gold from room (roomMatrix)
	void eatGold(Room& room, sf::Vector2i gRePosition);

	void openDoor(Room& room, sf::Vector2i dRePosition);
	void closeDoor(Room& room, sf::Vector2i dRePosition);

	void setAction(Game& game, Action);

	//hits enemy and the return the life of the enemy
	void hitEnemy(Room& room, sf::Vector2i eRePosition);

};
