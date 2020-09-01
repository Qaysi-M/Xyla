// Your First C++ Program

#include "precompiled.h"

#include "game.h"
#include "floor.h"

int main() {

    Game game;


	// Coming from the user
    sf::VideoMode userMode = sf::VideoMode::getDesktopMode(); // get the userMode ie. 1920 X 1080 etc.
    sf::RenderWindow windowView;
	  


	windowView.create(userMode, "Xyla");
	
	game.createFloor();
	Floor& floor = game.floors.back();
	floor.createRoom(userMode);

	game.player.setPosition(floor.rooms.back());


	
	sf::Event event;
	while (windowView.isOpen()) {
	
		while (windowView.pollEvent(event)) { // True if an event was polled (ie. recorded)

			if (event.type == sf::Event::Closed) {
				windowView.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				game.playerCT.identifyKey(event, floor.rooms.back(), game.player);
				
			}
			
		}


		windowView.clear();
		
		game.roomCT.drawRoom(windowView, floor.rooms.back());

		game.roomCT.drawGold(windowView, floor.rooms.back());

		game.playerCT.drawPlayer(windowView, game.player);
		game.playerCT.drawGoldCount(windowView, game.player);
		

		windowView.display();
	}

    return 0;
}

