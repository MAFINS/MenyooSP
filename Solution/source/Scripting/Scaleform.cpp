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
	BEGIN_SCALEFORM_MOVIE_METHOD(this->mHandle, const_cast<PCHAR>(function.c_str()));
}
void Scaleform::PushInteger(int arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg);
}
void Scaleform::PushBoolean(bool arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(arg);
}
void Scaleform::PushFloat(float arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg);
}
void Scaleform::PushString(const std::string& arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(const_cast<PCHAR>(arg.c_str()));
}
void Scaleform::PushString2(const std::string& arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(const_cast<PCHAR>(arg.c_str()));
}
void Scaleform::PushTextComponent(const std::string& arg)
{
	PCHAR text = const_cast<PCHAR>(arg.c_str());
	if (DOES_TEXT_LABEL_EXIST(text))
	{
		BEGIN_TEXT_COMMAND_SCALEFORM_STRING(text);
	}
	else
	{
		BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
		ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	}
	//ADD_TEXT_COMPONENT_INTEGER(-1);
	END_TEXT_COMMAND_SCALEFORM_STRING();
}
void Scaleform::PushRGBA(const RGBA& arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.R);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.G);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.B);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.A);
}
void Scaleform::PushRGB(const RgbS& arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.R);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.G);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.B);
}
void Scaleform::PushVector2(const Vector2& arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.x);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.y);
}
void Scaleform::PushVector3(const Vector3& arg)
{
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.x);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.y);
	SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.z);
}

void Scaleform::PopFunction()
{
	END_SCALEFORM_MOVIE_METHOD();
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
	DRAW_SCALEFORM_MOVIE_3D_SOLID(this->mHandle, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, unk.x, unk.y, unk.z, scale.x, scale.y, scale.z, 2);
}
void Scaleform::Render3DAdditive(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale)
{
	DRAW_SCALEFORM_MOVIE_3D(this->mHandle, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, unk.x, unk.y, unk.z, scale.x, scale.y, scale.z, 2);
}



