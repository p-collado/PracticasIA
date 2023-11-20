#include "stdafx.h"
#include "action.h"
#include "character.h"

void ActionSetImage::Start()
{
	if (CharacterRef)
	{
		const int imageIndex = CharacterRef->GetImageByIndex(ImageID.c_str());
		CharacterRef->SetImage(imageIndex);
	}
}

void ActionMoveToTarget::Update(float step)
{
	if (CharacterRef)
	{
		Character* target = CharacterRef->GetCurrentTarget();

		Move(target, step);
	}
}

void ActionMoveToTarget::Move(Character* target, float step)
{
	if (target)
	{
		USVec2D direction = target->GetLoc() - CharacterRef->GetLoc();
		const float length = direction.Length();

		if (length > 0.0f)
		{
			direction.NormSafe();
			direction *= Speed;
			CharacterRef->SetLoc(CharacterRef->GetLoc() + direction * step);
		}
	}
}

void ActionAttack::Start()
{
	if (CharacterRef)
	{
		Character* target = CharacterRef->GetCurrentTarget();

		Attack(target);
	}
}

void ActionAttack::Attack(Character* target)
{
	if (target)
	{
		target->ReceiveDamage(Damage);

		if (target->IsDead())
		{
			CharacterRef->DeleteCurrentTarget();
		}
	}
}

void ActionDie::Start()
{
	if (CharacterRef)
	{
		CharacterRef->Die();
	}
}