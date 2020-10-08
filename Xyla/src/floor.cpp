#include "precompiled.h"

#include "floor.h"

#include "mathematics.h"
#include <chrono>
#include <thread>


Floor::Floor() {
	Floor::circle.setRadius(350);
	Floor::circle.setPosition(Xyla::getCenterPosition(sf::Vector2f(1920,1080), sf::Vector2f(700,700))); // a circle psoistion is upperright of 
																										// a square tangent to circle from outside
	Room r;
	Floor::floorMatrix.resize(1080 / r.unit);
	for (auto& row : Floor::floorMatrix) {
		row.resize(1920 / r.unit);
	}


}

void Floor::createRoom(sf::VideoMode& userMode, sf::CircleShape circle) {

	Room room;
	float width, height;
	float x = 0;
	float y = 0;
	float r = circle.getRadius(), px = circle.getPosition().x, py = circle.getPosition().y;

	while (x == 0 || y ==0) {
		width = Xyla::rand(4, 10) * Floor::unit;
		x = Xyla::rand((int)px, (int)(px + 2 *r - width));
		float x2 = x + width;

		float xoffset = x - px, xoffset2 = x2 - px;
		
		height = Xyla::rand(4, 10) * Floor::unit;
		float halfChord = sqrt(pow(r, 2) - pow((r - xoffset), 2)), halfChord2 = sqrt(pow(r, 2) - pow((r - xoffset2), 2));
		y = Xyla::rand(std::max((int) (py + (r - halfChord)),(int) (py + (r - halfChord2))),
					   std::min((int) (py + r + halfChord - height), (int)(py + r + halfChord2 - height)));
	}
	sf::Vector2f position = Xyla::floor(sf::Vector2f(x, y), Floor::unit);
	room.setRoomMatrix();
	room.outlineVertices(userMode, position, sf::Vector2f(width, height)); 
	room.id = Floor::heighestRoomId++;
	Floor::rooms.insert({ room.id, room});

	Floor::addRoomtoMatrix(position, width, height, Floor::unit, room.id);

}

void Floor::createDungen(sf::VideoMode& userMode) {
	//srand(time(0) + 20);
	srand(20);
	for (int i = 0; i < 30; i++) {
		Floor::createRoom(userMode, Floor::circle);
		
	}
	
	Floor::printMatrix();
}


void Floor::addRoomtoMatrix(sf::Vector2f position, float width, float height, int unit, int roomId) {
	for (int i = position.y / unit; i < (int)((position.y + height) / unit); i++) {
		for (int j = (position.x / unit); j < (int)((position.x + width) / unit); j++) {
			Floor::floorMatrix[i][j].push_back(roomId);
		}
	}
}

void Floor::removeRoomFromMatrix(sf::Vector2f position, float width, float height, int unit, int roomId) {

	for (int i = position.y / unit; i < (int)((position.y + height) / unit); i++) {
		for (int j = (position.x / unit); j < (int)((position.x + width) / unit); j++) {
			Floor::floorMatrix[i][j].remove(roomId);
			
		}
	}
}


void Floor::printMatrix() {
	/*
	for (int i = 0; i < Floor::floorMatrix.size(); ++i) {
		for (int j = 0; j < Floor::floorMatrix[0].size(); ++j) {
			if(Floor::floorMatrix[i][j].empty())
				std::cout << 0 << " ";
			else
				std::cout << Floor::floorMatrix[i][j].back() << " ";
		}
		std::cout << std::endl;
	}
	*/
}

