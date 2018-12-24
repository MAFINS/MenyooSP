/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "SpoonerTaskSequence.h"

#include "..\..\macros.h"

//#include "STSTask.h"
#include "STSTasks.h"

//#include "..\..\Menu\Menu.h"
//#include "..\..\Menu\Routine.h"

//#include "..\..\Natives\natives2.h"

#include <Windows.h> //GetTickCount
#include <vector>

namespace sub::Spooner
{
	SpoonerTaskSequence::SpoonerTaskSequence()
	{
		this->bJustJumpedToNext = false;
		this->progress = -1;
		this->timer = GetTickCount();
	}

	void SpoonerTaskSequence::operator = (const SpoonerTaskSequence& right)
	{
		this->bJustJumpedToNext = right.bJustJumpedToNext;
		this->progress = right.progress;
		this->timer = right.timer;
		this->tasks = right.tasks;
	}

	bool SpoonerTaskSequence::ContainsType(const STSTaskType& value)
	{
		for (auto& t : this->tasks)
		{
			if (t != nullptr)
			{
				if (t->type == value)
					return true;
			}
		}
		return false;
	}

	UINT16 SpoonerTaskSequence::TaskCount() const
	{
		return (UINT16)this->tasks.size();
	}
	bool SpoonerTaskSequence::empty() const
	{
		return this->tasks.empty();
	}

