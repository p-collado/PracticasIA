#include <stdafx.h>

#include "pathfinder.h"
#include "Polygon.h"
#include "Link.h"

Pathfinder::Pathfinder() : MOAIEntity2D()
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END

		StepPoint = 1;
    Navmesh.ReadNavmesh("navmesh.xml");
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::UpdatePath()
{
	ResetMetrics();

	if (StartPolygon == nullptr || TargetPolygon == nullptr)
	{
		return;
	}

	OpenList.push_back(StartPolygon);

	while (OpenList.size() > 0)
	{
		Polygon* currentPolygon = RemoveLowestCostPolygon(OpenList);

		if (currentPolygon)
		{
			ClosedList.push_back(currentPolygon);

			if (currentPolygon->GetID() == TargetPolygon->GetID())
			{
				MakePath(currentPolygon);
				return;
			}

			int numberOfNeighbours = currentPolygon->GetVectorNeighbours().size();

			for (int i = 0; i < numberOfNeighbours; ++i)
			{
				if (ListContainsPolygon(currentPolygon->GetVectorNeighbours().at(i), ClosedList))
				{
					continue;
				}

				int costToNeighbour = currentPolygon->mG + GetPolygonsDistance(currentPolygon, currentPolygon->GetVectorNeighbours().at(i));

				if (costToNeighbour < currentPolygon->GetVectorNeighbours().at(i)->mG || !ListContainsPolygon(currentPolygon->GetVectorNeighbours().at(i), OpenList))
				{
					currentPolygon->GetVectorNeighbours().at(i)->mG = costToNeighbour;
					currentPolygon->GetVectorNeighbours().at(i)->mH = GetPolygonsDistance(currentPolygon->GetVectorNeighbours().at(i), TargetPolygon);
					currentPolygon->GetVectorNeighbours().at(i)->mParent = currentPolygon;

					if (!ListContainsPolygon(currentPolygon->GetVectorNeighbours().at(i), OpenList))
					{
						OpenList.push_back(currentPolygon->GetVectorNeighbours().at(i));
					}
				}
			}
		}
	}

	StepPoint = 1;
}

Polygon* Pathfinder::RemoveLowestCostPolygon(std::vector<Polygon*>& list)
{
	const int OpenListSize = list.size();

	if (OpenListSize > 0)
	{
		Polygon* PolygonToReturn = list.at(0);
		int NodeWithLowestCostIndex = 0;

		for (int i = 0; i < OpenListSize; ++i)
		{
			if (list.at(i)->GetCost() < PolygonToReturn->GetCost())
			{
				PolygonToReturn = list.at(i);
				NodeWithLowestCostIndex = i;
			}
		}

		list.erase(list.begin() + NodeWithLowestCostIndex);

		return PolygonToReturn;
	}

	return nullptr;

}

void Pathfinder::DrawDebug()
{
  MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

  const int numberOfPolygons = Navmesh.GetVectorPolygon().size();
  const int numberOfLinks = Navmesh.GetVectorLinks().size();

  // Polygons
  for (int i = 0; i < numberOfPolygons; ++i)
  {
    gfxDevice.SetPenColor(1.f, 0.0f, 0.f, 0.2f);
    MOAIDraw::DrawPolygonFilled(Navmesh.GetVectorPolygon().at(i)->GetVectorVertices());

    gfxDevice.SetPenColor(0.f, 0.f, 1.f, 1.0f);
    MOAIDraw::DrawPolygon(Navmesh.GetVectorPolygon().at(i)->GetVectorVertices());
  }

  // Links
  for (int i = 0; i < numberOfLinks; ++i)
  {
    gfxDevice.SetPenColor(0.0f, 1.f, 0.0f, 1.0f);


    MOAIDraw::DrawLine(Navmesh.GetVectorLinks().at(i)->StartEdge.Start, Navmesh.GetVectorLinks().at(i)->StartEdge.End);
    MOAIDraw::DrawLine(Navmesh.GetVectorLinks().at(i)->EndEdge.Start, Navmesh.GetVectorLinks().at(i)->EndEdge.End);
  }

	// Start and target position
	gfxDevice.SetPenColor(0.8f, 0.75f, 0.0f, 1.0f);
	MOAIDraw::DrawEllipseFill(StartPosition.mX, StartPosition.mY, 6, 6, 50);

	gfxDevice.SetPenColor(0.0f, 0.75f, 0.8f, 1.0f);
	MOAIDraw::DrawEllipseFill(EndPosition.mX, EndPosition.mY, 6, 6, 50);

	const int pathSize = mPath.Points.size();

	if (pathSize > 0)
	{
		for (int i = 0; i < pathSize; ++i)
		{
			if (i > 0)
			{
				gfxDevice.SetPenColor(0.f, 0.f, 0.f, 1.0f);
				MOAIDraw::DrawLine(mPath.Points.at(i - 1), mPath.Points.at(i));
			}
		}
	}
}

