/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "Menu.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Util\keyboard.h"
#include "..\Natives\natives2.h"
#include "..\Natives\types.h" // RGBA/RgbS
#include "..\Scripting\Scaleform.h"
#include "..\Memory\GTAmemory.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Scripting\ModelNames.h" // _vNeonColours
#include "Routine.h" // (loop_no_clip_toggle, loop_hide_hud)
#include "Language.h"
#include "..\Util\FileLogger.h"
#include "..\Menu\Menu.h"

#include <Windows.h>
#include <utility>

#define TRUE 1
#define FALSE 0


float get_xcoord_at_menu_rightEdge(float widthOfElement, float extraWidth, bool centered)
{
	if (centered)
	{
		return (0.16f + menuPos.x + 0.1f) - 0.002f - extraWidth - (widthOfElement / 2);
	}

	return (0.16f + menuPos.x + 0.1f) - 0.002f - extraWidth - (widthOfElement);
}
float get_xcoord_at_menu_leftEdge(float width, bool centered)
{
	if (centered)
	{
		return (0.16f + menuPos.x - 0.1f) + 0.002f + (width / 2);
	}

	return (0.16f + menuPos.x - 0.1f) + 0.002f;
}

//--------------------------------MenuPressTimer-------------------------------------------------

namespace MenuPressTimer
{
	MenuPressTimer::Button currentButton = { MenuPressTimer::Button::None };
	DWORD offsettedTime = 0;

	void Update()
	{
		//GeneralGlobalHax::DisableAnnoyingRecordingUI(true);

		if (currentButton == Button::None)
		{
			offsettedTime = GetTickCount() + 630;
		}

		if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_RIGHT) || IsKeyDown(VirtualKey::Numpad6))
		{
			currentButton = Button::Right;
		}
		else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_LEFT) || IsKeyDown(VirtualKey::Numpad4))
		{
			currentButton = Button::Left;
		}
		else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_DOWN) || IsKeyDown(VirtualKey::Numpad2))
		{
			currentButton = Button::Down;
		}
		else if (IS_DISABLED_CONTROL_PRESSED(2, INPUT_FRONTEND_UP) || IsKeyDown(VirtualKey::Numpad8))
		{
			currentButton = Button::Up;
		}
		else
		{
			currentButton = Button::None;
			offsettedTime = 0;
		}
	}
	bool IsButtonHeld(const MenuPressTimer::Button& button)
	{
		DWORD tickCount = GetTickCount();
		return (currentButton == button && offsettedTime < tickCount);
	}
	bool IsButtonTapped(const MenuPressTimer::Button& button)
	{
		bool isTapped = true;
		switch (button)
		{
		case Button::Right: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RIGHT) || IsKeyJustUp(VirtualKey::Numpad6); break;
		case Button::Left: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LEFT) || IsKeyJustUp(VirtualKey::Numpad4); break;
		case Button::Down: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_DOWN) || IsKeyJustUp(VirtualKey::Numpad2); break;
		case Button::Up: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_UP) || IsKeyJustUp(VirtualKey::Numpad8); break;
		case Button::Back: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RRIGHT) || IsKeyJustUp(VirtualKey::Numpad0); break;
		case Button::Accept: isTapped = IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_ACCEPT) || IsKeyJustUp(VirtualKey::Numpad5); break;
		}
		return isTapped;
	}
	bool IsButtonHeldOrTapped(const MenuPressTimer::Button& button)
	{
		return IsButtonHeld(button) || IsButtonTapped(button);
	}
}

//--------------------------------MenuInput------------------------------------------------------

bool MenuInput::IsUsingController()
{
	return !IS_USING_KEYBOARD_AND_MOUSE(2);
}
void MenuInput::UpdateDeltaCursorNormal()
{
	Vector2 l_deltaCursorNormal;
	l_deltaCursorNormal.x = GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_X);
	l_deltaCursorNormal.y = GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_Y);
	//if (l_deltaCursorNormal.x > 0.999f && l_deltaCursorNormal.x > g_deltaCursorNormal.x) l_deltaCursorNormal.x -= 0.01f;
	//if (l_deltaCursorNormal.y > 0.999f && l_deltaCursorNormal.y > g_deltaCursorNormal.y) l_deltaCursorNormal.y -= 0.01f;
	//if (l_deltaCursorNormal.x < -0.999f && l_deltaCursorNormal.x < g_deltaCursorNormal.x) l_deltaCursorNormal.x -= -0.01f;
	//if (l_deltaCursorNormal.y < -0.999f && l_deltaCursorNormal.y < g_deltaCursorNormal.y) l_deltaCursorNormal.y -= -0.01f;
	g_deltaCursorNormal = l_deltaCursorNormal - g_deltaCursorNormal;
}

//--------------------------------Menu-----------------------------------------------------------

bool titletext_ALPHA_DIS_TEMP;
bool bit_frontend_addnumber_selected = false;
bool g_menuNotOpenedYet = true;

Vector2 menuPos;
Vector2 g_deltaCursorNormal;
float OptionY;

INT8 font_title = 7;
INT8 font_options = 4;
INT8 font_selection = 4;
INT8 font_breaks = 1;
INT8 font_xyzh = 0;
INT8 font_speedo = 0;

RGBA titlebox(0, 255, 255, 247);
RGBA BG(10, 10, 10, 200);
RGBA titletext(255, 255, 255, 255);
RGBA optiontext(255, 255, 255, 255);
RGBA selectedtext(0, 0, 0, 255);
RGBA optionbreaks(255, 255, 255, 240);
RGBA optioncount(255, 255, 255, 255);
RGBA selectionhi(255, 255, 255, 211);
RGBA _globalPedTrackers_Col(0, 255, 255, 205);

std::pair<UINT16, UINT16> menubindsGamepad = { INPUT_FRONTEND_RB, INPUT_FRONTEND_LEFT };
UINT16 menubinds = VirtualKey::F8;
UINT16 respawnbinds = INPUT_LOOK_BEHIND;

UINT16 Menu::currentsub = 0, Menu::LOOCsub = SUB::MAINMENU;
INT Menu::currentop = 0, * Menu::currentopATM = &currentop;
INT Menu::currentop_w_breaks = 0;
INT Menu::totalop = 0;
INT Menu::printingop = 0;
UINT16 Menu::breakcount = 0;
UINT16 Menu::totalbreaks = 0;
UINT8 Menu::breakscroll = 0;
INT16 Menu::currentsub_ar_index = 0;
INT Menu::currentsub_ar[100] = {};
INT Menu::currentop_ar[100] = {};
INT Menu::SetSub_delayed = 0;
int Menu::delayedTimer = 0;
bool Menu::bit_controller = 0, Menu::bit_mouse = 0;
bool Menu::bit_centre_title = 1, Menu::bit_centre_options = 0, Menu::bit_centre_breaks = 1,
Menu::gradients = 1, Menu::thin_line_over_screct = 1, Menu::bit_glare_test = 1;
Scaleform Menu::scaleform_menuGlare;
Scaleform Menu::instructional_buttons;
std::vector<Scaleform_IbT> Menu::vIB;
std::function<void()> Menu::OnSubBack = nullptr;
INT8 loglevel = 2;