void Floor::seperateRooms(sf::VideoMode& userMode) {
	int count = 0;
bool check = true;
	while (check) {
		check = false;
		for (std::unordered_map<int, Room>::iterator it = Floor::rooms.begin(); it != Floor::rooms.end(); ) {
			Room& room = it->second;

			sf::Vector2f center = it->second.center;
			std::unordered_set<int> targets;

			//get targets ie. room ids that intersect with the room
			for (int i = room.position.y / room.unit; i < (int)((room.position.y + room.height) / room.unit); i++) {
				for (int j = (room.position.x / room.unit); j < (int)((room.position.x + room.width) / room.unit); j++) {
					std::list<int>::iterator it2 = std::find_if_not(Floor::floorMatrix[i][j].begin(),
						Floor::floorMatrix[i][j].end(), [&](int a) { return room.id == a; });
					if (it2 != Floor::floorMatrix[i][j].end())
						targets.insert(*it2);
				}
			}

			// Seperate room from their targets
			if (!targets.empty()) {
				check = true;
				float d = 0; //distance
				sf::Vector2f v = sf::Vector2f(0, 0); //displacment
				//sf::Vector2f v = sf::Vector2f(0, 0); //distance
				for (const int& target : targets) { // get distance and displacemnt between room & targets
					d += sqrt(pow(center.x - Floor::rooms[target].center.x, 2) + pow(center.y - Floor::rooms[target].center.y, 2));
					

					if (center.x < Floor::rooms[target].center.x)
						v.x -= abs(room.verteces[1].x - Floor::rooms[target].verteces[0].x);
					else
						v.x += abs(Floor::rooms[target].verteces[1].x - room.verteces[0].x);

					if (center.y < Floor::rooms[target].center.y)
						v.y -= abs(room.verteces[1].y - Floor::rooms[target].verteces[0].y);
					else
						v.y += abs(Floor::rooms[target].verteces[1].y - room.verteces[0].y);

	
				}
			
				float vMagnitude = sqrt(pow(v.x, 2) + pow(v.y, 2));
			
				d = (d / targets.size());

				sf::Vector2 newPosition = sf::Vector2f(room.position.x + (v.x) * (1920 / 1080), room.position.y + (v.y));
				newPosition = Xyla::floor(newPosition, room.unit);
				Floor::removeRoomFromMatrix(room.position, room.width, room.height, room.unit, room.id);

				if (newPosition.x >= 0 && newPosition.y >= 0
					&& newPosition.x + room.width < 1920 && newPosition.y + room.height < 1080) {
					room.setPosition(newPosition);
					Floor::addRoomtoMatrix(newPosition, room.width, room.height, room.unit, room.id);
					++it;
				}
				else
				{
					Floor::rooms.erase(it++);
				}
					

			} else ++it;

			
		}
		
	}
	
	
}

void Floor::setLivingAndDungenRooms(sf::VideoMode& userMode) {
	for (auto& room : Floor::rooms) {
		float area = room.second.width * room.second.height;
		
		if (area >= 7 * room.second.unit * 6 * room.second.unit )
			Floor::livingRooms.push_back(room.first);
		else
			Floor::dungenRooms.push_back(room.first);
	}

	Floor::allRooms = Floor::livingRooms;
	Floor::allRooms.insert(Floor::allRooms.end(), Floor::dungenRooms.begin(), Floor::dungenRooms.end());


}


std::vector<int> Floor::mergeSort(std::vector<int>& v) {
	if ( v.size() < 2)
		return v;
	else {
		std::vector<int> vl, vr;
		for (int i = 0; i < std::floor(v.size() / 2); ++i)
			vl.push_back(v[i]);
		for (int j = std::floor(v.size() / 2); j < v.size() ; ++j)
			vr.push_back(v[j]);
		
		std::vector<int>& nvl = mergeSort(vl);
		std::vector<int>& nvr = mergeSort(vr);
		return merge(nvl, nvr);
	}
}

std::vector<int> Floor::merge(std::vector<int>& vl, std::vector<int>& vr) {
	int a = 0, b = 0;
	std::vector<int> v;
	while (a < vl.size() && b < vr.size()) {
		if (Floor::rooms.at(vl[a]).center.x < Floor::rooms.at(vr[b]).center.x ||
			(Floor::rooms.at(vl[a]).center.x == Floor::rooms.at(vr[b]).center.x &&
				Floor::rooms.at(vl[a]).center.y < Floor::rooms.at(vr[b]).center.y)
			) {
			v.push_back(vl[a]);
			++a;
		}
		else {
			v.push_back(vr[b]);
			++b;
		}
	}

	if (a < vl.size()){
		while (a < vl.size()) {
			v.push_back(vl[a]);
			++a;
		}
	}
	else if( b < vr.size()) {
		while (b < vr.size()) {
			v.push_back(vr[b]);
			++b;
		}

	}
	return v;
}


int Floor::findOrientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
	float det = ((q.y - p.y) * (r.x - q.x)) - ((q.x - p.x) * (r.y - q.y));

	if (det == 0) {
		return 0;
		std::cout << Xyla::print(p) << " and " << Xyla::print(q) << " and " << Xyla::print(r) << " are colinear " << std::endl;;
	}
	else if (det > 0)
		return 1;
	else 
		return 2;

}


