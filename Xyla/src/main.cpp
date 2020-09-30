// Your First C++ Program

#include "precompiled.h"
#include "mathematics.h"
#include "game.h"
#include "floor.h"
#include <chrono>

#include <ctime>

int main() {

    Game game;

	// Coming from the user
    sf::VideoMode userMode = sf::VideoMode::getDesktopMode(); // get the userMode ie. 1920 X 1080 etc.
    sf::RenderWindow windowView;
	  

	windowView.create(userMode, "Xyla");
	
	game.createFloor(userMode);
	Floor& floor = game.floors.back();
	
	

	//game.player.setPosition(floor.rooms.back());
	int timer = time(0);
	sf::Event event;
	int i = 1;
	while (windowView.isOpen()) {
		//std::cout << "timer is " << time(0) << std::endl;
		/*
		if (time(0) > timer + i){
			i++;
			floor.rooms.back().moveEnemy(game.player);
		}
		*/
		while (windowView.pollEvent(event)) { // True if an event was polled (ie. recorded)

			if (event.type == sf::Event::Closed) {
				windowView.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				//game.playerCT.identifyKey(event, floor.rooms.back(), game.player);
				
			}
			
		}

		windowView.clear();
#ifdef XYLA_DEBUG
		game.floorCT.drawCircle(windowView, floor);
		game.floorCT.numberRooms(windowView, floor);
		//game.floorCT.drawEdges(windowView, floor, floor.adjacencyListDT, sf::Color::Blue);
		game.floorCT.drawEdges(windowView, floor, floor.adjacencyListMST, sf::Color::Red);
#endif // XYLA_DEBUG
		game.floorCT.drawDungen(windowView, floor);
		//game.roomCT.drawRoom(windowView, floor.rooms.back());

		//game.roomCT.drawGold(windowView, floor.rooms.back());

		//game.roomCT.drawEnemy(windowView, floor.rooms.back());

		//game.playerCT.drawPlayer(windowView, game.player);

		//game.playerCT.drawGoldCount(windowView, game.player);
		//game.playerCT.drawHealthCount(windowView, game.player);

		windowView.display();
	}

    return 0;
}

