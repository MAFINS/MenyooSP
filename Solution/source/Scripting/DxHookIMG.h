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

typedef unsigned char UINT8;

class Vector2;
class RGBA;

namespace DxHookIMG
{
	class DxTexture
	{
	private:
		//std::string name;
		int id;
		//UINT8 instanceIndex;

		static int globalDrawOrder;
	public:
		bool operator == (const DxTexture& right) const;
		DxTexture& operator = (const DxTexture& right);

		/// <summary>
		/// Initializes a new instance of the <see cref="DxTexture"/> class
		/// </summary>
		DxTexture();
		/// <summary>
		/// Initializes a new instance of the <see cref="DxTexture"/> class. Ctor can only be used in a thread that uses natives.
		/// </summary>
		/// <param name="iD">ID of texture loaded by createTexture (ScriptHookV)</param>
		DxTexture(int iD);
		/// <summary>
		/// Initializes a new instance of the <see cref="DxTexture"/> class. Ctor can only be used in a thread that uses natives.
		/// </summary>
		/// <param name="file">File to load.</param>
		DxTexture(const std::string& file);
		/// <summary>
		/// Loads a texture file and stores its ID.
		/// </summary>
		/// <param name="file">File to load.</param>
		void Load(const std::string& file);
		/// <summary>
		/// Returns whether or not ID is non-zero
		/// </summary>
		bool Exists();
		/// <summary>
		/// Gets the current draw level.
		/// </summary>
		/// <return>Reference to current draw level variable.</param>
		static int& GlobalDrawOrderRef();
		/// <summary>
		/// Gets this instance's ID.
		/// </summary>
		/// <return>Reference to this instance's ID.</param>
		int& ID();

		void Draw(UINT8 index, const Vector2& position, const Vector2& size, float rotationOutOf360, const RGBA& colour);
		void DrawAdvanced(UINT8 index, int level, int time, const Vector2& centrePos, const Vector2& position, const Vector2& size, float rotationOutOf360, const RGBA& colour);
	};

	//extern DxTexture titleui_spooner;
	extern DxTexture teleToWpBoxIconKeyboard;
	extern DxTexture teleToWpBoxIconGamepad;
	void LoadAllMenyooTexturesInit();
}





