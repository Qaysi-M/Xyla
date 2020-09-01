#pragma once

#include "SFML/Graphics.hpp"


#include "creature.h"
#include "room.h"



class Player : public Creature {
	friend class PlayerCT;
	int gold{ 0 };

	Room* room = nullptr;

public:
	// First time the player is created
	void setPosition(Room& room);
	
	void move(Room& room, Axis, Direction);

	void removeGold(std::list<sf::Vector2f>& gold, sf::Vector2f& position);
};