#pragma once

#include <vector>
#include <string>

class Action;
class Transition;
class Character;

class State
{
public:
	State() { EnterAction = nullptr; ExitAction = nullptr; StateAction = nullptr; InitialWaitTime = 0.0f; CurrentWaitTime = 0.0f; }

	void OnEnter();
	void Update(float step);
	void OnExit();

	Action* GetEnterAction() const { return EnterAction; }
	void SetEnterAction(Action* enterAction) { EnterAction = enterAction; }

	Action* GetExitAction() const { return ExitAction; }
	void SetExitAction(Action* exitAction) { ExitAction = exitAction; }

	Action* GetStateAction() const { return StateAction; }
	void SetStateAction(Action* stateAction) { StateAction = stateAction; }

	std::vector<Transition*> GetTransitions() const { return Transitions; }
	void SetTransitions(std::vector<Transition*> transitions) { Transitions = transitions; }

	const char* GetID() const { return ID.c_str(); }
	void SetID(const char* ID) { this->ID.assign(ID); }

	float GetInitialWaitTime() const { return InitialWaitTime; }
	float GetCurrentWaitTime() const { return CurrentWaitTime; }
	void SetWaitTime(float initialWaitTime) { InitialWaitTime = initialWaitTime; CurrentWaitTime = initialWaitTime; }
	float UpdateWaitTime(float step);

	void SetOwnerCharacter(Character* ownerCharacter);

protected:

	Action* EnterAction;
	Action* ExitAction;
	Action* StateAction;

	std::vector<Transition*> Transitions;
	std::string ID;

	Character* OwnerCharacter;

	float InitialWaitTime;
	float CurrentWaitTime;

};