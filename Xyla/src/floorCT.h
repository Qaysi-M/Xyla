#pragma once

#include "floor.h"
#include "roomCT.h"

class FloorCT{
	RoomCT roomCT;

public:
#ifdef XYLA_DEBUG
	void drawCircle(sf::RenderWindow& windowView, Floor&);
#endif // XYLA_DEBUG
	void drawDungen(sf::RenderWindow& windowView, Floor&);


#ifdef XYLA_DEBUG
	void numberRooms(sf::RenderWindow& windowView, Floor&);
#endif // XYLA_DEBUG

	void drawDT(sf::RenderWindow& windowView, Floor&); // DT := Delanuey Triangulations


};
