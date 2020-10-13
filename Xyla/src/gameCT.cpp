

#include "precompiled.h"
#include "mathematics.h"
#include "gameCT.h"


void GameCT::drawGameOver(sf::RenderWindow& windowView) {
	sf::Texture texture;
	texture.loadFromFile("./textures/gameOver.jpg");
	sf::Sprite sprite;
	sprite.setPosition(Xyla::getCenterPosition(sf::Vector2f(1920, 1080), (sf::Vector2f) texture.getSize()));
	sprite.setTexture(texture);

	sf::FloatRect size = sprite.getLocalBounds();
	windowView.draw(sprite);

	sf::Text text;
	sf::Font font;

	font.loadFromFile("./fonts/jmh_typewriter/JMH Typewriter.ttf");
	text.setColor(sf::Color::Green);
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(0, 30);
	std::string str = "press c to start a new game or exit the game";
	text.setString(str);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	windowView.draw(text);



}
