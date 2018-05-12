#ifndef __GOAL_H__
#define __GOAL_H__

#include "ctModule.h"
#include "ctPoint.h"
#include "ctDefs.h"

#include <queue>
#include <list>
#include <algorithm>
using namespace std;

class Entity;
class Player;

class UIImage;
class UILabel;

enum GoalType {

	GoalType_NoType,

	// Composite Goals
	GoalType_Think,

	GoalType_IntroCinematic,
	GoalType_MoveToPos,

	// Atomic Goals

	GoalType_MaxTypes
};

enum GoalStatus {

	GoalStatus_Inactive, // the goal is waiting to be activated
	GoalStatus_Active, // the goal has been activated and will be processed each update step
	GoalStatus_Completed, // the goal has completed and will be removed on the next update
	GoalStatus_Failed // the goal has failed and will either replan or be removed on the next update
};

class Goal
{
public:

	Goal(Player* owner, GoalType goalType);
	~Goal();

	// Contains initialization logic (planning phase of the goal)
	/// It can be called any number of times to replan
	virtual void Activate();

	// It is executed each update step
	virtual GoalStatus Process(float dt);

	// Undertakes any necessary tidying up before a goal is exited
	/// It is called just before a goal is destroyed
	virtual void Terminate();

	virtual void AddSubgoal(Goal* goal);

	// -----

	void ActivateIfInactive();

	bool IsActive() const;
	bool IsInactive() const;
	bool IsCompleted() const;
	bool HasFailed() const;

	GoalType GetType() const;

protected:

	Player* owner = nullptr;
	GoalStatus goalStatus = GoalStatus_Inactive;
	GoalType goalType = GoalType_NoType;
};

// Atomic Goal: it cannot aggregate child goals
// Composite Goal: it can aggregate child goals

class AtomicGoal :public Goal
{
public:

	AtomicGoal(Player* owner, GoalType goalType);

	virtual void Activate();
	virtual GoalStatus Process(float dt);
	virtual void Terminate();
};

class CompositeGoal :public Goal
{
public:

	CompositeGoal(Player* owner, GoalType goalType);

	virtual void Activate();
	virtual GoalStatus Process(float dt);
	virtual void Terminate();

	// -----

	void AddSubgoal(Goal* goal);
	list<Goal*> GetSubgoalsList() const;

	// It is called each update step to process the subgoals
	// It ensures that all completed and failed goals are removed from the list before
	// processing the next subgoal in line and returning its status
	// If the subgoal list is empty, 'completed' is returned
	GoalStatus ProcessSubgoals(float dt);

	void ReactivateIfFailed();

	// Clears the subgoals list
	// It ensures that all subgoals are destroyed cleanly by calling each one's 'Terminate' method
	// before deletion
	void RemoveAllSubgoals();

protected:

	list<Goal*> subgoals;
};

// Composite Goals ---------------------------------------------------------------------

class Goal_Think :public CompositeGoal
{
public:

	Goal_Think(Player* owner);

	void Activate();
	GoalStatus Process(float dt);
	void Terminate();

	// Arbitrate between available strategies, choosing the most appropriate
	// to be pursued. Calculate the desirability of the strategies
	//void Arbitrate();
	void AddGoal_IntroCinematic(UIImage* title, UILabel* pressStart);
	void AddGoal_Goal_MoveCameraDownAndStartGame(UIImage* title);
};

class Goal_IntroCinematic :public CompositeGoal
{
public:

	Goal_IntroCinematic(Player* owner, UIImage* title, UILabel* pressStart);

	void Activate();
	GoalStatus Process(float dt);
	void Terminate();

private:

	UIImage* title = nullptr;
	UILabel* pressStart = nullptr;
};


class Goal_PressStart :public AtomicGoal
{
public:

	Goal_PressStart(Player* owner, UIImage* title, UILabel* pressStart);

	void Activate();
	GoalStatus Process(float dt);
	void Terminate();

private:

	UIImage* title = nullptr;
	UILabel* pressStart = nullptr;

	int alpha = 0;
};

class Goal_MoveCameraDownAndStartGame :public AtomicGoal
{
public:

	Goal_MoveCameraDownAndStartGame(Player* owner, UIImage* title);

	void Activate();
	GoalStatus Process(float dt);
	void Terminate();

private:

	UIImage* title = nullptr;

	int alpha = 0;
};

#endif //__GOAL_H__