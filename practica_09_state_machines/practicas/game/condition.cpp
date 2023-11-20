#include "stdafx.h"
#include "condition.h"
#include "character.h"

bool ConditionInverse::Check()
{
	bool result = false;
	SubCondition ? result = !SubCondition->Check() : result = false;
	return result;
}

void ConditionInverse::SetOwnerCharacter(Character* ownerCharacter)
{
	CharacterRef = ownerCharacter;

	if (SubCondition)
	{
		SubCondition->SetOwnerCharacter(ownerCharacter);
	}
}

bool ConditionAnd::Check()
{
	bool returnValue = false;

	const int NumSubConditions = SubConditions.size();

	for (int i = 0; i < NumSubConditions; ++i)
	{
		if (SubConditions.at(i))
		{
			i == 0 ? returnValue = SubConditions.at(i)->Check() : returnValue = returnValue && SubConditions.at(i)->Check();
		}
	}

	return returnValue;
}

void ConditionAnd::SetOwnerCharacter(Character* ownerCharacter)
{
	CharacterRef = ownerCharacter;

	const int NumSubconditions = SubConditions.size();

	for (int i = 0; i < NumSubconditions; ++i)
	{
		if (SubConditions.at(i))
		{
			SubConditions.at(i)->SetOwnerCharacter(ownerCharacter);
		}
	}
}

bool ConditionCheckForTarget::Check()
{
	bool result = false;
	CharacterRef && CharacterRef->GetCurrentTarget() ? result =  true : result =  false;
	return result;
}

bool ConditionCheckDistance::Check()
{
	bool result = false;

	if (CharacterRef)
	{
		Character* target = CharacterRef->GetCurrentTarget();

		if (target)
		{
			USVec2D characterLoc2D = USVec2D(CharacterRef->GetLoc().mX, CharacterRef->GetLoc().mY);
			USVec2D enemyLoc2D = USVec2D(target->GetLoc().mX, target->GetLoc().mY);
			const float distance = characterLoc2D.Dist(enemyLoc2D);
			distance <= Threshold ? result = true : result = false;
		}
	}
	return result;
}

bool ConditionReceiveDamage::Check()
{
	bool result = false;
	CharacterRef ? result = CharacterRef->HasReceivedDamage() : result = false;
	return result;
}

bool ConditionCheckHealth::Check()
{
	bool result = false;
	CharacterRef ? result = CharacterRef->GetHealth() <= Value : result = false;
	return result;
}