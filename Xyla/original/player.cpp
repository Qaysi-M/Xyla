
#include"SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "player.h"


void Player::drawPlayer(sf::RenderWindow& windowView){
	sf::Texture playerTexture;
	


	playerTexture.loadFromFile("C:/Users/Qaysi/ProgramProjects/VSProjects/Xyla/Xyla/original/textures/player.jpg");
	
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(playerTexture);

	playerSprite.setColor(sf::Color(80,146,222,255));

	windowView.draw(playerSprite);






}