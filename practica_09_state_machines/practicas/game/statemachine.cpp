#include "stdafx.h"
#include "statemachine.h"
#include <tinyxml.h>
#include "state.h"
#include "action.h"
#include "transition.h"
#include "condition.h"
#include <vector>

bool StateMachine::ReadStateMachineFile(const char* filename)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		fprintf(stderr, "Couldn't read state machine from %s", filename);
		return false;
	}

	TiXmlHandle hDoc(&doc);

	TiXmlElement* pElem;
	pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
	{
		fprintf(stderr, "Invalid format for %s", filename);
		return false;
	}

	TiXmlHandle hRoot(pElem);
	TiXmlHandle hStates = hRoot.FirstChildElement("states");

	InitialStateID = hStates.Element()->Attribute("initial-state");

	TiXmlElement* stateElem = hStates.FirstChild().Element();

	for (stateElem; stateElem; stateElem = stateElem->NextSiblingElement())
	{
		State* state = new State();

		char aux[20];

		strcpy(aux, stateElem->Attribute("id"));

		//state->SetID(stateElem->Attribute("id"));
		state->SetID(aux);

		float waitTime = 0.0f;
		stateElem->Attribute("wait-time", &waitTime);
		state->SetWaitTime(waitTime);

		TiXmlElement* stateSubElem = stateElem->FirstChildElement();

		for (stateSubElem; stateSubElem; stateSubElem = stateSubElem->NextSiblingElement())
		{
			const char* subElemName = stateSubElem->Value();

			if (!strcmp(subElemName, "enter-action") || 
				!strcmp(subElemName, "exit-action") ||
				!strcmp(subElemName, "state-action"))
			{
				Action* action = nullptr;
				ReadAction(stateSubElem, action, subElemName, state);
			}
			else if (!strcmp(subElemName, "transitions"))
			{
				ReadTransitions(stateSubElem, state);
			}
		}

		States.push_back(state);
	}

	return true;
}

void StateMachine::ReadAction(TiXmlElement* actionElem, Action*& action, const char* actiontrigger, State* state)
{
	const char* actionElemName = actionElem->Value();
	const char* actionType = actionElem->Attribute("type");

	if (!strcmp(actionType, "set-image"))
	{
		action = new ActionSetImage(actionElem->Attribute("image"));
	}
	else if (!strcmp(actionType, "move-to-target"))
	{
		float speed = 0.0f;
		actionElem->Attribute("speed", &speed);
		action = new ActionMoveToTarget(speed);
	}
	else if (!strcmp(actionType, "attack"))
	{
		float damage = 0.0f;
		actionElem->Attribute("damage", &damage);
		action = new ActionAttack(damage);
	}
	else if (!strcmp(actionType, "die"))
	{
		action = new ActionDie();
	}

	if (!strcmp(actiontrigger, "enter-action"))
	{
		state->SetEnterAction(action);
	}
	else if (!strcmp(actiontrigger, "exit-action"))
	{
		state->SetExitAction(action);
	}
	else if (!strcmp(actiontrigger, "state-action"))
	{
		state->SetStateAction(action);
	}
}

void StateMachine::ReadTransitions(TiXmlElement* transitionsElem, State*& state)
{
	std::vector<Transition*> transitions;

	TiXmlElement* transitionElem = transitionsElem->FirstChildElement();

	for (transitionElem; transitionElem; transitionElem = transitionElem->NextSiblingElement())
	{
		Transition* transition = new Transition();

		transition->SetTargetStateID(transitionElem->Attribute("target-state"));

		TiXmlElement* transitionSubElem = transitionElem->FirstChildElement();

		if (transitionSubElem != nullptr)
		{
			for (transitionSubElem; transitionSubElem; transitionSubElem = transitionSubElem->NextSiblingElement())
			{
				const char* subElemName = transitionSubElem->Value();

				if (!strcmp(subElemName, "trigger-action"))
				{
					Action* action = nullptr;

					ReadAction(transitionSubElem, action, subElemName, state);

					transition->SetTriggerAction(action);
				}

				else if (!strcmp(subElemName, "condition"))
				{
					Condition* condition = nullptr;

					ReadCondition(transitionSubElem, condition);

					transition->SetCondition(condition);
				}
			}
		}

		transitions.push_back(transition);
	}

	state->SetTransitions(transitions);
}

