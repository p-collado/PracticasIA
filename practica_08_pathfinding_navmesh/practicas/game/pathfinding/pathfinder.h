#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <moaicore/MOAIEntity2D.h>
#include <Navmesh.h>

struct Path
{
	std::vector<USVec2D> Points;
};

class Pathfinder: public virtual MOAIEntity2D
{
public:
	Pathfinder();
	~Pathfinder();

	int StepPoint;
	Navmesh Navmesh;

	virtual void DrawDebug();

	void SetStartPosition(float x, float y);
	void SetEndPosition(float x, float y);
	const USVec2D& GetStartPosition() const { return StartPosition;}
	const USVec2D& GetEndPosition() const { return EndPosition;}
	Polygon* GetPolygonFromPosition(USVec2D position);
	void MakePath(Polygon* polygon);
	bool PathfindStep();
	void ResetMetrics();
	Pathfinder* GetPointerToThis() { return this; }
	Path GetPath() { return mPath; }
	void setStep(int step);

private:
	void UpdatePath();
	Polygon* RemoveLowestCostPolygon(std::vector<Polygon*>& list);
	bool ListContainsPolygon(const Polygon* polygon, const std::vector<Polygon*>& list);
	int GetPolygonsDistance(const Polygon* polygonA, const Polygon* polygonB);
	void GeneratePath(Polygon*& poly);

private:
	USVec2D StartPosition;
	USVec2D EndPosition;
	Polygon* StartPolygon;
	Polygon* TargetPolygon;
	Path mPath;
	std::vector<Polygon*> OpenList;
	std::vector<Polygon*> ClosedList;

	// Lua configuration
public:
	DECL_LUA_FACTORY(Pathfinder)
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setStartPosition(lua_State* L);
	static int _setEndPosition(lua_State* L);
    static int _pathfindStep(lua_State* L);
		static int _getPointerToThis(lua_State* L);
		static int _setStep(lua_State* L);
};


#endif