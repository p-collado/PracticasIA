#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include <params.h>
#include <moaicore/MOAIMutex_win32.h>
#include "AlignSteering.h"
#include "ArriveSteering.h"
#include "SeekSteering.h"
#include "PathFollowingSteering.h"

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END

}

Character::~Character()
{
	
}

void Character::OnStart()
{
  ReadParams("params.1.xml", mParams);
	ReadPathFromFile("path.xml", Path);
	Seek =  new SeekSteering(this, GetParams().targetPosition);
	Arrive = new ArriveSteering(this, GetParams().targetPosition);
	Align = new AlignSteering(this, GetParams().targetPosition, 90);
	PathFollowing = new PathFollowingSteering(this);
	Arrive->Target = Path.PointList[Path.PointList.size()-1];
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	if ((GetLoc() - Path.PointList.at(Path.PointList.size()-1)).Length() <= mParams.arrive_radius)
	{
		Accel = Arrive->GetSteering();
	}
	else
	{
		Accel = PathFollowing->GetSteering(mParams.targetPosition);
	}
	
	Vel = GetLinearVelocity() + Accel * step;

	if (Vel.mX >= mParams.max_velocity || Vel.mY >=mParams.max_velocity)
	{
		SetLinearVelocity(mParams.max_velocity,mParams.max_velocity);
	}
	
	SetLinearVelocity(Vel.mX , Vel.mY);
	
	USVec2D newpos = GetLoc() + Vel * step;
	
	this->SetLoc(newpos);

	AngularAccel = Align->GetSteering();
	const float VelNewAngle = GetAngularVelocity() + AngularAccel * step;
	SetAngularVelocity(VelNewAngle);
	SetRot(GetRot() + GetAngularVelocity() * step);

}

void Character::DrawDebug()
{
	Seek->DrawDebug();
	Arrive->DrawDebug();
	PathFollowing->DrawDebug();
	Align->DrawDebug();
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	