#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"


class PlayerCT{


public:
	void drawPlayer(sf::RenderWindow& windowView, Player& player);

	void drawGoldCount(sf::RenderWindow& windowView, Player& player);
	void drawHealthCount(sf::RenderWindow& windowView, Player& player);

	void identifyKey(sf::Event& event,Game& game, Player& player);
	



};