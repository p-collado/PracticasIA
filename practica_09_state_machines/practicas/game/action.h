#pragma once

#include <string>

class Character;

class Action
{
public:
	virtual void Start() = 0;
	virtual void Update(float step) = 0;
	virtual void End() = 0;

	virtual ~Action() {};

	void SetOwnerCharacter(Character* ownerCharacter) { CharacterRef = ownerCharacter; }

protected:
	Character* CharacterRef;
};

class ActionSetImage : public Action
{
public:
	ActionSetImage(const char* image) { ImageID = image; }

	virtual void Start() override;
	virtual void Update(float step) override { }
	virtual void End() override { }

	virtual ~ActionSetImage() {};

private:
	std::string ImageID;
};

class ActionMoveToTarget : public Action
{
public:
	ActionMoveToTarget(float speed) { Speed = speed; }

	virtual void Start() override { }
	virtual void Update(float step) override;
	virtual void End() override { }

	virtual ~ActionMoveToTarget(){}

private:
	void Move(Character* character, float step);
	float Speed;
};

class ActionAttack : public Action
{
public:
	ActionAttack(float damage) { Damage = damage; }

	virtual void Start() override;
	virtual void Update(float step) override{ }
	virtual void End() override{ }

	virtual ~ActionAttack(){}

private:
	void Attack(Character* character);
	float Damage;
};

class ActionDie : public Action
{
public:
	ActionDie() { }

	virtual void Start() override;
	virtual void Update(float step) override{ }
	virtual void End() override{ }

	virtual ~ActionDie(){}
};