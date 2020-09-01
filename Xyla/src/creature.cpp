#include "precompiled.h"

#include "creature.h"

#include "mathematics.h"

void Creature::setPosition(Room& room) {

	Mathematics m;
	std::srand(time(0));
	float px = m.Mathematics::rand((int)(room.position.x), (int)(room.position.x + room.width));
	float py = m.Mathematics::rand((int)(room.position.y), (int)(room.position.y + room.height));

	Creature::position = m.floor(sf::Vector2f(px, py), (int)room.unit, sf::Vector2f(room.position.x + 5, room.position.y + 5));
}