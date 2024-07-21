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
/* When you make a crappy menu structure originally written in C in 2015 and decide to keep it */

#include "submenu_enum.h"
#include "..\Scripting\enums.h"
#include "..\Scripting\Scaleform.h"

#include <utility>
#include <vector>
//#include <array>
#include <string>
#include <functional>

typedef int INT, BOOL;
typedef signed char INT8;
typedef short INT16;
typedef unsigned int UINT;
typedef unsigned __int8 UINT8;
typedef unsigned short UINT16;
typedef unsigned long DWORD;
typedef char *PCHAR;

namespace VirtualKey {
	enum VirtualKey : int;
}

class Vector2;

class RGBA;
class RgbS;

//struct Scaleform_IbT { int button; std::string text; bool isKey; };
//class Scaleform;


#define GTA_SCROLLOP 8
#define GTA_BETOP 6
#define GTA_MAXOP 14


float get_xcoord_at_menu_rightEdge(float widthOfElement, float extraWidth, bool centered);
float get_xcoord_at_menu_leftEdge(float width, bool centered);

namespace MenuPressTimer
{
	enum class Button
	{
		None, Up, Down, Left, Right, Back, Accept
	};
	extern MenuPressTimer::Button currentButton;
	extern DWORD offsettedTime;

	void Update();
	bool IsButtonHeld(const MenuPressTimer::Button& button);
	bool IsButtonTapped(const MenuPressTimer::Button& button);
	bool IsButtonHeldOrTapped(const MenuPressTimer::Button& button);
}

extern bool titletext_ALPHA_DIS_TEMP;
extern bool bit_frontend_addnumber_selected;
extern bool g_menuNotOpenedYet;

extern Vector2 menuPos;
extern Vector2 g_deltaCursorNormal;
extern float OptionY;

extern INT8 font_title;
extern INT8 font_options;
extern INT8 font_selection;
extern INT8 font_breaks;
extern INT8 font_xyzh;
extern INT8 font_speedo;

extern RGBA titlebox;
extern RGBA BG;
extern RGBA titletext;
extern RGBA optiontext;
extern RGBA selectedtext;
extern RGBA optionbreaks;
extern RGBA optioncount;
extern RGBA selectionhi;
extern RGBA _globalPedTrackers_Col;

extern std::pair<UINT16, UINT16> menubindsGamepad;
extern UINT16 menubinds;
extern UINT16 respawnbinds;
extern INT8 g_loglevel;

class MenuInput final
{
public:

	static bool IsUsingController();
	static void UpdateDeltaCursorNormal();

};

class MouseSupport final
{
public:
	static bool pressedSelectAfterSelect;
	static INT currentopM;
	struct ItemNumber { INT real; INT onScreen; };
	static std::vector<ItemNumber> vItems;

	static INT ItemNumberToItemNumberOnScreen(INT itemNumber);

	static Vector2 ItemNumberToItemCoords(INT itemNumber);

	static void Tick();

	static void DisableControls();

	static void DoMouseTick();

	static void DrawOptionHighlight();

	static Vector2 GetSafezoneBounds();

	static Vector2 MousePosition();
	static bool IsMouseInBounds(Vector2 const& boxCentre, Vector2 const& boxSize);

	static std::pair<int, int> GetScreenResolutionMantainRatio();

	static void DoScrollChecks();

};

class Menu final
{
public:
	static UINT16 currentsub, LOOCsub;
	static INT currentop;
	static INT* currentopATM;
	static INT currentop_w_breaks;
	static INT totalop;
	static INT printingop;
	static UINT16 breakcount;
	static UINT16 totalbreaks;
	static UINT8 breakscroll;
	static INT16 currentsub_ar_index;
	static INT currentsub_ar[100];
	static INT currentop_ar[100];
	static INT SetSub_delayed;
	static int delayedTimer;
	static bool bit_controller, bit_mouse, bit_centre_title, bit_centre_options, bit_centre_breaks, gradients, thin_line_over_screct, bit_glare_test;
	static Scaleform scaleform_menuGlare, instructional_buttons;
	static std::vector<Scaleform_IbT> vIB;
	static std::function<void()> OnSubBack;