void Menu::SetInputMethods()
{
	bit_controller = MenuInput::IsUsingController();
}
void Menu::DisableControls()
{
	// Keyboard
	if (!bit_controller)
	{
		//DISPLAY_HUD(0);
		HIDE_HELP_TEXT_THIS_FRAME();
		SET_CINEMATIC_BUTTON_ACTIVE(1);
		DISABLE_CONTROL_ACTION(0, INPUT_LOOK_BEHIND, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, TRUE);
		SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_ACCEPT);
		SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_CANCEL);
		DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, TRUE);
		SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_DOWN);
		SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_UP);
		SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_LEFT);
		SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_RIGHT);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, TRUE);
		HIDE_HUD_COMPONENT_THIS_FRAME(10);
		HIDE_HUD_COMPONENT_THIS_FRAME(6);
		HIDE_HUD_COMPONENT_THIS_FRAME(7);
		HIDE_HUD_COMPONENT_THIS_FRAME(9);
		HIDE_HUD_COMPONENT_THIS_FRAME(8);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, TRUE);
		DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_CANCEL, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_SELECT, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_UP, TRUE);
		DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_DOWN, TRUE);

		return;
	}
	// Controller
	//DISPLAY_HUD(0);
	HIDE_HELP_TEXT_THIS_FRAME();
	SET_CINEMATIC_BUTTON_ACTIVE(1);
	DISABLE_CONTROL_ACTION(0, INPUT_NEXT_CAMERA, TRUE);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_X);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_ACCEPT);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_CANCEL);
	DISABLE_CONTROL_ACTION(0, INPUT_HUD_SPECIAL, TRUE);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_DOWN);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_UP);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_CANCEL, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_LEFT, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RIGHT, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_DOWN, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_UP, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_RDOWN, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_FRONTEND_ACCEPT, TRUE);
	HIDE_HUD_COMPONENT_THIS_FRAME(10);
	HIDE_HUD_COMPONENT_THIS_FRAME(6);
	HIDE_HUD_COMPONENT_THIS_FRAME(7);
	HIDE_HUD_COMPONENT_THIS_FRAME(9);
	HIDE_HUD_COMPONENT_THIS_FRAME(8);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_LEFT);
	SET_INPUT_EXCLUSIVE(2, INPUT_FRONTEND_RIGHT);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_UNARMED, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_MELEE, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HANDGUN, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SHOTGUN, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SMG, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_AUTO_RIFLE, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SNIPER, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HEAVY, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SPECIAL, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_NEXT, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_WHEEL_PREV, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_SPECIAL, 1);
	DISABLE_CONTROL_ACTION(0, INPUT_WEAPON_SPECIAL_TWO, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_DIVE, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_LIGHT, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_MELEE_ATTACK_HEAVY, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_MELEE_BLOCK, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_ARREST, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_HEADLIGHT, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_RADIO_WHEEL, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_CONTEXT, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_RELOAD, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_CIN_CAM, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_JUMP, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_SELECT_NEXT_WEAPON, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_FLY_SELECT_NEXT_WEAPON, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_FRANKLIN, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MICHAEL, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_TREVOR, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_CHARACTER_WHEEL, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_CANCEL, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_SELECT, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_UP, TRUE);
	DISABLE_CONTROL_ACTION(2, INPUT_CELLPHONE_DOWN, TRUE);
	DISABLE_CONTROL_ACTION(0, INPUT_DETONATE, 1);
	DISABLE_CONTROL_ACTION(0, INPUT_SPRINT, 1);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_DUCK, 1);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_HEADLIGHT, 1);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_PUSHBIKE_SPRINT, 1);
	DISABLE_CONTROL_ACTION(0, INPUT_VEH_PUSHBIKE_PEDAL, 1);

	// pi_menu
	/*	if (CONTROLS::_0xA571D46727E2B718(2)) {
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 237);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 238);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 241);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 242);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 239);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 240);
	CONTROLS::ENABLE_CONTROL_ACTION(2, 176, 1);
	}
	else {
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 176);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
	}
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 172);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 173);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 174);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 175);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_UNARMED, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_MELEE, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HANDGUN, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SHOTGUN, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SMG, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_AUTO_RIFLE, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SNIPER, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_HEAVY, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_SELECT_WEAPON_SPECIAL, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(0, INPUT_VEH_RADIO_WHEEL, 1);*/


}
void Menu::base()
{
	//GET_ACTUAL_SCREEN_RESOLUTION(&Game::defaultScreenRes.first, &Game::defaultScreenRes.second);
	if (Menu::currentsub != SUB::CLOSED)
	{
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("MenyooExtras")) REQUEST_STREAMED_TEXTURE_DICT("MenyooExtras", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("CommonMenu")) REQUEST_STREAMED_TEXTURE_DICT("CommonMenu", 0);
		//if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shared")) REQUEST_STREAMED_TEXTURE_DICT("shared", 0);
		//if (!HAS_STREAMED_TEXTURE_DICT_LOADED("mpsafecracking")) REQUEST_STREAMED_TEXTURE_DICT("mpsafecracking", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_highendsalon")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_highendsalon", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_highendfashion")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_highendfashion", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_midfashion")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_midfashion", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_tattoos")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_tattoos", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_tattoos3")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_tattoos3", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_conveniencestore")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_conveniencestore", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_carmod")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_carmod", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_gunclub")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_gunclub", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_movie_masks")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_movie_masks", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("director_editor_title")) REQUEST_STREAMED_TEXTURE_DICT("director_editor_title", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_carmod2")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_carmod2", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_supermod")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_supermod", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("shopui_title_tennis")) REQUEST_STREAMED_TEXTURE_DICT("shopui_title_tennis", 0);
		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("dock_dlc_banner")) REQUEST_STREAMED_TEXTURE_DICT("dock_dlc_banner", 0);
		background();
		titlebox_draw();
		optionhi();
		GeneralGlobalHax::DisableAnnoyingRecordingUI(true);
		MenuPressTimer::Update();
	}
	else
	{
		GeneralGlobalHax::DisableAnnoyingRecordingUI(false);
		scaleform_menuGlare.Unload();
	}

	SetInputMethods();
	draw_IB(); // Draw instructional buttons
}
void Menu::titlebox_draw()
{
	titletext_ALPHA_DIS_TEMP = true;

	// Oh why oh why did I do it this way
	switch (currentsub)
	{
	case SUB::COMPONENTS: case SUB::COMPONENTS2: case SUB::COMPONENTS_OUTFITS: case SUB::COMPONENTS_OUTFITS2:
		DRAW_SPRITE("shopui_title_highendfashion", "shopui_title_highendfashion", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::COMPONENTSPROPS: case SUB::COMPONENTSPROPS2:
		DRAW_SPRITE("shopui_title_midfashion", "shopui_title_midfashion", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::PEDDECALS_TYPES: case SUB::PEDDECALS_ZONES: case SUB::PEDDECALS_INZONE:
		DRAW_SPRITE("shopui_title_tattoos", "shopui_title_tattoos", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::PEDDAMAGET_CATEGORYLIST:	case SUB::PEDDAMAGET_BONESELECTION: case SUB::PEDDAMAGET_BLOOD: case SUB::PEDDAMAGET_DAMAGEDECALS: case SUB::PEDDAMAGET_DAMAGEPACKS:
		DRAW_SPRITE("shopui_title_tattoos3", "shopui_title_tattoos3", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::PED_HEADFEATURES_MAIN: case SUB::PED_HEADFEATURES_HEADOVERLAYS: case SUB::PED_HEADFEATURES_HEADOVERLAYS_INITEM: case SUB::PED_HEADFEATURES_FACEFEATURES: case SUB::PED_HEADFEATURES_SKINTONE:
		DRAW_SPRITE("shopui_title_highendsalon", "shopui_title_highendsalon", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::MODSHOP: case SUB::MSDOORS: case SUB::MSCATALL: case SUB::MSEXTRA: case SUB::MSLIGHTS: case SUB::MSNEONS: case SUB::MSWHEELS: case SUB::MSWHEELS2: case SUB::MSWHEELS3: case SUB::MS_TYRESBURST: case SUB::GETALLPAINTIDS: case SUB::MSPAINTS: case SUB::MSPAINTS2: case SUB::MSPAINTS2_CHROME: case SUB::MSPAINTS2_MATTE: case SUB::MSPAINTS2_METAL: case SUB::MSPAINTS2_CHAMELEON: case SUB::MSPAINTS2_METALLIC: case SUB::MSPAINTS2_NORMAL: case SUB::MSPAINTS2_SHARED: case SUB::MSENGINESOUND: //case SUB::MSPAINTS_RGB:
		if (Menu::currentsub_ar[currentsub_ar_index] != SUB::MS_BENNYS)
		{
			DRAW_SPRITE("shopui_title_carmod", "shopui_title_carmod", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
		}
	case SUB::MS_BENNYS:
		DRAW_SPRITE("shopui_title_supermod", "shopui_title_supermod", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::WEAPONOPS: case SUB::KABOOMGUN: case SUB::BULLETGUN: case SUB::OBJECTGUN: case SUB::PEDGUN: case SUB::WEAPONOPS_WEAPONFAVOURITES: case SUB::WEAPONOPS_INDIVS_CATEGORIES: case SUB::WEAPONOPS_INDIVS_CATEGORY: case SUB::WEAPONOPS_INDIVS_ITEM: case SUB::WEAPONOPS_INDIVS_ITEM_MODS: case SUB::WEAPONOPS_PARACHUTE: case SUB::WEAPONOPS_LOADOUTS: case SUB::WEAPONOPS_LOADOUTS_INITEM: case SUB::WEAPONOPS_LASERSIGHT: case SUB::FORGEGUN: case SUB::GRAVITYGUN:
		DRAW_SPRITE("shopui_title_gunclub", "shopui_title_gunclub", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
		//case SUB::OBJECTSPAWNER_LIGHTINGOPS: case SUB::OBJECTSPAWNER_LIGHT: case SUB::OBJECTSPAWNER_SPOTLIGHT:
			//DRAW_SPRITE("shopui_title_movie_masks", "shopui_title_movie_masks", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A); break;
	case SUB::SPAWNVEHICLE: case SUB::SPAWNVEHICLE_OPTIONS: case SUB::SPAWNVEHICLE_ALLCATS: case SUB::SPAWNVEHICLE_FAVOURITES: case SUB::FUNNYVEHICLES: case SUB::VEHICLE_SAVER: case SUB::VEHICLE_SAVER_INITEM:
		DRAW_SPRITE("shopui_title_carmod2", "shopui_title_carmod2", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::ANIMATIONSUB: case SUB::ANIMATIONSUB_DEER: case SUB::ANIMATIONSUB_GESTSIT: case SUB::ANIMATIONSUB_GUARDREAC: case SUB::ANIMATIONSUB_MISSRAPPEL: case SUB::ANIMATIONSUB_RANDARREST: case SUB::ANIMATIONSUB_SHARK: case SUB::ANIMATIONSUB_SWAT: case SUB::ANIMATIONSUB_CUSTOM: case SUB::ANIMATIONSUB_SETTINGS: case SUB::ANIMATIONSUB_TASKSCENARIOS: case SUB::ANIMATIONSUB_TASKSCENARIOS2: case SUB::MOVEMENTGROUP:
		DRAW_SPRITE("shopui_title_tennis", "shopui_title_tennis", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
	case SUB::TELEPORTOPS_YACHTS: case SUB::TELEPORTOPS_YACHTS_INGRP:
		DRAW_SPRITE("dock_dlc_banner", "yacht_banner_0", 0.16f + menuPos.x, 0.0989f + menuPos.y, 0.20f, 0.083f, 0.0f, 255, 255, 255, titlebox.A, false, 0); break;
		//case SUB::SPOONER_MAIN:
		//DxHookIMG::titleui_spooner.Draw(0, Vector2(0.16f + menuPos.x, 0.0989f + menuPos.y), Vector2(0.20f, 0.083f), 0.0f, RGBA(255, 255, 255, titlebox.A)); break;

	default:
		if (gradients) DRAW_SPRITE("CommonMenu", "Gradient_Nav"/*"interaction_bgd"*/, 0.16f + menuPos.x, 0.1175f + menuPos.y, 0.20f, 0.083f, 0.0f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, false, 0);
		else DRAW_RECT(0.16f + menuPos.x, 0.1175f + menuPos.y, 0.20f, 0.083f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, false);
		RESET_SCRIPT_GFX_ALIGN();
		titletext_ALPHA_DIS_TEMP = false;
		//glare_test();
		break;

	}

	if (titletext_ALPHA_DIS_TEMP) // Draw titlebox lower stripe
	{
		if (gradients) DRAW_SPRITE("CommonMenu", "Gradient_Nav"/*"interaction_bgd"*/, 0.16f + menuPos.x, 0.1496f + menuPos.y, 0.20f, 0.02f, 0.0f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, false, 0);
		else DRAW_RECT(0.16f + menuPos.x, 0.1496f + menuPos.y, 0.20f, 0.02f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, false);

	}


}
void Menu::background()
{
	float temp;
	if (totalop > GTA_MAXOP) temp = GTA_MAXOP; else temp = (float)totalop; // Calculate last option number to draw rect

																		   // Calculate Y Coord
	float bg_Y = ((temp * 0.035f) / 2.0f) + 0.159f;
	float bg_length = temp * 0.035f;


	// Draw background
	if (gradients && BG.R < 20 && BG.G < 20 && BG.B < 20) DRAW_SPRITE("CommonMenu", "Gradient_Bgd", 0.16f + menuPos.x, bg_Y + menuPos.y, 0.20f, bg_length, 0.0f, 255, 255, 255, BG.A, false, 0);
	else DRAW_RECT(0.16f + menuPos.x, bg_Y + menuPos.y, 0.20f, bg_length, BG.R, BG.G, BG.B, BG.A, false);

	// Draw scroller indicator rect
	if (totalop > GTA_MAXOP) temp = GTA_MAXOP; else temp = totalop;
	float scr_rect_Y = ((temp + 1.0f) * 0.035f) + 0.1415f;
	if (gradients) DRAW_SPRITE("CommonMenu", "Gradient_Nav"/*"interaction_bgd"*/, 0.16f + menuPos.x, scr_rect_Y + menuPos.y, 0.20f, 0.0345f, 0.0f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, false, 0);
	else DRAW_RECT(0.16f + menuPos.x, scr_rect_Y + menuPos.y, 0.20f, 0.0345f, titlebox.R, titlebox.G, titlebox.B, titlebox.A, false);

	// Draw thin line over scroller indicator rect
	if (thin_line_over_screct)
	{
		if (totalop < GTA_MAXOP) DRAW_RECT(0.16f + menuPos.x, (totalop * 0.035f + 0.1589f) + menuPos.y, 0.20f, 0.0011f, 255, 255, 255, 255, false);
		else DRAW_RECT(0.16f + menuPos.x, (14.0f * 0.035f + 0.1589f) + menuPos.y, 0.20f, 0.0011f, 255, 255, 255, 255, false);
	}

	// Draw scroller indicator
	if ((totalop > GTA_MAXOP)) //&& HAS_STREAMED_TEXTURE_DICT_LOADED("CommonMenu"))
	{
		Vector3 texture_res = GET_TEXTURE_RESOLUTION("CommonMenu", "shop_arrows_upANDdown");
		texture_res.x /= (Game::defaultScreenRes.first * 2);
		texture_res.y /= (Game::defaultScreenRes.second * 2);

		temp = ((GTA_MAXOP + 1.0f) * 0.035f) + 0.1413f; //0.1259f;

		/*if (currentop == 1)	DRAW_SPRITE("CommonMenu", "arrowright", 0.16f + menuPos.x, temp + menuPos.y, texture_res.x, texture_res.y, 90.0f, optioncount.R, optioncount.G, optioncount.B, 255);
		else if (currentop == totalop) DRAW_SPRITE("CommonMenu", "arrowright", 0.16f + menuPos.x, temp + menuPos.y, texture_res.x, texture_res.y, 270.0f, optioncount.R, optioncount.G, optioncount.B, 255);
		else*/
		DRAW_SPRITE("CommonMenu", "shop_arrows_upANDdown", 0.16f + menuPos.x, temp + menuPos.y, texture_res.x, texture_res.y, 0.0f, optioncount.R, optioncount.G, optioncount.B, 255, false, 0);

	}

	// Draw option count
	temp = scr_rect_Y - 0.0124f;

	std::string toPrint = std::to_string(*currentopATM) + " / " + std::to_string(totalop);

	Game::Print::setupdraw(GTAfont::Arial, Vector2(0.0f, 0.26f), false, false, false, optioncount);
	float width = Game::Print::GetTextWidth(toPrint);
	Game::Print::setupdraw(GTAfont::Arial, Vector2(0.0f, 0.26f), false, false, false, optioncount);
	Game::Print::drawstring(toPrint, get_xcoord_at_menu_rightEdge(width, 0.0f, false), temp + menuPos.y);

	//BEGIN_TEXT_COMMAND_DISPLAY_TEXT("CM_ITEM_COUNT");
	//ADD_TEXT_COMPONENT_INTEGER(*currentopATM); // ! currentop_w_breaks
	//ADD_TEXT_COMPONENT_INTEGER(totalop); // ! totalop - totalbreaks
	//if (totalop < 1000) END_TEXT_COMMAND_DISPLAY_TEXT(0.219f + menuPos.x, temp + menuPos.y); // < 1000
	//else END_TEXT_COMMAND_DISPLAY_TEXT(0.212f + menuPos.x, temp + menuPos.y); // >= 1000
}
void Menu::optionhi()
{
	if (totalop < 1) { if (bit_glare_test && !titletext_ALPHA_DIS_TEMP) glare_test(); return; }

	float Y_coord;
	if (currentop > GTA_SCROLLOP && totalop > GTA_MAXOP)
	{
		Y_coord = GTA_SCROLLOP;

		if (currentop > totalop - GTA_BETOP)
		{
			//for (inull = 0; inull <= GTA_BETOP; inull++)
			//if (currentop == totalop - GTA_BETOP + inull) break;
			Y_coord = GTA_SCROLLOP + currentop - totalop + GTA_BETOP;
		}
	}
	else Y_coord = currentop;

	Y_coord = (Y_coord * 0.035f) + 0.1415f;

	if (!Menu::bit_mouse)
	{
		if (gradients) DRAW_SPRITE("CommonMenu", "Gradient_Nav", 0.16f + menuPos.x, Y_coord + menuPos.y, 0.20f, 0.035f, 0.0f, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A, false, 0);
		else DRAW_RECT(0.16f + menuPos.x, Y_coord + menuPos.y, 0.20f, 0.035f, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A, false);
	}

	if (bit_glare_test && !titletext_ALPHA_DIS_TEMP) glare_test();
}
bool Menu::isBinds()
{
	// Open menu - RB + Left / F8
	UINT8 index1 = menubindsGamepad.first < 50 ? 0 : 2;
	UINT8 index2 = menubindsGamepad.second < 50 ? 0 : 2;
	return bit_controller ? (IS_DISABLED_CONTROL_PRESSED(index1, menubindsGamepad.first) && IS_DISABLED_CONTROL_JUST_PRESSED(index2, menubindsGamepad.second)) : IsKeyJustUp(menubinds); // F8
}
void Menu::while_closed()
{
	if (isBinds())
	{
		if (g_menuNotOpenedYet)
			justopened();

		Game::Sound::PlayFrontend("FocusIn", "HintCamSounds");
		currentsub = LOOCsub;
		if (currentsub == SUB::MAINMENU)
		{
			currentop = 1;
			*currentopATM = 1;
		}
		//currentop = currentop;
		/*currentsub = SUB::MAINMENU;
		currentsub_ar_index = 0;
		currentop = 1;*/
	}
}
void Menu::while_opened()
{
	totalop = printingop; printingop = 0;
	totalbreaks = breakcount; breakcount = 0; breakscroll = 0;

	if (IS_PAUSE_MENU_ACTIVE()) SetSub_closed();

	if (IS_GAMEPLAY_HINT_ACTIVE()) STOP_GAMEPLAY_HINT(false);
	DISPLAY_AMMO_THIS_FRAME(0);
	DISPLAY_CASH(0);
	SET_RADAR_ZOOM(0);
	//FLOAT* g_3805 = reinterpret_cast<FLOAT *>(getGlobalPtr(0x3805));
	//SET_MOBILE_PHONE_POSITION(g_3805[0], g_3805[1], g_3805[2]);
	if (IS_MOBILE_PHONE_CALL_ONGOING()) STOP_SCRIPTED_CONVERSATION(0);
	//TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_controller");

	if (!HAS_THIS_ADDITIONAL_TEXT_LOADED("HAR_MNU", 9)) REQUEST_ADDITIONAL_TEXT("HAR_MNU", 9);
	if (!HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 2)) REQUEST_ADDITIONAL_TEXT("MOD_MNU", 2);
	DisableControls();
	//set_THEPHONEDOWN();
	set_opened_IB();

	// Scroll up
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Up))
	{
		if (currentop <= 1)
			Bottom();
		else
			Up();
	}

	// Scroll down
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Down))
	{
		if (currentop >= totalop)
			Top();
		else
			Down();
	}

	// B press
	if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Back))
	{
		if (currentsub == SUB::MAINMENU)
			SetSub_closed();
		else
			SetSub_previous();
	}

	// Binds press
	if (isBinds())//&& currentsub != SUB::MAINMENU)
	{
		SetSub_closed();
	}
		
}
void Menu::Up(bool playSound)
{
	currentop--;
	currentop_w_breaks--;
	if (playSound)
		Game::Sound::PlayFrontend_default("NAV_UP_DOWN");
	breakscroll = 1;
}
void Menu::Down(bool playSound)
{
	currentop++;
	currentop_w_breaks++;
	if (playSound)
		Game::Sound::PlayFrontend_default("NAV_UP_DOWN");
	breakscroll = 2;
}
void Menu::Bottom(bool playSound)
{
	currentop = totalop;
	currentop_w_breaks = totalop;
	if (playSound)
		Game::Sound::PlayFrontend_default("NAV_UP_DOWN");
	breakscroll = 1;
}
void Menu::Top(bool playSound)
{
	currentop = 1;
	currentop_w_breaks = 1;
	if (playSound)
		Game::Sound::PlayFrontend_default("NAV_UP_DOWN");
	breakscroll = 2;
}
void Menu::SetSub_previous()
{
	if (OnSubBack != nullptr)
	{
		OnSubBack();
		OnSubBack = nullptr;
	}

	currentsub = currentsub_ar[currentsub_ar_index]; // Get previous submenu from array and set as current submenu
	currentop = currentop_ar[currentsub_ar_index]; // Get last selected option from array and set as current selected option
	
	currentsub_ar[currentsub_ar_index] = -2;
	currentop_ar[currentsub_ar_index] = -2;

	currentsub_ar_index--; // Decrement array index by 1
	printingop = 0; // Reset option print variable
	totalop = 0; // Reset total option count variable
	Game::Sound::PlayFrontend_default("BACK"); // Play sound

	*currentopATM = currentop;

}

void Menu::SetSub_new(INT sub_index)
{
	currentsub_ar_index++; //Increment array index
	currentsub_ar[currentsub_ar_index] = currentsub; // Store current submenu index in array
	currentsub = sub_index; // Set new submenu as current submenu

	currentop_ar[currentsub_ar_index] = currentop; // Store currently selected option in array
	currentop = 1; currentop_w_breaks = 1; // Set new selected option as first option in submenu

	printingop = 0; // Reset currently printing option var
	totalop = 0; // Reset total number of options var"

	*currentopATM = currentop; //SetSub_new complete

}


void Menu::SetSub_closed()
{
	//Game::RequestScript("cellphone_controller");
	ENABLE_ALL_CONTROL_ACTIONS(0);
	ENABLE_ALL_CONTROL_ACTIONS(2);
	Game::Sound::PlayFrontend_default("BACK");

	LOOCsub = currentsub;
	currentsub = SUB::CLOSED;

	// if the current sub is stored in Menu::LOOCsub, it can be reopened on menuOpen.
	// This way, the binds can be used in any submenu and that submenu can be reopened instantly
	// But this isn't possible due to the infobox loop below

	/*for (auto& su : Menu::currentsub_ar) su = SUB::CLOSED;
	currentsub = SUB::CLOSED;*/
}

void Menu::glare_test()
{
	if (loop_no_clip_toggle)
	{
		//Label_unloadglare:;
		scaleform_menuGlare.Unload();
	}

	if (!scaleform_menuGlare.Load("MP_MENU_GLARE")) return;

	scaleform_menuGlare.PushFunction("SET_DATA_SLOT");
	scaleform_menuGlare.PushFloat(0.0f); // glare_test_camstuff(_0x5B4E4C817FCC2DFB(2).z, 0.0f, 360.0f)
	scaleform_menuGlare.PopFunction();

	/*SET_SCRIPT_GFX_ALIGN(0, 0);
	SET_SCRIPT_GFX_ALIGN_PARAMS(0.0f, 0.0f, 0.0f, 0.0f);
	RESET_SCRIPT_GFX_ALIGN();*/

	Vector2 pos = { 0.4800f + menuPos.x, 0.4850f + menuPos.y };
	Vector2 size = { 0.9800f, 0.9100f };
	//Vector2 pos = { _global_glare_pos.x + menuPos.x, _global_glare_pos.y + menuPos.y };
	//Vector2& size = _global_glare_size;

	scaleform_menuGlare.Render2DScreenSpace(pos, size, { titletext.R, titletext.G, titletext.A, titlebox.A });


	/*if (!HAS_SCALEFORM_MOVIE_LOADED(scaleform_menuGlare)){ scaleform_menuGlare = REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE"); return; }

	Vector3 camstuff = _0x5B4E4C817FCC2DFB(2);
	FLOAT tempFloat = sub_2cbfc(camstuff.z, 0.0, 360.0); // WHAT ARE Vector3 STRUCT ITEMS NAMED AS?? ._f2

	BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_menuGlare, "SET_DATA_SLOT");
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0);
	//SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(tempFloat);
	END_SCALEFORM_MOVIE_METHOD();

	BEGIN_SCALEFORM_MOVIE_METHOD(scaleform_menuGlare, "SET_MAX_WIDTH");
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0.2f);
	END_SCALEFORM_MOVIE_METHOD();

	//Int2 res;
	//GET_ACTUAL_SCREEN_RESOLUTION(&res.x, &res.y);
	//if (res == toInt2(1920, 1080)) END_SCALEFORM_MOVIE_METHOD();

	SET_SCRIPT_GFX_ALIGN(76, 84);
	SET_SCRIPT_GFX_ALIGN_PARAMS(0.008 + menuPos.x, 0.045f + menuPos.y, 0.0f, -0.5f);
	RESET_SCRIPT_GFX_ALIGN();

	_0x0DF606929C105BE1(scaleform_menuGlare, titletext.R, titletext.G, titletext.A, titlebox.A);
	//DRAW_SCALEFORM_MOVIE(scaleform_menuGlare, 0.5f, 0.5f, 0.2f, 0.1f, 255, 255, 255, 255);*/

}

void Menu::set_opened_IB()
{
	if (!bit_frontend_addnumber_selected)
		add_IB(INPUT_CELLPHONE_SELECT, "ITEM_SELECT");
	if (currentsub != SUB::MAINMENU)
		add_IB(INPUT_FRONTEND_RRIGHT, "ITEM_BACK");
	else
		add_IB(INPUT_FRONTEND_RRIGHT, "ITEM_EXIT");
	/*if (bit_frontend_addnumber_selected)
	{
	Menu::add_IB(INPUT_FRONTEND_RIGHT, "Right");
	Menu::add_IB(INPUT_FRONTEND_LEFT, "Left");
	}
	if (Menu::totalop > 1)
	{
	add_IB(INPUT_FRONTEND_DOWN, "Down");
	add_IB(INPUT_FRONTEND_UP, "Up");
	}*/

	bit_frontend_addnumber_selected = false;
}
void Menu::add_IB(ControllerInput button_id, std::string string_val)
{
	vIB.push_back({ button_id, (string_val), false });
}
void Menu::add_IB(VirtualKey::VirtualKey button_id, std::string string_val)
{
	vIB.push_back({ button_id, (string_val), true });
}
void Menu::add_IB(ScaleformButton button_id, std::string string_val)
{
	vIB.push_back({ int(button_id) + 1000, (string_val), false });
}
std::string Menu::get_key_IB(const Scaleform_IbT& ib)
{
	if (ib.button == -3)
		return "";

	if (!ib.isKey)
		return GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(2, ib.button, 1);

	std::string bs = "t_" + VkCodeToStr(ib.button);

	return bs;
}
void Menu::draw_IB()
{
	if (vIB.empty() || UPDATE_ONSCREEN_KEYBOARD() == 0 || loop_hide_hud)//IS_HUD_HIDDEN())
	{
		//instructional_buttons.Unload();
		return;
	}

	if (!instructional_buttons.Load("instructional_buttons"))
		return;

	instructional_buttons.PushFunction("CLEAR_ALL");
	instructional_buttons.PopFunction();

	instructional_buttons.PushFunction("SET_MAX_WIDTH");
	instructional_buttons.PushFloat(100.0f);
	instructional_buttons.PopFunction();

	instructional_buttons.PushFunction("TOGGLE_MOUSE_BUTTONS");
	instructional_buttons.PushBoolean(true);
	instructional_buttons.PopFunction();

	for (UINT8 i = 0; i < vIB.size(); i++)
	{
		instructional_buttons.PushFunction("SET_DATA_SLOT");
		instructional_buttons.PushInteger(i);

		if (vIB[i].button >= 1000) // Direct scaleform button index
		{
			instructional_buttons.PushInteger(vIB[i].button - 1000);
			instructional_buttons.PushTextComponent(vIB[i].text);
		}
		else
		{
			instructional_buttons.PushString2(get_key_IB(vIB[i]));
			instructional_buttons.PushTextComponent(vIB[i].text);
			instructional_buttons.PushBoolean(true);
			instructional_buttons.PushInteger(vIB[i].button);
		}
		instructional_buttons.PopFunction();
	}

	instructional_buttons.PushFunction("SET_BACKGROUND_COLOUR");
	instructional_buttons.PushRGBA(RGBA(0, 0, 0, 80));
	instructional_buttons.PopFunction();

	instructional_buttons.PushFunction("DRAW_INSTRUCTIONAL_BUTTONS");
	instructional_buttons.PushInteger(0);
	instructional_buttons.PopFunction();

	SET_SCRIPT_GFX_ALIGN(76, 66); // Safezone
	SET_SCRIPT_GFX_ALIGN_PARAMS(0.0f, 0.0f, 0.0f, 0.0f); // Offset
	RESET_SCRIPT_GFX_ALIGN(); // Safezone end

	instructional_buttons.Render2D();

	vIB.clear();
}

void Menu::sub_handler()
{
	if (currentsub == SUB::CLOSED)
	{
		while_closed();
	}

	else
	{
		submenu_switch();

		if (Menu::currentop > Menu::printingop) { Menu::currentop = Menu::printingop + 1; Menu::Up(false); }
		else if (Menu::currentop < 1) { Menu::currentop = 0; Menu::Down(false); }

		//// These czechs is kill
		//if (currentop < 1) currentop = 1;
		//else if (currentop > totalop) currentop = totalop;

		if (SetSub_delayed != -1)
		{
			SetSub_new(SetSub_delayed);
			SetSub_delayed = -1;
		}

		while_opened();
	}

	if (GET_GAME_TIMER() >= delayedTimer)
	{
		delayedTimer = GET_GAME_TIMER() + 810; // Delay for rainbow related loops
		if (delayedTimer > INT_MAX - 1000) delayedTimer = 0;
	}

}

//--------------------------------MouseSupport---------------------------------------------------

bool MouseSupport::pressedSelectAfterSelect = 0;
INT MouseSupport::currentopM = -1;
std::vector<MouseSupport::ItemNumber> MouseSupport::vItems;

//INT MouseSupport::ItemNumberToItemNumberOnScreen(INT itemNumber)
//{
//	if (itemNumber <= GTA_SCROLLOP)
//	{
//		return itemNumber;
//	}
//	else if (itemNumber >= (Menu::totalop - GTA_BETOP))
//	{
//		return GTA_SCROLLOP + (GTA_BETOP - (Menu::totalop - itemNumber));
//	}
//	else // itemNumber > GTA_SCROLLOP && itemNumber < (menu::totalop - GTA_BETOP)
//	{
//		INT result = GTA_SCROLLOP + (itemNumber % GTA_SCROLLOP); // wrong m9
//	}
//
//}
INT MouseSupport::ItemNumberToItemNumberOnScreen(INT itemNumber)
{
	/*if (itemNumber >= vItems.size() + Menu::breakcount)
	{
	return -1;
	}*/
	for (auto& it : vItems)
	{
		if (itemNumber == it.real)
			return it.onScreen;
	}
	return -1;
}

Vector2 MouseSupport::ItemNumberToItemCoords(INT itemNumber)
{
	INT itemNumberOnScreen = ItemNumberToItemNumberOnScreen(itemNumber);

	if (itemNumberOnScreen < 0)
		return Vector2(-1, -1);

	return Vector2(0.16f + menuPos.x, (itemNumberOnScreen * 0.035f) + 0.1415f + menuPos.y);

}

void MouseSupport::Tick()
{
	Menu::currentopATM = Menu::bit_mouse ? &MouseSupport::currentopM : &Menu::currentop;

	pressedSelectAfterSelect = false;

	if (Menu::bit_mouse)
	{
		DisableControls();
		DoMouseTick();
	}
}

void MouseSupport::DisableControls()
{
	std::vector<ControllerInput> list
	{
		INPUT_ATTACK,
		INPUT_FRONTEND_ACCEPT,
		INPUT_FRONTEND_AXIS_X,
		INPUT_FRONTEND_AXIS_Y,
		INPUT_FRONTEND_CANCEL,
		INPUT_FRONTEND_SELECT,
		INPUT_CURSOR_SCROLL_UP,
		INPUT_CURSOR_SCROLL_DOWN,
		INPUT_CURSOR_SCROLL_UP,
		INPUT_CURSOR_X,
		INPUT_CURSOR_Y,
		INPUT_VEH_FLY_YAW_LEFT,
		INPUT_VEH_FLY_YAW_RIGHT,
		INPUT_VEH_FLY_ROLL_LR,
		INPUT_VEH_FLY_PITCH_UD,
		INPUT_VEH_HANDBRAKE

	};

	for (auto& control : list)
	{
		DISABLE_CONTROL_ACTION(0, control, true);
	}

}

void MouseSupport::DoMouseTick()
{

	//Vector2& safezoneOffset = GetSafezoneBounds();

	SET_MOUSE_CURSOR_THIS_FRAME();

	if (IsMouseInBounds(Vector2(0.0078f, 0.5f), Vector2(0.0156f, 1.0f)))
	{
		GameplayCamera::RelativeHeading_set(GameplayCamera::RelativeHeading_get() + 5.0f);
		SET_MOUSE_CURSOR_STYLE(6);
	}
	else if (IsMouseInBounds(Vector2(1.0 - 0.0078f, 0.5f), Vector2(0.0156f, 1.0f)))
	{
		GameplayCamera::RelativeHeading_set(GameplayCamera::RelativeHeading_get() - 5.0f);
		SET_MOUSE_CURSOR_STYLE(7);
	}
	else
	{
		SET_MOUSE_CURSOR_STYLE(1);
	}

	DoScrollChecks();


	Vector2 pos;
	for (auto& item : vItems)
	{
		pos = ItemNumberToItemCoords(item.real);

		if (IsMouseInBounds(pos, Vector2(0.20f, 0.035f)))
		{
			// hover highlight
			DRAW_RECT(pos.x, pos.y, 0.20f, 0.035f, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A / 3, false);

			if (IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_ATTACK))
			{
				//pressedSelectAfterSelect = false;
				if (currentopM != item.real)
					currentopM = item.real;
				else
				{
					pressedSelectAfterSelect = true; // used for proper highlight, execute press
				}
			}
		}


	}

}

void MouseSupport::DrawOptionHighlight()
{
	if (Menu::totalop < 1)
		return;

	Vector2 pos = ItemNumberToItemCoords(MouseSupport::currentopM);
	Vector2 size = { 0.20f, 0.035f };

	if (Menu::gradients)
		DRAW_SPRITE("CommonMenu", "Gradient_Nav", pos.x, pos.y, size.x, size.y, 0.0f, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A, false, 0);
	else
		DRAW_RECT(pos.x, pos.y, size.x, size.y, selectionhi.R, selectionhi.G, selectionhi.B, selectionhi.A, false);

}

Vector2 MouseSupport::GetSafezoneBounds()
{
	float g = GET_SAFE_ZONE_SIZE(); // Safezone size.
	g = (g * 100) - 90;
	g = 10 - g;

	const float hmp = 5.4f;
	int screenw, screenh;
	GET_ACTUAL_SCREEN_RESOLUTION(&screenw, &screenh);
	float ratio = (float)screenw / screenh;
	float wmp = ratio * hmp;

	return Vector2(round(g * wmp) / 1920, round(g * hmp) / 1080);
}

Vector2 MouseSupport::MousePosition()
{
	//auto& res = MouseSupport::GetScreenResolutionMantainRatio();
	Vector2 pos;

	pos.x = GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_X); //idk
	pos.y = GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_Y);

	return pos;
}
bool MouseSupport::IsMouseInBounds(Vector2 const& boxCentre, Vector2 const& boxSize)
{
	Vector2 pos = MousePosition();

	return (pos.x >= boxCentre.x - boxSize.x / 2 && pos.x <= boxCentre.x + boxSize.x / 2)
		&& (pos.y > boxCentre.y - boxSize.y / 2 && pos.y < boxCentre.y + boxSize.y / 2);
}