std::vector<int> Floor::constructConvexHull(std::vector<int> v) {
	int n = v.size();
	

	if (n < 3) {
		return v;
		std::cout << " you must have more than 3 points to get the convex hull" << std::endl;
	}
	else {
		std::vector<int> convexHull; // CH
		int p = 0, q;
		do {
			convexHull.push_back(v[p]);

			q = (p + 1) % n;

			for (int i = 0; i < n; i++) {
				if (Floor::findOrientation(Floor::rooms.at(v[p]).center, Floor::rooms.at(v[q]).center, Floor::rooms.at(v[i]).center) == 2)
					q = i;
			}


			p = q;
		} while (p != 0);

		/*
		// Print Result 
		std::cout << "Convex hull " << std::endl;
		for (auto& vertex : convexHull)
			std::cout << vertex << " , ";
		std::cout << std::endl;
		*/

		return convexHull;

	}

	
}


std::vector<int> Floor::constructDelauneyTrangulation(std::vector<int>& v) {
	
	if (v.size() <= 3) {
		std::vector<int>& convexHull = Floor::constructConvexHull(v);
		for (int i = 0; i < convexHull.size(); ++i) {
			if (Floor::adjacencyList.find(convexHull[i]) == Floor::adjacencyList.end()) {
				std::vector<int> v;
				Floor::adjacencyList[convexHull[i]];
			}
			
			for (int j = i + 1; (j % convexHull.size()) != i; ++j) {
				Floor::adjacencyList.at(convexHull[i]).push_back(convexHull[j % convexHull.size()]);

			}

		}
		return Floor::mergeSort(convexHull);
		
	}
	else {
		std::vector<int> vl, vr;
		for (int i = 0; i < std::floor(v.size() / 2); ++i)
			vl.push_back(v[i]);
		for (int j = std::floor(v.size() / 2); j < v.size(); ++j)
			vr.push_back(v[j]);

		std::vector<int>& nvl = constructDelauneyTrangulation(vl);
		std::vector<int>& nvr = constructDelauneyTrangulation(vr);
		return Floor::mergeSort(mergeDTs(nvl, nvr));
	}
}



std::vector<int> Floor::mergeDTs(std::vector<int>& vl, std::vector<int>& vr) {
	std::vector<std::vector<int>> BTandUT = Floor::findBTandUT(vl, vr);
	std::vector<int> BT = BTandUT[0], UT = BTandUT[1];
	int l = BT[0], r = BT[1];
	int r1, r2;
	int l1, l2;
	while (BT != UT) {
		
		bool a = false, b = false;
		Floor::insert(l, r, Floor::adjacencyList);
		r1 = Floor::pred(r, l, Floor::adjacencyList);
		
		// if r1 is left of line(l , r) ie if (l,r, r1) is counter clockwise
		if (Floor::findOrientation(Floor::rooms.at(l).center, Floor::rooms.at(r).center, Floor::rooms.at(r1).center) == 1) { 
			r2 = Floor::pred(r, r1, Floor::adjacencyList);
			// do until ( qtest)
			while (Floor::qtest(Floor::rooms.at(l).center, Floor::rooms.at(r).center, Floor::rooms.at(r1).center, Floor::rooms.at(r2).center)) {
				
				Floor::deletee(r, r1, Floor::adjacencyList);
				r1 = r2;
				r2 = Floor::pred(r, r1, Floor::adjacencyList);
			} 
		}
		else 
			a = true;



		l1 = Floor::succ(l, r, Floor::adjacencyList);
		// if l1 is right of line(r, l) ie. if (r, l, l1) is clockwise
		if (Floor::findOrientation(Floor::rooms.at(r).center, Floor::rooms.at(l).center, Floor::rooms.at(l1).center) == 2) {
			l2 = Floor::succ(l, l1, Floor::adjacencyList);

			//notice that i flipped (r, l, l1) to (l1, l, r) to make it from clock wise to counter clockwise
			while (Floor::qtest(Floor::rooms.at(l).center, Floor::rooms.at(r).center, Floor::rooms.at(l1).center, Floor::rooms.at(l2).center)) {
				Floor::deletee(l, l1, Floor::adjacencyList);
				l1 = l2;
				l2 = Floor::succ(l, l1, Floor::adjacencyList);

			} 
		}
		else
			b = true;

		if (a)
			l = l1;
		else {
			if (b)
				r = r1;
			else {
				if (!Floor::qtest(Floor::rooms.at(l).center, Floor::rooms.at(r).center, Floor::rooms.at(r1).center, Floor::rooms.at(l1).center))
					r = r1;
				else
					l = l1;
				
			}
		}

		BT = std::vector<int>{ l, r };
	}
	
	Floor::insert(l, r, Floor::adjacencyList);

	std::vector<int> v = vl;
	v.insert(v.end(), vr.begin(), vr.end());
	return v;
}




