/*
* Copyright (C) 2015 crosire
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#pragma once

#include "..\Natives\types.h" // RGBA, RgbS

#include <string>

class Vector3;
class Vector2;

struct Scaleform_IbT { int button; std::string text; bool isKey; };
class Scaleform final
{
public:

	Scaleform();
	Scaleform(const Scaleform& obj);
	Scaleform(int handle);

	int& Handle();

	int GetHandle() const;

	bool HasLoaded() const;

	bool Load(const std::string& scaleformID);
	
	void Unload();

	void PushFunction(const std::string& function);
	void PushInteger(int arg);
	void PushBoolean(bool arg);
	void PushFloat(float arg);
	void PushString(const std::string& arg);
	void PushString2(const std::string& arg);
	void PushTextComponent(const std::string& arg);
	void PushRGBA(const RGBA& arg);
	void PushRGB(const RgbS& arg);
	void PushVector2(const Vector2& arg);
	void PushVector3(const Vector3& arg);
	
	void PopFunction();


	void Render2D(RGBA colour = { 255, 255, 255, 255 });
	void Render2DScreenSpace(const Vector2& location, const Vector2& size, RGBA colour = { 255, 255, 255, 255 });
	void Render3D(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale);
	void Render3DAdditive(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale);

private:
	int mHandle;
};