std::pair<int, int> MouseSupport::GetScreenResolutionMantainRatio()
{
	int screenw, screenh;
	GET_ACTUAL_SCREEN_RESOLUTION(&screenw, &screenh);
	const float height = 1080.0f;
	float ratio = (float)screenw / screenh;
	float width = height * ratio;

	return std::make_pair((int)width, (int)height);
}

void MouseSupport::DoScrollChecks()
{
	if (IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_UP))
	{
		if (Menu::currentop > 1)
			Menu::Up();
	}
	else if (IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_DOWN))
	{
		if (Menu::currentop < Menu::totalop)
			Menu::Down();
	}

}

//--------------------------------Menu option drawing functions--------------------------------

bool IsOptionPressed()
{
	if (MenuPressTimer::IsButtonTapped(MenuPressTimer::Button::Accept) || MouseSupport::pressedSelectAfterSelect)
	{
		Game::Sound::PlayFrontend_default("SELECT");
		return true;
	}
	return false;
}
bool IsOptionRPressed()
{
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Right))
	{
		Game::Sound::PlayFrontend_default("NAV_LEFT_RIGHT");
		return true;
	}
	else return false;
}
bool IsOptionLPressed()
{
	if (MenuPressTimer::IsButtonHeldOrTapped(MenuPressTimer::Button::Left))
	{
		Game::Sound::PlayFrontend_default("NAV_LEFT_RIGHT");
		return true;
	}
	else return false;
}

