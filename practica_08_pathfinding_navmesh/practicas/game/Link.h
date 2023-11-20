#pragma once

#include "Edge.h"

class Polygon;

struct Link
{
public:

	int ID;

	USVec2D Center;

	Polygon* StartPolygon;
	Edge StartEdge;

	Polygon* EndPolygon;
	Edge EndEdge;
};

