#include "precompiled.h"


#include "roomCT.h"



void RoomCT::drawRoom(sf::RenderWindow& windowView, Room room) {
	RoomCT::roomBorder = sf::RectangleShape(sf::Vector2f(room.width,room.height));
	RoomCT::roomBorder.setFillColor(sf::Color::Transparent);
	RoomCT::roomBorder.setOutlineColor(sf::Color::Red);
	RoomCT::roomBorder.setOutlineThickness(5);
	RoomCT::roomBorder.setPosition(room.position);

	windowView.draw(roomBorder);


}

void RoomCT::drawGold(sf::RenderWindow& windowView, Room room) {
	for (std::list<sf::Vector2f>::iterator it = room.gold.begin(); it != room.gold.end(); it++) {
		sf::Texture texture;
		texture.loadFromFile("./src/textures/gold.jpg");

		sf::Sprite sprite;
		sprite.setPosition(*it);
		sprite.setTexture(texture);

		sf::FloatRect size = sprite.getLocalBounds();

		windowView.draw(sprite);
	}
}