bool null;
int inull;
void nullFunc() { return; }

void AddTitle(std::string text)
{
	text = Language::TranslateToSelected(text);

	if (titletext_ALPHA_DIS_TEMP)
	{
		Game::Print::setupdraw(font_title, Vector2(0.26, 0.26), true, false, false, titletext);
		Game::Print::drawstringGXT(text, 0.16f + menuPos.x, 0.1406f + menuPos.y);
		return;
	}

	Game::Print::setupdraw();
	if (titletext.A > 0 && titletext.R > 240 && titletext.G > 240 && titletext.B > 240) SET_TEXT_OUTLINE();
	SET_TEXT_FONT(font_title);

	SET_TEXT_COLOUR(titletext.R, titletext.G, titletext.B, titletext.A);

	if (Menu::bit_centre_title)
	{
		SET_TEXT_CENTRE(1);
		OptionY = 0.16f; // X coord
	}
	else OptionY = 0.066f; // X coord

	auto length = text.length();

	FLOAT offset = 0;

	if (length < 15)
		SET_TEXT_SCALE(0.75f, 0.75f);
	else if (length < 19)
	{
		SET_TEXT_SCALE(0.62f, 0.62f);
		offset = 0.006f;
	}
	else if (length < 23)
	{
		SET_TEXT_SCALE(0.51f, 0.51f);
		offset = 0.011f;
	}
	else offset = 0.015f;//SET_TEXT_SCALE(0.40f, 0.40f);

	Game::Print::drawstringGXT(text, OptionY + menuPos.x, 0.1f + offset + menuPos.y);

}
void AddOption(std::string text, bool& option_code_bool, void(&callback)(), int submenu_index, bool show_arrow, bool gxt)
{
	std::string tempChar;

	Menu::printingop++;

	OptionY = 0;
	if ((Menu::currentop < GTA_SCROLLOP && Menu::printingop <= GTA_MAXOP) || Menu::totalop <= GTA_MAXOP)
	{
		OptionY = Menu::printingop;
	}
	else
	{
		if (Menu::currentop >= GTA_SCROLLOP)
		{

			if (Menu::currentop > (Menu::totalop - GTA_BETOP))
			{
				OptionY = GTA_SCROLLOP + (GTA_BETOP - (Menu::totalop - Menu::printingop));
			}
			else
			{
				OptionY = GTA_SCROLLOP + (Menu::printingop - Menu::currentop);
			}
		}
	}
	if (OptionY > GTA_MAXOP || OptionY <= 0) return;

	// store on screen item number in array
	if (Menu::printingop == 1) MouseSupport::vItems.clear();
	MouseSupport::vItems.push_back({ Menu::printingop, (int)OptionY });

	OptionY = OptionY * 0.035f + 0.125f;

	Game::Print::setupdraw();
	if (font_options == 0)
		SET_TEXT_SCALE(0, 0.33f);
	SET_TEXT_FONT(font_options);
	SET_TEXT_COLOUR(optiontext.R, optiontext.G, optiontext.B, optiontext.A);
	if (Menu::bit_mouse ? Menu::printingop == MouseSupport::currentopM : Menu::printingop == Menu::currentop)
	{
		if (font_selection == 2 || font_selection == 7) tempChar = "  ~b~=="; // Font unsafe
		else tempChar = "  ~b~>"; // Font safe

		SET_TEXT_FONT(font_selection);
		SET_TEXT_COLOUR(selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A);
		if (IsOptionPressed())
		{
			/*if (&option_code_bool != &null)*/ option_code_bool = true;
			callback();
			if (submenu_index != -1)
				Menu::SetSub_delayed = submenu_index;
		}
	}
	else
	{
		if (font_options == 2 || font_options == 7)
			tempChar = "  ~b~=="; // Font unsafe
		else
			tempChar = "  ~b~>"; // Font safe
	}

	text = Language::TranslateToSelected(text);

	if (show_arrow || submenu_index != -1)
	{
		//Menu::possibleNameOfCurrentSubmenu = text;
		if (!gxt)
			text += tempChar;
	}
	if (gxt)
	{
		if (Menu::bit_centre_options)
		{
			SET_TEXT_CENTRE(1);
			Game::Print::drawstringGXT(text, 0.16f + menuPos.x, OptionY + menuPos.y);
		}
		else
			Game::Print::drawstringGXT(text, 0.066f + menuPos.x, OptionY + menuPos.y);
	}
	else
	{
		if (Menu::bit_centre_options)
		{
			SET_TEXT_CENTRE(1);
			Game::Print::drawstring(text, 0.16f + menuPos.x, OptionY + menuPos.y);
		}
		else
			Game::Print::drawstring(text, 0.066f + menuPos.x, OptionY + menuPos.y);
	}
}
inline void AddOption(std::ostream& os, bool& option_code_bool, void(&callback)(), int submenu_index, bool show_arrow, bool gxt)
{
	AddOption(dynamic_cast<std::ostringstream&>(os).str(), option_code_bool, callback, submenu_index, show_arrow, gxt);
}
void OptionStatus(BOOL status)
{
	if (OptionY < 0.6325f && OptionY > 0.1425f)
	{
		//char* tempChar;
		//SET_TEXT_FONT(4);
		//SET_TEXT_SCALE(0.34f, 0.34f);
		//SET_TEXT_CENTRE(1); SET_TEXT_OUTLINE();

		//if (status == 0){
		//	SET_TEXT_COLOUR(255, 102, 102, 250); //RED
		//	tempChar = "OFF";
		//}
		//else if (status == 1){
		//	SET_TEXT_COLOUR(102, 255, 102, 250); //GREEN
		//	tempChar = "ON";
		//}
		//else{
		//	SET_TEXT_COLOUR(255, 255, 102, 250); //YELLOW
		//	tempChar = "??";
		//}
		//Game::Print::drawstring(tempChar, 0.233f + menuPos.x, OptionY + menuPos.y);

		//char* tempChar = "000";
		//SET_TEXT_FONT(0);
		//SET_TEXT_SCALE(0.28f, 0.28f);
		//SET_TEXT_CENTRE(1);

		if (!HAS_STREAMED_TEXTURE_DICT_LOADED("mprankbadge")) REQUEST_STREAMED_TEXTURE_DICT("mprankbadge", 0);

		Vector2 res = { 0.022f, 0.03f };

		if (status == 0)
		{
			DRAW_SPRITE("mprankbadge", "rankglobe_21x21_colour", get_xcoord_at_menu_rightEdge(res.x, 0.0f, true), OptionY + 0.0166f + menuPos.y, res.x, res.y, 0.0f, 255, 102, 102, 250, false, 0);
			// medaldot_32
			//DRAW_SPRITE("mpsafecracking", "dial_bg", get_xcoord_at_menu_rightEdge(res.x, 0.0f, true), OptionY + 0.0166f, res.x, res.y, 0.0f, 255, 102, 102, 250);
			//DRAW_RECT(0.233 + menuPos.x, OptionY + 0.0147f + menuPos.y, 0.05, 0.0315, 255, 102, 102, 250);
			//DRAW_SPRITE("CommonMenu", "shop_box_blank", 0.233f + menuPos.x, OptionY + 0.0147f + menuPos.y, 0.06f, 0.037f, 0.0f, 255, 102, 102, 250);
			//SET_TEXT_COLOUR(255, 102, 102, 250); //RED
			//tempChar = "OFF";
		}
		else
		{
			DRAW_SPRITE("mprankbadge", "rankglobe_21x21_colour", get_xcoord_at_menu_rightEdge(res.x, 0.0f, true), OptionY + 0.0166f + menuPos.y, res.x, res.y, 0.0f, 102, 255, 102, 250, false, 0);
			// medaldot_32 + emptydot_32
			//DRAW_SPRITE("mpsafecracking", "dial_bg", get_xcoord_at_menu_rightEdge(res.x, 0.0f, true), OptionY + 0.0166f, res.x, res.y, 0.0f, 102, 255, 102, 250);
			//DRAW_SPRITE("mpsafecracking", "dial_bg", 0.233f + menuPos.x, OptionY + 0.0146f + menuPos.y, 0.03f, 0.03f, 0.0f, 255, 102, 102, 250);
			//DRAW_RECT(0.233 + menuPos.x, OptionY + 0.0147f + menuPos.y, 0.05, 0.0315, 102, 255, 102, 250);
			//DRAW_SPRITE("CommonMenu", "shop_box_blank", 0.233f + menuPos.x, OptionY + 0.0147f + menuPos.y, 0.06f, 0.037f, 0.0f, 102, 255, 102, 250);
			//SET_TEXT_COLOUR(102, 255, 102, 250); //GREEN
			//tempChar = "ON";
		}

		//Game::Print::drawstring(tempChar, 0.233f + menuPos.x, OptionY + menuPos.y);

	}
}
void AddToggle(const std::string& text, bool& loop_variable, bool& extra_option_code_ON, bool& extra_option_code_OFF, bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);

	if (null) {
		loop_variable = !loop_variable;
		if (loop_variable != 0) extra_option_code_ON = true;
		else extra_option_code_OFF = true;
	}

	OptionStatus(loop_variable); // Display ON/OFF
}
void AddToggle(const std::string& text, bool& loop_variable, void(&callback_ON)(), void(&callback_OFF)(), bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);

	if (null) {
		loop_variable = !loop_variable;
		if (loop_variable != 0) callback_ON();
		else callback_OFF();
	}

	OptionStatus(loop_variable); // Display ON/OFF
}
void AddLocal(const std::string& text, BOOL condition, bool& option_code_ON, bool& option_code_OFF, bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);
	if (null)
	{
		if (condition == 0) option_code_ON = true;
		else option_code_OFF = true;
	}

	OptionStatus(condition); // Display ON/OFF
}
void AddLocal(const std::string& text, BOOL condition, void(&callback_ON)(), void(&callback_OFF)(), bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);
	if (null)
	{
		if (condition == 0) callback_ON();
		else callback_OFF();
	}

	OptionStatus(condition); // Display ON/OFF
}
void AddBreak(std::string text)
{
	Menu::printingop++; Menu::breakcount++;

	OptionY = 0;
	if ((Menu::currentop < GTA_SCROLLOP && Menu::printingop <= GTA_MAXOP) || Menu::totalop <= GTA_MAXOP)
	{
		OptionY = Menu::printingop;
	}
	else
	{
		if (Menu::currentop >= GTA_SCROLLOP)
		{

			if (Menu::currentop > (Menu::totalop - GTA_BETOP))
			{
				OptionY = GTA_SCROLLOP + (GTA_BETOP - (Menu::totalop - Menu::printingop));
			}
			else
			{
				OptionY = GTA_SCROLLOP + (Menu::printingop - Menu::currentop);
			}
		}
	}
	if (OptionY > GTA_MAXOP || OptionY <= 0) return;

	OptionY = OptionY * 0.035f + 0.125f;


	Game::Print::setupdraw(); //SET_TEXT_OUTLINE();
	SET_TEXT_FONT(font_breaks);
	SET_TEXT_COLOUR(optionbreaks.R, optionbreaks.G, optionbreaks.B, optionbreaks.A);
	if (Menu::printingop == Menu::currentop)
	{
		switch (Menu::breakscroll)
		{
		case 1: // Up
			if (Menu::currentop <= 1) Menu::Bottom();
			else Menu::Up();
			break;
		case 2: default: // Down
			if (Menu::currentop >= Menu::totalop) Menu::Top();
			else Menu::Down();
			break;
			//case 3: // Bottom
			//	Menu::currentop_w_breaks = Menu::totalop - (Menu::totalbreaks - 1);
			//	Menu::currentop--;
			//	break;
			//case 4: // Top
			//	Menu::currentop_w_breaks = 1;
			//	Menu::currentop++;
			//	break;
		}

	}

	text = Language::TranslateToSelected(text);

	if (Menu::bit_centre_breaks)
	{
		SET_TEXT_CENTRE(1);
		Game::Print::drawstringGXT(text, 0.16f + menuPos.x, OptionY + menuPos.y);
	}
	else
	{
		Game::Print::drawstringGXT(text, 0.066f + menuPos.x, OptionY + menuPos.y);
	}

}
void AddNumber(const std::string& text, float value, __int8 decimal_places, bool& A_PRESS, bool& RIGHT_PRESS, bool& LEFT_PRESS, bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);

	if (OptionY < 0.6325f && OptionY > 0.1425f)
	{
		FLOAT newXpos;
		Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, optiontext);
		if (Menu::printingop == *Menu::currentopATM)
		{
			if (&RIGHT_PRESS != &null && &LEFT_PRESS != &null)
			{
				Vector3 textureRes = GET_TEXTURE_RESOLUTION("CommonMenu", "arrowright");
				textureRes.x /= (Game::defaultScreenRes.first * 2);
				textureRes.y /= (Game::defaultScreenRes.second * 2);
				newXpos = get_xcoord_at_menu_rightEdge(textureRes.x - 0.005, 0.0f, true);
				DRAW_SPRITE("CommonMenu", "arrowright", newXpos, OptionY + 0.016f + menuPos.y, textureRes.x, textureRes.y, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A, false, 0); // Right
				newXpos = get_xcoord_at_menu_rightEdge(textureRes.x - 0.005, textureRes.x - 0.005 + Game::Print::GetTextWidth(value, decimal_places), true);
				DRAW_SPRITE("CommonMenu", "arrowleft", newXpos, OptionY + 0.016f + menuPos.y, textureRes.x, textureRes.y, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A, false, 0); // Left

				Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, selectedtext);
				newXpos = get_xcoord_at_menu_rightEdge(Game::Print::GetTextWidth(value, decimal_places), textureRes.x - 0.005, true);
				Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, selectedtext);
			}
			else
			{
				newXpos = get_xcoord_at_menu_rightEdge(Game::Print::GetTextWidth(value, decimal_places), 0.0024f, true);
				Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, selectedtext);
			}
		}
		else
		{
			newXpos = get_xcoord_at_menu_rightEdge(Game::Print::GetTextWidth(value, decimal_places), 0.0024f, true);
			Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, optiontext);
		}

		Game::Print::drawfloat(value, decimal_places, newXpos, OptionY + 0.0056 + menuPos.y);
	}

	if (Menu::printingop == *Menu::currentopATM)
	{
		bit_frontend_addnumber_selected = true;
		if (&A_PRESS != &null) Menu::add_IB(INPUT_CELLPHONE_SELECT, "Input");

		if (null) A_PRESS = true;
		else if (IsOptionRPressed()) RIGHT_PRESS = true;
		else if (IsOptionLPressed()) LEFT_PRESS = true;
	}

}
void draw_tickol_tick_BNW(const std::string& textureDict, const std::string& normal, const std::string& selected, const RGBA& colour)
{
	if (!HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict.c_str())) REQUEST_STREAMED_TEXTURE_DICT(textureDict.c_str(), 0);
	std::string textureName;
	if (Menu::printingop == *Menu::currentopATM)
		textureName = selected;
	else textureName = normal;
	Vector3 texture_res = GET_TEXTURE_RESOLUTION(textureDict.c_str(), textureName.c_str());
	texture_res.x /= (Game::defaultScreenRes.first * 2);
	texture_res.y /= (Game::defaultScreenRes.second * 2);
	DRAW_SPRITE(textureDict.c_str(), textureName.c_str(), get_xcoord_at_menu_rightEdge(texture_res.x, 0.0f, true), OptionY + 0.016f + menuPos.y, texture_res.x, texture_res.y, 0.0f, 255, 255, 255, colour.A, false, 0);

}
inline void draw_tickol_tick(TICKOL tickType)
{
	RGBA* colour = &optiontext;
	if (Menu::printingop == *Menu::currentopATM) colour = &selectedtext;
	std::string textureDict, textureName;
	Vector3 texture_res;

	switch (tickType)
	{
	case TICKOL::TICK: textureDict = "CommonMenu"; textureName = "shop_tick_icon"; break;
	case TICKOL::TICK2: textureDict = "crosstheline"; textureName = "timer_largetick_32"; break;
	case TICKOL::CROSS: textureDict = "crosstheline"; textureName = "timer_largecross_32"; break;

	case TICKOL::ARROWRIGHT: textureDict = "CommonMenu"; textureName = "arrowright"; break;
	case TICKOL::ARROWLEFT: textureDict = "CommonMenu"; textureName = "arrowleft"; break;

	case TICKOL::MANWON: textureDict = "CommonMenuTU"; textureName = "last_team_standing"; break;

	case TICKOL::SKULL_DM: textureDict = "CommonMenuTU"; textureName = "deathmatch"; break;
	case TICKOL::SKULL_TDM: textureDict = "CommonMenuTU"; textureName = "team_deathmatch"; break;

	case TICKOL::CARBANG_DM: textureDict = "CommonMenuTU"; textureName = "vehicle_deathmatch"; break;

	case TICKOL::SMALLNEWSTAR: textureDict = "CommonMenu"; textureName = "shop_new_star"; break;

	case TICKOL::PERCENTAGESTICKER: textureDict = "mpshopsale"; textureName = "saleicon"; break;

	case TICKOL::BOXTICK:
		draw_tickol_tick_BNW("CommonMenu", "shop_box_tick", "shop_box_tickb", *colour);
		return; break;
	case TICKOL::BOXCROSS:
		draw_tickol_tick_BNW("CommonMenu", "shop_box_cross", "shop_box_crossb", *colour);
		return; break;
	case TICKOL::BOXBLANK:
		draw_tickol_tick_BNW("CommonMenu", "shop_box_blank", "shop_box_blankb", *colour);
		return; break;

	case TICKOL::CARTHING:
		draw_tickol_tick_BNW("CommonMenu", "shop_garage_icon_a", "shop_garage_icon_b", *colour);
		return; break;

	case TICKOL::BIKETHING:
		draw_tickol_tick_BNW("CommonMenu", "shop_garage_bike_icon_a", "shop_garage_bike_icon_b", *colour);
		return; break;

	case TICKOL::WEAPONTHING:
		draw_tickol_tick_BNW("CommonMenu", "shop_gunclub_icon_a", "shop_gunclub_icon_b", *colour);
		return; break;

	case TICKOL::TATTOOTHING:
		draw_tickol_tick_BNW("CommonMenu", "shop_tattoos_icon_a", "shop_tattoos_icon_b", *colour);
		return; break;

	case TICKOL::MAKEUPTHING:
		draw_tickol_tick_BNW("CommonMenu", "shop_makeup_icon_a", "shop_makeup_icon_b", *colour);
		return; break;

	case TICKOL::MASKTHING:
		draw_tickol_tick_BNW("CommonMenu", "shop_mask_icon_a", "shop_mask_icon_b", *colour);
		return; break;

		//case TICKOL::


	}

	if (!HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict.c_str())) REQUEST_STREAMED_TEXTURE_DICT(textureDict.c_str(), 0);
	texture_res = GET_TEXTURE_RESOLUTION(textureDict.c_str(), textureName.c_str());
	texture_res.x /= (Game::defaultScreenRes.first * 2);
	texture_res.y /= (Game::defaultScreenRes.second * 2);

	DRAW_SPRITE(textureDict.c_str(), textureName.c_str(), get_xcoord_at_menu_rightEdge(texture_res.x, 0.0f, true), OptionY + 0.016f + menuPos.y, texture_res.x, texture_res.y, 0.0f, colour->R, colour->G, colour->B, colour->A, false, 0);

}
void AddTickol(const std::string& text, BOOL condition, bool& option_code_ON, bool& option_code_OFF, TICKOL tickTrue, TICKOL tickFalse, bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);

	if (OptionY < 0.6325f && OptionY > 0.1425f)
	{
		if (condition)
		{
			if (tickTrue != TICKOL::NONE) draw_tickol_tick(tickTrue);
		}
		else
		{
			if (tickFalse != TICKOL::NONE) draw_tickol_tick(tickFalse);
		}
	}

	if (null)
	{
		if (condition == 0) option_code_ON = true;
		else option_code_OFF = true;
	}
}
void AddTickol(const std::string& text, BOOL condition, void(&callback_ON)(), void(&callback_OFF)(), TICKOL tickTrue, TICKOL tickFalse, bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);

	if (OptionY < 0.6325f && OptionY > 0.1425f)
	{
		if (condition)
		{
			if (tickTrue != TICKOL::NONE) draw_tickol_tick(tickTrue);
		}
		else
		{
			if (tickFalse != TICKOL::NONE) draw_tickol_tick(tickFalse);
		}
	}

	if (null)
	{
		if (condition == 0) callback_ON();
		else callback_OFF();
	}
}
template<typename TA>
inline void AddTexter(const std::string& text, int selectedindex, const TA& textarray, bool& A_PRESS, bool& RIGHT_PRESS, bool& LEFT_PRESS, bool gxt)
{
	null = 0;
	AddOption(text, null, nullFunc, -1, false, gxt);

	if (OptionY < 0.6325f && OptionY > 0.1425f)
	{
		std::string chartickStr;
		if (selectedindex < 0 || (selectedindex >= textarray.size()))
		{
			chartickStr = std::to_string(selectedindex);
		}
		else
		{
			chartickStr = textarray.at(selectedindex);
		}

		chartickStr = DOES_TEXT_LABEL_EXIST(chartickStr.c_str()) ? GET_FILENAME_FOR_AUDIO_CONVERSATION(chartickStr.c_str()) : Language::TranslateToSelected(chartickStr);
		FLOAT newXpos;
		Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, optiontext);

		if (Menu::printingop == *Menu::currentopATM)
		{
			if (&RIGHT_PRESS != &null && &LEFT_PRESS != &null)
			{
				Vector3 textureRes = GET_TEXTURE_RESOLUTION("CommonMenu", "arrowright");
				textureRes.x /= (Game::defaultScreenRes.first * 2);
				textureRes.y /= (Game::defaultScreenRes.second * 2);
				newXpos = get_xcoord_at_menu_rightEdge(textureRes.x - 0.005, 0.0f, true);
				DRAW_SPRITE("CommonMenu", "arrowright", newXpos, OptionY + 0.016f + menuPos.y, textureRes.x, textureRes.y, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A, false, 0); // Right
				newXpos = get_xcoord_at_menu_rightEdge(textureRes.x - 0.005, textureRes.x - 0.005 + Game::Print::GetTextWidth(chartickStr), true);
				DRAW_SPRITE("CommonMenu", "arrowleft", newXpos, OptionY + 0.016f + menuPos.y, textureRes.x, textureRes.y, 0.0f, selectedtext.R, selectedtext.G, selectedtext.B, selectedtext.A, false, 0); // Left

				Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, selectedtext);
				newXpos = get_xcoord_at_menu_rightEdge(Game::Print::GetTextWidth(chartickStr), textureRes.x - 0.005, true);
				Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, selectedtext);
			}
			else
			{
				newXpos = get_xcoord_at_menu_rightEdge(Game::Print::GetTextWidth(chartickStr), 0.0024f, true);
				Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, selectedtext);
			}
		}
		else
		{
			newXpos = get_xcoord_at_menu_rightEdge(Game::Print::GetTextWidth(chartickStr), 0.0024f, true);
			Game::Print::setupdraw(0, Vector2(0.26, 0.26), true, true, false, optiontext);
		}

		Game::Print::drawstring(chartickStr, newXpos, OptionY + 0.0056 + menuPos.y);
	}

	if (Menu::printingop == *Menu::currentopATM)
	{
		bit_frontend_addnumber_selected = true;
		if (&A_PRESS != &null) Menu::add_IB(INPUT_CELLPHONE_SELECT, "Input");

		if (null) A_PRESS = true;
		else if (IsOptionRPressed()) RIGHT_PRESS = true;
		else if (IsOptionLPressed()) LEFT_PRESS = true;

	}

}
void AddTexter(const std::string& text, int selectedindex, const std::vector<std::string>& textarray, bool& A_PRESS, bool& RIGHT_PRESS, bool& LEFT_PRESS, bool gxt)
{
	AddTexter<std::vector<std::string>>(text, selectedindex, textarray, A_PRESS, RIGHT_PRESS, LEFT_PRESS, gxt);
}



