#pragma once

#include <vector>

class Polygon;
class Link;

class Navmesh
{
  std::vector<Polygon*> Polygons;
  std::vector<Link*> Links;

public:

  bool ReadNavmesh(const char* filename);
  void FillPolygonEdges(Polygon& polygon);
  void CalculatePolygonCenter(Polygon& polygon);
  void CalculateLinkCenterAndFillNeighbours(Link& link);
  std::vector<Polygon*>& GetVectorPolygon() { return Polygons; }
  std::vector<Link*>& GetVectorLinks() { return Links; }
  USVec2D GetMiddlePoint(USVec2D pointA, USVec2D pointB);
  bool PolygonContainsLink(Polygon* polygon, const Link* link);
};

