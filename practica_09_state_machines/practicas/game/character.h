#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class Pathfinder;
class StateMachine;

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
	int GetImageByIndex(const char* image) const;
	Character* GetCurrentTarget() const { return CurrentTarget; }
	void ReceiveDamage(float damage) { Health -= damage; mHasReceivedDamage = true; ReceiveDamageTime = InitialReceiveDamageTime; }
	bool IsDead() const { return Health <= 0.0f; }
	void Die() { RemoveEntity(this); }
	bool HasReceivedDamage() { return mHasReceivedDamage; mHasReceivedDamage = false; ReceiveDamageTime = 0.0f; }
	void DeleteCurrentTarget() { CurrentTarget = nullptr; }
	void AddTarget(Character* target) { Targets.push_back(target); }
	void ReadAndInitializeStateMachine(const char* filename);
	void SetHealth(float health) { Health = health; }
	float GetHealth() const { return Health; }
	void AddImageName(const char* image);
	Params GetParams() { return Param; }

private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	Pathfinder* mPathfinder;
	StateMachine* mStateMachine;
	Params Param;
	

	std::vector<const char*> ImagesIDS;
	Character* CurrentTarget;
	std::vector<Character*> Targets;
	float Health;
	bool mHasReceivedDamage;
	float InitialReceiveDamageTime;
	float ReceiveDamageTime;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
	static int _setPathfinder(lua_State* L);
	static int _getPointerToThis(lua_State* L);
	static int _readAndInitializeStateMachine(lua_State* L);
	static int _addTarget(lua_State* L);
	static int _setHealth(lua_State* L);
	static int _addImageName(lua_State* L);
};

#endif