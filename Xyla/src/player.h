#pragma once

#include "SFML/Graphics.hpp"


#include "creature.h"
#include "room.h"



class Player : public Creature {
	friend int main();
	friend class PlayerCT;
	friend class Room;

	std::vector<Gold> golds;
	int health = 10;

	Direction direction = Direction::none;

	Room* room = nullptr;

public:
	// First time the player is created
	void setPosition(Room& room);
	
	void setDirection(Room& room, Direction);

	void moveTo(Room& room, sf::Vector2i position);

	//remove the gold from room (roomMatrix)
	void eatGold(Room& room, sf::Vector2i gRePosition);

	void setAction(Room& room, Action);

	//hits enemy and the return the life of the enemy
	void hitEnemy(Room& room, sf::Vector2i eRePosition);
};
