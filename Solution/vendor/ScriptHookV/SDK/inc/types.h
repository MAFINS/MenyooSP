#pragma once

#include <windows.h>

typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
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
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

#define PI 3.141592653589793238462643383279502884L

struct Vector2
{
	float x, y;

	Vector2()
		: x(0.f)
		, y(0.f)
	{ }

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{ }
};

struct Vector3
{
public:
	alignas(8) float x;
	alignas(8) float y;
	alignas(8) float z;

public:
	Vector3()
		: x(0.f)
		, y(0.f)
		, z(0.f)
	{ }

	Vector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{ }

	Vector3(float arr[3]) 
		: x(arr[0])
		, y(arr[1])
		, z(arr[2])
	{ }
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4()
		: x(0.f)
		, y(0.f)
		, z(0.f)
		, w(0.f)
	{ }

	Vector4(float x, float y, float z, float w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{ }
};