#pragma once


#include "SFML/Graphics.hpp"

#include "entity.h"
#include "creature.h"

#include "player.h"
	

class Room: public Entity{
	friend int main();
	friend class RoomCT;
	friend class Floor;
	friend class Creature;
	friend class Player;
	friend class Enemy;
	


	const sf::Vector2f origin = sf::Vector2f(0, 0); // is the origin ( ie. (0,0) )

	sf::Vector2f size{ sf::Vector2f(0,0) }; // size is a sf::vector2f(w,h) such that w & h is the width & of the room respectively.   

	std::array<sf::Vector2f, 4> verteces = { origin ,origin ,origin ,origin }; // up left, up right, down left, down right

	

	int doors{ 0 };
	int stairs{ 0 };

	std::list<Gold> golds;
	std::list<Enemy> enemies;
	
	float height{ 0 };
	float width{ 0 };

public:

	float unit{ 20 };
	sf::Vector2f position = origin; // upleft
	sf::Vector2f center = origin;

	std::vector<std::vector<CreatureType>> roomMatrix;


public:
	void setSize(sf::Vector2f);
	inline void setPosition(sf::Vector2f position);
	void outlineVertices(sf::VideoMode& userMode, sf::Vector2f position, sf::Vector2f size);
	void setRoomMatrix();
	

	void createGold();
	
	void createEnemies();
	void moveEnemy(Player& player); 

	//given a creature relative position and a direction, it gives the position of that direction
	sf::Vector2i getNeighbor(sf::Vector2i cRePosition, Direction direction);

	

};

