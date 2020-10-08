#pragma once


#include "SFML/Graphics.hpp"

#include "entity.h"
#include "creature.h"

#include "player.h"
	

struct Door { // the room that the door opens to
	sf::Vector2f position;
	int neighborRoom;
	Direction neighborDirection;
};
class Room: public Entity{
	friend int main();
	friend class RoomCT;
	friend class Floor;
	friend class Creature;
	friend class Player;
	friend class Enemy;
	

	
	const sf::Vector2f origin = sf::Vector2f(0, 0); // is the origin ( ie. (0,0) )
   

	std::array<sf::Vector2f, 4> verteces = { origin ,origin ,origin ,origin }; // up left, up right, down left, down right

	
	int stairs{ 0 };

	std::list<Gold> golds;
	std::list<Enemy> enemies;
	
	float height{ 0 };
	float width{ 0 };

public:
	

	std::vector<Door> doors;
	float unit{ 30 };
	sf::Vector2f position = origin; // upleft
	sf::Vector2f size{ sf::Vector2f(0,0) }; // size is a sf::vector2f(w,h) such that w & h is the width & of the room respectively.
	sf::Vector2f center = origin;

	std::vector<std::vector<CreatureType>> roomMatrix;


public:
	void setSize(sf::Vector2f);
	void setPosition(sf::Vector2f position);
	void outlineVertices(sf::VideoMode& userMode, sf::Vector2f position, sf::Vector2f size);
	void setRoomMatrix();
	
private:	bool isInhabitable(); // checks if the room has space for a creature to live there,
public:
	void createGold();
	void createEnemies();
	void createDoors();

	void moveEnemy(Player& player); 

	//given a creature relative position and a direction, it gives the position of that direction
	sf::Vector2i getNeighbor(sf::Vector2i cRePosition, Direction direction);

	

};

