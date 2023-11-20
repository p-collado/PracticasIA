#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>
#include "path.h"

class AlignSteering;
class ArriveSteering;
class SeekSteering;
class PathFollowingSteering;

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
    void OnStart() override;
	virtual void OnStop();
    void OnUpdate(float step) override;
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}

	Params GetParams()const {return mParams;}
	Path GetPath() { return this->Path; }

	USVec2D Accel;
	USVec2D Vel;
	float AngularAccel;
	SeekSteering* Seek;
	ArriveSteering* Arrive;
	AlignSteering* Align;
	PathFollowingSteering* PathFollowing;

	Path Path;
	
private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	
	Params mParams;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

#endif