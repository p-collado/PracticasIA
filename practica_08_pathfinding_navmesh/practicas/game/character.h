#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class Pathfinder;
class SeekSteering;
class ArriveSteering;
class AlignSteering;

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
	Params GetParams() { return Params; }
	void SetPathfinder(Pathfinder* pathfinder);

	USVec2D Accel;
	USVec2D Vel;
	float AngularAccel;

private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	
	Pathfinder* mPathfinder;
	Params Params;
	


	SeekSteering* Seek;
	ArriveSteering* Arrive;
	AlignSteering* Align;

	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _setPathfinder(lua_State* L);
};

#endif