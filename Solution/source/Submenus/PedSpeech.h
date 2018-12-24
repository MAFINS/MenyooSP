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
#include <array>

typedef unsigned short uint16_t;

namespace sub
{
	namespace Speech_catind
	{
		//#pragma region ambient speech names old
		struct SpeechNameS { std::string title, label; };
		extern std::vector<SpeechNameS> vSpeechNames;
		//#pragma region ambient speech voice names old
		struct VoiceNameS { std::string title, label; };
		extern std::vector<VoiceNameS> vVoiceNames;
		//#pragma region ambient speech data organised old
		struct AmbientSpeechDataS { std::string title, voiceName, speechName, paramName; };
		extern const std::vector<AmbientSpeechDataS> vSpeechData;
		//#pragma region ambient speech SPEECH_PARAM names
		struct SpeechParamS { std::string title, label; };
		extern const std::array<SpeechParamS, 37> vSpeechParams;

		struct AmbientVoice_t
		{
			std::string voiceName;
			std::vector<std::string> speechNames;
		};
		extern std::vector<AmbientVoice_t> vVoiceData;

		extern AmbientVoice_t* _currVoiceInfo;
		extern uint16_t _currSpeechParamIndex;

		//extern std::string& _searchStr;

		bool PopulateVoiceData();

		void Sub_VoiceChanger();

		void Sub_AmbientSpeechPlayer();
		void Sub_AmbientSpeechPlayer_InVoice();

	}

}