void Pathfinder::SetStartPosition(float x, float y)
{
  StartPolygon = GetPolygonFromPosition({ x, y });

  if (StartPolygon)
  {
    StartPosition = USVec2D(x, y);
    UpdatePath();
  }
}

void Pathfinder::SetEndPosition(float x, float y)
{
  TargetPolygon = GetPolygonFromPosition({ x, y });

  if (TargetPolygon)
  {
    EndPosition = USVec2D(x, y);
    UpdatePath();
  }
}

Polygon* Pathfinder::GetPolygonFromPosition(USVec2D position)
{
	const int numberOfPolygons = Navmesh.GetVectorPolygon().size();
	int numberOfPoints = 0;

	// Get max and min point values
	for (int i = 0; i < numberOfPolygons; ++i)
	{
		numberOfPoints = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().size();

		float minX = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(0).mX;
		float maxX = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(0).mX;
		float minY = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(0).mY;
		float maxY = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(0).mY;

		for (int j = 0; j < numberOfPoints; ++j)
		{
			if (Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mX < minX)
			{
				minX = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mX;
			}
			else if (Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mX > maxX)
			{
				maxX = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mX;
			}

			if (Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mY < minY)
			{
				minY = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mY;
			}
			else if (Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mY > maxY)
			{
				maxY = Navmesh.GetVectorPolygon().at(i)->GetVectorVertices().at(j).mY;
			}
		}

		if (position.mX >= minX && position.mX <= maxX && position.mY >= minY && position.mY <= maxY)
		{
			return Navmesh.GetVectorPolygon().at(i);
		}
	}

	return nullptr;
}

void Pathfinder::MakePath(Polygon* polygon)
{
	if (polygon)
	{
		Polygon* pathPolygon = polygon;
		mPath.Points.push_back(EndPosition);
		while (pathPolygon->mParent != nullptr)
		{
			GeneratePath(pathPolygon);
		}
		mPath.Points.insert(mPath.Points.begin(), StartPosition);
	}
}

void Pathfinder::GeneratePath(Polygon*& pathPolygon)
{
	const int numberOfLinks = pathPolygon->GetVectorLinks().size();
	for (int i = 0; i < numberOfLinks; ++i)
	{
		if (pathPolygon->GetVectorLinks().at(i)->StartPolygon->GetID() == pathPolygon->mParent->GetID() ||
			pathPolygon->GetVectorLinks().at(i)->EndPolygon->GetID() == pathPolygon->mParent->GetID())
		{
			mPath.Points.insert(mPath.Points.begin(), pathPolygon->GetVectorLinks().at(i)->Center);
		}
	}
	pathPolygon = pathPolygon->mParent;
}

bool Pathfinder::PathfindStep()
{
    // returns true if pathfinding process finished
    return true;
}

void Pathfinder::ResetMetrics()
{
	mPath.Points.clear();
	OpenList.clear();
	ClosedList.clear();

	const int numberOfPolygons = Navmesh.GetVectorPolygon().size();

	for (int i = 0; i < numberOfPolygons; ++i)
	{
		Navmesh.GetVectorPolygon().at(i)->mG = 0;
		Navmesh.GetVectorPolygon().at(i)->mH = 0;
		Navmesh.GetVectorPolygon().at(i)->mParent = nullptr;
	}
}

void Pathfinder::setStep(int step)
{
	StepPoint = step;
}

bool Pathfinder::ListContainsPolygon(const Polygon* polygon, const std::vector<Polygon*>& list)
{

	int listSize = list.size();

	for (int i = 0; i < listSize; ++i)
	{
		if (list[i]->GetID() == polygon->GetID())
		{
			return true;
		}
	}

	return false;
}

int Pathfinder::GetPolygonsDistance(const Polygon* polygonA, const Polygon* polygonB)
{
	int distanceX = abs(polygonA->GetCentroid().mX - polygonB->GetCentroid().mX);
	int distanceY = abs(polygonA->GetCentroid().mY - polygonB->GetCentroid().mY);

	if (distanceX > distanceY)
	{
		return 14 * distanceY + 10 * (distanceX - distanceY);
	}

	return 14 * distanceX + 10 * (distanceY - distanceX);
}

//lua configuration ----------------------------------------------------------------//
void Pathfinder::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity::RegisterLuaFuncs(state);

	luaL_Reg regTable [] = {
		{ "setStartPosition",		_setStartPosition},
		{ "setEndPosition",			_setEndPosition},
    { "pathfindStep",           _pathfindStep},
		{"getPointerToThis", _getPointerToThis},
		{"setStep",						_setStep},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Pathfinder::_setStartPosition(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetStartPosition(pX, pY);
	return 0;
}

int Pathfinder::_setEndPosition(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetEndPosition(pX, pY);
	return 0;
}

int Pathfinder::_pathfindStep(lua_State* L)
{
    MOAI_LUA_SETUP(Pathfinder, "U")

    self->PathfindStep();
    return 0;
}

int Pathfinder::_getPointerToThis(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

		lua_pushlightuserdata(state, self->GetPointerToThis());

	return 1;
}

int Pathfinder::_setStep(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	self->setStep(1);

	return 0;
}