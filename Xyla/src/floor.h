#pragma once

#include "entity.h"

#include "room.h"

#include "SFML/Graphics/CircleShape.hpp"




class Floor : public Entity{
	friend int main();
	friend class Game;
	friend class FloorCT;
	std::unordered_map<int, Room> rooms;

	std::vector<int> livingRooms; // rooms that are visible
	std::vector<int> dungenRooms; // Hallway rooms ie. rooms that are hallways to living rooms

	std::vector<std::vector<std::list<int>>> floorMatrix;
	
	sf::CircleShape circle;

public:

	Floor();
	void printMatrix();


	void addRoomtoMatrix(sf::Vector2f position, float width, float height, int unit, int roomId); //set room area in floorMatrix
	void removeRoomFromMatrix(sf::Vector2f position, float width, float height, int unit, int roomId); //set room area in floorMatrix


	void createRoom(sf::VideoMode& userMode, sf::CircleShape circle);
	void createDungen(sf::VideoMode& userMode);
	void seperateRooms(sf::VideoMode& userMode);
	void setLivingAndDungenRooms(sf::VideoMode& userMode);
	
	
	
	
private:
	

	std::vector<std::array<int, 2>> edges; //edges to connect livingRooms; to set delauney tringulaiton and Minumem spanning tree.
	
	std::unordered_map<int, std::vector<int>> adjacencyList;

	// to sort vertices such that v1 is before v2 iff v1.x < v2.x or (v1.x == v2.x and v1.y < v2.y)
	std::vector<int> mergeSort(std::vector<int>& v);
	std::vector<int> merge(std::vector<int>& vl, std::vector<int>& vr);

	//find the orientation ( clockwise or counter clock wise of the curve starting from p, passing q, and ending at r
	// it will be used in constructing the convex hull
	//return 0 if colinear, 1 if counter clockwise, 2 if clockwises
	int findOrientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);

	std::vector<int> constructConvexHull(std::vector<int> v);


#ifdef XYLA_DEBUG
	void printAL();  // print the adjacencylist
#endif // XYLA_DEBUG


public:
	//find common bottom tangent and common upper tangent of two convex hulls
	//returns a vector v; v[0] is BT and v[1] UT ; BT and UT are vectors ; BT[0] is left BT; BT[1] is right of BT
	std::vector<std::vector<int>> findBTandUT(std::vector<int>& vl, std::vector<int>& vr); 

	//test whether k is in the circumcircle of the triangle h i j
	//returns 0 if k on the circle; return 1 if a is in circle; return 2 if a is out of the circle 
	bool qtest(sf::Vector2f h, sf::Vector2f i, sf::Vector2f j, sf::Vector2f k);

	// insert a into the adjacency of b
	// insert b into the adjacency of a
	void insert(int a, int b);
	// delete a from the adjacency of b
	// delete b from the adjacency of a
	void deletee(int a, int b);
	
	// it gets predecessor of b in the adjacency list of a
	int pred(int a, int b);
	// it gets successor  of b in the adjacency list of a
	int succ(int a, int b);






	std::vector<int> mergeDTs(std::vector<int>& vl, std::vector<int>& vr); //DTs := two Delauney Triangulations 




public:
	std::vector<int> constructDelauneyTrangulation(std::vector<int>& );

	
};















/*
	// implemtaion of circular doubly linked list
	struct Node {
		int value;
		Node* pred;
		Node* succ;
	};

	void push_back(Node*& list, int value); // insert at the end of list,; list is a pointer to start
	void push_front(Node*&  list, int value); //insert at the begininng of the list
	void insertAt(Node*& list, int value, int position); // insert the value at position in the list
	*/