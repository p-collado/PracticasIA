#pragma once

class Character;

class Condition
{
public:
	Condition() { CharacterRef = nullptr; }

	virtual bool Check() = 0;

	virtual void SetOwnerCharacter(Character* ownerCharacter) { CharacterRef = ownerCharacter; }

	virtual ~Condition(){}

protected:
	Character* CharacterRef;
};

class ConditionInverse : public Condition
{
public:
	ConditionInverse(Condition* subCondition) : Condition() { SubCondition = subCondition; }

	virtual void SetOwnerCharacter(Character* ownerCharacter);

	virtual bool Check() override;

	virtual ~ConditionInverse() {}

private:
	Condition* SubCondition;
};

class ConditionAnd : public Condition
{
public:
	ConditionAnd(std::vector<Condition*> subConditions) : Condition() { SubConditions = subConditions; }

	virtual void SetOwnerCharacter(Character* ownerCharacter);

	virtual bool Check() override;

	virtual ~ConditionAnd() {}

private:
	std::vector<Condition*> SubConditions;
};

class ConditionCheckForTarget : public Condition
{
public:
	ConditionCheckForTarget() : Condition() { }

	virtual bool Check();

	virtual ~ConditionCheckForTarget() {}
};

class ConditionCheckDistance : public Condition
{
public:
	ConditionCheckDistance(float threshold) : Condition() { Threshold = threshold; }

	virtual bool Check() override;

	virtual ~ConditionCheckDistance() {}

private:
	float Threshold;
};

class ConditionReceiveDamage : public Condition
{
public:
	ConditionReceiveDamage() : Condition() { }

	virtual bool Check() override;

	virtual ~ConditionReceiveDamage() {}
};

class ConditionCheckHealth : public Condition
{
public:
	ConditionCheckHealth(float value) : Condition() { Value = value; }

	virtual bool Check() override;

	virtual ~ConditionCheckHealth(){}

private:
	float Value;
};