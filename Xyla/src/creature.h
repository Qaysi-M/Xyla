#pragma once

#include "SFML/Graphics.hpp"

//creature is a player, enemy, or gold

enum class Action {
	weildWeapon = 1,
};


enum class Direction {
	none = 0,
	up = -1,
	down = 1,
	left = -2,
	right = 2
};

enum class CreatureType {

	Block = 0, // something player could not walk on
	Sand = 1, // something player could walk on 
	Grass = 2, 
	Player = 2,
	Wall = 3,
	Gold = 4,
	Enemy = 5,
	Door = 6,
	Stair = 7,
};




class Creature {
	friend class Player;
	friend class Room;


public:
	const sf::Vector2f origin = sf::Vector2f(0, 0);
	sf::Vector2f position = origin; 
	sf::Vector2f size = sf::Vector2f(20, 20);

	float unit{20};
	
public:
	// set position based of the room position and size
	void initiatePosition(sf::Vector2f& rPosotion, sf::Vector2f& rSize, float& rUnit);

	std::vector<sf::Vector2i>& getNeighbors(std::vector<std::vector<CreatureType>>& roomMatrix, std::vector<sf::Vector2i>& neighbors, sf::Vector2i vertex);
};


class Gold : public Creature {
	friend class Player;
	friend class Room;

};


class Enemy : public Creature {
	friend class Player;
	friend class Room;
	int health = 3;
public:
	sf::Vector2i nextMove(std::vector<std::vector<CreatureType>>& roomMatrix, sf::Vector2i start, sf::Vector2i end); // uses breadth first search to move enemy
	



};