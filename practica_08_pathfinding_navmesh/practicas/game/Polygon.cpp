#include "stdafx.h"
#include "Polygon.h"
#include "Edge.h"

void Polygon::PushPoint(USVec2D point)
{
  Vertices.push_back(point);
}

void Polygon::PushPolygon(Polygon* pol)
{
  Neighbours.push_back(pol);
}

void Polygon::PushLink(Link* link)
{
  Links.push_back(link);
}

void Polygon::PushEdge(Edge edge)
{
  Edges.push_back(edge);
}

USVec2D& Polygon::GetPointAtPosition(int pos)
{
  return Vertices[pos];
}
