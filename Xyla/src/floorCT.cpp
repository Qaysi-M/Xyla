#include "precompiled.h"

#include "floorCT.h"

#include <chrono>
#include <thread>

#ifdef XYLA_DEBUG
void FloorCT::drawCircle(sf::RenderWindow& windowView, Floor& floor) {
	floor.circle.setOutlineColor(sf::Color::Green);
	floor.circle.setOutlineThickness(10);

	windowView.draw(floor.circle);

}
#endif // XYLA_DEBUG

void FloorCT::drawDungen(sf::RenderWindow& windowView, Floor& floor) {
	
	for (auto& roomid : floor.livingRooms) {
		FloorCT::roomCT.drawLivingRoom(windowView, floor.rooms.at(roomid));
		//windowView.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
#ifdef XYLA_DEBUG
	for (auto& roomid : floor.dungenRooms) {
		FloorCT::roomCT.drawDungenRoom(windowView, floor.rooms.at(roomid));
		//windowView.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	/*
	for (auto& roomid : floor.hallwayRooms) {
		FloorCT::roomCT.drawHallwayRoom(windowView, floor.rooms.at(roomid));
		//windowView.display();
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	*/
#endif // XYLA_DEBUG

}




void FloorCT::drawRooms(sf::RenderWindow& windowView, Floor& floor) {

	for (auto& roomid : floor.visitedRooms) {
		FloorCT::roomCT.drawLivingRoom(windowView, floor.rooms.at(roomid));
	}
}

void FloorCT::drawDoors(sf::RenderWindow& windowView, Floor& floor) {
	for (auto& roomid : floor.visitedRooms) {
		FloorCT::roomCT.drawDoors(windowView, floor.rooms.at(roomid));
	}
}

#ifdef XYLA_DEBUG
void FloorCT::numberRooms(sf::RenderWindow& windowView, Floor& floor) {
	sf::Text roomNumber;
	sf::Font font;
	font.loadFromFile("./fonts/jmh_typewriter/JMH Typewriter.ttf");
	roomNumber.setColor(sf::Color::Magenta);
	roomNumber.setFont(font);
	roomNumber.setCharacterSize(25);
	for (auto& room : floor.rooms) {
		std::string str = std::to_string(room.first);
		roomNumber.setPosition(sf::Vector2f(room.second.position.x - room.second.unit, room.second.position.y - room.second.unit));
		roomNumber.setString(str);
		windowView.draw(roomNumber);
	}
}
#endif // XYLA_DEBUG


void FloorCT::drawEdges(sf::RenderWindow& windowView,Floor& floor, std::unordered_map<int, std::vector<int>>& AL, sf::Color color) {
	//std::array<sf::Vertex[2], 255> edges;
	for (auto& v1 : AL) {
		for (int& v2 : v1.second) {
			sf::Vertex edge[] = { sf::Vertex(floor.rooms.at(v1.first).center), sf::Vertex(floor.rooms.at(v2).center) };
			edge->color = color;
			windowView.draw(edge, 2, sf::Lines);
		}
	}
	

}



void FloorCT::drawEnemies(sf::RenderWindow& windowView, Floor& floor) {
	for (auto& roomid : floor.visitedRooms) {
		FloorCT::roomCT.drawEnemy(windowView, floor.rooms.at(roomid));
	}
}

void FloorCT::drawGolds(sf::RenderWindow& windowView, Floor& floor) {
	for (auto& roomid : floor.visitedRooms) {
		FloorCT::roomCT.drawGold(windowView, floor.rooms.at(roomid));
	}
}


void FloorCT::drawStair(sf::RenderWindow& windowView, Floor& floor) {
	for (auto& roomid : floor.visitedRooms) {
		FloorCT::roomCT.drawStair(windowView, floor.rooms.at(roomid));
	}
}


void FloorCT::drawHallways(sf::RenderWindow& windowView, Floor& floor) {
	for (auto& position : floor.visitedHallway) {
		sf::Texture texture;
		texture.loadFromFile("./textures/mesh.jpg");

		sf::Sprite sprite;
		sprite.setPosition(position);
		sprite.setTexture(texture);

		sf::FloatRect size = sprite.getLocalBounds();
		windowView.draw(sprite);
	}
}