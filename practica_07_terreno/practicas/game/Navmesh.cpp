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

		FillPolygonEdges(*polygon);

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

		Links.push_back(link);

		linkID += 1;
	}

	return true;
}

void Navmesh::FillPolygonEdges(Polygon& polygon)
{
	const int numberOfPoints = polygon.GetVectorVertices().size();
	Edge edge;

	for (int i = 0; i < numberOfPoints; ++i)
	{
		if (i == numberOfPoints - 1)
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