	inline void SpoonerTaskSequence::AddTask(STSTask* tskPtr)
	{
		this->tasks.push_back(tskPtr);
	}
	STSTask* SpoonerTaskSequence::AddTask(const STSTaskType& ofType)
	{
		STSTask* tskPtr = nullptr;
		switch (ofType)
		{
		case STSTaskType::Nothing: tskPtr = (new STSTasks::Nothing); break;
		case STSTaskType::SetHealth: tskPtr = (new STSTasks::SetHealth); break;
		case STSTaskType::AddBlip: tskPtr = (new STSTasks::AddBlip); break;
		case STSTaskType::RemoveBlip: tskPtr = (new STSTasks::RemoveBlip); break;
		case STSTaskType::Pause: tskPtr = (new STSTasks::Pause); break;
		case STSTaskType::UsePhone: tskPtr = (new STSTasks::UsePhone); break;
		case STSTaskType::ThrowProjectile: tskPtr = (new STSTasks::ThrowProjectile); break;
		case STSTaskType::Writhe: tskPtr = (new STSTasks::Writhe); break;
		case STSTaskType::FaceDirection: tskPtr = (new STSTasks::FaceDirection); break;
		case STSTaskType::FaceEntity: tskPtr = (new STSTasks::FaceEntity); break;
		case STSTaskType::LookAtCoord: tskPtr = (new STSTasks::LookAtCoord); break;
		case STSTaskType::LookAtEntity: tskPtr = (new STSTasks::LookAtEntity); break;
		case STSTaskType::TeleportToCoord: tskPtr = (new STSTasks::TeleportToCoord); break;
		case STSTaskType::SeekCoverAtCoord: tskPtr = (new STSTasks::SeekCoverAtCoord); break;
		case STSTaskType::SlideToCoord: tskPtr = (new STSTasks::SlideToCoord); break;
		case STSTaskType::GoToCoord: tskPtr = (new STSTasks::GoToCoord); break;
		case STSTaskType::FollowRoute: tskPtr = (new STSTasks::FollowRoute); break;
		case STSTaskType::FollowEntity: tskPtr = (new STSTasks::FollowEntity); break;
		case STSTaskType::PatrolInRange: tskPtr = (new STSTasks::PatrolInRange); break;
		case STSTaskType::WanderFreely: tskPtr = (new STSTasks::WanderFreely); break;
		case STSTaskType::FleeFromCoord: tskPtr = (new STSTasks::FleeFromCoord); break;
		case STSTaskType::NearestAppropriateAction: tskPtr = (new STSTasks::NearestAppropriateAction); break;
		case STSTaskType::ScenarioAction: tskPtr = (new STSTasks::ScenarioAction); break;
		case STSTaskType::PlayAnimation: tskPtr = (new STSTasks::PlayAnimation); break;
		case STSTaskType::SetActiveWeapon: tskPtr = (new STSTasks::SetActiveWeapon); break;
		case STSTaskType::AimAtCoord: tskPtr = (new STSTasks::AimAtCoord); break;
		case STSTaskType::AimAtEntity: tskPtr = (new STSTasks::AimAtEntity); break;
		case STSTaskType::ShootAtCoord: tskPtr = (new STSTasks::ShootAtCoord); break;
		case STSTaskType::ShootAtEntity: tskPtr = (new STSTasks::ShootAtEntity); break;
		case STSTaskType::FightHatedTargets: tskPtr = (new STSTasks::FightHatedTargets); break;
		case STSTaskType::FightPed: tskPtr = (new STSTasks::FightPed); break;
		case STSTaskType::SpeakToPed: tskPtr = (new STSTasks::SpeakToPed); break;
		case STSTaskType::PlaySpeechWithVoice: tskPtr = (new STSTasks::PlaySpeechWithVoice); break;

		case STSTaskType::WarpIntoVehicle: tskPtr = (new STSTasks::WarpIntoVehicle); break;
		case STSTaskType::EnterVehicle: tskPtr = (new STSTasks::EnterVehicle); break;
		case STSTaskType::ExitVehicle: tskPtr = (new STSTasks::ExitVehicle); break;
		case STSTaskType::DriveWander: tskPtr = (new STSTasks::DriveWander); break;
		case STSTaskType::DriveToCoord: tskPtr = (new STSTasks::DriveToCoord); break;
		case STSTaskType::DriveFollowEntity: tskPtr = (new STSTasks::DriveFollowEntity); break;
		case STSTaskType::DriveLandPlane: tskPtr = (new STSTasks::DriveLandPlane); break;

		case STSTaskType::AchieveVehicleForwardSpeed: tskPtr = (new STSTasks::AchieveVehicleForwardSpeed); break;
		case STSTaskType::EmptyVehicle: tskPtr = (new STSTasks::EmptyVehicle); break;

		case STSTaskType::ChangeTextureVariation: tskPtr = (new STSTasks::ChangeTextureVariation); break;

		case STSTaskType::AchieveVelocity: tskPtr = (new STSTasks::AchieveVelocity); break;
		case STSTaskType::AchievePushForce: tskPtr = (new STSTasks::AchievePushForce); break;
		case STSTaskType::OscillateToPoint: tskPtr = (new STSTasks::OscillateToPoint); break;
		case STSTaskType::OscillateToEntity: tskPtr = (new STSTasks::OscillateToEntity); break;
		case STSTaskType::FreezeInPlace: tskPtr = (new STSTasks::FreezeInPlace); break;
		case STSTaskType::SetRotation: tskPtr = (new STSTasks::SetRotation); break;
		case STSTaskType::ChangeOpacity: tskPtr = (new STSTasks::ChangeOpacity); break;
		case STSTaskType::TriggerFx: tskPtr = (new STSTasks::TriggerFx); break;

		case STSTaskType::SnapTasks: tskPtr = (new STSTasks::SnapTasks); break;
		case STSTaskType::EndSequence: tskPtr = (new STSTasks::EndSequence); break;
		}

		if (tskPtr != nullptr)
			this->tasks.push_back(tskPtr);
		return tskPtr;
	}

	void SpoonerTaskSequence::DeallocTask(STSTask* tskPtr)
	{
		if (tskPtr != nullptr)
		{
			delete tskPtr;
			//tskPtr = nullptr;
		}
	}
	void SpoonerTaskSequence::RemoveTask(UINT16 index)
	{
		if (this->tasks.size() < 2) // 1 or 0
		{
			this->Reset(true);
		}
		else
		{
			STSTask* tskPtr = this->tasks[index];
			DeallocTask(tskPtr);
			this->tasks.erase(this->tasks.begin() + index);
			//return this->tasks.erase(this->tasks.begin() + index);
		}
	}

