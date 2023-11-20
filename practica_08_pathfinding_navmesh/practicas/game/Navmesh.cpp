#include "stdafx.h"
#include "Navmesh.h"
#include <tinyxml.h>
#include <Polygon.h>
#include "Link.h"

bool Navmesh::ReadNavmesh(const char* filename)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Error en la lectura del fichero: %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Formato invalido %s", filename);
		return false;
	}

	// Polygons
	TiXmlHandle hRoot(pElem);
	TiXmlHandle hPolygons = hRoot.FirstChildElement("polygons");

	TiXmlElement* polygonElement = hPolygons.FirstChild().Element();
	int polygonID = 0;

	for (; polygonElement; polygonElement = polygonElement->NextSiblingElement())
	{
		TiXmlElement* PointInPolygon = polygonElement->FirstChildElement();

		Polygon* polygon = new Polygon();
		USVec2D point;

		for (; PointInPolygon; PointInPolygon = PointInPolygon->NextSiblingElement())
		{
			PointInPolygon->Attribute("x", &point.mX);
			PointInPolygon->Attribute("y", &point.mY);

			polygon->PushPoint(point);
		}

		polygon->SetID(polygonID);
		polygon->mG = 0;
		polygon->mH = 0;
		polygon->mParent = nullptr;

		FillPolygonEdges(*polygon);
		CalculatePolygonCenter(*polygon);

		Polygons.push_back(polygon);

		polygonID += 1;
	}

	// Links
	TiXmlHandle hLinks = hRoot.FirstChildElement("links");

	TiXmlElement* linkElem = hLinks.FirstChild().Element();
	TiXmlElement* linkStartElem = nullptr;
	TiXmlElement* linkEndElem = nullptr;

	int linkID = 0;

	for (linkElem; linkElem; linkElem = linkElem->NextSiblingElement())
	{
		Link* link = new Link();

		linkStartElem = linkElem->FirstChildElement("start");
		linkEndElem = linkElem->FirstChildElement("end");

		int startPolygon;
		int startPolygonEdgeStart;
		int startPolygonEdgeEnd;

		int endPolygon;
		int endPolygonEdgeStart;
		int endPolygonEdgeEnd;

		linkStartElem->Attribute("polygon", &startPolygon);
		linkStartElem->Attribute("edgestart", &startPolygonEdgeStart);
		linkStartElem->Attribute("edgeend", &startPolygonEdgeEnd);

		linkEndElem->Attribute("polygon", &endPolygon);
		linkEndElem->Attribute("edgestart", &endPolygonEdgeStart);
		linkEndElem->Attribute("edgeend", &endPolygonEdgeEnd);

		link->StartPolygon = Polygons.at(startPolygon);
		link->StartEdge.Start = link->StartPolygon->GetPointAtPosition(startPolygonEdgeStart);
		link->StartEdge.End = link->StartPolygon->GetPointAtPosition(startPolygonEdgeEnd);

		link->EndPolygon = Polygons.at(endPolygon);
		link->EndEdge.Start = link->EndPolygon->GetPointAtPosition(endPolygonEdgeStart);
		link->EndEdge.End = link->EndPolygon->GetPointAtPosition(endPolygonEdgeEnd);

		link->ID = linkID;

		CalculateLinkCenterAndFillNeighbours(*link);
		Links.push_back(link);

		linkID += 1;
	}

	return true;
}

void Navmesh::FillPolygonEdges(Polygon& polygon)
{
	const int NumberPoints = polygon.GetVectorVertices().size();
	Edge edge;

	for (int i = 0; i < NumberPoints; ++i)
	{
		if (i == NumberPoints - 1)
		{
			edge.Start = { polygon.GetPointAtPosition(i).mX, polygon.GetPointAtPosition(i).mY };
			edge.End = { polygon.GetPointAtPosition(0).mX, polygon.GetPointAtPosition(0).mY };

			polygon.PushEdge(edge);
		}
		else
		{
			edge.Start = { polygon.GetPointAtPosition(i).mX, polygon.GetPointAtPosition(i).mY };
			edge.End = { polygon.GetPointAtPosition(i + 1).mX, polygon.GetPointAtPosition(i + 1).mY };

			polygon.PushEdge(edge);
		}
	}
}

