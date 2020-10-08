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
	
	game.startGame(userMode);
	

	//game.player.setPosition(floor.rooms.back());
	int timer = time(0);
	sf::Event event;
	int i = 1;
	while (windowView.isOpen()) {
		Floor& floor = game.floors.at(game.currentFloor);
		Room& room = floor.rooms.at(game.currentRoom);

		
		while (windowView.pollEvent(event)) { // True if an event was polled (ie. recorded)

			if (event.type == sf::Event::Closed) {
				windowView.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				game.playerCT.identifyKey(event, game,game.player);
				
			}
			
		}

		if (time(0) > timer + i) {
			i++;
			game.onTick();
		}
	
		windowView.clear();
#ifdef XYLA_DEBUG
		game.floorCT.drawCircle(windowView, floor);
		game.floorCT.numberRooms(windowView, floor);
		//game.floorCT.drawEdges(windowView, floor, floor.adjacencyListDT, sf::Color::Blue);
		//game.floorCT.drawEdges(windowView, floor, floor.adjacencyListMST, sf::Color::Red);
#endif // XYLA_DEBUG
		game.floorCT.drawDungen(windowView, floor);
		game.floorCT.drawDoors(windowView, floor);

		game.floorCT.drawEnemies(windowView, floor);
		game.floorCT.drawGolds(windowView, floor);
		//Room& room = floor.rooms.at(game.currentRoom);
		//game.roomCT.drawRoom(windowView, room);

		//game.roomCT.drawGold(windowView, room);

		//game.roomCT.drawEnemy(windowView, room);

		game.playerCT.drawPlayer(windowView, game.player);

		game.playerCT.drawGoldCount(windowView, game.player);
		game.playerCT.drawHealthCount(windowView, game.player);

		windowView.display();
	}

    return 0;
}

