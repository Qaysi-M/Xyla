// Your First C++ Program

#include <iostream>

#include "game.h"
#include "floor.h"

int main() {

    Game game;


	// Coming from the user
    sf::VideoMode userMode = sf::VideoMode::getDesktopMode(); // get the userMode ie. 1920 X 1440 etc.
    sf::RenderWindow windowView;
  


	windowView.create(userMode, "Xyla");
	
	game.createFloor();
	Floor& floor = game.floors.back();
	floor.createRoom(userMode);


	sf::Event event;

	while (windowView.isOpen()) {
		while (windowView.pollEvent(event)) { // True if an event was returned (ie. popped) , or false if the event queue was empty

			if (event.type == sf::Event::Closed) {
				windowView.close();

			}
		}


		windowView.clear();

		game.roomCT.drawRoom(windowView, floor.rooms.back());

		

		game.player.drawPlayer(windowView);

		windowView.display();
	}

    return 0;
}

