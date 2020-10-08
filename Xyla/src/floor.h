#pragma once

#include "entity.h"

#include "room.h"

#include "SFML/Graphics/CircleShape.hpp"




class Floor : public Entity{
	friend int main();
	friend class Game;
	friend class Player;
	friend class FloorCT;
	std::unordered_map<int, Room> rooms;


	int heighestRoomId{ 1};
	std::vector<int> livingRooms; // rooms that are visible
	std::vector<int> dungenRooms; // Hallway rooms ie. rooms that are hallways to living rooms
	std::vector<int> allRooms;  // union of livingRooms and dungenRooms
	float unit{ 30 };
	std::vector<std::vector<std::list<int>>> floorMatrix;
	
	sf::CircleShape circle;

public:

	Floor();
	void printMatrix();


	void addRoomtoMatrix(sf::Vector2f position, float width, float height, int unit, int roomId); //set room area in floorMatrix
	void removeRoomFromMatrix(sf::Vector2f position, float width, float height, int unit, int roomId); //set room area in floorMatrix


private:	
	void createRoom(sf::VideoMode& userMode, sf::CircleShape circle);

public:
	void createDungen(sf::VideoMode& userMode);
	void seperateRooms(sf::VideoMode& userMode);
	void setLivingAndDungenRooms(sf::VideoMode& userMode);
	
	
	
	
private:
	
	
	std::unordered_map<int, std::vector<int>> adjacencyList;

	// to sort vertices such that v1 is before v2 iff v1.x < v2.x or (v1.x == v2.x and v1.y < v2.y)
	std::vector<int> mergeSort(std::vector<int>& v);
	std::vector<int> merge(std::vector<int>& vl, std::vector<int>& vr);

	//find the orientation ( clockwise or counter clock wise of the curve starting from p, passing q, and ending at r
	// it will be used in constructing the convex hull
	//return 0 if colinear, 1 if counter clockwise, 2 if clockwises
	int findOrientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);

	std::vector<int> constructConvexHull(std::vector<int> v);




	std::unordered_map<int, std::vector<int>> adjacencyListDT; // adjacency list for delaunay triangulations
	std::unordered_map<int, std::vector<int>> adjacencyListMST; // adjacency list for minumem spaning tree;

	std::vector<std::array<int, 2>> edgesDT;
	std::vector<std::array<int, 2>> edgesMST;
#ifdef XYLA_DEBUG
	void printAL(std::unordered_map<int, std::vector<int>>& AL);  // print the adjacencylist
	void printEdges(std::vector<std::array<int, 2>>&);
#endif // XYLA_DEBUG


	// insert a into the adjacency of b
	// insert b into the adjacency of a
	void insert(int a, int b, std::unordered_map<int, std::vector<int>>& AL);
	// delete a from the adjacency of b
	// delete b from the adjacency of a
	void deletee(int a, int b, std::unordered_map<int, std::vector<int>>& AL);

	// it gets predecessor of b in the adjacency list of a
	int pred(int a, int b, std::unordered_map<int, std::vector<int>>& AL);
	// it gets successor  of b in the adjacency list of a
	int succ(int a, int b, std::unordered_map<int, std::vector<int>>& AL);



public:
	//find common bottom tangent and common upper tangent of two convex hulls
	//returns a vector v; v[0] is BT and v[1] UT ; BT and UT are vectors ; BT[0] is left BT; BT[1] is right of BT
	std::vector<std::vector<int>> findBTandUT(std::vector<int>& vl, std::vector<int>& vr); 

	//test whether k is in the circumcircle of the triangle h i j
	//returns 0 if k on the circle; return 1 if a is in circle; return 2 if a is out of the circle 
	bool qtest(sf::Vector2f h, sf::Vector2f i, sf::Vector2f j, sf::Vector2f k);

	std::vector<int> mergeDTs(std::vector<int>& vl, std::vector<int>& vr); //DTs := two Delauney Triangulations 




public:
	std::vector<int> constructDelauneyTrangulation(std::vector<int>& rooms);
	void constructEdges(std::unordered_map<int, std::vector<int>>& AL, std::vector<std::array<int, 2>>& edges); // constrct edges from adjacency list; edge (a, b , w) is underected edge from a to b with weight w
	void constructMST(int start, std::vector<int>& ); //construct Minumem spaning tree
	void addEdgesToMSTFromDT();
	
	// given two rooms, it creates a door between them;
	void createConnectingDoor(sf::Vector2f position, Room& room1, Direction direction,  Room& room2, Direction direction2 );
	void createHallway(sf::VideoMode& userMode,Room& room, sf::Vector2f position, float width, float height);
	void createHallways(sf::VideoMode& userMode, std::vector<std::array<int, 2>>& edges);
	//given two interval (a1, b1) and (a2, b2), it return interval where those intervals intersect
	std::vector<float> getIntersectingIntervals(float a1, float b1, float a2, float b2);
	
	void createGolds();
	void createEnemies();

	void createDoors();

};






	