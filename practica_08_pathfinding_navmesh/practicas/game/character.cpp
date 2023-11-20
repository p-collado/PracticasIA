#include <stdafx.h>
#include <tinyxml.h>
#include "character.h"
#include "pathfinding/pathfinder.h"
#include "SeekSteering.h"
#include "AlignSteering.h"
#include "ArriveSteering.h"

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END



}

Character::~Character()
{

}

void Character::SetPathfinder(Pathfinder* pathfinder)
{
	mPathfinder = pathfinder;
}

void Character::OnStart()
{
	ReadParams("params.xml",Params);
	Seek = new SeekSteering(this, GetParams().targetPosition);
	Arrive = new ArriveSteering(this, GetParams().targetPosition);
	Align = new AlignSteering(this, GetParams().targetPosition, 90);
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	if (mPathfinder == nullptr)
	{
		return;
	}

	Path path;
	path = mPathfinder->GetPath();

	const int size = path.Points.size();
	if (size > 0 && mPathfinder->StepPoint > 0)
	{
		Seek->Target = path.Points[mPathfinder->StepPoint - 1];
		Arrive->Target = path.Points[mPathfinder->StepPoint - 1];

		if ((GetLoc() - Params.targetPosition).Length() <= Params.arrive_radius && mPathfinder->StepPoint == size)
		{
			Accel = Arrive->GetSteering();
		}
		else
		{
			Accel = Seek->GetStearing();
		}

		Vel = GetLinearVelocity() + Accel * step;

		if (Vel.mX >= Params.max_velocity || Vel.mY >= Params.max_velocity)
		{
			SetLinearVelocity(Params.max_velocity, Params.max_velocity);
		}

		SetLinearVelocity(Vel.mX, Vel.mY);

		USVec2D newpos = GetLoc() + Vel * step;

		this->SetLoc(newpos);

		if ((GetLoc() - Seek->Target).Length() <= 10)
		{
			mPathfinder->StepPoint++;

			if (mPathfinder->StepPoint == size+1)
			{
				mPathfinder->StepPoint = 0;
			}
		}
	}
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//MOAIDraw::DrawPoint(0.0f, 0.0f);
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable[] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "setPathfinder",	_setPathfinder},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(2, 0.0f);
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

int Character::_setPathfinder(lua_State* L)
{

	MOAI_LUA_SETUP(Character, "U")

		void* ptr = lua_touserdata(state, 2);

	self->SetPathfinder(reinterpret_cast<Pathfinder*>(ptr));

	return 0;
}
	