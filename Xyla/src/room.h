#pragma once


#include "SFML/Graphics.hpp"

	

class Room {
	friend class RoomCT;
	friend class Creature;
	friend class Player;
	friend class Enemy;

	const sf::Vector2f origin = sf::Vector2f(0, 0); // is the origin ( ie. (0,0) )

	sf::Vector2f size{ sf::Vector2f(0,0) }; // size is a sf::vector2f(w,h) such that w & h is the width & of the room respectively.   

	float unit{ 50 };

	int doors{ 0 };
	int enemies{ 0 };
	int goldNumber{ 0 };
	int stairs{ 0 };

	std::list<sf::Vector2f> gold;

	sf::Vector2f vertices[4] = {origin, origin, origin, origin};
	
	float height{ 0 };
	float width{ 0 };
	sf::Vector2f position = origin; // upleft


public:

	void setWidth(float width);
	void setHeight(float height);
	void setSize(sf::Vector2f);


	void outlineVertices(sf::VideoMode& userMode);
	void setPosition(sf::VideoMode& userMode);

	void setGoldNumber();
	void createGold();


};