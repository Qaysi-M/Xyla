
#include "precompiled.h"

#include "mathematics.h"



sf::Vector2f Xyla::getCenterPosition(sf::Vector2f outer, sf::Vector2f inner) {
	float px = (outer.x - inner.x) / ((float) 2);
	float py = (outer.y - inner.y) / ((float) 2);
	
	sf::Vector2f position = sf::Vector2f(px, py);

	return position;
}


sf::Vector2f Xyla::floor(sf::Vector2f size, int b, sf::Vector2f start, int indentation) {
	float x = (float)((b * (((int)(size.x - start.x)) / b) + (int) start.x + indentation));
	float y = (float)((b * (((int)(size.y - start.y)) / b) + (int) start.y + indentation));
	
	sf::Vector2f s = sf::Vector2f(x, y);
	return s;

}

float Xyla::floor(float a, int b, float start, int indentation) {
	return (float)((b * (((int)(a - start)) / b) + (int)start + indentation));

}

float Xyla::rand(int a, int b) {
	if (a <= b) {
		float x = (float)(std::rand() % (b - a + 1) + a);
		return x;
	}
	else 
		return 0;
}


sf::Vector2i Xyla::getRelativePosition(sf::Vector2f& a, sf::Vector2f& b, float u) {
	int x = (int)((a.x - b.x) / u);
	int y = (int)((a.y - b.y) / u);
	return sf::Vector2i(x, y); // (x,y) := as x is the number of column, y is the number of rows
}


sf::Vector2f Xyla::getGeneralPosition(sf::Vector2i& a, sf::Vector2f& b, float u, float indentation) {
	float x = b.x + ((float)a.x * u) + indentation;  //
	float y = b.y + ((float)a.y * u) + indentation; 
	return sf::Vector2f(x, y);
}



char Xyla::print(sf::Vector2f v) {
	std::cout << "(" << v.x << ", " << v.y << ")";
	return NULL;
}

char Xyla::print(sf::Vector2i v) {
	std::cout << "(" << v.x << ", " << v.y << ")";
	return NULL;
}

char Xyla::print(std::vector<int>& v) {
	using namespace std;
	cout << "( ";
	for (auto& v : v)
		cout << v << ", ";
	cout << ")" << endl;

	return NULL;
}


float Xyla::getDistance(sf::Vector2f& a, sf::Vector2f& b) {
	float d = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	return d;
}


std::vector<float> Xyla::getIntersectingIntervals(float a1, float b1, float a2, float b2) {
	float a, b;

	if (abs(b2 - a1) < abs(a2 - b1)) {
		a = std::max(a1, a2);
		b = std::min(std::min((abs(b2 - a1)), abs(b1 - a1)), abs( b2 -a2));
	}
	else {
		a = std::max(a1, a2);
		b = std::min(std::min((abs(b1 - a2)), abs(b1 - a1)), abs(b2 - a2));
	}

	return std::vector<float> {a, a + b};

}