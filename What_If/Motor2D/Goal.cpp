#include "ctDefs.h"
#include "ctLog.h"

#include "ctApp.h"
#include "Goal.h"
#include "ctGui.h"
#include "UIImage.h"
#include "UILabel.h"
#include "Entity.h"
#include "Player.h"
#include "ctInput.h"

//#include "Brofiler\Brofiler.h"

Goal::Goal(Player* owner, GoalType goalType) :owner(owner), goalType(goalType) {}

Goal::~Goal() {}

void Goal::Activate() {}

GoalStatus Goal::Process(float dt) { return goalStatus; }

void Goal::Terminate() {}

void Goal::AddSubgoal(Goal* goal) {}

void Goal::ActivateIfInactive()
{
	if (IsInactive())
		Activate();
}

bool Goal::IsActive() const
{
	return goalStatus == GoalStatus_Active;
}

bool Goal::IsInactive() const
{
	return goalStatus == GoalStatus_Inactive;
}

bool Goal::IsCompleted() const
{
	return goalStatus == GoalStatus_Completed;
}

bool Goal::HasFailed() const
{
	return goalStatus == GoalStatus_Failed;
}

GoalType Goal::GetType() const
{
	return goalType;
}

// AtomicGoal ---------------------------------------------------------------------

AtomicGoal::AtomicGoal(Player* owner, GoalType goalType) :Goal(owner, goalType) {}

void AtomicGoal::Activate() {}

GoalStatus AtomicGoal::Process(float dt) { return goalStatus; }

void AtomicGoal::Terminate() {}

// CompositeGoal ---------------------------------------------------------------------

CompositeGoal::CompositeGoal(Player* owner, GoalType goalType) : Goal(owner, goalType) {}

void CompositeGoal::Activate() {}

GoalStatus CompositeGoal::Process(float dt) { return goalStatus; }

void CompositeGoal::Terminate() {}

void CompositeGoal::AddSubgoal(Goal* goal)
{
	subgoals.push_front(goal);
}

list<Goal*> CompositeGoal::GetSubgoalsList() const 
{
	return subgoals;
}

GoalStatus CompositeGoal::ProcessSubgoals(float dt)
{
	// Remove all completed and failed goals from the front of the subgoal list
	while (subgoals.size() > 0
		&& (subgoals.front()->IsCompleted() || subgoals.front()->HasFailed())) {

		subgoals.front()->Terminate();
		delete subgoals.front();
		subgoals.pop_front();
	}

	// If any subgoals remain, process the one at the front of the list
	if (subgoals.size() > 0) {

		// Grab the status of the frontmost subgoal
		GoalStatus subgoalsStatus = subgoals.front()->Process(dt);

		// SPECIAL CASE: the frontmost subgoal reports 'completed' and the subgoal list
		// contains additional goals. To ensure the parent keeps processing its subgoal list,
		// the 'active' status is returned
		if (subgoalsStatus == GoalStatus_Completed && subgoals.size() > 1)
			return GoalStatus_Active;

		return subgoalsStatus;
	}
	else

		// No more subgoals to process. Return 'completed'
		return GoalStatus_Completed;
}

void CompositeGoal::ReactivateIfFailed()
{
	if (HasFailed())
		Activate();
}

void CompositeGoal::RemoveAllSubgoals()
{
	for (list<Goal*>::const_iterator it = subgoals.begin(); it != subgoals.end(); ++it) {

		(*it)->Terminate();
		delete *it;
	}

	subgoals.clear();
}

// COMPOSITE GOALS
// Goal_Think ---------------------------------------------------------------------

Goal_Think::Goal_Think(Player* owner) :CompositeGoal(owner, GoalType_Think) {}

void Goal_Think::Activate()
{
	goalStatus = GoalStatus_Active;

	// If this goal is reactivated then there may be some existing subgoals that
	// must be removed
	RemoveAllSubgoals();

	// Initialize the goal
	// TODO: Add some code here
}

GoalStatus Goal_Think::Process(float dt)
{
	// Process the subgoals
	ProcessSubgoals(dt);

	// If any of the subgoals have failed then this goal replans
	ReactivateIfFailed();

	return goalStatus;
}

void Goal_Think::Terminate()
{
	// Switch the goal off
	// TODO: Add some code here
}

void Goal_Think::AddGoal_IntroCinematic(UIImage* title, UILabel* pressStart)
{
	AddSubgoal(new Goal_IntroCinematic(owner, title, pressStart));
}

void Goal_Think::AddGoal_Goal_MoveCameraDownAndStartGame(UIImage* title)
{
	AddSubgoal(new Goal_MoveCameraDownAndStartGame(owner, title));
}

// Goal_WalkingIntro ---------------------------------------------------------------------

Goal_IntroCinematic::Goal_IntroCinematic(Player* owner, UIImage* title, UILabel* pressStart) :CompositeGoal(owner, GoalType_IntroCinematic), title(title), pressStart(pressStart) {}

void Goal_IntroCinematic::Activate()
{
	// This happens once (when this goal is started)
	goalStatus = GoalStatus_Active;
	// -----

	AddSubgoal(new Goal_PressStart(owner, title, pressStart));
}

GoalStatus Goal_IntroCinematic::Process(float dt)
{
	ActivateIfInactive();

	goalStatus = ProcessSubgoals(dt);
	// -----

	return goalStatus;
}

void Goal_IntroCinematic::Terminate()
{
	// This happens once (when this goal is completed)
}

// Goal_PressStart ---------------------------------------------------------------------

Goal_PressStart::Goal_PressStart(Player* owner, UIImage* title, UILabel* pressStart) :AtomicGoal(owner, GoalType_MoveToPos), title(title), pressStart(pressStart) {}

void Goal_PressStart::Activate()
{
	// This happens once (when this goal is started)
	goalStatus = GoalStatus_Active;
	// -----
}

GoalStatus Goal_PressStart::Process(float dt)
{
	ActivateIfInactive();
	// -----

	float speed = 0.0f;
	alpha -= 5.0f * dt;
	if (alpha <= 0)
		alpha = 255;

	pressStart->alpha = alpha;

	if (App->input->gamepad.A == GAMEPAD_STATE::PAD_BUTTON_DOWN) {

		alpha = 255;
		goalStatus = GoalStatus_Completed;
	}

	return goalStatus;
}

void Goal_PressStart::Terminate()
{
	// This happens once (when this goal is completed)
	App->gui->DeleteUIElement(*(UIElement*)pressStart);

	pressStart = nullptr;
}

// Goal_MoveCameraDownAndStartGame ---------------------------------------------------------------------

Goal_MoveCameraDownAndStartGame::Goal_MoveCameraDownAndStartGame(Player* owner, UIImage* title) :AtomicGoal(owner, GoalType_MoveToPos), title(title) {}

void Goal_MoveCameraDownAndStartGame::Activate()
{
	// This happens once (when this goal is started)
	goalStatus = GoalStatus_Active;
	// -----
}

GoalStatus Goal_MoveCameraDownAndStartGame::Process(float dt)
{
	ActivateIfInactive();
	// -----

	float speed = 0.0f;
	alpha -= 5.0f * dt;
	if (alpha <= 0)
		alpha = 0;

	title->alpha = alpha;



	//goalStatus = GoalStatus_Completed;

	return goalStatus;
}

void Goal_MoveCameraDownAndStartGame::Terminate()
{
	// This happens once (when this goal is completed)
	App->gui->DeleteUIElement(*(UIElement*)title);

	title = nullptr;
}