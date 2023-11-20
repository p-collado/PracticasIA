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
  std::vector<Polygon*>& GetVectorPolygon() { return Polygons; }
  std::vector<Link*>& GetVectorLinks() { return Links; }
};

