
#include "precompiled.h"

#include "mathematics.h"



sf::Vector2f Mathematics::getCenterPosition(sf::Vector2f outer, sf::Vector2f inner) {
	float px = (outer.x - inner.x) / ((float) 2);
	float py = (outer.y - inner.y) / ((float) 2);
	
	sf::Vector2f position = sf::Vector2f(px, py);

	return position;
}


sf::Vector2f Mathematics::floor(sf::Vector2f size, int b, sf::Vector2f start) {

	
	
	float x = (float)((b * (((int)(size.x - start.x)) / b)) + (int) start.x);
	float y = (float)((b * (((int)(size.y - start.y)) / b)) + (int) start.y);
	
	sf::Vector2f s = sf::Vector2f(x, y);
	return s;

}


float Mathematics::rand(int a, int b) {
	float x = (float) (std::rand() % (b - a) + 1 + a);
	return x;
}
