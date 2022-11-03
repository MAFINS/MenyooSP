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

#include <stdlib.h> //rand()

typedef int BOOL, INT;
typedef unsigned long DWORD;
typedef unsigned __int8 UINT8, BYTE;
typedef unsigned __int32 UINT32;
typedef char *PCHAR;

typedef DWORD Void;
typedef DWORD uint;
typedef DWORD Hash;
typedef int Any;
typedef int ScrHandle;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int ColourIndex;
typedef int Sphere;

// Colour types  - RGB.h/cpp
class RGBA
{
public:
	int R, G, B, A;
	RGBA() : R(0), G(0), B(0), A(0)
	{
	}
	RGBA(int r, int g, int b, int a) : R(r), G(g), B(b), A(a)
	{
	}
	RGBA(const RGBA& imp, int a) : R(imp.R), G(imp.G), B(imp.B), A(a)
	{
	}
	RGBA Inverse(bool inverseAlpha)
	{
		return RGBA(255 - R, 255 - G, 255 - B, inverseAlpha ? 255 - A : A);
	}

	void operator = (const RGBA& right)
	{
		this->R = right.R;
		this->G = right.G;
		this->B = right.B;
		this->A = right.A;
	}
	friend bool operator == (const RGBA& left, const RGBA& right)
	{
		return (left.R == right.R && left.G == right.G && left.B == right.B && left.A == right.A);
	}

	UINT32 ToArgb() const
	{
		return ((this->A & 0xFF) << 24) + ((this->R & 0xFF) << 16) + ((this->G & 0xFF) << 8) + (this->A & 0xFF);
	}
	static RGBA FromArgb(UINT32 value)
	{
		RGBA val;
		val.A = (value & 0xFF000000) >> 24;
		val.R = (value & 0x00FF0000) >> 16;
		val.G = (value & 0x0000FF00) >> 8;
		val.B = (value & 0x000000FF);
		return val;
	}
	static RGBA AllWhite()
	{
		return RGBA(255, 255, 255, 255);
	}
};
class RgbS
{
public:
	__int16 R, G, B;
	RgbS() : R(0i16), G(0i16), B(0i16)
	{
	}
	RgbS(__int16 r, __int16 g, __int16 b) : R(r), G(g), B(b)
	{
	}
	RgbS(const RGBA& rgba) : R(rgba.R), G(rgba.G), B(rgba.B)
	{
	}
	RgbS Inverse()
	{
		return RgbS(255 - R, 255 - G, 255 - B);
	}
	static RgbS Random()
	{
		return RgbS (rand() % (int)256, (rand() % (int)256), (rand() % (int)256));
	}

	RGBA ToRGBA(__int16 alpha = 255)
	{
		return RGBA(this->R, this->G, this->B, alpha);
	}

	void operator = (const RgbS& right)
	{
		this->R = right.R;
		this->G = right.G;
		this->B = right.B;
	}
	friend bool operator == (const RgbS& left, const RgbS& right)
	{
		return (left.R == right.R && left.G == right.G && left.B == right.B);
	}
};