std::vector<std::vector<int>> Floor::findBTandUT(std::vector<int>& vl, std::vector<int>& vr) {
	std::vector<int> BT;
	std::vector<int> UT;
	
	int x = vl[vl.size() - 1], y = vr[0]; // x is most right of vl, y is most left of vr
	int z = Floor::adjacencyList.at(y)[0]; // first(y) 
	int z1 = Floor::adjacencyList.at(x)[0]; // first(x)
	int z2 = Floor::adjacencyList.at(x)[Floor::adjacencyList.at(x).size() - 1]; // PRED(x, z1)
	bool check = true;
	while (check) {
		// if z is right of line(x,y) ie if x y z is clock wise
		
		if (Floor::findOrientation(Floor::rooms.at(x).center, Floor::rooms.at(y).center, Floor::rooms.at(z).center) == 2) {
			int newZ = z;
			z = Floor::succ(z, y, Floor::adjacencyList);
			y = newZ;
		}
		else {
			if (Floor::findOrientation(Floor::rooms.at(x).center, Floor::rooms.at(y).center, Floor::rooms.at(z2).center) == 2) {
				int newZ2 = z2;
				z2 = Floor::pred(z2, x, Floor::adjacencyList);
				x = newZ2;
			}
			else {
				BT = { x,y };
				check = false;
			}

		}
	}

	y = vl[vl.size() - 1], x = vr[0]; // x is most right of vl, y is most left of vr
	z = Floor::adjacencyList.at(y)[0]; // first(y) 
	z1 = Floor::adjacencyList.at(x)[0]; // first(x)
	z2 = Floor::adjacencyList.at(x)[Floor::adjacencyList.at(x).size() - 1]; // PRED(x, z1)
	check = true;
	while (check) {
		// if z is right of line(y,x) ie if x y z is clock wise
		if (Floor::findOrientation(Floor::rooms.at(y).center, Floor::rooms.at(x).center, Floor::rooms.at(z).center) == 1) {
			int newZ = z;
			z = Floor::succ(z, y, Floor::adjacencyList);
			y = newZ;
		}
		else {
			if (Floor::findOrientation(Floor::rooms.at(y).center, Floor::rooms.at(x).center, Floor::rooms.at(z2).center) == 1) {
				int newZ2 = z2;
				z2 = pred(z2, x, Floor::adjacencyList);
				x = newZ2;
			}
			else {
				UT = { y,x };
				check = false;
			}

		}
	}


	//std::cout << "BT is (" << BT[0] << ", " << BT[1] << " )" << std::endl;
	//std::cout << "UT is (" << UT[0] << ", " << UT[1] << " )" << std::endl;

	return std::vector<std::vector<int>> {BT, UT};
	

}





bool Floor::qtest(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) {
	// provided that a b c are counter clock wise, then
		//  if det ==0, then d is on circle;
		// if det > 0, then d is in the circle
		// if det < 0, then d is out of the circle;

	float ax = a.x - d.x,  ay = a.y - d.y;
	float bx = b.x - d.x,  by = b.y - d.y;
	float cx = c.x - d.x,  cy = c.y - d.y;

	float det = (ax * ax + ay * ay) * (bx * cy - cx * by) -
				(bx * bx + by * by) * (ax * cy - cx * ay) +
				(cx * cx + cy * cy) * (ax * by - bx * ay);

	
	if (det == 0) {
		return false;
		
	}
	else if (det > 0)
		return false;
	else
		return true;



}





void Floor::insert(int a, int b, std::unordered_map<int, std::vector<int>>& AL) {
	//AL.at(b).push_back(a); //insert a into the adjacency list of b
	//AL.at(a).insert(AL.at(a).begin(), b);  //insert b into the adjacency list of a
	
	for (int i = AL.at(a).size() - 1; i >= 0; --i) {
		if (Floor::findOrientation(Floor::rooms.at(a).center, Floor::rooms.at(AL.at(a)[i]).center, Floor::rooms.at(b).center) == 1) {
			AL.at(a).insert(AL.at(a).begin() + i + 1, b);
			break;
		}
		else if( i ==0)
			AL.at(a).insert(AL.at(a).begin(), b);
	}
	int n = AL.at(b).size();
	for (int i = 0; i < n; ++i) {
		//std::cout << AL.at(b).size() << " ";
		if (Floor::findOrientation(Floor::rooms.at(b).center, Floor::rooms.at(AL.at(b)[i]).center, Floor::rooms.at(a).center) == 2) {
			AL.at(b).insert(AL.at(b).begin() + i, a);
			break;
		}
		else if (i == n - 1)
			AL.at(b).push_back(a);
	}
	
}


