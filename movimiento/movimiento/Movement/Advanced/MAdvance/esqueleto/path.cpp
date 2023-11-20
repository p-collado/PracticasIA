#include "stdafx.h"
#include <tinyxml.h>
#include "path.h"

bool ReadPathFromFile(const char* filename, Path& path)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Error en la lectura en %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Formato invañido en %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);
	TiXmlHandle hPoints = hRoot.FirstChildElement("points");

	TiXmlElement* pointElem = hPoints.FirstChild().Element();

	for (pointElem; pointElem; pointElem = pointElem->NextSiblingElement())
	{
	    const char* pointName = pointElem->Value();

	    if (!strcmp(pointName, "point"))
	    {
			float x = 0.0f;
			float y = 0.0f;

			pointElem->Attribute("x", &x);
			pointElem->Attribute("y", &y);

			path.PointList.push_back({ x, y });
	    }
	}
	
	return true;
}