void Add_preset_colour_options_previews(UINT8 const r, UINT8 const g, UINT8 const b)
{
	Vector2 res = { 0.1f, 0.0889f };

	/*res = GET_TEXTURE_RESOLUTION("lgm_dlc_luxe", "t20");
	res.x = res.x * 0.5f / Game::defaultScreenRes.first;
	res.y = res.y * 0.5f / Game::defaultScreenRes.second;*/

	FLOAT x_coord = 0.324f + menuPos.x;
	if (menuPos.x > 0.45f) x_coord = menuPos.x - 0.003f;

	DRAW_RECT(x_coord, OptionY + 0.044f + menuPos.y, res.x + 0.003f, res.y + 0.003f, 0, 0, 0, 212, false);

	DRAW_RECT(x_coord, OptionY + 0.044f + menuPos.y, res.x, res.y, r, g, b, 255, false);
}
void Add_preset_colour_options_previews(const RgbS& rgb)
{
	Add_preset_colour_options_previews(rgb.R, rgb.G, rgb.B);
}
void Add_preset_colour_options_previews(const RGBA& rgb)
{
	Add_preset_colour_options_previews(rgb.R, rgb.G, rgb.B);
}
bool Add_preset_colour_options(INT& r, INT& g, INT& b)
{
	bool bPressed = false;
	for (auto& colol : _vNeonColours)
	{
		null = 0;
		AddTickol(colol.name.c_str(), r == colol.rgb.R && g == colol.rgb.G && b == colol.rgb.B, null, null);
		if (null)
		{
			r = colol.rgb.R;
			g = colol.rgb.G;
			b = colol.rgb.B;
			bPressed = true;
		}

		if (Menu::printingop == *Menu::currentopATM)
			Add_preset_colour_options_previews(colol.rgb.R, colol.rgb.G, colol.rgb.B);
	}
	return bPressed;
}