void Floor::deletee(int a, int b, std::unordered_map<int, std::vector<int>>& AL) {
	for (int i = 0; i < AL.at(a).size(); ++i) {
		if (AL.at(a)[i] == b) {
			AL.at(a).erase(AL.at(a).begin() + i);
			break;
		}
	}
	for (int i = 0; i < AL.at(b).size(); ++i) {
		if (AL.at(b)[i] == a) {
			AL.at(b).erase(AL.at(b).begin() + i);
			break;
		}
	}

}


int Floor::pred(int a, int b, std::unordered_map<int, std::vector<int>>& AL) {
	int pred;
	for (int i = 0; i < AL.at(a).size(); ++i) {
		if (AL.at(a)[i] == b) {
			pred = AL.at(a)[(i - 1 + AL.at(a).size()) % AL.at(a).size()];
			break;
		}
	}

	return pred;
}


int Floor::succ(int a, int b, std::unordered_map<int, std::vector<int>>& AL) {
	int succ;
	for (int i = 0; i < AL.at(a).size(); ++i) {
		if (AL.at(a)[i] == b) {
			succ = (AL.at(a)[(i + 1) % AL.at(a).size()]); //z = SUCC(z, y)
			break;
		}
	}

	return succ;
}




void Floor::constructEdges(std::unordered_map<int, std::vector<int>>& AL, std::vector<std::array<int, 2>>& edges) {
	for (auto& v1 : AL) {
		for (auto& v2 : v1.second) {
			std::array<int, 2> edge = {std::min(v1.first, v2), std::max(v1.first, v2)};
			if (std::find(edges.begin(), edges.end(), edge) == edges.end())
				edges.push_back(edge);
		}
	}
}



void Floor::constructMST(int start, std::vector<int>& rooms) {

	struct Parent {
		int vertex;
		Parent* parent;
		Parent(int vertex, Parent* parent) {
			this->vertex = vertex;
			this->parent = parent;
		}
	};

	std::queue<Parent*> Q;
	std::vector<int> visited;
	std::vector<Parent*> parents;

	visited.push_back(start);
	Parent* p1 = new Parent(start, nullptr);
	parents.push_back(p1);
	Q.push(p1);


	while (!Q.empty()) { // it terminates when all vertices are visited. 
		Parent* q = Q.front();
		std::vector<int> neighbors = Floor::adjacencyList.at(q->vertex);
		Q.pop();
		for (int& v : neighbors) {
			if (std::find(visited.begin(), visited.end(), v) == visited.end()) { //check if v is not in visited
				visited.push_back(v);
				Parent* p = new Parent(v, q);
				parents.push_back(p);
				Q.push(p);
			}
		}
		neighbors.clear();
	}
	


	for (int& v : rooms) { // inilize adjacnencylistMST to be all rooms;
		Floor::adjacencyListMST[v];
	}


	
	int v;
	Parent* p;
	for (int i = parents.size() - 1; i >= 1; --i) {
		v = parents[i]->vertex;
		p = parents[i]->parent;
		Floor::adjacencyListMST.at(v).push_back(p->vertex);
		Floor::adjacencyListMST.at(p->vertex).push_back(v);
	}
	

	for (auto& p : parents) {
		delete(p);
	}
	Floor::adjacencyList = Floor::adjacencyListMST; // update the GENERAL AL to be the ALMST;

}

void Floor::addEdgesToMSTFromDT() {
	std::vector<std::array<int, 2>> edgesMSTComplement; // edgesMSTComplement = edgesDT - edgesMST
	for (auto& e : Floor::edgesDT) {
		if (std::find(Floor::edgesMST.begin(), Floor::edgesMST.end(), e) == Floor::edgesMST.end()) {
			if (Floor::adjacencyListMST.at(e[0]).size() < 2 && Floor::adjacencyListMST.at(e[1]).size() < 2) {
				edgesMSTComplement.push_back(e);
			}
		}
	}

	
	srand(time(0));
	for (auto& e : edgesMSTComplement) {
		if (Xyla::rand(1, 100) <= 15) {
			Floor::insert(e[0], e[1], Floor::adjacencyListMST);
		}
	}
	Floor::constructEdges(Floor::adjacencyListMST, Floor::edgesMST);
	Floor::adjacencyList = Floor::adjacencyListMST;


}

