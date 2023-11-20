#include "stdafx.h"
#include "state.h"
#include "action.h"
#include "transition.h"

void State::OnEnter()
{
	if (EnterAction != nullptr)
	{
		EnterAction->Start();
	}

	if (StateAction != nullptr)
	{
		StateAction->Start();
	}
}

void State::Update(float step)
{
	if (StateAction != nullptr)
	{
		StateAction->Update(step);
	}
}

void State::OnExit()
{
	if (StateAction != nullptr)
	{
		StateAction->End();
	}

	if (ExitAction != nullptr)
	{
		ExitAction->Start();
	}
}

float State::UpdateWaitTime(float step)
{
	CurrentWaitTime -= step;
	
	if (CurrentWaitTime <= 0.0f)
	{
		const float valueToReturn = CurrentWaitTime;

		CurrentWaitTime = InitialWaitTime;

		return valueToReturn;
	}

	return CurrentWaitTime;
}

void State::SetOwnerCharacter(Character* ownerCharacter)
{
	OwnerCharacter = ownerCharacter;

	if (EnterAction != nullptr)
	{
		EnterAction->SetOwnerCharacter(ownerCharacter);
	}

	if (ExitAction != nullptr)
	{
		ExitAction->SetOwnerCharacter(ownerCharacter);
	}

	if (StateAction != nullptr)
	{
		StateAction->SetOwnerCharacter(ownerCharacter);
	}

	const int numberOfTransitions = Transitions.size();

	for (int i = 0; i < numberOfTransitions; ++i)
	{
		if (Transitions.at(i) != nullptr)
		{
			Transitions.at(i)->SetOwnerCharacter(ownerCharacter);
		}
	}
}