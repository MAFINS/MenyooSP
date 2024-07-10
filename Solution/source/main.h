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
#pragma once

#include <Windows.h>

//#pragma comment(lib, "..\external\ScriptHookV\SDK\lib\ScriptHookV.lib")



/* textures */

// Create texture
//	texFileName	- texture file name, it's best to specify full texture path and use PNG textures
//	returns	internal texture id
//	Texture deletion is performed automatically when game reloads scripts
//	Can be called only in the same thread as natives

///extern int(*createTexture)(const char *texFileName);
__declspec(dllimport) int createTexture(const char *texFileName);

// Draw texture
//	id		-	texture id recieved from createTexture()
//	index	-	each texture can have up to 64 different instances on screen at one time
//	level	-	draw level, being used in global draw order, texture instance with least level draws first
//	time	-	how much time (ms) texture instance will stay on screen, the amount of time should be enough
//				for it to stay on screen until the next corresponding drawTexture() call
//	sizeX,Y	-	size in screen space, should be in the range from 0.0 to 1.0, e.g setting this to 0.2 means that
//				texture instance will take 20% of the screen space
//	centerX,Y -	center position in texture space, e.g. 0.5 means real texture center
//	posX,Y	-	position in screen space, [0.0, 0.0] - top left corner, [1.0, 1.0] - bottom right,
//				texture instance is positioned according to it's center
//	rotation -	should be in the range from 0.0 to 1.0
//	screenHeightScaleFactor - screen aspect ratio, used for texture size correction, you can get it using natives
//	r,g,b,a	-	color, should be in the range from 0.0 to 1.0
//
//	Texture instance draw parameters are updated each time script performs corresponding call to drawTexture()
//	You should always check your textures layout for 16:9, 16:10 and 4:3 screen aspects, for ex. in 1280x720,
//	1440x900 and 1024x768 screen resolutions, use windowed mode for this
//	Can be called only in the same thread as natives

///extern void(*drawTexture)(int id, int index, int level, int time,float sizeX, float sizeY, float centerX, float centerY,float posX, float posY, float rotation, float screenHeightScaleFactor,float r, float g, float b, float a);
__declspec(dllimport) void drawTexture(int id, int index, int level, int time,float sizeX, float sizeY, float centerX, float centerY,float posX, float posY, float rotation, float screenHeightScaleFactor,float r, float g, float b, float a);

// IDXGISwapChain::Present callback
// Called right before the actual Present method call, render test calls don't trigger callbacks
// When the game uses DX10 it actually uses DX11 with DX10 feature level
// Remember that you can't call natives inside
// void OnPresent(IDXGISwapChain *swapChain);
typedef void(*PresentCallback)(void *);

// Register IDXGISwapChain::Present callback
// must be called on dll attach
///extern void(*presentCallbackRegister)(PresentCallback cb);
__declspec(dllimport) void presentCallbackRegister(PresentCallback cb);

// Unregister IDXGISwapChain::Present callback
// must be called on dll detach
///extern void(*presentCallbackUnregister)(PresentCallback cb);
__declspec(dllimport) void presentCallbackUnregister(PresentCallback cb);

/* keyboard */

// DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow
typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

// Register keyboard handler
// must be called on dll attach
///extern void(*keyboardHandlerRegister)(KeyboardHandler handler);
__declspec(dllimport) void keyboardHandlerRegister(KeyboardHandler handler);

// Unregister keyboard handler
// must be called on dll detach
///extern void(*keyboardHandlerUnregister)(KeyboardHandler handler);
__declspec(dllimport) void keyboardHandlerUnregister(KeyboardHandler handler);

/* scripts */

///extern void(*scriptWait)(DWORD time);
__declspec(dllimport) void scriptWait(DWORD time);
///extern void(*scriptRegister)(HMODULE module, void(*LP_SCRIPT_MAIN)());
__declspec(dllimport) void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
///extern void(*scriptRegisterAdditionalThread)(HMODULE module, void(*LP_SCRIPT_MAIN)());
__declspec(dllimport) void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
/////extern void(*scriptUnregister)(HMODULE module);
__declspec(dllimport) void scriptUnregister(HMODULE module);
///extern void(*scriptUnregister)(void(*LP_SCRIPT_MAIN)());
__declspec(dllimport) void scriptUnregister(void(*LP_SCRIPT_MAIN)()); // deprecated

///extern void(*nativeInit)(UINT64 hash);
__declspec(dllimport) void nativeInit(UINT64 hash);
///extern void(*nativePush64)(UINT64 val);
__declspec(dllimport) void nativePush64(UINT64 val);
///extern PUINT64(*nativeCall)();
__declspec(dllimport) PUINT64 nativeCall();

//static void WAIT(DWORD time) { scriptWait(time); }
//static void TERMINATE() { WAIT(MAXDWORD); }

// Returns pointer to global variable
// make sure that you check game version before accessing globals because
// ids may differ between patches
///extern PUINT64(*getGlobalPtr)(int globalId);
__declspec(dllimport) PUINT64 getGlobalPtr(int globalId);

/* world */

