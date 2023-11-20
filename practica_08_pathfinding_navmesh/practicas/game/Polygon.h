#pragma once

#include <vector>

class Link;
class Edge;

struct Polygon
{
private:
  int ID;
  std::vector<USVec2D> Vertices;
  std::vector<Polygon*> Neighbours;
  std::vector<Link*> Links;
  std::vector<Edge> Edges;
  USVec2D Center;

public:

  Polygon* mParent;
  int mG;
  int mH;

  int GetCost() const { return mG + mH; }
  void PushPoint(USVec2D point);
  int GetID() const { return ID; }
  void SetID(int id) { ID = id; }
  void PushPolygon(Polygon* pol);
  void PushLink(Link* link);
  void PushEdge(Edge edge);
  USVec2D& GetPointAtPosition(int pos);
  USVec2D GetCentroid() const { return Center; }
  void SetCentroid(USVec2D Center) { this->Center = Center; }
  std::vector<USVec2D>& GetVectorVertices() { return Vertices; }
  std::vector<Polygon*>& GetVectorNeighbours() { return Neighbours; }
  std::vector<Link*>& GetVectorLinks() { return Links; }
  std::vector<Edge>& GetVectorEdges() { return Edges; }
};

