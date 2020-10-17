// Your First C++ Program

#include "precompiled.h"
#include "mathematics.h"
#include "game.h"
#include "gameCT.h"
#include "floor.h"
#include <chrono>

#include <ctime>

int main() {

    Game *game = new Game();
	GameCT gameCT;
	// Coming from the user
    sf::VideoMode userMode = sf::VideoMode::getDesktopMode(); // get the userMode ie. 1920 X 1080 etc.
    sf::RenderWindow windowView;
	  

	windowView.create(userMode, "Xyla");
	
	game->startGame();
	
	//game.player.setPosition(floor.rooms.back());
	int timer = time(0);
	int timer2 = time(0);
	sf::Event event;
	int i = 0.1;
	int j = 0.5;
	while (windowView.isOpen()) {
		Xyla::output(5);
		if (game->player.isAlive) {
			Floor& floor = game->floors.at(game->currentFloor);
			Room& room = floor.rooms.at(game->currentRoom);

			while (windowView.pollEvent(event)) { // True if an event was polled (ie. recorded)

				if (event.type == sf::Event::Closed) {
					windowView.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					game->playerCT.identifyKey(event, *game, game->player);

				}

			}

			if (time(0) > timer + i) {
				timer = time(0);
				game->onTick();
			}
			
			if (time(0) > timer2 + j) {
				timer2 = time(0);
				game->onWait();
			}
			
			windowView.clear();
#ifdef XYLA_DEBUG
			//game.floorCT.drawCircle(windowView, floor);
			//game.floorCT.numberRooms(windowView, floor);
			//game.floorCT.drawEdges(windowView, floor, floor.adjacencyListDT, sf::Color::Blue);
			//game.floorCT.drawEdges(windowView, floor, floor.adjacencyListMST, sf::Color::Red);
#endif // XYLA_DEBUG
		//game.floorCT.drawDungen(windowView, floor);
			game->floorCT.drawRooms(windowView, floor);
			game->floorCT.drawHallways(windowView, floor);
			game->floorCT.drawStair(windowView, floor);
			game->floorCT.drawEnemies(windowView, floor);
			game->floorCT.drawGolds(windowView, floor);
			game->floorCT.drawDoors(windowView, floor);

			game->playerCT.drawPlayer(windowView, game->player);

			game->playerCT.drawGoldCount(windowView, game->player);
			game->playerCT.drawHealthCount(windowView, game->player);
			game->playerCT.hitEnemy(windowView, game->player);

			windowView.display();
		}
		else {
			windowView.clear();
			gameCT.drawGameOver(windowView);
			windowView.display();
			while (windowView.pollEvent(event)) { // True if an event was polled (ie. recorded)

				if (event.type == sf::Event::Closed) {
					windowView.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::C:
					{
						delete(game);
						game = new Game();
						game->startGame();
					}
					}
					
				}

			}
		}
	}

    return 0;
}

