

#include "SFML/Graphics.hpp"
#include "room.h"

namespace Xyla {
	// Assume (w1,h1) are the width and hieght of a rectangle R1 ( ie. window)  [outer rectangle]
	// Assume (w2,h2) are the width adn eheight of another rectangle R2 (room shape) [inner rectangle]
	// The, getCenterPosition returns the point (x,y) such that (x,y)
	// is the upper left point of that R2 is center of R1
	sf::Vector2f getCenterPosition(sf::Vector2f outer, sf::Vector2f inner);


	//	floor(a,b) is defined as x such that x is max({ y | y :=: b (mod b) and y <= a}).
	// :=: denotes equivlance ie. 80 :=: 40 (mod 40) ;
	// ie. floor( 50, 40) = 40 ; floor(90, 40)  = 8 ; floor(90,40, 10) = 80
	sf::Vector2f floor(sf::Vector2f, int b, sf::Vector2f start = sf::Vector2f(0, 0), int indentation=0);

	float floor(float a, int b, float start = 0, int indentation = 0);

	// given two intengers, rand(a,b) givesa psudo-random between a and b (includes a and b)
	float rand(int a, int b);


	
	//Gives the position of a relative to b in an increment of u
	//For example, if a=40 and b=30 and u =2, then getRelativePosition(a,b,u) = 5
	sf::Vector2i getRelativePosition(sf::Vector2f& a, sf::Vector2f& b , float u = 30);

	//This is oppoistie of getRelativePosition
	sf::Vector2f getGeneralPosition(sf::Vector2i& a, sf::Vector2f& b, float u, float indentation = 0);

	template<typename T>
	void output(T out) {
		std::cout << out << std::endl;
	}
	
	char print(sf::Vector2f v);
	char print(sf::Vector2i v);

	char print(std::vector<int>& v);



	float getDistance(sf::Vector2f& a, sf::Vector2f& b);

	//given two interval (a1, b1) and (a2, b2), it return interval where those intervals intersect provided that the two intervals intersect
	std::vector<float> getIntersectingIntervals(float a1, float b1, float a2, float b2);

	
};