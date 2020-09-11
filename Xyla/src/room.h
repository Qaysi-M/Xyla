#pragma once


#include "SFML/Graphics.hpp"

#include "creature.h"

#include "player.h"
	

class Room {
	friend int main();
	friend class RoomCT;
	friend class Creature;
	friend class Player;
	friend class Enemy;
	


	const sf::Vector2f origin = sf::Vector2f(0, 0); // is the origin ( ie. (0,0) )

	sf::Vector2f size{ sf::Vector2f(0,0) }; // size is a sf::vector2f(w,h) such that w & h is the width & of the room respectively.   

	

	int doors{ 0 };
	int stairs{ 0 };

	std::list<Gold> golds;
	std::list<Enemy> enemies;
	
	sf::Vector2f vertices[4] = {origin, origin, origin, origin};
	
	float height{ 0 };
	float width{ 0 };

public:
	float unit{ 50 };
	sf::Vector2f position = origin; // upleft

	std::vector<std::vector<CreatureType>> roomMatrix;


public:

	void setWidth(float width);
	void setHeight(float height);
	void setSize(sf::Vector2f);
	void setPosition(sf::VideoMode& userMode);

	void outlineVertices(sf::VideoMode& userMode);
	void setRoomMatrix();
	

	void createGold();
	
	void createEnemies();
	void moveEnemy(Player& player); //given

	//given a creature relative position and a direction, it gives the position of that direction
	sf::Vector2i getNeighbor(sf::Vector2i cRePosition, Direction direction);

	

};

