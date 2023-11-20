#include <stdafx.h>
#include "character.h"
#include "pathfinding\pathfinder.h"
#include "statemachine.h"


Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f), mPathfinder(NULL)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END

	mStateMachine = new StateMachine();

	CurrentTarget = nullptr;

	Health = 0.0f;

	mHasReceivedDamage = false;
	InitialReceiveDamageTime = 0.5f;
	ReceiveDamageTime = 0.0f;
}

Character::~Character()
{

}

int Character::GetImageByIndex(const char* imageName) const
{
	const int numberOfImages = ImagesIDS.size();

	for (int i = 0; i < numberOfImages; ++i)
	{
		if (!strcmp(ImagesIDS.at(i), imageName))
		{
			return i;
		}
	}

	return -1;
}

void Character::ReadAndInitializeStateMachine(const char* filename)
{
	if (mStateMachine != nullptr && mStateMachine->ReadStateMachineFile(filename))
	{
		mStateMachine->SetCharacterReferences(this);
		mStateMachine->OnStart();
	}
}

void Character::AddImageName(const char* image)
{
	ImagesIDS.push_back(image);
}

void Character::OnStart()
{
	
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	if (CurrentTarget == nullptr)
	{
		const int numberOfTargets = Targets.size();

		if (numberOfTargets > 0)
		{
			CurrentTarget = Targets.back();
			Targets.pop_back();
		}
	}

	// Update receive damage timer
	if (ReceiveDamageTime > 0.0f)
	{
		ReceiveDamageTime -= step;
	}
	else if (ReceiveDamageTime <= 0.0f)
	{
		ReceiveDamageTime = 0.0f;
		mHasReceivedDamage = false;
	}

	// Update State Machine
	if (mStateMachine != nullptr && mStateMachine->HasBeenInitialized())
	{
		mStateMachine->Update(step);
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
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "setPathfinder",			_setPathfinder},
		{ "addImageName",						_addImageName },
		{ "readAndInitializeStateMachine",		_readAndInitializeStateMachine },
		{ "addTarget",							_addTarget},
		{ "setHealth",							_setHealth},
		{ "getPointerToThis",					_getPointerToThis },
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	const float pX = state.GetValue<float>(2, 0.0f);
	const float pY = state.GetValue<float>(2, 0.0f);

	self->SetLinearVelocity(pX, pY);

	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	const float angle = state.GetValue<float>(2, 0.0f);

	self->SetAngularVelocity(angle);

	return 0;
}

int Character::_setPathfinder(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	Pathfinder* pathfinder = state.GetLuaObject<Pathfinder>(2, true);

	self->mPathfinder = pathfinder;

	return 0;
}

int Character::_getPointerToThis(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	int pointer = reinterpret_cast<int>(self);

	lua_pushinteger(L, pointer);

	return 1;
}

int Character::_readAndInitializeStateMachine(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

		cc8* filename = lua_tostring(state, -1);

	self->ReadAndInitializeStateMachine(filename);

	lua_pop(L, -1);

	return 0;
}

int Character::_addTarget(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

		int targetToInt = lua_tonumber(L, -1);

	if (targetToInt != 0)
	{
		self->AddTarget(reinterpret_cast<Character*>(targetToInt));
	}

	lua_pop(L, -1);

	return 0;
}

int Character::_setHealth(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	const int health = lua_tonumber(L, -1);

	self->SetHealth(health);

	lua_pop(L, -1);

	return 0;
}

int Character::_addImageName(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

	cc8* image = lua_tostring(state, -1);

	self->AddImageName(image);

	lua_pop(L, -1);

	return 0;
}