void Navmesh::CalculatePolygonCenter(Polygon& polygon)
{
	USVec2D Center = USVec2D(0.0f, 0.0f);

	float Area = 0.0f;
	float PartialArea = 0.0f;

	float CurrentVertexX = 0.0f;
	float CurrentVertexY = 0.0f;

	float NextVertexX = 0.0f;
	float NextVertexY = 0.0f;

	const int NumVertex = polygon.GetVectorVertices().size();

	int i = 0;

	for (i = 0; i < NumVertex - 1; ++i)
	{
		CurrentVertexX = polygon.GetVectorVertices().at(i).mX;
		CurrentVertexY = polygon.GetVectorVertices().at(i).mY;

		NextVertexX = polygon.GetVectorVertices().at(i + 1).mX;
		NextVertexY = polygon.GetVectorVertices().at(i + 1).mY;

		PartialArea = CurrentVertexX * NextVertexY - NextVertexX * CurrentVertexY;
		Area += PartialArea;

		Center.mX += (CurrentVertexX + NextVertexX) * PartialArea;
		Center.mY += (CurrentVertexY + NextVertexY) * PartialArea;
	}

	CurrentVertexX = polygon.GetVectorVertices().at(i).mX;
	CurrentVertexY = polygon.GetVectorVertices().at(i).mY;

	NextVertexX = polygon.GetVectorVertices().at(0).mX;
	NextVertexY = polygon.GetVectorVertices().at(0).mY;

	PartialArea = CurrentVertexX * NextVertexY - NextVertexX * CurrentVertexY;;
	Area += PartialArea;

	Center.mX += (CurrentVertexX + NextVertexX) * PartialArea;
	Center.mY += (CurrentVertexY + NextVertexY) * PartialArea;

	Area *= 0.5f;
	Center.mX /= (6.0f * Area);
	Center.mY /= (6.0f * Area);

	polygon.SetCentroid(Center);
}

void Navmesh::CalculateLinkCenterAndFillNeighbours(Link& link)
{
	float startEdgeSquaredLength = 0.0f;
	float endEdgeSquaredLength = 0.0f;

	// Center point
	startEdgeSquaredLength = link.StartEdge.SquaredLegnth();
	endEdgeSquaredLength = link.EndEdge.SquaredLegnth();

	if (startEdgeSquaredLength < endEdgeSquaredLength)
	{
		link.Center = GetMiddlePoint(link.StartEdge.Start, link.StartEdge.End);
	}
	else
	{
		link.Center= GetMiddlePoint(link.EndEdge.Start, link.EndEdge.End);
	}

	// Neighbours
	link.StartPolygon->GetVectorNeighbours().push_back(link.EndPolygon);

	if (!PolygonContainsLink(link.StartPolygon, &link))
	{
		link.StartPolygon->GetVectorLinks().push_back(&link);
	}

	link.EndPolygon->GetVectorNeighbours().push_back(link.StartPolygon);

	if (!PolygonContainsLink(link.EndPolygon, &link))
	{
		link.EndPolygon->GetVectorLinks().push_back(&link);
	}
}

USVec2D Navmesh::GetMiddlePoint(USVec2D pointA, USVec2D pointB)
{

	return { (pointA.mX + pointB.mX) / 2, (pointA.mY + pointB.mY) / 2 };
}

bool Navmesh::PolygonContainsLink(Polygon* polygon, const Link* link)
{
	const int numberOfLinks = polygon->GetVectorLinks().size();

	for (int i = 0; i < numberOfLinks; ++i)
	{
		if (polygon->GetVectorLinks().at(i)->ID == link->ID)
		{
			return true;
		}
	}

	return false;
}
