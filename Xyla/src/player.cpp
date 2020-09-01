
#include "precompiled.h"
#include "player.h"
#include "mathematics.h"

void Player::setPosition(Room& room){
	Player::room = &room;
	Mathematics m;
	std::srand(time(0));
	float px = m.Mathematics::rand((int)(room.position.x), (int)(room.position.x + room.width));
	float py = m.Mathematics::rand((int)(room.position.y), (int)(room.position.y + room.height));

	Player::position = m.floor(sf::Vector2f(px, py), (int)room.unit, sf::Vector2f(room.position.x + 5, room.position.y + 5));
}

void Player::move(Room& room, Player::Axis axis, Player::Direction direction) {
	if (axis == Player::Axis::x) {
		if (direction == Player::Direction::negative) {
			if (room.position.x <= (Player::position.x - room.unit)) {
				#ifdef XYLA_DEBUG
					std::cout << "you can move left ";
				#endif
				Player::position.x = (Player::position.x - room.unit);
				Player::removeGold(room.gold, Player::position);
				
				
			}
			else {
				#ifdef XYLA_DEBUG
					std::cout << "you cannot move left ";
				#endif // DEBUG
			}
		}
		else {
			if (room.position.x + room.width >= Player::position.x + room.unit) {
				#ifdef XYLA_DEBUG 
					std::cout << "you can move right ";
				#endif
				Player::position.x = (Player::position.x + room.unit);
				Player::removeGold(room.gold, Player::position);
			}
			else {
				#ifdef XYLA_DEBUG
				std::cout << "you cannot move right ";
				#endif // DEBUG

			}
			

		}

		
	}
	else if (axis == Player::Axis::y) {
		if (direction == Player::Direction::negative) {
			if (room.position.y <= (Player::position.y - room.unit)) {
				#ifdef XYLA_DEBUG
				std::cout << "you can move up ";
				#endif // DEBUG
				Player::position.y = (Player::position.y - room.unit);
				Player::removeGold(room.gold, Player::position);
			}
			else {
				#ifdef XYLA_DEBUG
				std::cout << "you cannot move up ";
				#endif
			}
		}
		else {
			if (room.position.y + room.height >= Player::position.y + room.unit) {
				#ifdef XYLA_DEBUG
					std::cout << "you can move down ";
				#endif
				Player::position.y = (Player::position.y + room.unit);
				Player::removeGold(room.gold, Player::position);
			}
			else {
				#ifdef XYLA_DEBUG
					std::cout << "you cannot move down ";
				#endif
			}


		}


	}


}


void Player::removeGold(std::list<sf::Vector2f>& gold,sf::Vector2f& position) {
	for (std::list<sf::Vector2f>::iterator i = gold.begin(); i != gold.end(); ++i) {
		if (*i == position) {
			gold.erase(i);
			++Player::gold;
			break;
		}
		
	}

}




