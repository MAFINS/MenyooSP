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

#include <string>
#include <vector>
#include <utility>

typedef unsigned __int8 UINT8;

namespace PTFX {
	class LoopedPTFX;
}

namespace sub
{
	namespace BreatheStuff_catind
	{
		enum class BreathePtfxType : UINT8 { None, Blood, Fire, };
		extern const std::vector<std::pair<std::string, BreathePtfxType>> vCaptions_breatheStuffs;

		extern PTFX::LoopedPTFX _globalBreatheStuff_ptfx;
		extern BreathePtfxType loop_player_breatheStuff;

		void set_self_breathe_ptfx(const BreathePtfxType& type);


		void __AddOption(const std::string& text, const BreathePtfxType& type);

		void BreatheStuffSub_();

	}

}