	static inline void Tick()
	{
		MouseSupport::Tick();
		Menu::base();
		Menu::loops();
		Menu::sub_handler();
	}

	static void loops();
	static void sub_handler();
	static void submenu_switch();
	static void justopened();

	static void SetInputMethods();
	static void DisableControls();
	static void base();
	static void titlebox_draw();
	static void background();
	static void optionhi();
	static bool isBinds();
	static void while_closed();
	static void while_opened();
	static void Up(bool playSound = true);
	static void Down(bool playSound = true);
	static void Bottom(bool playSound = true);
	static void Top(bool playSound = true);
	static void SetSub_previous();
	static void SetSub_new(INT sub_index);
	static void SetSub_closed();

	static void glare_test();

	static void set_opened_IB();
	static void add_IB(ControllerInput button_id, std::string string_val);
	static void add_IB(VirtualKey::VirtualKey button_id, std::string string_val);
	static void add_IB(ScaleformButton button_id, std::string string_val);
	static std::string get_key_IB(const Scaleform_IbT& ib);
	static void draw_IB();

};


//bool IsOptionPressed();
//bool IsOptionRPressed();
//bool IsOptionLPressed();

extern bool null;
extern int inull;
void nullFunc();

enum class TICKOL : UINT8
{
	NONE,
	TICK,
	TICK2,
	CROSS,
	BOXTICK,
	BOXCROSS,
	BOXBLANK,
	ARROWRIGHT,
	ARROWLEFT,
	CARTHING,
	BIKETHING,
	WEAPONTHING,
	TATTOOTHING,
	MAKEUPTHING,
	MASKTHING,
	MANWON,
	SKULL_DM,
	SKULL_TDM,
	CARBANG_DM,
	SMALLNEWSTAR,
	PERCENTAGESTICKER,
};

void AddTitle(std::string text);
void AddOption(std::string text, bool &option_code_bool = null, void(&callback)() = nullFunc, int submenu_index = -1, bool show_arrow = 0, bool gxt = 0);
inline void AddOption(std::ostream& os, bool &option_code_bool = null, void(&callback)() = nullFunc, int submenu_index = -1, bool show_arrow = 0, bool gxt = 0);
void OptionStatus(BOOL status);
void AddToggle(const std::string& text, bool &loop_variable, bool &extra_option_code_ON = null, bool &extra_option_code_OFF = null, bool gxt = 0);
void AddToggle(const std::string& text, bool &loop_variable, void(&callback_ON)(), void(&callback_OFF)(), bool gxt = 0);
void AddLocal(const std::string& text, BOOL condition, bool &option_code_ON, bool &option_code_OFF, bool gxt = 0);
void AddLocal(const std::string& text, BOOL condition, void(&callback_ON)(), void(&callback_OFF)(), bool gxt = 0);
void AddBreak(std::string text);
void AddNumber(const std::string& text, float value, __int8 decimal_places, bool &A_PRESS = null, bool &RIGHT_PRESS = null, bool &LEFT_PRESS = null, bool gxt = 0);
void draw_tickol_tick_BNW(const std::string& textureDict, const std::string& normal, const std::string& selected, const RGBA& colour);
inline void draw_tickol_tick(TICKOL tickType);
void AddTickol(const std::string& text, BOOL condition, bool &option_code_ON, bool &option_code_OFF, TICKOL tickTrue = TICKOL::TICK, TICKOL tickFalse = TICKOL::NONE, bool gxt = false);
void AddTickol(const std::string& text, BOOL condition, void(&callback_ON)(), void(&callback_OFF)(), TICKOL tickTrue = TICKOL::TICK, TICKOL tickFalse = TICKOL::NONE, bool gxt = false);
void AddTexter(const std::string& text, int selectedindex, const std::vector<std::string>& textarray, bool &A_PRESS = null, bool &RIGHT_PRESS = null, bool &LEFT_PRESS = null, bool gxt = 0);


void Add_preset_colour_options_previews(UINT8 const r, UINT8 const g, UINT8 const b);
void Add_preset_colour_options_previews(const RgbS& rgb);
void Add_preset_colour_options_previews(const RGBA& rgb);
bool Add_preset_colour_options(INT& r, INT& g, INT& b);



