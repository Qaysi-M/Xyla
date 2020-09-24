#include "precompiled.h"


#include "roomCT.h"



void RoomCT::drawLivingRoom(sf::RenderWindow& windowView, Room& room) {
	RoomCT::roomBorder = sf::RectangleShape(sf::Vector2f(room.width - 2 * room.unit, room.height - 2 * room.unit));
	RoomCT::roomBorder.setFillColor(sf::Color::Transparent);
	RoomCT::roomBorder.setOutlineColor(sf::Color::Red);
	RoomCT::roomBorder.setOutlineThickness(10);
	RoomCT::roomBorder.setPosition(sf::Vector2f(room.position.x + room.unit, room.position.y + room.unit));


	windowView.draw(roomBorder);


}
#ifdef XYLA_DEBUG
void RoomCT::drawDungenRoom(sf::RenderWindow& windowView, Room& room) {
	RoomCT::roomBorder = sf::RectangleShape(sf::Vector2f(room.width - 2 * room.unit, room.height - 2 * room.unit));
	RoomCT::roomBorder.setFillColor(sf::Color::Transparent);
	RoomCT::roomBorder.setOutlineColor(sf::Color::Blue);
	RoomCT::roomBorder.setOutlineThickness(10);
	RoomCT::roomBorder.setPosition(sf::Vector2f(room.position.x + room.unit, room.position.y + room.unit));


	windowView.draw(roomBorder);
}
#endif

void RoomCT::drawGold(sf::RenderWindow& windowView, Room& room) {

	for (std::list<Gold>::iterator it = room.golds.begin(); it != room.golds.end(); it++) {
		sf::Texture texture;
		texture.loadFromFile("./src/textures/gold.jpg");

		sf::Sprite sprite;
		sprite.setPosition((it)->position);
		sprite.setTexture(texture);

		sf::FloatRect size = sprite.getLocalBounds();
		windowView.draw(sprite);
	}

}

void RoomCT::drawEnemy(sf::RenderWindow& windowView, Room& room) {

	for (std::list<Enemy>::iterator it = room.enemies.begin(); it != room.enemies.end(); it++) {
		sf::Texture texture;
		texture.loadFromFile("./src/textures/enemy.jpg");

		sf::Sprite sprite;
		sprite.setPosition((it)->position);
		sprite.setTexture(texture);

		sf::FloatRect size = sprite.getLocalBounds();
		windowView.draw(sprite);
	}

}










