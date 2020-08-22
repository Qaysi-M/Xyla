
#include "roomCT.h"
#include <iostream>



RoomCT::RoomCT() {

}








void RoomCT::drawRoom(sf::RenderWindow& windowView, Room room) {
	RoomCT::roomBorder = sf::RectangleShape(sf::Vector2f(room.width,room.height));
	RoomCT::roomBorder.setOutlineColor(sf::Color::Red);
	RoomCT::roomBorder.setOutlineThickness(10);
	RoomCT::roomBorder.setPosition(room.position);

	windowView.draw(roomBorder);


}