void Floor::createConnectingDoor(sf::Vector2f position, Room& room1, Direction direction, Room& room2, Direction direction2) {
	Door door1;
	door1.position = position;
	door1.neighborRoom = room2.id;
	door1.neighborDirection = direction2; // it opens to room 2 
	room1.doors.push_back(door1);

	Door door2;
	door2.position = position;
	door2.neighborRoom = room1.id;
	door2.neighborDirection = direction;
	room2.doors.push_back(door2);
}


void Floor::createHallway(sf::VideoMode& userMode, Room& room, sf::Vector2f position, float width, float height) {

	room.outlineVertices(userMode, position, sf::Vector2f(width, height));

	Floor::rooms.insert({ room.id, room });
	Floor::addRoomtoMatrix(position, width, height, Floor::unit, room.id);
	Floor::dungenRooms.push_back(room.id);
	Floor::allRooms.push_back(room.id);

}

void Floor::createHallways(sf::VideoMode& userMode, std::vector<std::array<int, 2>>& edges) {
	

	std::vector<float> rx, ry;
	float x, y;
	float width, height;

	sf::Vector2f out; // door position to get out
	
	for (auto& e : edges) {
		int v1 = e[0], v2 = e[1];
		float a1x = Floor::rooms.at(v1).position.x + Floor::unit, b1x = Floor::rooms.at(v1).position.x + Floor::rooms.at(v1).width - Floor::unit;
		float a2x = Floor::rooms.at(v2).position.x + Floor::unit, b2x = Floor::rooms.at(v2).position.x + Floor::rooms.at(v2).width - Floor::unit;

		float a1y = Floor::rooms.at(v1).position.y + Floor::unit, b1y = Floor::rooms.at(v1).position.y + Floor::rooms.at(v1).height - Floor::unit;
		float a2y = Floor::rooms.at(v2).position.y + Floor::unit, b2y = Floor::rooms.at(v2).position.y + Floor::rooms.at(v2).height - Floor::unit;

		srand(time(0));
		if (a1x < b2x && a2x < b1x) { // if the two rooms intersect in x direction
			rx = Xyla::getIntersectingIntervals(a1x, b1x, a2x, b2x); // get the interval of intersection
			x = Xyla::floor(Xyla::rand((int)rx[0], (int)rx[1]) - Floor::unit, Floor::unit);

			if (Floor::rooms.at(v1).position.y < Floor::rooms.at(v2).position.y) { // if v1 is above v2
				y = Floor::rooms.at(v1).position.y + Floor::rooms.at(v1).height - Floor::unit;
				width = 3 * Floor::unit;
				height = Floor::rooms.at(v2).position.y - y + Floor::unit;
				Room hallway;
				hallway.id = Floor::heighestRoomId++;
				Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

				//create 2 doors
				sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.x = doorPos.x + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(v1), Direction::up, Floor::rooms.at(hallway.id), Direction::down);
				//create 2 doors
				doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.y = doorPos.y + Floor::rooms.at(hallway.id).height - Floor::unit, doorPos.x = doorPos.x + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::up, Floor::rooms.at(v2), Direction::down);
			}
			else // if v2 is above v1
			{
				y = Floor::rooms.at(v2).position.y + Floor::rooms.at(v2).height - Floor::unit;
				width = 3 * Floor::unit;
				height = Floor::rooms.at(v1).position.y - y + Floor::unit;
				Room hallway;
				hallway.id = Floor::heighestRoomId++;
				Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

				//create 2 doors
				sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.x = doorPos.x + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(v2), Direction::up, Floor::rooms.at(hallway.id), Direction::down);
				//create 2 doors
				doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.y = doorPos.y + Floor::rooms.at(hallway.id).height - Floor::unit, doorPos.x = doorPos.x + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::up, Floor::rooms.at(v1), Direction::down);
			}
		}
		else if (a1y < b2y && a2y < b1y) {  // if the two rooms intersect in y direction
			ry = Xyla::getIntersectingIntervals(a1y, b1y, a2y, b2y); // get the interval of intersection
			y = Xyla::floor(Xyla::rand((int)ry[0], (int)ry[1]) - Floor::unit, Floor::unit);

			if (Floor::rooms.at(v1).position.x < Floor::rooms.at(v2).position.x) { // if v1 is left v2
				x = Floor::rooms.at(v1).position.x + Floor::rooms.at(v1).width - Floor::unit;
				height = 3 * Floor::unit;
				width = Floor::rooms.at(v2).position.x - x + Floor::unit;
				Room hallway;
				hallway.id = Floor::heighestRoomId++;
				Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

				//create 2 doors
				sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.y = doorPos.y + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(v1), Direction::left, Floor::rooms.at(hallway.id), Direction::right);
				//create 2 doors
				doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.x = doorPos.x + Floor::rooms.at(hallway.id).width - Floor::unit, doorPos.y = doorPos.y + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::left, Floor::rooms.at(v2), Direction::right);
			}
			else // if v2 is above v1
			{
				x = Floor::rooms.at(v2).position.x + Floor::rooms.at(v2).width - Floor::unit;
				height = 3 * Floor::unit;
				width = Floor::rooms.at(v1).position.x - x + Floor::unit;
				Room hallway;
				hallway.id = Floor::heighestRoomId++;
				Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

				//create 2 doors
				sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.y = doorPos.y + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(v2), Direction::left, Floor::rooms.at(hallway.id), Direction::right);
				//create 2 doors
				doorPos = Floor::rooms.at(hallway.id).position;
				doorPos.x = doorPos.x + Floor::rooms.at(hallway.id).width - Floor::unit, doorPos.y = doorPos.y + Floor::unit;
				Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::left, Floor::rooms.at(v1), Direction::right);
			}
			
		}
		else { //create an L shaped hallway
			if (Floor::rooms.at(v1).position.x < Floor::rooms.at(v2).position.x) {
				if (Floor::rooms.at(v1).position.y < Floor::rooms.at(v2).position.y) {
					x = Xyla::floor(Xyla::rand(Floor::rooms.at(v1).position.x, Floor::rooms.at(v1).position.x + Floor::rooms.at(v1).width - 3 * Floor::unit), Floor::unit);
					y = Floor::rooms.at(v1).position.y + Floor::rooms.at(v1).height - Floor::unit;	
					width = 3 * Floor::unit;
					float y2 = Xyla::floor(Xyla::rand(Floor::rooms.at(v2).position.y + 3 * Floor::unit, Floor::rooms.at(v2).position.y + Floor::rooms.at(v2).height), Floor::unit);
					height = y2 - y;
					Room hallway;
					hallway.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

					y = y2 - 3 * Floor::unit;
					x = x + 2 * Floor::unit;
					height = 3 * Floor::unit;
					width = Floor::rooms.at(v2).position.x + Floor::unit - x;
					Room hallway2;
					hallway2.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway2, sf::Vector2f(x, y), width, height);

					//create 2 doors to connect v1 to hallway
					sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
					doorPos.x = doorPos.x + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(v1), Direction::up, Floor::rooms.at(hallway.id), Direction::down);
					//create 2 doors to connect halway1 to hallway2
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::left, Floor::rooms.at(hallway2.id), Direction::right);
					//create 2 doors to connect halway2 to v2
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.x = doorPos.x + Floor::rooms.at(hallway2.id).width - Floor::unit, doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway2.id), Direction::left, Floor::rooms.at(v2), Direction::right);


				}
				else {
					x = Xyla::floor(Xyla::rand(Floor::rooms.at(v1).position.x, Floor::rooms.at(v1).position.x + Floor::rooms.at(v1).width - 3 * Floor::unit), Floor::unit);
					y = Xyla::floor(Xyla::rand(Floor::rooms.at(v2).position.y, Floor::rooms.at(v2).position.y + Floor::rooms.at(v2).width - 3 * Floor::unit), Floor::unit);
					width = 3 * Floor::unit;
					height = Floor::rooms.at(v1).position.y + Floor::unit - y;
					Room hallway;
					hallway.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

					x = x + 2 * Floor::unit;
					y = y;
					height = 3 * Floor::unit;
					float x2 = Floor::rooms.at(v2).position.x + Floor::unit;
					width = x2 - x;
					Room hallway2;
					hallway2.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway2, sf::Vector2f(x, y), width, height);

					//create 2 doors to connect v1 to hallway
					sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
					doorPos.x = doorPos.x + Floor::unit, doorPos.y = doorPos.y + Floor::rooms.at(hallway.id).height - Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(v1), Direction::down, Floor::rooms.at(hallway.id), Direction::up);
					//create 2 doors to connect halway1 to hallway2
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::left, Floor::rooms.at(hallway2.id), Direction::right);
					//create 2 doors to connect halway2 to v2
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.x = doorPos.x + Floor::rooms.at(hallway2.id).width - Floor::unit, doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway2.id), Direction::left, Floor::rooms.at(v2), Direction::right);
				}


			}

			else if (Floor::rooms.at(v2).position.x < Floor::rooms.at(v1).position.x) {
				if (Floor::rooms.at(v2).position.y < Floor::rooms.at(v1).position.y) {
					x = Xyla::floor(Xyla::rand(Floor::rooms.at(v2).position.x, Floor::rooms.at(v2).position.x + Floor::rooms.at(v2).width - 3 * Floor::unit), Floor::unit);
					y = Xyla::floor(Floor::rooms.at(v2).position.y + Floor::rooms.at(v2).height - Floor::unit, Floor::unit);
					width = 3 * Floor::unit;
					float y2 = Xyla::floor(Xyla::rand(Floor::rooms.at(v1).position.y + 3 * Floor::unit, Floor::rooms.at(v1).position.y + Floor::rooms.at(v1).height), Floor::unit);
					height = y2 - y;
					Room hallway;
					hallway.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

					y = y2 - 3 * Floor::unit;
					x = x + 2 * Floor::unit;
					height = 3 * Floor::unit;
					width = Floor::rooms.at(v1).position.x + Floor::unit - x;
					Room hallway2;
					hallway2.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway2, sf::Vector2f(x, y), width, height);

					//create 2 doors to connect v2 to hallway
					sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
					doorPos.x = doorPos.x + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(v2), Direction::up, Floor::rooms.at(hallway.id), Direction::down);
					//create 2 doors to connect halway1 to hallway2
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::left, Floor::rooms.at(hallway2.id), Direction::right);
					//create 2 doors to connect halway2 to v1
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.x = doorPos.x + Floor::rooms.at(hallway2.id).width - Floor::unit, doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway2.id), Direction::left, Floor::rooms.at(v1), Direction::right);

				}
				else {
					x = Xyla::floor(Xyla::rand(Floor::rooms.at(v2).position.x, Floor::rooms.at(v2).position.x + Floor::rooms.at(v2).width - 3 * Floor::unit), Floor::unit);
					y = Xyla::floor(Xyla::rand(Floor::rooms.at(v1).position.y, Floor::rooms.at(v1).position.y + Floor::rooms.at(v1).width - 3 * Floor::unit), Floor::unit);
					width = 3 * Floor::unit;
					height = Floor::rooms.at(v2).position.y + Floor::unit - y;
					Room hallway;
					hallway.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway, sf::Vector2f(x, y), width, height);

					x = x + 2 * Floor::unit;
					y = y;
					height = 3 * Floor::unit;
					float x2 = Floor::rooms.at(v1).position.x + Floor::unit;
					width = x2 - x;
					Room hallway2;
					hallway2.id = Floor::heighestRoomId++;
					Floor::createHallway(userMode, hallway2, sf::Vector2f(x, y), width, height);

					//create 2 doors to connect v2 to hallway
					sf::Vector2f doorPos = Floor::rooms.at(hallway.id).position;
					doorPos.x = doorPos.x + Floor::unit, doorPos.y = doorPos.y + Floor::rooms.at(hallway.id).height - Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(v2), Direction::down, Floor::rooms.at(hallway.id), Direction::up);
					//create 2 doors to connect halway1 to hallway2
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway.id), Direction::left, Floor::rooms.at(hallway2.id), Direction::right);
					//create 2 doors to connect halway2 to v1
					doorPos = Floor::rooms.at(hallway2.id).position;
					doorPos.x = doorPos.x + Floor::rooms.at(hallway2.id).width - Floor::unit, doorPos.y = doorPos.y + Floor::unit;
					Floor::createConnectingDoor(doorPos, Floor::rooms.at(hallway2.id), Direction::left, Floor::rooms.at(v1), Direction::right);
				}
			}

		}
	}
}



#ifdef XYLA_DEBUG

void Floor::printAL(std::unordered_map<int, std::vector<int>>& AL) {
	using namespace std;
	cout << "-------adjacency list---------" << endl;
	for (auto& v1 : AL) {
		cout << v1.first << " (";
		for (int& v2 : v1.second) {
			cout << v2 << ", ";
		}
		cout << ")" << endl;
	}
}


void Floor::printEdges(std::vector<std::array<int, 2>>& edges) {
	std::cout << " ---- Edges ----" << std::endl;
	for (auto e : edges) {
		std::cout << "( ";
		for (auto& v : e)
			std::cout << v << ", ";
		std::cout << ")";
	}
	std::cout << std::endl;
}

#endif // XYLA_DEBUG


void Floor::createGolds() {
	for (auto& room : Floor::rooms) {
		room.second.createGold();
	}
}

void Floor::createEnemies() {
	for (auto& room : Floor::rooms) {
		room.second.createEnemies();
	}
}


void Floor::createDoors() {
	for (auto& room : Floor::rooms) {
		room.second.createDoors();
	}
}