

#include "SFML/Graphics.hpp"

class Mathematics {


public:
	// Assume (w1,h1) are the width and hieght of a rectangle R1 ( ie. window)  [outer rectangle]
	// Assume (w2,h2) are the width adn eheight of another rectangle R2 (room shape) [inner rectangle]
	// The, getCenterPosition returns the point (x,y) such that (x,y)
	// is the upper left point of that R2 is center of R1
	sf::Vector2f getCenterPosition(sf::Vector2f outer, sf::Vector2f inner);



	//	floor(a,b) is defined as x such that x is max({ y | y :=: b (mod b) and y <= a}).
	// :=: denotes equivlance ie. 80 :=: 40 (mod 40) ;
	// ie. floor( 50, 40) = 40 ; floor(90, 40)  = 80 etc.
	sf::Vector2f floor(sf::Vector2f, int b, sf::Vector2f start = sf::Vector2f(0, 0));


	// given two intengers, rand(a,b) givesa psudo-random between a and b
	float rand(int a, int b);

	

	


};