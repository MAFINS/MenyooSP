/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#include "keyboard.h"

#include <Windows.h>

#define NOW_PERIOD 100
#define MAX_DOWN 5000 // ms
#define KEYS_SIZE 255


bool get_key_pressed(DWORD key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}


struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];


void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}


bool IsKeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}



void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}


// Game
std::string VkCodeToStr(UINT8 key)
{
	// I can just use GetKeyNameTextA ?
	switch (key)
	{
	default: return ""; break;
	case VirtualKey::A:  return ("A"); break;
	case VirtualKey::Add:  return ("+"); break;
	case VirtualKey::Subtract:  return ("-"); break;
	case VirtualKey::B: return ("B"); break;
	case VirtualKey::C:  return ("C"); break;
	case VirtualKey::D:  return ("D"); break;
	case VirtualKey::Decimal:  return ("."); break;
	case VirtualKey::Delete:  return ("Delete"); break;
	case VirtualKey::Divide:  return ("/"); break;
	case VirtualKey::Up:  return ("Up"); break;
	case VirtualKey::Down:  return ("Down"); break;
	case VirtualKey::Left:  return ("Left"); break;
	case VirtualKey::Right:  return ("Right"); break;
	case VirtualKey::E:  return ("E"); break;
	case VirtualKey::End:  return ("End"); break;
	case VirtualKey::Escape:  return ("ESC"); break;
	case VirtualKey::F:  return ("F"); break;
	case VirtualKey::F1:  return ("F1"); break;
	case VirtualKey::F2:  return ("F2"); break;
	case VirtualKey::F3:  return ("F3"); break;
	case VirtualKey::F4:  return ("F4"); break;
	case VirtualKey::F5:  return ("F5"); break;
	case VirtualKey::F6:  return ("F6"); break;
	case VirtualKey::F7:  return ("F7"); break;
	case VirtualKey::F8:  return ("F8"); break;
	case VirtualKey::F9:  return ("F9"); break;
	case VirtualKey::F10:  return ("F10"); break;
	case VirtualKey::F11:  return ("F11"); break;
	case VirtualKey::F12:  return ("F12"); break;
	case VirtualKey::G:  return ("G"); break;
	case VirtualKey::H:  return ("H"); break;
	case VirtualKey::I:  return ("I"); break;
	case VirtualKey::J:  return ("J"); break;
	case VirtualKey::K:  return ("K"); break;
	case VirtualKey::L:  return ("L"); break;
	case VirtualKey::M:  return ("M"); break;
	case VirtualKey::N:  return ("N"); break;
	case VirtualKey::O:  return ("O"); break;
	case VirtualKey::P:  return ("P"); break;
	case VirtualKey::Q:  return ("Q"); break;
	case VirtualKey::R:  return ("R"); break;
	case VirtualKey::S:  return ("S"); break;
	case VirtualKey::T:  return ("T"); break;
	case VirtualKey::U:  return ("U"); break;
	case VirtualKey::V:  return ("V"); break;
	case VirtualKey::W:  return ("W"); break;
	case VirtualKey::X:  return ("X"); break;
	case VirtualKey::Y:  return ("Y"); break;
	case VirtualKey::Z:  return ("Z"); break;
	case VirtualKey::Shift:  return ("Shift"); break;
	case VirtualKey::Space:  return ("Space"); break;
	}
}


