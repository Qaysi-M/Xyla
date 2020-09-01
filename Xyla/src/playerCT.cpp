
#include "precompiled.h"

#include "playerCT.h"


void PlayerCT::drawPlayer(sf::RenderWindow& windowView, Player& player) {
	sf::Texture playerTexture;
	playerTexture.loadFromFile("./src/textures/player.jpg");

	sf::Sprite sprite;
	sprite.setPosition(player.position);
	sprite.setTexture(playerTexture);
	
	sf::FloatRect size = sprite.getLocalBounds();  
	
	windowView.draw(sprite);
}


void PlayerCT::drawGoldCount(sf::RenderWindow& windowView, Player& player) {
	sf::Text goldCount;
	sf::Font font;
	
	font.loadFromFile("./src/fonts/jmh_typewriter/JMH Typewriter.ttf");
	goldCount.setColor(sf::Color::Yellow);
	goldCount.setFont(font);
	goldCount.setCharacterSize(24);
	std::string str= "Gold: " + std::to_string(player.gold);
	goldCount.setString(str);
	goldCount.setStyle(sf::Text::Bold | sf::Text::Underlined);

	windowView.draw(goldCount);
}


void PlayerCT::identifyKey(sf::Event& event, Room& room, Player& player) {
	
	switch (event.key.code) {
		case sf::Keyboard::Left:
			player.move(room, Player::Axis::x, Player::Direction::negative);
			break;
		case sf::Keyboard::Right:
			player.move(room, Player::Axis::x, Player::Direction::positive);
			break;
		case sf::Keyboard::Up:
			player.move(room, Player::Axis::y, Player::Direction::negative);
			break;
		case sf::Keyboard::Down:
			player.move(room, Player::Axis::y, Player::Direction::positive);
			break;
		default:
			break;
	};


}