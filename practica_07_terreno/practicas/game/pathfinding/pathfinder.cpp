#include <stdafx.h>

#include "pathfinder.h"
#include "Polygon.h"
#include "Link.h"

Pathfinder::Pathfinder() : MOAIEntity2D()
{
  RTTI_BEGIN
    RTTI_EXTEND(MOAIEntity2D)
    RTTI_END

    Navmesh.ReadNavmesh("navmesh.xml");
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::UpdatePath()
{

}

void Pathfinder::DrawDebug()
{
  MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

  const int numberOfPolygons = Navmesh.GetVectorPolygon().size();
  const int numberOfLinks = Navmesh.GetVectorLinks().size();

  // Polygons
  for (int i = 0; i < numberOfPolygons; ++i)
  {
    gfxDevice.SetPenColor(1.f, 0.0f, 0.f, 0.7f);
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
}

bool Pathfinder::PathfindStep()
{
    // returns true if pathfinding process finished
    return true;
}

//lua configuration ----------------------------------------------------------------//
void Pathfinder::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity::RegisterLuaFuncs(state);

	luaL_Reg regTable [] = {
		{ "setStartPosition",		_setStartPosition},
		{ "setEndPosition",			_setEndPosition},
        { "pathfindStep",           _pathfindStep},
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