void StateMachine::ReadCondition(TiXmlElement* conditionElem, Condition*& condition)
{
	if (conditionElem != nullptr)
	{
		const char* conditionType = conditionElem->Attribute("type");

		if (!strcmp(conditionType, "inverse"))
		{
			TiXmlElement* subConditionElem = conditionElem->FirstChildElement();
			Condition* subCondition = nullptr;

			ReadCondition(subConditionElem, subCondition);

			condition = new ConditionInverse(subCondition);
		}
		else if (!strcmp(conditionType, "and"))
		{
			TiXmlElement* subConditionElem = conditionElem->FirstChildElement();
			std::vector<Condition*> subConditions;

			for (subConditionElem; subConditionElem; subConditionElem = subConditionElem->NextSiblingElement())
			{
				Condition* subCondition = nullptr;

				ReadCondition(subConditionElem, subCondition);

				subConditions.push_back(subCondition);
			}

			condition = new ConditionAnd(subConditions);
		}
		else if (!strcmp(conditionType, "check-for-target"))
		{
			condition = new ConditionCheckForTarget();
		}
		else if (!strcmp(conditionType, "check-distance"))
		{
			float threshold = 0.0f;
			conditionElem->Attribute("threshold", &threshold);
			condition = new ConditionCheckDistance(threshold);
		}
		else if (!strcmp(conditionType, "receive-damage"))
		{
			condition = new ConditionReceiveDamage();
		}
		else if (!strcmp(conditionType, "check-health"))
		{
			float value = 0.0f;
			conditionElem->Attribute("value", &value);
			condition = new ConditionCheckHealth(value);
		}
	}
}

void StateMachine::SetCharacterReferences(Character* ownerCharacter)
{
	const int numberOfStates = States.size();

	for (int i = 0; i < numberOfStates; ++i)
	{
		if (States.at(i) != nullptr)
		{
			States.at(i)->SetOwnerCharacter(ownerCharacter);
		}
	}
}

void StateMachine::OnStart()
{
	const int numberOfStates = States.size();

	for (int i = 0; i < numberOfStates; ++i)
	{
		if (States.at(i) != nullptr)
		{
			if (!strcmp(States.at(i)->GetID(), InitialStateID.c_str()))
			{
				CurrentState = States.at(i);
			}

			std::vector<Transition*> transitions = States.at(i)->GetTransitions();
			const int numberOfTransitions = transitions.size();

			for (int j = 0; j < numberOfTransitions; ++j)
			{
				const char* targetStateID = transitions.at(j)->GetTargetStateID();

				for (int k = 0; k < numberOfStates; ++k)
				{
					if (!strcmp(States.at(k)->GetID(), targetStateID))
					{
						transitions.at(j)->SetTargetState(States.at(k));
					}
				}
			}
		}
	}

	if (CurrentState != nullptr)
	{
		CurrentState->OnEnter();
	}

	mHasBeenInitialized = true;
}

void StateMachine::Update(float step)
{
	if (CurrentState != nullptr)
	{
		CurrentState->Update(step);

		if (CurrentState->UpdateWaitTime(step) <= 0.0f)
		{
			std::vector<Transition*> transitions = CurrentState->GetTransitions();
			const int numberOfTransitions = transitions.size();

			for (int i = 0; i < numberOfTransitions; ++i)
			{
				if (transitions.at(i)->CanTrigger(step) && transitions.at(i)->GetTargetState() != nullptr)
				{
					CurrentState->OnExit();
					State* nextState = transitions.at(i)->Trigger();
					if (nextState)
					{
						nextState->OnEnter();
					}
					CurrentState = nextState;
					return;
				}
			}
		}
	}
}