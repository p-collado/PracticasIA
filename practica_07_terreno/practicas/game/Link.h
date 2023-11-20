#pragma once

#include "Edge.h"

class Polygon;

struct Link
{
public:

	int ID;

	Polygon* StartPolygon;
	Edge StartEdge;

	Polygon* EndPolygon;
	Edge EndEdge;
};