// Get entities from internal pools
// return value represents filled array elements count
// can be called only in the same thread as natives
///extern int(*worldGetAllVehicles)(int *arr, int arrSize);
__declspec(dllimport) int worldGetAllVehicles(int *arr, int arrSize);
///extern int(*worldGetAllPeds)(int *arr, int arrSize);
__declspec(dllimport) int worldGetAllPeds(int *arr, int arrSize);
///extern int(*worldGetAllObjects)(int *arr, int arrSize);
__declspec(dllimport) int worldGetAllObjects(int *arr, int arrSize);
///extern int(*worldGetAllPickups)(int *arr, int arrSize);
__declspec(dllimport) int worldGetAllPickups(int *arr, int arrSize);

/* misc */

// Returns base object pointer using it's script handle
// make sure that you check game version before accessing object fields because
// offsets may differ between patches
///extern BYTE(*getScriptHandleBaseAddress)(int handle);
__declspec(dllimport) BYTE *getScriptHandleBaseAddress(int handle);

enum eGameVersion : int
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,

	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,

	VER_1_0_372_2_STEAM,
	VER_1_0_372_2_NOSTEAM,

	VER_1_0_393_2_STEAM,
	VER_1_0_393_2_NOSTEAM,

	VER_1_0_393_4_STEAM,
	VER_1_0_393_4_NOSTEAM,

	VER_1_0_463_1_STEAM,
	VER_1_0_463_1_NOSTEAM,

	VER_1_0_505_2_STEAM,
	VER_1_0_505_2_NOSTEAM,

	VER_1_0_573_1_STEAM,
	VER_1_0_573_1_NOSTEAM,

	VER_1_0_617_1_STEAM,
	VER_1_0_617_1_NOSTEAM,

	VER_1_0_678_1_STEAM,
	VER_1_0_678_1_NOSTEAM,

	VER_1_0_757_2_STEAM,
	VER_1_0_757_2_NOSTEAM,

	VER_1_0_757_4_STEAM,
	VER_1_0_757_4_NOSTEAM,

	VER_1_0_791_2_STEAM,
	VER_1_0_791_2_NOSTEAM,

	VER_1_0_877_1_STEAM,
	VER_1_0_877_1_NOSTEAM,

	VER_1_0_944_2_STEAM,
	VER_1_0_944_2_NOSTEAM,

	VER_1_0_1011_1_STEAM,
	VER_1_0_1011_1_NOSTEAM,

	VER_1_0_1032_1_STEAM,
	VER_1_0_1032_1_NOSTEAM,

	VER_1_0_1103_2_STEAM,
	VER_1_0_1103_2_NOSTEAM,

	VER_1_0_1180_2_STEAM,
	VER_1_0_1180_2_NOSTEAM,

	VER_1_0_1290_1_STEAM,
	VER_1_0_1290_1_NOSTEAM,

	VER_1_0_1365_1_STEAM,
	VER_1_0_1365_1_NOSTEAM,

	VER_1_0_1493_0_STEAM,
	VER_1_0_1493_0_NOSTEAM,

	VER_1_0_1493_1_STEAM,
	VER_1_0_1493_1_NOSTEAM,

	VER_1_0_1604_0_STEAM,
	VER_1_0_1604_0_NOSTEAM,

	VER_1_0_1604_1_STEAM,
	VER_1_0_1604_1_NOSTEAM,
	
    	VER_1_0_1737_0_STEAM,
    	VER_1_0_1737_0_NOSTEAM,
	
	VER_1_0_1737_6_STEAM,
    	VER_1_0_1737_6_NOSTEAM,
	
	VER_1_0_1868_0_STEAM,
    	VER_1_0_1868_0_NOSTEAM,
	
	VER_1_0_1868_1_STEAM,
  	VER_1_0_1868_1_NOSTEAM,
	VER_1_0_1868_4_EGS,
    
    	VER_1_0_2060_0_STEAM,
	VER_1_0_2060_0_NOSTEAM,
	
	VER_1_0_2060_1_STEAM,
	VER_1_0_2060_1_NOSTEAM,
    
   	VER_1_0_2189_0_STEAM,
	VER_1_0_2189_0_NOSTEAM,
	
	VER_1_0_2215_0_STEAM,
	VER_1_0_2215_0_NOSTEAM,
	
	VER_1_0_2245_0_STEAM,
	VER_1_0_2245_0_NOSTEAM,

	VER_1_0_2372_0_STEAM,
	VER_1_0_2372_0_NOSTEAM,
	
	VER_1_0_2545_0_STEAM,
	VER_1_0_2545_0_NOSTEAM,

	VER_1_0_2612_1_STEAM,
	VER_1_0_2612_1_NOSTEAM,

	VER_1_0_2628_2_STEAM,
	VER_1_0_2628_2_NOSTEAM,

	VER_1_0_2699_0_STEAM,
	VER_1_0_2699_0_NOSTEAM,

	VER_1_0_2699_16,

	VER_1_0_2802_0,
	
	VER_1_0_2824_0,

	VER_1_0_2845_0,

	VER_1_0_2944_0,

	VER_1_0_3028_0,
	
	VER_1_0_3095_0,

	VER_1_0_3258_0,

	VER_SIZE,
	VER_UNK = -1
};

///extern eGameVersion(*getGameVersion)();
__declspec(dllimport) eGameVersion getGameVersion();
