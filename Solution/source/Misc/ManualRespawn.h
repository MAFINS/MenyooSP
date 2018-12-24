/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#pragma once

#include "GenericLoopedMode.h"

namespace _ManualRespawn_
{
	class ManualRespawn final : public GenericLoopedMode
	{
	private:
		bool inRespawn;
	public:
		ManualRespawn();

		bool InRespawn();

		void TurnOff() override;

		bool IsSkipPressed();

		inline void ShowRespawnHelpText();

		void Tick() override;
		inline void DoManualRespawnTick();

	};
	

	extern ManualRespawn g_manualRespawn;

	void ToggleOnOff();


	void Check_self_death_model();
}







