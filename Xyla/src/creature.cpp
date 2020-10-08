#include "precompiled.h"

#include "creature.h"

#include "mathematics.h"


void Creature::initiatePosition(sf::Vector2f& rPosition, sf::Vector2f& rSize, float& rUnit) {
	float px = Xyla::rand((int)(rPosition.x + rUnit), (int)(rPosition.x + rSize.x - rUnit - 1));
	float py = Xyla::rand((int)(rPosition.y + rUnit), (int)(rPosition.y + rSize.y - rUnit - 1));
	Creature::position = Xyla::floor(sf::Vector2f(px, py), (int)rUnit, sf::Vector2f(rPosition.x, rPosition.y), 5);	
	
}


std::vector<sf::Vector2i>& Creature::getNeighbors(std::vector<std::vector<CreatureType>>& roomMatrix, std::vector<sf::Vector2i>& neighbors, sf::Vector2i vertex) {
	if (vertex.x > 0) {
		if (roomMatrix[vertex.y][vertex.x - 1] == CreatureType::None || roomMatrix[vertex.y][vertex.x - 1] == CreatureType::Player)
			neighbors.push_back(sf::Vector2i(vertex.x - 1, vertex.y));
	}
	if (vertex.x < roomMatrix[0].size() - 1) {
		if(roomMatrix[vertex.y][vertex.x + 1] == CreatureType::None || roomMatrix[vertex.y][vertex.x + 1] == CreatureType::Player)
			neighbors.push_back(sf::Vector2i(vertex.x + 1, vertex.y));
	}
	if (vertex.y > 0) {
		if (roomMatrix[vertex.y - 1][vertex.x] == CreatureType::None || roomMatrix[vertex.y - 1][vertex.x] == CreatureType::Player)
			neighbors.push_back(sf::Vector2i(vertex.x, vertex.y - 1));
	}
	if (vertex.y < roomMatrix.size() - 1) {
		if (roomMatrix[vertex.y + 1][vertex.x] == CreatureType::None || roomMatrix[vertex.y + 1][vertex.x] == CreatureType::Player)
			neighbors.push_back(sf::Vector2i(vertex.x, vertex.y + 1));
	}
	
	return neighbors;
}

sf::Vector2i Enemy::nextMove(std::vector<std::vector<CreatureType>>& roomMatrix, sf::Vector2i start, sf::Vector2i end) {

	struct Parent {
		sf::Vector2i vertex;
		Parent *parent;
		Parent(sf::Vector2i vertex, Parent* parent) {
			this->vertex = vertex;
			this->parent = parent;
		}
	};

	std::vector<sf::Vector2i> neighbors;
	std::queue<Parent*> Q;
	std::vector<sf::Vector2i> visited;
	std::vector<Parent*> parents;

	visited.push_back(start);
	Parent* p1 = new Parent(start, nullptr);
	parents.push_back(p1);
	Q.push(p1);
	
	while (!Q.empty()){
		Parent* q = Q.front();
		Enemy::getNeighbors(roomMatrix, neighbors, q->vertex);
		Q.pop();
		for (sf::Vector2i& v : neighbors) {
			if (std::find(visited.begin(), visited.end(), v) == visited.end()) { //check if v is not in visited
				visited.push_back(v);
				Parent* p = new Parent(v, q);
				parents.push_back(p);
				if (v == end)
					goto end;
				Q.push(p);
			}
		}
		neighbors.clear();
	}

end:
	sf::Vector2i nextMove;
	Parent* p = parents.back();
	while ( p != p1){ //p1 is the start parent
		nextMove = p->vertex;
		p = p->parent;
		std::cout << Xyla::print(nextMove) << " ";
	}
	std::cout << std::endl;

	for (auto& p : parents) {
		delete(p);
	}
	
	return nextMove;
	
}