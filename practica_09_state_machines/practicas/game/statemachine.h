#pragma once

#include <vector>
#include <string>

class TiXmlElement;
class State;
class Character;
class Condition;
class Action;

class StateMachine
{
public:
	StateMachine() { CurrentState = nullptr;  mHasBeenInitialized = false; }

	bool HasBeenInitialized() const { return mHasBeenInitialized; }

	bool ReadStateMachineFile(const char* filename);
	void SetCharacterReferences(Character* ownerCharacter);

	void OnStart();
	void Update(float step);

private:
	bool mHasBeenInitialized;

	std::vector<State*> States;
	State* CurrentState;
	std::string InitialStateID;

	void ReadAction(TiXmlElement* actionElem, Action*& action, const char* actiontype, State* machine);
	void ReadTransitions(TiXmlElement* transitionsElem, State*& state);
	void ReadCondition(TiXmlElement* conditionElem, Condition*& condition);
};