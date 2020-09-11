
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
	std::string str= "Gold: " + std::to_string(player.golds.size());
	goldCount.setString(str);
	goldCount.setStyle(sf::Text::Bold | sf::Text::Underlined);

	windowView.draw(goldCount);
}

void PlayerCT::drawHealthCount(sf::RenderWindow& windowView, Player& player) {
	sf::Text healthCount;
	sf::Font font;

	font.loadFromFile("./src/fonts/jmh_typewriter/JMH Typewriter.ttf");
	healthCount.setColor(sf::Color::Green);
	healthCount.setFont(font);
	healthCount.setCharacterSize(24);
	healthCount.setPosition(0, 30);
	std::string str = "health: " + std::to_string(player.health);
	healthCount.setString(str);
	healthCount.setStyle(sf::Text::Bold | sf::Text::Underlined);

	windowView.draw(healthCount);
}

void PlayerCT::identifyKey(sf::Event& event, Room& room, Player& player) {
	
	switch (event.key.code) {
		case sf::Keyboard::Left:
			player.setDirection(room, Direction::left);
			break;
		case sf::Keyboard::Right:
			player.setDirection(room, Direction::right);
			break;
		case sf::Keyboard::Up:
			player.setDirection(room, Direction::up);
			break;
		case sf::Keyboard::Down:
			player.setDirection(room, Direction::down);
			break;

		case sf::Keyboard::W:
			player.setAction(room, Action::weildWeapon);
			break;

		default:
			break;
		
	};


}