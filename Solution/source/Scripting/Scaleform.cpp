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
#include "Scaleform.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\types.h"
#include "..\Natives\natives2.h"

#include <string>

Scaleform::Scaleform()
{
}
Scaleform::Scaleform(const Scaleform& obj)
	: mHandle(obj.mHandle)
{
}
Scaleform::Scaleform(int handle)
	: mHandle(handle)
{
}

int& Scaleform::Handle()
{
	return this->mHandle;
}

int Scaleform::GetHandle() const
{
	return this->mHandle;
}

bool Scaleform::HasLoaded() const
{
	return HAS_SCALEFORM_MOVIE_LOADED(this->mHandle) != 0;
}

bool Scaleform::Load(const std::string& scaleformID)
{
	//this->mScaleformID = scaleformID;

	if (!HAS_SCALEFORM_MOVIE_LOADED(this->mHandle))
	{
		this->mHandle = REQUEST_SCALEFORM_MOVIE(const_cast<PCHAR>(scaleformID.c_str()));
		if (HAS_SCALEFORM_MOVIE_LOADED(this->mHandle))
			return true;
		return false;
	}

	return true;
}

void Scaleform::Unload()
{
	auto& handle = this->mHandle;
	if (HAS_SCALEFORM_MOVIE_LOADED(handle))
		SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&handle);
}

void Scaleform::PushFunction(const std::string& function)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION(this->mHandle, const_cast<PCHAR>(function.c_str()));
}
void Scaleform::PushInteger(int arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg);
}
void Scaleform::PushBoolean(bool arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(arg);
}
void Scaleform::PushFloat(float arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(arg);
}
void Scaleform::PushString(const std::string& arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(const_cast<PCHAR>(arg.c_str()));
}
void Scaleform::PushString2(const std::string& arg)
{
	_0xE83A3E3557A56640(const_cast<PCHAR>(arg.c_str()));
}
void Scaleform::PushTextComponent(const std::string& arg)
{
	PCHAR text = const_cast<PCHAR>(arg.c_str());
	if (DOES_TEXT_LABEL_EXIST(text))
	{
		_BEGIN_TEXT_COMPONENT(text);
	}
	else
	{
		_BEGIN_TEXT_COMPONENT("STRING");
		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	}
	//ADD_TEXT_COMPONENT_INTEGER(-1);
	_END_TEXT_COMPONENT();
}
void Scaleform::PushRGBA(const RGBA& arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.R);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.G);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.B);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.A);
}
void Scaleform::PushRGB(const RgbS& arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.R);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.G);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(arg.B);
}
void Scaleform::PushVector2(const Vector2& arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(arg.x);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(arg.y);
}
void Scaleform::PushVector3(const Vector3& arg)
{
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(arg.x);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(arg.y);
	_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(arg.z);
}

void Scaleform::PopFunction()
{
	_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
}


void Scaleform::Render2D(RGBA colour)
{
	DRAW_SCALEFORM_MOVIE_FULLSCREEN(this->mHandle, colour.R, colour.G, colour.B, colour.A, 0);
}
void Scaleform::Render2DScreenSpace(const Vector2& location, const Vector2& size, RGBA colour)
{
	DRAW_SCALEFORM_MOVIE(this->mHandle, location.x, location.y, size.x, size.y, colour.R, colour.G, colour.B, colour.A, 0);
}
void Scaleform::Render3D(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale)
{
	_DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE(this->mHandle, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, unk.x, unk.y, unk.z, scale.x, scale.y, scale.z, 2);
}
void Scaleform::Render3DAdditive(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale)
{
	DRAW_SCALEFORM_MOVIE_3D(this->mHandle, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, unk.x, unk.y, unk.z, scale.x, scale.y, scale.z, 2);
}