	void SpoonerTaskSequence::SwapTasks(UINT16 index1, UINT16 index2)
	{
		if (index1 >= 0 && index1 < this->tasks.size()
			&& index2 >= 0 && index2 < this->tasks.size())
		{
			STSTask* t1 = this->tasks[index1];
			this->tasks[index1] = this->tasks[index2];
			this->tasks[index2] = t1;
		}
	}

	std::vector<STSTask*>& SpoonerTaskSequence::AllTasks()
	{
		return this->tasks;
	}

	bool SpoonerTaskSequence::IsActive() const
	{
		return this->progress >= 0;
	}
	void SpoonerTaskSequence::Start()
	{
		if (!this->tasks.empty())
		{
			this->bJustJumpedToNext = true;
			this->progress = 0;
			this->timer = GetTickCount() + this->tasks[0]->duration;
		}
	}
	void SpoonerTaskSequence::Reset(bool deleteTasks)
	{
		///CLEAR_PED_TASKS_IMMEDIATELY(ep.Handle()); // NO
		//this->bJustJumpedToNext = true;
		this->progress = -1;
		//this->timer = GetTickCount();
		if (deleteTasks)
		{
			for (STSTask* tskPtr : this->tasks)
			{
				DeallocTask(tskPtr);
			}
			this->tasks.clear();
		}
	}
	void SpoonerTaskSequence::Tick(void* ev)
	{
		/*Game::Print::setupdraw(GTAfont::Arial, Vector2(0.34f, 0.34f), false, true, true);
		Game::Print::drawstring(oss_ << "Task count = " << (int)this->tasks.size(), 0.9f, 0.23f);
		Game::Print::setupdraw(GTAfont::Arial, Vector2(0.34f, 0.34f), false, true, true);
		Game::Print::drawstring(oss_ << "Task index = " << (int)this->progress, 0.9f, 0.2f);
		Game::Print::setupdraw(GTAfont::Arial, Vector2(0.34f, 0.34f), false, true, true);
		Game::Print::drawstring(oss_ << "Just Jumped = " << (int)this->bJustJumpedToNext, 0.9f, 0.26f);
		if (this->progress < this->tasks.size())
		{
		Game::Print::setupdraw(GTAfont::Arial, Vector2(0.34f, 0.34f), false, true, true);
		Game::Print::drawstring(oss_ << "Current task duration = " << (int)this->tasks[this->progress]->duration, 0.9f, 0.29f);
		}
		Game::Print::setupdraw(GTAfont::Arial, Vector2(0.34f, 0.34f), false, true, true);
		Game::Print::drawstring(oss_ << "Timer = " << (int)this->timer, 0.9f, 0.32f);
		Game::Print::setupdraw(GTAfont::Arial, Vector2(0.34f, 0.34f), false, true, true);
		Game::Print::drawstring(oss_ << "TickCount = " << (int)GetTickCount(), 0.9f, 0.35f);*/

		if (this->progress < 0 || this->tasks.empty())
		{
			return;
			//goto label_returnPls;
		}
		else if (this->progress >= this->tasks.size()) { this->progress = 0; }

		STSTask* task = this->tasks[this->progress];

		if (this->bJustJumpedToNext || task->isLoopedTask)
		{
			task->Run(ev);
			this->bJustJumpedToNext = false;
			if (task->type == STSTaskType::EndSequence)
			{
				this->Reset();
				return;
				//goto label_returnPls;
			}
		}

		if (GetTickCount() > this->timer)
		{
			if (task->durationAfterLife <= 0)
				task->End(ev);
			INT16 nextTaskIndex = (this->progress + 1 >= this->tasks.size()) ?
				0 : this->progress + 1;
			STSTask* nextTask = this->tasks[nextTaskIndex];
			this->bJustJumpedToNext = true;
			this->progress++;
			this->timer = GetTickCount() + (nextTask->duration);
		}

		if (this->progress >= this->tasks.size())
		{
			this->Start(); // Repeat
		}

		//label_returnPls:;
	}

}



