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
#include "GTAmemory.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\main.h"
#include "..\Natives\natives2.h"
#include "..\Util\FileLogger.h"
#include "..\Menu\Menu.h"

#include <Windows.h>
#include <Psapi.h>

#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <utility>

HMODULE g_MainModule = 0;
MODULEINFO g_MainModuleInfo = { 0 };

ScriptTable* scriptTable;
ScriptHeader* shopController;

template<typename R> R GetMultilayerPointer(void* base, const std::vector<DWORD>& offsets)
{
	DWORD64 addr = (UINT64)base;
	if (!addr)
		return NULL;
	auto numOffsets = offsets.size();

	for (auto i = 0; i < numOffsets - 1; i++)
	{
		addr = *(UINT64*)(addr + offsets[i]);
		if (!addr)
			return NULL;
	}
	addr += offsets[numOffsets - 1];
	return (R)addr;
}

namespace MemryScan
{
	PatternByte::PatternByte() : ignore(true)
	{
	}

	PatternByte::PatternByte(std::string byteString, bool ignoreThis)
	{
		data = StringToUint8(byteString);
		ignore = ignoreThis;
	}

	UINT8 PatternByte::StringToUint8(std::string str)
	{
		std::istringstream iss(str);

		UINT32 ret;

		if (iss >> std::hex >> ret)
		{
			return (UINT8)ret;
		}

		return 0;
	}

	DWORD64 Pattern::Scan(DWORD64 dwStart, DWORD64 dwLength, const std::string& s)
	{
		std::vector<PatternByte> p;
		std::istringstream iss(s);
		std::string w;

		while (iss >> w)
		{
			if (w.data()[0] == '?') // Wildcard
			{
				p.push_back(PatternByte());
			}
			else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) // Hex
			{
				p.push_back(PatternByte(w));
			}
			else
			{
				return NULL; // Bad
			}
		}

		for (DWORD64 i = 0; i < dwLength; i++)
		{
			UINT8* lpCurrentByte = (UINT8*)(dwStart + i);

			bool found = true;

			for (size_t ps = 0; ps < p.size(); ps++)
			{
				if (p[ps].ignore == false && lpCurrentByte[ps] != p[ps].data)
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				return (DWORD64)lpCurrentByte;
			}
		}

		return NULL;
	}
	DWORD64 Pattern::Scan(MODULEINFO mi, const std::string& s)
	{
		return Scan((DWORD64)mi.lpBaseOfDll, (DWORD64)mi.SizeOfImage, s);
	}

	bool PatternScanner::CompareMemory(const BYTE *data, const BYTE *pattern, const char *mask)
	{
		for (; *mask; ++mask, ++data, ++pattern)
		{
			if (*mask == 'x' && *data != *pattern)
			{
				return false;
			}
		}
		return (*mask) == NULL;
	}

	DWORD64 PatternScanner::FindPattern(std::vector<unsigned short> pattern)
	{
		DWORD64 i;
		DWORD64 size;
		DWORD64 address;

		MODULEINFO info = g_MainModuleInfo;
		size = (DWORD64)info.SizeOfImage;

		std::vector<unsigned char> search;
		std::vector<char> mask;

		for (auto elem : pattern)
		{
			if (elem != 0xFFFF)
			{
				search.push_back((unsigned char)elem);
				mask.push_back('x');
			}
			else
			{
				search.push_back(0);
				mask.push_back('?');
			}
		}

		for (i = 0; i < size; ++i)
		{
			if (CompareMemory((BYTE *)(address + i), (BYTE *)search.data(), mask.data()))
			{
				return (DWORD64)(address + i);
			}
		}
		return 0;
	}
	DWORD64 PatternScanner::FindPattern(const char* bMaskc, const char* sMaskc)
	{
		// Game Base & Size
		static DWORD64 pGameBase = (DWORD64)g_MainModule;
		static uint32_t pGameSize = 0;
		if (!pGameSize)
		{
			MODULEINFO info = g_MainModuleInfo;
			pGameSize = info.SizeOfImage;
		}

		// Scan
		for (uint32_t i = 0; i < pGameSize; i++)
		{
			if (CompareMemory((uint8_t*)(pGameBase + i), (uint8_t*)bMaskc, sMaskc))
			{
				return pGameBase + i;
			}
		}
		return 0;
	}
	DWORD64 PatternScanner::FindPattern(const char* pattern, const char* mask, DWORD64 startAddress, size_t size)
	{
		const char* currAddress = (const char*)startAddress;
		const char* endAddress = (const char*)(startAddress + size);
		const uint32_t mask_length = static_cast<uint32_t>(strlen(mask) - 1);

		for (uint32_t i = 0; currAddress < endAddress; currAddress++)
		{
			if (*currAddress == pattern[i] || mask[i] == '?')
			{
				if (mask[i + 1] == '\0')
				{
					return reinterpret_cast<DWORD64>(currAddress) - mask_length;
				}
				i++;
			}
			else
			{
				i = 0;
			}
		}
		return 0;
	}
	DWORD64 PatternScanner::FindPattern(const std::string& patternString)
	{
		return MemryScan::Pattern::Scan((DWORD64)g_MainModuleInfo.lpBaseOfDll, (DWORD64)g_MainModuleInfo.SizeOfImage, patternString);
	}
	DWORD64 PatternScanner::FindPattern(MODULEINFO moduleInfo, const std::string& patternString)
	{
		return MemryScan::Pattern::Scan((DWORD64)moduleInfo.lpBaseOfDll, (DWORD64)moduleInfo.SizeOfImage, patternString);
	}
}

//--------------------------------GTAmemory------------------------------------------------------

const UINT16 GTAmemory::poolCount_vehicles = 1024;
const UINT16 GTAmemory::poolCount_peds = 1024;
const UINT16 GTAmemory::poolCount_objects = 1024;

BlipList* GTAmemory::_blipList;
BlipList* GTAmemory::GetBlipList()
{
	return GTAmemory::_blipList;
}

UINT64 GTAmemory::modelHashTable, GTAmemory::modelNum2, GTAmemory::modelNum3, GTAmemory::modelNum4;
int GTAmemory::modelNum1;
unsigned short GTAmemory::modelHashEntries;
std::array<std::vector<unsigned int>, 0x20> GTAmemory::vehicleModels;

unsigned int(*GTAmemory::_getHashKey)(const char* stringPtr, unsigned int initialHash);
UINT64(*GTAmemory::_entityAddressFunc)(int handle);
UINT64(*GTAmemory::_playerAddressFunc)(int handle);
UINT64(*GTAmemory::_ptfxAddressFunc)(int handle);
int(*GTAmemory::_addEntityToPoolFunc)(UINT64 address);
UINT64(*GTAmemory::_entityPositionFunc)(UINT64 address, float *position);
UINT64(*GTAmemory::_entityModel1Func)(UINT64 address), (*GTAmemory::_entityModel2Func)(UINT64 address);
UINT64 *GTAmemory::_entityPoolAddress, *GTAmemory::_vehiclePoolAddress, *GTAmemory::_pedPoolAddress, *GTAmemory::_objectPoolAddress, *GTAmemory::_cameraPoolAddress, *GTAmemory::_pickupObjectPoolAddress;
unsigned char(*GTAmemory::SetNmBoolAddress)(__int64, __int64, unsigned char);
unsigned char(*GTAmemory::SetNmIntAddress)(__int64, __int64, int);
unsigned char(*GTAmemory::SetNmFloatAddress)(__int64, __int64, float);
unsigned char(*GTAmemory::SetNmVec3Address)(__int64, __int64, float, float, float);
unsigned char(*GTAmemory::SetNmStringAddress)(__int64, __int64, __int64);
UINT64 GTAmemory::CreateNmMessageFunc, GTAmemory::GiveNmMessageFunc;
UINT64(*GTAmemory::CheckpointBaseAddr)();
UINT64(*GTAmemory::CheckpointHandleAddr)(UINT64 baseAddr, int Handle);
UINT64 *GTAmemory::checkpointPoolAddress;
float *GTAmemory::_readWorldGravityAddress, *GTAmemory::_writeWorldGravityAddress;
UINT64 *GTAmemory::_gamePlayCameraAddr;
int*GTAmemory:: _cursorSpriteAddr;
INT32* GTAmemory::_transitionStatus = nullptr;

UINT64 GTAmemory::_gxtLabelFromHashAddr1;
char*(__fastcall *GTAmemory::_gxtLabelFromHashFuncAddr)(UINT64 address, unsigned int hash);

/*struct EntityPoolTask
{
enum class Type
{
Ped,
Object,
Vehicle,
Entity,
PickupObject
};

EntityPoolTask(Type type) : _type(type), _posCheck(false), _modelCheck(false)
{
}

bool CheckEntity(uintptr_t address)
{
if (_posCheck)
{
float position[3];
GTAmemory::_entityPositionFunc(address, position);

if (Vector3::Subtract(_position, Vector3(position[0], position[1], position[2])).LengthSquared() > _radiusSquared)
{
return false;
}
}

if (_modelCheck)
{
UINT32 v0 = *reinterpret_cast<UINT32 *>(GTAmemory::_entityModel1Func(*reinterpret_cast<UINT64 *>(address + 32)));
UINT32 v1 = v0 & 0xFFFF;
UINT32 v2 = ((v1 ^ v0) & 0x0FFF0000 ^ v1) & 0xDFFFFFFF;
UINT32 v3 = ((v2 ^ v0) & 0x10000000 ^ v2) & 0x3FFFFFFF;
const uintptr_t v5 = GTAmemory::_entityModel2Func(reinterpret_cast<uintptr_t>(&v3));

if (!v5)
{
return false;
}
for (DWORD hash : _modelHashes)
{
if (*reinterpret_cast<int *>(v5 + 24) == hash)
{
return true;
}
}
return false;
}

return true;
}

void Run(std::vector<int>& _handles)
{
const uintptr_t EntityPool = *GTAmemory::_entityPoolAddress;
const uintptr_t VehiclePool = *GTAmemory::_vehiclePoolAddress;
const uintptr_t PedPool = *GTAmemory::_pedPoolAddress;
const uintptr_t ObjectPool = *GTAmemory::_objectPoolAddress;

if (EntityPool == 0 || VehiclePool == 0 || PedPool == 0 || ObjectPool == 0)
{
return;
}

switch (_type)
{
case Type::Entity:
case Type::Vehicle:
{
const uintptr_t VehiclePoolInfo = *reinterpret_cast<UINT64 *>(VehiclePool);
for (unsigned int i = 0; i < *reinterpret_cast<UINT32 *>(VehiclePoolInfo + 8); i++)
{
if (*reinterpret_cast<UINT32 *>(EntityPool + 16) - (*reinterpret_cast<UINT32 *>(EntityPool + 32) & 0x3FFFFFFF) <= 256)
{
break;
}

if ((*reinterpret_cast<UINT32 *>(*reinterpret_cast<UINT64 *>(VehiclePoolInfo + 48) + 4 * (static_cast<UINT64>(i) >> 5)) >> (i & 0x1F)) & 1)
{
const uintptr_t address = *reinterpret_cast<UINT64 *>(i * 8 + *reinterpret_cast<UINT64 *>(VehiclePoolInfo));

if (address && CheckEntity(address))
{
_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
}
}
}
if (_type != Type::Entity)
{
break;
}
}
case Type::Ped:
{
for (unsigned int i = 0; i < *reinterpret_cast<UINT32 *>(PedPool + 16); i++)
{
if (*reinterpret_cast<UINT32 *>(EntityPool + 16) - (*reinterpret_cast<UINT32 *>(EntityPool + 32) & 0x3FFFFFFF) <= 256)
{
break;
}

if (~(*reinterpret_cast<UINT8 *>(*reinterpret_cast<UINT64 *>(PedPool + 8) + i) >> 7) & 1)
{
const uintptr_t address = *reinterpret_cast<UINT64 *>(PedPool) + i * *reinterpret_cast<UINT32 *>(PedPool + 20);

if (address && CheckEntity(address))
{
_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
}
}
}
if (_type != Type::Entity)
{
break;
}
}
case Type::Object:
{
for (unsigned int i = 0; i < *reinterpret_cast<UINT32 *>(ObjectPool + 16); i++)
{
if (*reinterpret_cast<UINT32 *>(EntityPool + 16) - (*reinterpret_cast<UINT32 *>(EntityPool + 32) & 0x3FFFFFFF) <= 256)
{
break;
}

if (~(*reinterpret_cast<UINT8 *>(*reinterpret_cast<UINT64 *>(ObjectPool + 8) + i) >> 7) & 1)
{
const uintptr_t address = *reinterpret_cast<UINT64 *>(ObjectPool) + i * *reinterpret_cast<UINT32 *>(ObjectPool + 20);

if (address && CheckEntity(address))
{
_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
}
}
}
break;
}
case Type::PickupObject:
{
if (*GTAmemory::_pickupObjectPoolAddress)
{
GenericPool* pickupPool = reinterpret_cast<GenericPool*>(*GTAmemory::_pickupObjectPoolAddress);

for (UINT32 i = 0; i < pickupPool->size; i++)
{
//if (entityPool->Full()) { break; }
if (pickupPool->isValid(i))
{
UINT64 address = pickupPool->getAddress(i);
if (address)
{
if (_posCheck)
{
float* position = (float*)(address + 0x90);
if (Vector3::Subtract(_position, Vector3(position[0], position[1], position[2])).LengthSquared() > _radiusSquared)
{
continue;
}
}
_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
}
}
}
}
}
}
}

EntityPoolTask::Type _type;
//std::vector<int> _handles;
bool _posCheck, _modelCheck;
Vector3 _position;
float _radiusSquared;
std::vector<DWORD> _modelHashes;
};*/

class EntityPool
{
public:
	char _padding0[16];
	UINT32 num1;
	char _padding1[12];
	UINT32 num2;

	inline bool Full()
	{
		return num1 - (num2 & 0x3FFFFFFF) <= 256;
	}
};
class VehiclePool
{
public:
	//char _padding0[0];
	UINT64 *poolAddress;
	//char _padding1[0];
	UINT32 size;
	char _padding2[36];
	UINT32* bitArray;
	char _padding3[40];
	UINT32 itemCount;

	inline bool isValid(UINT32 i)
	{
		return (bitArray[i >> 5] >> (i & 0x1F)) & 1;
	}

	inline UINT64 getAddress(UINT32 i)
	{
		return poolAddress[i];
	}
};
class GenericPool {
public:
	//char _padding0[0];
	UINT64 poolStartAddress;
	//char _padding1[0];
	BYTE* byteArray;
	//char _padding2[0];
	UINT32 size;
	//char _padding2[0];
	UINT32 itemSize;


	inline bool isValid(UINT32 i)
	{
		return mask(i) != 0;
	}

	inline UINT64 getAddress(UINT32 i)
	{
		return mask(i) & (poolStartAddress + i * itemSize);
	}
private:
	inline long long mask(UINT32 i)
	{
		long long num1 = byteArray[i] & 0x80;
		return ~((num1 | -num1) >> 63);
	}
};
struct EntityPoolTask
{
	enum Type : UINT16
	{
		Vehicle = 1,
		Ped = 2,
		Prop = 4,
		PickupObject = 8
	};
	inline bool TypeHasFlag(UINT16 flag)
	{
		return (_type & flag) != 0;
	}

	EntityPoolTask(UINT16 type) : _type(type), _posCheck(false), _modelCheck(false)
	{
	}

	inline bool CheckEntity(uintptr_t address)
	{
		if (_posCheck)
		{
			float position[3];
			GTAmemory::_entityPositionFunc(address, position);

			if (Vector3::Subtract(_position, Vector3(position[0], position[1], position[2])).LengthSquared() > _radiusSquared)
			{
				return false;
			}
		}

		if (_modelCheck)
		{
			UINT32 v0 = *reinterpret_cast<UINT32 *>(GTAmemory::_entityModel1Func(*reinterpret_cast<UINT64 *>(address + 32)));
			UINT32 v1 = v0 & 0xFFFF;
			UINT32 v2 = ((v1 ^ v0) & 0x0FFF0000 ^ v1) & 0xDFFFFFFF;
			UINT32 v3 = ((v2 ^ v0) & 0x10000000 ^ v2) & 0x3FFFFFFF;
			const uintptr_t v5 = GTAmemory::_entityModel2Func(reinterpret_cast<uintptr_t>(&v3));


			if (!v5)
			{
				return false;
			}
			for (int hash : _modelHashes)
			{
				if (*reinterpret_cast<int *>(v5 + 24) == hash)
				{
					return true;
				}
			}
			return false;
		}

		return true;
	}

	void Run(std::vector<int>& _handles)
	{
		if (*GTAmemory::_entityPoolAddress == 0)
		{
			return;
		}
		EntityPool* entityPool = reinterpret_cast<EntityPool*>(*GTAmemory::_entityPoolAddress);

		if (TypeHasFlag(Type::Vehicle))
		{
			if (*GTAmemory::_vehiclePoolAddress)
			{
				VehiclePool* vehiclePool = *reinterpret_cast<VehiclePool**>(*GTAmemory::_vehiclePoolAddress);

				for (UINT32 i = 0; i < vehiclePool->size; i++)
				{
					//if (entityPool->Full()) break;
					if (vehiclePool->isValid(i))
					{
						UINT64 address = vehiclePool->getAddress(i);
						if (address && CheckEntity(address))
						{
							_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
						}
					}
				}
			}
		}
		if (TypeHasFlag(Type::Ped))
		{
			if (*GTAmemory::_pedPoolAddress)
			{
				GenericPool* pedPool = reinterpret_cast<GenericPool*>(*GTAmemory::_pedPoolAddress);

				for (UINT32 i = 0; i < pedPool->size; i++)
				{
					//if (entityPool->Full()) break;
					if (pedPool->isValid(i))
					{
						UINT64 address = pedPool->getAddress(i);
						if (address && CheckEntity(address))
						{
							_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
						}
					}
				}
			}
		}
		if (TypeHasFlag(Type::Prop))
		{
			if (*GTAmemory::_objectPoolAddress)
			{
				GenericPool* propPool = reinterpret_cast<GenericPool*>(*GTAmemory::_objectPoolAddress);

				for (UINT32 i = 0; i < propPool->size; i++)
				{
					//if (entityPool->Full()) break;
					if (propPool->isValid(i))
					{
						UINT64 address = propPool->getAddress(i);
						if (address && CheckEntity(address))
						{
							_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
						}
					}
				}
			}
		}
		if (TypeHasFlag(Type::PickupObject))
		{
			if (*GTAmemory::_pickupObjectPoolAddress)
			{
				GenericPool* pickupPool = reinterpret_cast<GenericPool*>(*GTAmemory::_pickupObjectPoolAddress);

				for (UINT32 i = 0; i < pickupPool->size; i++)
				{
					//if (entityPool->Full()) break;
					if (pickupPool->isValid(i))
					{
						UINT64 address = pickupPool->getAddress(i);
						if (address)
						{
							if (_posCheck)
							{
								float* position = (float*)(address + 0x90);
								if (Vector3::Subtract(_position, Vector3(position[0], position[1], position[2])).LengthSquared() > _radiusSquared)
								{
									continue;
								}
							}
							_handles.push_back(GTAmemory::_addEntityToPoolFunc(address));
						}
					}
				}
			}
		}

	}

	UINT16 _type;
	//std::vector<int> _handles;
	bool _posCheck, _modelCheck;
	Vector3 _position;
	float _radiusSquared;
	std::vector<DWORD> _modelHashes;
};
struct GenericTask
{
public:
	typedef UINT64(*func)(UINT64);
	GenericTask(func pFunc, UINT64 Arg) : _toRun(pFunc), _arg(Arg)
	{
	}
	virtual void Run()
	{
		_res = _toRun(_arg);
	}

	UINT64 GetResult()
	{
		return _res;
	}

private:
	func _toRun;
	UINT64 _arg;
	UINT64 _res;
};

void GTAmemory::Init()
{
	UINT64 address;

	// Get relative address and add it to the instruction address.
	// 3 bytes equal the size of the opcode and its first argument. 7 bytes are the length of opcode and all its parameters.

	address = FindPattern("\x4C\x8D\x05\x00\x00\x00\x00\x0F\xB7\xC1", "xxx????xxx");
	if (address) _blipList = reinterpret_cast<BlipList*>(*reinterpret_cast<int *>(address + 3) + address + 7);

	address = FindPattern("\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x18\x89\x54\x24\x10\x56\x57\x41\x56\x48\x83\xEC\x20", "xxxxxxxxxxxxxxxxxxxxxx");
	_gxtLabelFromHashFuncAddr = reinterpret_cast<char*(__fastcall *)(UINT64, unsigned int)>(address);
	address = FindPattern("\x84\xC0\x74\x34\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD3", "xxxxxxx????xxx");
	_gxtLabelFromHashAddr1 = *reinterpret_cast<int *>(address + 7) + address + 11;

	if (GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_1290_1_STEAM)
	{
		address = FindPattern("\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x2E\x48\x83\x3D", "x????xxxxxxxxxxx");
		_entityAddressFunc = reinterpret_cast<uintptr_t(*)(int)>(*reinterpret_cast<int *>(address + 1) + address + 5);
		address = FindPattern("\xB2\x01\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x1C\x8A\x88", "xxx????xxxxxxx");
		_playerAddressFunc = reinterpret_cast<uintptr_t(*)(int)>(*reinterpret_cast<int *>(address + 3) + address + 7);

		address = FindPattern("\x48\x8B\xDA\xE8\x00\x00\x00\x00\xF3\x0F\x10\x44\x24", "xxxx????xxxxx");
		_entityPositionFunc = reinterpret_cast<UINT64(*)(UINT64, float *)>(address - 6);
		address = FindPattern("\x0F\x85\x00\x00\x00\x00\x48\x8B\x4B\x20\xE8\x00\x00\x00\x00\x48\x8B\xC8", "xx????xxxxx????xxx");
		_entityModel1Func = reinterpret_cast<UINT64(*)(UINT64)>(*reinterpret_cast<int *>(address + 11) + address + 15);
		address = FindPattern("\x45\x33\xC9\x3B\x05", "xxxxx");
		_entityModel2Func = reinterpret_cast<UINT64(*)(UINT64)>(address - 0x46);

		address = FindPattern("\x4C\x8B\x05\x00\x00\x00\x00\x40\x8A\xF2\x8B\xE9", "xxx????xxxxx");
		_pickupObjectPoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 3) + address + 7);
	}
	else
	{
		address = FindPattern("\x33\xFF\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x58", "xxx????xxxxx");
		_entityAddressFunc = reinterpret_cast<UINT64(*)(int)>(*reinterpret_cast<int *>(address + 3) + address + 7);
		address = FindPattern("\xB2\x01\xE8\x00\x00\x00\x00\x33\xC9\x48\x85\xC0\x74\x3B", "xxx????xxxxxxx");
		_playerAddressFunc = reinterpret_cast<UINT64(*)(int)>(*reinterpret_cast<int *>(address + 3) + address + 7);

		address = FindPattern("\x48\x8B\xC8\xE8\x00\x00\x00\x00\xF3\x0F\x10\x54\x24\x00\xF3\x0F\x10\x4C\x24\x00\xF3\x0F\x10", "xxxx????xxxxx?xxxxx?xxx");
		_entityPositionFunc = reinterpret_cast<UINT64(*)(UINT64, float *)>(*reinterpret_cast<int *>(address + 4) + address + 8);
		address = FindPattern("\x25\xFF\xFF\xFF\x3F\x89\x44\x24\x38\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x03", "xxxxxxxxxx????xxxxx");
		_entityModel1Func = reinterpret_cast<UINT64(*)(UINT64)>(*reinterpret_cast<int *>(address - 61) + address - 57);
		_entityModel2Func = reinterpret_cast<UINT64(*)(UINT64)>(*reinterpret_cast<int *>(address + 10) + address + 14);

		address = FindPattern("\x8B\xF0\x48\x8B\x05\x00\x00\x00\x00\xF3\x0F\x59\xF6", "xxxxx????xxxx");
		_pickupObjectPoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 5) + address + 9);
	}

	address = FindPattern("\x74\x21\x48\x8B\x48\x20\x48\x85\xC9\x74\x18\x48\x8B\xD6\xE8", "xxxxxxxxxxxxxxx") - 10;
	_ptfxAddressFunc = reinterpret_cast<UINT64(*)(int)>(*reinterpret_cast<int*>(address) + address + 4);

	address = FindPattern("\x48\xF7\xF9\x49\x8B\x48\x08\x48\x63\xD0\xC1\xE0\x08\x0F\xB6\x1C\x11\x03\xD8", "xxxxxxxxxxxxxxxxxxx");
	_addEntityToPoolFunc = reinterpret_cast<int(*)(UINT64)>(address - 0x68);

	address = FindPattern("\x4C\x8B\x0D\x00\x00\x00\x00\x44\x8B\xC1\x49\x8B\x41\x08", "xxx????xxxxxxx");
	_entityPoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 3) + address + 7);
	address = FindPattern("\x48\x8B\x05\x00\x00\x00\x00\xF3\x0F\x59\xF6\x48\x8B\x08", "xxx????xxxxxxx");
	_vehiclePoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 3) + address + 7);
	address = FindPattern("\x48\x8B\x05\x00\x00\x00\x00\x41\x0F\xBF\xC8\x0F\xBF\x40\x10", "xxx????xxxxxxxx");
	_pedPoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 3) + address + 7);
	address = FindPattern("\x48\x8B\x05\x00\x00\x00\x00\x8B\x78\x10\x85\xFF", "xxx????xxxxx");
	_objectPoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 3) + address + 7);

	CreateNmMessageFunc = FindPattern("\x33\xDB\x48\x89\x1D\x00\x00\x00\x00\x85\xFF", "xxxxx????xx") - 0x42;
	GiveNmMessageFunc = FindPattern("\x0F\x84\x00\x00\x00\x00\x48\x8B\x01\xFF\x90\x00\x00\x00\x00\x41\x3B\xC5", "xx????xxxxx????xxx") - 0x78;
	address = FindPattern("\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x63\x49\x0C\x41\x8A\xF8", "xxxx?xxxxxxxxxxxxxxx");
	SetNmBoolAddress = reinterpret_cast<unsigned char(*)(__int64, __int64, unsigned char)>(address);
	address = FindPattern("\x40\x53\x48\x83\xEC\x30\x48\x8B\xD9\x48\x63\x49\x0C", "xxxxxxxxxxxxx");
	SetNmFloatAddress = reinterpret_cast<unsigned char(*)(__int64, __int64, float)>(address);
	address = FindPattern("\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x63\x49\x0C\x41\x8B\xF8", "xxxx?xxxxxxxxxxxxxxx");
	SetNmIntAddress = reinterpret_cast<unsigned char(*)(__int64, __int64, int)>(address);
	address = FindPattern("\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x63\x49\x0C\x49\x8B\xE8", "xxxxxxxxxxxxxxx") - 15;
	SetNmStringAddress = reinterpret_cast<unsigned char(*)(__int64, __int64, __int64)>(address);
	address = FindPattern("\x40\x53\x48\x83\xEC\x40\x48\x8B\xD9\x48\x63\x49\x0C", "xxxxxxxxxxxxx");
	SetNmVec3Address = reinterpret_cast<unsigned char(*)(__int64, __int64, float, float, float)>(address);

	address = FindPattern("\x8A\x4C\x24\x60\x8B\x50\x10\x44\x8A\xCE", "xxxxxxxxxx");
	CheckpointBaseAddr = reinterpret_cast<UINT64(*)()>(*reinterpret_cast<int*>(address - 19) + address - 15);
	CheckpointHandleAddr = reinterpret_cast<UINT64(*)(UINT64, int)>(*reinterpret_cast<int*>(address - 9) + address - 5);
	checkpointPoolAddress = reinterpret_cast<UINT64 *>(*reinterpret_cast<int *>(address + 17) + address + 21);

	address = FindPattern("\x48\x8B\x0B\x33\xD2\xE8\x00\x00\x00\x00\x89\x03", "xxxxxx????xx");
	_getHashKey = reinterpret_cast<unsigned int(*)(const char*, unsigned int)>(*reinterpret_cast<int*>(address + 6) + address + 10);

	address = FindPattern("\x48\x63\xC1\x48\x8D\x0D\x00\x00\x00\x00\xF3\x0F\x10\x04\x81\xF3\x0F\x11\x05\x00\x00\x00\x00", "xxxxxx????xxxxxxxxx????");
	_writeWorldGravityAddress = reinterpret_cast<float *>(*reinterpret_cast<int *>(address + 6) + address + 10);
	_readWorldGravityAddress = reinterpret_cast<float *>(*reinterpret_cast<int *>(address + 19) + address + 23);

	address = FindPattern("\x74\x11\x8B\xD1\x48\x8D\x0D\x00\x00\x00\x00\x45\x33\xC0", "xxxxxxx????xxx");
	_cursorSpriteAddr = reinterpret_cast<int *>(*reinterpret_cast<int*>(address - 4) + address);

	address = FindPattern("\x48\x8B\xC7\xF3\x0F\x10\x0D", "xxxxxxx") - 0x1D;
	address = address + *reinterpret_cast<int*>(address) + 4;
	_gamePlayCameraAddr = reinterpret_cast<UINT64*>(*reinterpret_cast<int*>(address + 3) + address + 7);
	address = FindPattern("\x48\x8B\xC8\xEB\x02\x33\xC9\x48\x85\xC9\x74\x26", "xxxxxxxxxxxx") - 9;
	_cameraPoolAddress = reinterpret_cast<UINT64*>(*reinterpret_cast<int*>(address) + address + 4);

	GenerateVehicleModelList();

	// Bypass model requests block
	address = MemryScan::PatternScanner::FindPattern("48 85 C0 0F 84 ? ? ? ? 8B 48 50");
	if (address) memset(reinterpret_cast<void*>(address), 0x90, 24);

	// Bypass is player model allowed to spawn checks
	address = MemryScan::PatternScanner::FindPattern("48 8B C8 FF 52 30 84 C0 74 05 48");
	if (address) memset(reinterpret_cast<void*>(address + 0x8), 0x90, 2);

	_SpSnow = SpSnow();

}

Vector3 GTAmemory::ReadVector3(UINT64 address)
{
	const float* data = (float*)address;
	return Vector3(data[0], data[1], data[2]);
}
void GTAmemory::WriteVector3(UINT64 address, const Vector3& value)
{
	float* data = (float*)address;
	data[0] = value.x;
	data[1] = value.y;
	data[2] = value.z;
}

struct HashNode
{
	int hash;
	UINT16 data;
	UINT16 padding;
	HashNode* next;
};
void GTAmemory::GenerateVehicleModelList()
{
	//Zorg
	uintptr_t address = FindPattern("\x66\x81\xF9\x00\x00\x74\x10\x4D\x85\xC0", "xxx??xxxxx");
	if (address)
	{
		address = address - 0x21;
		//UINT64 baseFuncAddr = *reinterpret_cast<int*>(address - 0x21) + address - 0x1D;
		UINT64 baseFuncAddr = address + *reinterpret_cast<int*>(address) + 0x4;
		//int classOffset = *reinterpret_cast<int*>(address + 0x10);
		int classOffset = *reinterpret_cast<int*>(address + 0x31);
		modelHashEntries = *reinterpret_cast<UINT16*>(baseFuncAddr + *reinterpret_cast<int*>(baseFuncAddr + 3) + 7);
		modelNum1 = *reinterpret_cast<int*>(*reinterpret_cast<int*>(baseFuncAddr + 0x52) + baseFuncAddr + 0x56); //cmp
		modelNum2 = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x63) + baseFuncAddr + 0x67); //mov
		modelNum3 = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x7A) + baseFuncAddr + 0x7E); //mul
		modelNum4 = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x81) + baseFuncAddr + 0x85); //add

		modelHashTable = *reinterpret_cast<PUINT64>(*reinterpret_cast<int*>(baseFuncAddr + 0x24) + baseFuncAddr + 0x28);
		HashNode** HashMap = reinterpret_cast<HashNode**>(modelHashTable);
		//I know 0x20 items are defined but there are only 0x16 vehicle classes.
		//But keeping it at 0x20 is just being safe as the & 0x1F in theory supports up to 0x20
		auto& hashes = GTAmemory::vehicleModels;
		for (auto& vec : hashes)
			vec.clear();
		for (int i = 0; i < modelHashEntries; i++)
		{
			for (HashNode* cur = HashMap[i]; cur; cur = cur->next)
			{
				UINT16 data = cur->data;
				if ((int)data < modelNum1 && bittest(*reinterpret_cast<int*>(modelNum2 + (4 * data >> 5)), data & 0x1F))
				{
					UINT64 addr1 = modelNum4 + modelNum3 * data;
					if (addr1)
					{
						UINT64 addr2 = *reinterpret_cast<PUINT64>(addr1);
						if (addr2)
						{
							if ((*reinterpret_cast<PBYTE>(addr2 + 157) & 0x1F) == 5)
							{
								hashes[*reinterpret_cast<PBYTE>(addr2 + classOffset) & 0x1F].push_back((unsigned int)cur->hash);
							}
						}
					}
				}
			}
		}
	}
}
bool GTAmemory::IsModelAPed(unsigned int modelHash)
{
	HashNode** HashMap = reinterpret_cast<HashNode**>(modelHashTable);
	for (HashNode* cur = HashMap[modelHash % modelHashEntries]; cur; cur = cur->next)
	{
		if ((unsigned int)cur->hash != modelHash)
		{
			continue;
		}
		UINT16 data = cur->data;
		if ((int)data < modelNum1 && bittest(*reinterpret_cast<int*>(modelNum2 + (4 * data >> 5)), data & 0x1F))
		{
			UINT64 addr1 = modelNum4 + modelNum3 * data;
			if (addr1)
			{
				UINT64 addr2 = *reinterpret_cast<PUINT64>(addr1);
				if (addr2)
				{
					return (*reinterpret_cast<PBYTE>(addr2 + 157) & 0x1F) == 6;
				}
			}
		}
	}
	return false;
}

INT32 GTAmemory::TransitionStatus()
{
	if (_transitionStatus != nullptr)
		return *_transitionStatus;

	switch (GTAmemory::GetGameVersion())
	{
	case eGameVersion::VER_1_0_1290_1_STEAM: case eGameVersion::VER_1_0_1290_1_NOSTEAM:
	case eGameVersion::VER_1_0_1365_1_STEAM: case eGameVersion::VER_1_0_1365_1_NOSTEAM:
		_transitionStatus = GTAmemory::GetGlobalPtr<INT32>(1312789); break;
	case eGameVersion::VER_1_0_1604_1_STEAM: case eGameVersion::VER_1_0_1604_1_NOSTEAM:
		_transitionStatus = GTAmemory::GetGlobalPtr<INT32>(1312792); break;
	}
	return _transitionStatus == nullptr ? 0i32 : *_transitionStatus;
}

// Unknown_Modder
UINT64 GTAmemory::_globalTextBlockAddr;
std::vector<GTAmemory::GXT2Entry> GTAmemory::_vecGXT2Entries;
void GTAmemory::LoadGlobalGXTEntries()
{
	UINT64 address = FindPattern("\x84\xC0\x74\x34\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD3", "xxxxxxx????xxx");
	if (address)
	{
		address = *reinterpret_cast<int *>(address + 7) + address + 11;
		DWORD offset = 0xA0; // for text block "GLOBAL"
		_globalTextBlockAddr = *(UINT64 *)(address + offset);

		UINT32 numEntries = *(UINT32 *)(_globalTextBlockAddr + 4);

		for (UINT32 entry = 0; entry < numEntries; entry++)
		{
			DWORD labelHash = *(DWORD *)(_globalTextBlockAddr + 8 + entry * 8);

			DWORD strOffset = *(DWORD *)(_globalTextBlockAddr + 12 + entry * 8);

			_vecGXT2Entries.push_back({ labelHash, strOffset });
		}
	}
}
void GTAmemory::EditGXTLabel(DWORD labelHash, LPCSTR string)
{
	static bool sbLoadGxtEntries = true;
	if (sbLoadGxtEntries)
	{
		sbLoadGxtEntries = false;
		LoadGlobalGXTEntries();
	}

	for (GXT2Entry& entry : _vecGXT2Entries)
	{
		if (entry.labelHash == labelHash)
		{
			strcpy_s((char *)(_globalTextBlockAddr + entry.strOffset), strlen(string), string);
			//strcpy((char *)(_globalTextBlockAddr + entry.strOffset), string);
		}
	}
}

UINT64 GTAmemory::GetEntityAddress(int handle)
{
	return (GTAmemory::_entityAddressFunc(handle));
}
UINT64 GTAmemory::GetPlayerAddress(int handle)
{
	return (GTAmemory::_playerAddressFunc(handle));
}
UINT64 GTAmemory::GetCheckpointAddress(int handle)
{
	UINT64 addr = GTAmemory::CheckpointHandleAddr(GTAmemory::CheckpointBaseAddr(), handle);
	if (addr)
	{
		return (UINT64)((UINT64)(GTAmemory::checkpointPoolAddress) + 96 * *reinterpret_cast<int *>(addr + 16));
	}
	return 0;
}
UINT64 GTAmemory::GetPtfxAddress(int handle)
{
	return (GTAmemory::_ptfxAddressFunc(handle));
}

int GTAmemory::GetEntityBoneCount(int handle)
{
	UINT64 MemAddress = _entityAddressFunc(handle);
	UINT64 Addr2 = (*(UINT64(__fastcall **)(__int64))(*(UINT64 *)MemAddress + 88i64))(MemAddress);
	UINT64 Addr3;
	if (!Addr2)
	{
		Addr3 = *(UINT64*)(MemAddress + 80);
		if (!Addr3)
		{
			return 0;
		}
		else
		{
			Addr3 = *(UINT64*)(Addr3 + 40);
		}
	}
	else
	{
		Addr3 = *(UINT64*)(Addr2 + 104);
		if (!Addr3 || !*(UINT64*)(Addr2 + 120))
		{
			return 0;
		}
		else
		{
			Addr3 = *(UINT64*)(Addr3 + 376);
		}
	}
	if (!Addr3)
	{
		return 0;
	}
	return *(int*)(Addr3 + 32);
}
UINT64 GTAmemory::GetEntityBoneMatrixAddress(int handle, int boneIndex)
{
	if ((boneIndex & 0x80000000) != 0)//boneIndex cant be negative
		return 0;

	UINT64 MemAddress = _entityAddressFunc(handle);
	UINT64 Addr2 = (*(UINT64(__fastcall **)(__int64))(*(UINT64 *)MemAddress + 88i64))(MemAddress);
	UINT64 Addr3;
	if (!Addr2)
	{
		Addr3 = *(UINT64*)(MemAddress + 80);
		if (!Addr3)
		{
			return 0;
		}
		else
		{
			Addr3 = *(UINT64*)(Addr3 + 40);
		}
	}
	else
	{
		Addr3 = *(UINT64*)(Addr2 + 104);
		if (!Addr3 || !*(UINT64*)(Addr2 + 120))
		{
			return 0;
		}
		else
		{
			Addr3 = *(UINT64*)(Addr3 + 376);
		}
	}
	if (!Addr3)
	{
		return 0;
	}
	if (boneIndex < *(int*)(Addr3 + 32))
	{
		return UINT64((*(UINT64*)(Addr3 + 24) + (boneIndex << 6)));
	}
	return 0;
}

int GTAmemory::CursorSprite_get()
{
	return *_cursorSpriteAddr;
}

UINT64 GTAmemory::GetGameplayCameraAddress()
{
	return (*GTAmemory::_gamePlayCameraAddr);
}

UINT64 GTAmemory::GetCameraAddress(int handle)
{
	unsigned int index = (unsigned int)(handle >> 8);
	UINT64 poolAddr = *_cameraPoolAddress;
	if (*(BYTE *)(index + *(INT64*)(poolAddr + 8)) == (BYTE)(handle & 0xFF))
	{
		return (*(INT64*)poolAddr + (unsigned int)(index * *(UINT32 *)(poolAddr + 20)));
	}
	return 0;
}

void GTAmemory::GetVehicleHandles(std::vector<Entity>& result)
{
	EntityPoolTask(EntityPoolTask::Type::Vehicle).Run(result);
}
void GTAmemory::GetVehicleHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Vehicle);
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}
void GTAmemory::GetVehicleHandles(std::vector<Entity>& result, const Vector3& position, float radius)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Vehicle);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool.Run(result);
}
void GTAmemory::GetVehicleHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Vehicle);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}

void GTAmemory::GetPedHandles(std::vector<Entity>& result)
{
	EntityPoolTask(EntityPoolTask::Type::Ped).Run(result);
}
void GTAmemory::GetPedHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Ped);
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}
void GTAmemory::GetPedHandles(std::vector<Entity>& result, const Vector3& position, float radius)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Ped);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool.Run(result);
}
void GTAmemory::GetPedHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Ped);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}

void GTAmemory::GetPropHandles(std::vector<Entity>& result)
{
	EntityPoolTask(EntityPoolTask::Type::Prop).Run(result);
}
void GTAmemory::GetPropHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Prop);
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}
void GTAmemory::GetPropHandles(std::vector<Entity>& result, const Vector3& position, float radius)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Prop);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool.Run(result);
}
void GTAmemory::GetPropHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Prop);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}

void GTAmemory::GetEntityHandles(std::vector<Entity>& result)
{
	EntityPoolTask(EntityPoolTask::Type::Ped | EntityPoolTask::Type::Vehicle | EntityPoolTask::Type::Prop).Run(result);
}
void GTAmemory::GetEntityHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Ped | EntityPoolTask::Type::Vehicle | EntityPoolTask::Type::Prop);
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}
void GTAmemory::GetEntityHandles(std::vector<Entity>& result, const Vector3& position, float radius)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Ped | EntityPoolTask::Type::Vehicle | EntityPoolTask::Type::Prop);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool.Run(result);
}
void GTAmemory::GetEntityHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::Ped | EntityPoolTask::Type::Vehicle | EntityPoolTask::Type::Prop);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool._modelHashes = modelHashes;
	pool._modelCheck = !modelHashes.empty();
	pool.Run(result);
}

void GTAmemory::GetPickupObjectHandles(std::vector<int>& result)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::PickupObject);
	pool.Run(result);
}
void GTAmemory::GetPickupObjectHandles(std::vector<int>& result, const Vector3& position, float radius)
{
	auto pool = EntityPoolTask(EntityPoolTask::Type::PickupObject);
	pool._position = position;
	pool._radiusSquared = radius * radius;
	pool._posCheck = true;
	pool.Run(result);
}

void GTAmemory::GetCheckpointHandles(std::vector<int>& result)
{
	UINT64 addr = GTAmemory::CheckpointBaseAddr();
	//result.resize(64);
	UINT8 count = 0;
	for (UINT64 i = *(UINT64*)(addr + 48); i && count < 64; i = *(UINT64*)(i + 24))
	{
		//result[count++] = *(int*)(i + 12);
		result.push_back(*(int*)(i + 12));
	}
	//result.resize(count);
}

int GTAmemory::GetNumberOfVehicles()
{
	if (*_vehiclePoolAddress)
	{
		VehiclePool* pool = *reinterpret_cast<VehiclePool**>(*_vehiclePoolAddress);
		return pool->itemCount;
	}
	return 0;
}

float GTAmemory::WorldGravity_get()
{
	return *_readWorldGravityAddress;
}
void GTAmemory::WorldGravity_set(float value)
{
	*_writeWorldGravityAddress = value;
	SET_GRAVITY_LEVEL(0);
}

/*void GTAmemory::GetVehicleHandles(std::vector<Entity>& result)
{
	Entity* entities = new Entity[poolCount_vehicles];
	int count = worldGetAllVehicles(entities, poolCount_vehicles);
	for (int i = 0; i < count; i++)
	{
		//if (IS_ENTITY_A_VEHICLE(entities[i]))
		result.push_back(entities[i]);
	}
	delete[] entities;
}
void GTAmemory::GetPedHandles(std::vector<Entity>& result)
{
	Entity* entities = new Entity[poolCount_peds];
	int count = worldGetAllPeds(entities, poolCount_peds);
	for (int i = 0; i < count; i++)
	{
		//if (IS_ENTITY_A_PED(entities[i]))
		result.push_back(entities[i]);
	}
	delete[] entities;
}
void GTAmemory::GetPropHandles(std::vector<Entity>& result)
{
	Entity* entities = new Entity[poolCount_objects];
	int count = worldGetAllObjects(entities, poolCount_objects);
	for (int i = 0; i < count; i++)
	{
		//if (IS_ENTITY_AN_OBJECT(entities[i]))
		result.push_back(entities[i]);
	}
	delete[] entities;
}
void GTAmemory::GetEntityHandles(std::vector<Entity>& result)
{
	GTAmemory::GetVehicleHandles(result);
	GTAmemory::GetPedHandles(result);
	GTAmemory::GetPropHandles(result);
}*/

uintptr_t GTAmemory::FindPattern(const char *pattern, const char *mask, const char* startAddress, size_t size) {
	const char* address_end = startAddress + size;
	const auto mask_length = static_cast<size_t>(strlen(mask) - 1);

	for (size_t i = 0; startAddress < address_end; startAddress++) {
		if (*startAddress == pattern[i] || mask[i] == '?') {
			if (mask[i + 1] == '\0') {
				return reinterpret_cast<uintptr_t>(startAddress) - mask_length;
			}
			i++;
		}
		else {
			i = 0;
		}
	}
	return 0;
}

uintptr_t GTAmemory::FindPattern(const char *pattern, const char *mask)
{
	MODULEINFO modInfo = g_MainModuleInfo;

	const char *start_offset = reinterpret_cast<const char *>(modInfo.lpBaseOfDll);
	const uintptr_t size = static_cast<uintptr_t>(modInfo.SizeOfImage);

	intptr_t pos = 0;
	const uintptr_t searchLen = static_cast<uintptr_t>(strlen(mask) - 1);

	for (const char *retAddress = start_offset; retAddress < start_offset + size; retAddress++)
	{
		if (*retAddress == pattern[pos] || mask[pos] == '?')
		{
			if (mask[pos + 1] == '\0')
			{
				return (reinterpret_cast<uintptr_t>(retAddress) - searchLen);
			}

			pos++;
		}
		else
		{
			pos = 0;
		}
	}

	return 0;
}

//--------------------------------SpSnow---------------------------------------------------------

SpSnow _SpSnow;

void SpSnow::EnableSnow(bool bEnable)
{
	// Adresses
	static auto SpSnow_addr1 = MemryScan::PatternScanner::FindPattern("\x80\x3D\x00\x00\x00\x00\x00\x74\x27\x84\xC0", "xx?????xxxx");
	static auto SpSnow_addr2 = MemryScan::PatternScanner::FindPattern("\x44\x38\x3D\x00\x00\x00\x00\x74\x0F", "xxx????xx");
	static auto SpSnow_addr12 = MemryScan::PatternScanner::FindPattern("\x40\x38\x35\x00\x00\x00\x00\x74\x18\x84\xdb\x74\x14", "xxx????xxxxxx");
	static auto SpSnow_addr13 = MemryScan::PatternScanner::FindPattern("\x80\x3D\x00\x00\x00\x00\x00\x74\x25\xB9\x40\x00\x00\x00", "xx????xxxxxxxx");
	static auto SpSnow_addr22 = MemryScan::PatternScanner::FindPattern("\x44\x38\x3D\x00\x00\x00\x00\x74\x1D\xB9\x40\x00\x00\x00", "xxx????xxxxxxx");

	auto& addr1 = SpSnow_addr1;
	auto& addr2 = SpSnow_addr2;
	auto& addr12 = SpSnow_addr12;
	auto& addr13 = SpSnow_addr13;
	auto& addr22 = SpSnow_addr22;

	const bool isMinGameVersion3095 = GTAmemory::GetGameVersion() >= eGameVersion::VER_1_0_3095_0;

	// Patterns may change
	if (!addr1 && !isMinGameVersion3095)
	{
		if (!addr12)
		{
			if (!addr13)
			{
				BEGIN_TEXT_COMMAND_PRINT("STRING");
				ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~r~Error:~s~ Snow is not compatible with this GTA Version.");
				END_TEXT_COMMAND_PRINT(2000, 1);
				//auto snow_ptr = GetTunablePtr<INT32>(RawTunableIndex::TURN_SNOW_ON_OFF);
				//*snow_ptr = bEnable ? 1 : 0;
				return;
			}
			else
			{
				addr1 = addr13;
				bUseAddr13 = true;
			}
		}
		else
		{
			addr1 = addr12;
		}
	}

	if (!addr2)
	{
		if (!addr22)
		{
			BEGIN_TEXT_COMMAND_PRINT("STRING");
			ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~r~Error:~s~ Snow is not compatible with this GTA Version.");
			END_TEXT_COMMAND_PRINT(2000, 1);
			//auto snow_ptr = GetTunablePtr<INT32>(RawTunableIndex::TURN_SNOW_ON_OFF);
			//*snow_ptr = bEnable ? 1 : 0;
			return;
		}
		else
		{
			addr2 = addr22;
			bUseAddr22 = true;
		}
	}

	// Initialize
	if (!this->bInitialized)
	{
		// Unprotect Memory
		if(!isMinGameVersion3095) VirtualProtect((void*)addr1, 13, PAGE_EXECUTE_READWRITE, nullptr); 
		VirtualProtect((void*)addr2, 14, PAGE_EXECUTE_READWRITE, nullptr);

		// Copy original Memory
		if (!isMinGameVersion3095) memcpy(&original1, (void*)addr1, 13);
		memcpy(&original2, (void*)addr2, 14);

		this->traxv_call = MemryScan::PatternScanner::FindPattern("\x40\x38\x3D\x00\x00\x00\x00\x48\x8B\x42\x20", "xxx????xxxx");
		if (this->traxv_call == NULL) this->tracks_available = false;

		this->traxvt = MemryScan::PatternScanner::FindPattern("\xB9\x00\x00\x00\x00\x84\xC0\x44\x0F\x44\xF1", "x????xxxxxx");
		if (this->traxvt == NULL) this->tracks_available = false;

		this->traxp_call = MemryScan::PatternScanner::FindPattern("\x80\x3D\x00\x00\x00\x00\x00\x48\x8B\xD9\x74\x37", "xx?????xxxxx");
		if (this->traxp_call == NULL) this->tracks_available = false;

		this->traxpt = MemryScan::PatternScanner::FindPattern("\xB9\x00\x00\x00\x00\x84\xC0\x0F\x44\xD9\x48\x8B\x4F\x30", "x????xxxxxxxxx");
		if (this->traxpt == NULL) this->tracks_available = false;

		if (this->tracks_available)
		{
			this->traxv = this->traxv_call + (*(int32_t *)(this->traxv_call + 3)) + 7;
			this->traxp = this->traxp_call + (*(int32_t *)(this->traxp_call + 2)) + 7;
		}

		this->bInitialized = true;
	}

	//auto snow_ptr = GetTunablePtr<INT32>(RawTunableIndex::TURN_SNOW_ON_OFF);


	// Toggle
	if (bEnable)
	{
		// NOP checks
		if (!isMinGameVersion3095)
		{
			if (bUseAddr13)
			{
				BYTE* pFrom = (BYTE*)addr1;
				BYTE* pTo = (BYTE*)addr1 + 0x1B;
				DWORD protect;
				VirtualProtect(pFrom, 16, PAGE_EXECUTE_READWRITE, &protect);
				pFrom[0] = 0x48;  // mov rax, func
				pFrom[1] = 0xB8;
				*reinterpret_cast<BYTE**>(&pFrom[2]) = pTo;
				pFrom[10] = 0x50; // push rax
				pFrom[11] = 0xC3; // ret
				VirtualProtect(pFrom, 16, protect, &protect);
			}
			else
			{
				memset((void*)addr1, 0x90, 13);
			}
		}

		if (bUseAddr22)
		{
			BYTE* pFrom = (BYTE*)addr2;
			BYTE* pTo = (BYTE*)addr2 + 0x1C;
			DWORD protect;
			VirtualProtect(pFrom, 16, PAGE_EXECUTE_READWRITE, &protect);
			pFrom[0] = 0x48;  // mov rax, func
			pFrom[1] = 0xB8;
			*reinterpret_cast<BYTE **>(&pFrom[2]) = pTo;
			pFrom[10] = 0x50; // push rax
			pFrom[11] = 0xC3; // ret
			VirtualProtect(pFrom, 16, protect, &protect);
		}
		else
		{
			memset((void*)addr2, 0x90, 14);
		}

		// Weather
		//SET_WEATHER_TYPE_NOW_PERSIST("Snow");

		//*snow_ptr = 1;

		//USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(true);
		//USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(true);
		this->EnableTracks(true, true, true, true);
		if (isMinGameVersion3095) 
			FORCE_GROUND_SNOW_PASS(true);
		// Now on
	}
	else
	{
		// Copy original bytes back
		if (!isMinGameVersion3095) memcpy((void*)addr1, &original1, 13);
		memcpy((void*)addr2, &original2, 14);

		// Weather
		//CLEAR_WEATHER_TYPE_PERSIST();
		//SET_WEATHER_TYPE_NOW("Sunny");

		//*snow_ptr = 0;

		//USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(false);
		//USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(false);
		this->EnableTracks(false, false, false, false);
		if (isMinGameVersion3095) 
			FORCE_GROUND_SNOW_PASS(false);
		// Now off
	}
}
void SpSnow::EnableTracks(bool tracksPed, bool deepTracksPed, bool tracksVehicle, bool deepTracksVehicle)
{
	if (this->tracks_available)
	{
		memset((void*)this->traxv, tracksVehicle ? 0x1 : 0x0, 1);
		memset((void*)(this->traxvt + 1), deepTracksVehicle ? 0x13 : 0x14, 1);
		memset((void*)this->traxp, tracksPed ? 0x1 : 0x0, 1);
		memset((void*)(this->traxpt + 1), deepTracksPed ? 0x13 : 0x14, 1);
	}

	if (tracksPed || tracksVehicle)
	{
		REQUEST_NAMED_PTFX_ASSET("core_snow");
		USE_PARTICLE_FX_ASSET("core_snow");
	}
	else
	{
		REMOVE_NAMED_PTFX_ASSET("core_snow");
	}
	if (tracksPed)
	{
		REQUEST_SCRIPT_AUDIO_BANK("ICE_FOOTSTEPS", true, 0);
		REQUEST_SCRIPT_AUDIO_BANK("SNOW_FOOTSTEPS", true, 0);
	}
	else
	{
		RELEASE_NAMED_SCRIPT_AUDIO_BANK("ICE_FOOTSTEPS");
		RELEASE_NAMED_SCRIPT_AUDIO_BANK("SNOW_FOOTSTEPS");
	}
	USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(tracksPed);
	USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(tracksVehicle);
}

SpSnow::SpSnow()
	: bDisabled(true), loop_spsnow(false), bInitialized(false),
	bUseAddr13(false), bUseAddr22(false),
	tracks_available(true),
	traxp(NULL),
	traxp_call(NULL),
	traxpt(NULL),
	traxv(NULL),
	traxv_call(NULL),
	traxvt(NULL)
{
}
bool SpSnow::IsSnow()
{
	return this->loop_spsnow;
}
void SpSnow::ToggleSnow(bool bEnable)
{
	if (bEnable) this->bDisabled = false;
	this->loop_spsnow = bEnable;
}
void SpSnow::Tick()
{
	if (this->bDisabled)
	{
		return;
	}

	if (this->loop_spsnow) this->EnableSnow(true);
	else
	{
		this->EnableSnow(false);
		this->bDisabled = true;
	}

}

//--------------------------------GeneralGlobalHax-----------------------------------------------

void GeneralGlobalHax::DisableAnnoyingRecordingUI(bool uSure)
{
	// Has to be updated every patch.
	switch (GTAmemory::GetGameVersion())
	{
	case eGameVersion::VER_1_0_757_4_NOSTEAM: case eGameVersion::VER_1_0_757_4_STEAM:
	case eGameVersion::VER_1_0_791_2_NOSTEAM: case eGameVersion::VER_1_0_791_2_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x42DE + 0x9) = uSure ? 1 : 0; break;
	case eGameVersion::VER_1_0_877_1_NOSTEAM: case eGameVersion::VER_1_0_877_1_STEAM:
	case eGameVersion::VER_1_0_944_2_NOSTEAM: case eGameVersion::VER_1_0_944_2_STEAM:
	case eGameVersion::VER_1_0_1011_1_NOSTEAM: case eGameVersion::VER_1_0_1011_1_STEAM:
	case eGameVersion::VER_1_0_1032_1_NOSTEAM: case eGameVersion::VER_1_0_1032_1_STEAM:
	case eGameVersion::VER_1_0_1103_2_NOSTEAM: case eGameVersion::VER_1_0_1103_2_STEAM:
	case eGameVersion::VER_1_0_1180_2_NOSTEAM: case eGameVersion::VER_1_0_1180_2_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x42FF + 0x9) = uSure ? 1 : 0;
		*GTAmemory::GetGlobalPtr<INT32>(0x42FF + 0x82) = uSure ? 1 : 0;
		break;
	case eGameVersion::VER_1_0_1290_1_NOSTEAM: case eGameVersion::VER_1_0_1290_1_STEAM:
	case eGameVersion::VER_1_0_1365_1_NOSTEAM: case eGameVersion::VER_1_0_1365_1_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x430A + 0x82) = uSure ? 1 : 0; break;
	case eGameVersion::VER_1_0_1493_0_NOSTEAM: case eGameVersion::VER_1_0_1493_0_STEAM:
	case eGameVersion::VER_1_0_1493_1_NOSTEAM: case eGameVersion::VER_1_0_1493_1_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x4336 + 0x82) = uSure ? 1 : 0; break;
	case eGameVersion::VER_1_0_1604_0_NOSTEAM: case eGameVersion::VER_1_0_1604_0_STEAM:
	case eGameVersion::VER_1_0_1604_1_NOSTEAM: case eGameVersion::VER_1_0_1604_1_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x434C + 0x82) = uSure ? 1 : 0; break;
	case eGameVersion::VER_1_0_1737_0_NOSTEAM: case eGameVersion::VER_1_0_1737_0_STEAM:
	case eGameVersion::VER_1_0_1737_6_NOSTEAM: case eGameVersion::VER_1_0_1737_6_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x4378 + 0x82) = uSure ? 1 : 0; break;
	case eGameVersion::VER_1_0_1868_0_NOSTEAM: case eGameVersion::VER_1_0_1868_0_STEAM:
	case eGameVersion::VER_1_0_1868_1_NOSTEAM: case eGameVersion::VER_1_0_1868_1_STEAM:
		*GTAmemory::GetGlobalPtr<INT32>(0x56C3 + 0x82) = uSure ? 1 : 0; break;
	}
}

//https://github.com/ikt32/GTAVAddonLoader/blob/master/GTAVAddonLoader/NativeMemory.cpp
void GeneralGlobalHax::EnableBlockedMpVehiclesInSp()
{	
	const char* patt617_1 = "\x2C\x01\x00\x00\x20\x56\x04\x00\x6E\x2E\x00\x01\x5F\x00\x00\x00\x00\x04\x00\x6E\x2E\x00\x01";
	const char* mask617_1 = "xx??xxxxxx?xx????xxxx?x";
	const unsigned int offset617_1 = 13;

	const char* patt1604_0 = "\x2D\x00\x00\x00\x00\x2C\x01\x00\x00\x56\x04\x00\x6E\x2E\x00\x01\x5F\x00\x00\x00\x00\x04\x00\x6E\x2E\x00\x01";
	const char* mask1604_0 = "x??xxxx??xxxxx?xx????xxxx?x";
	const unsigned int offset1064_0 = 17;

	// Updated pattern entirely thanks to @alexguirre
	const char* patt2802_0 = "\x2D\x00\x00\x00\x00\x2C\x01\x00\x00\x56\x04\x00\x71\x2E\x00\x01\x62\x00\x00\x00\x00\x04\x00\x71\x2E\x00\x01";
	const char* mask2802_0 = "x??xxxx??xxxxx?xx????xxxx?x";
	const unsigned int offset2802_0 = 17;

	const char* pattern = patt617_1;
	const char* mask = mask617_1;
	int offset = offset617_1;

	if (getGameVersion() >= 80) {
		pattern = patt2802_0;
		mask = mask2802_0;
		offset = offset2802_0;
	}
	else if (getGameVersion() >= 46) {
		pattern = patt1604_0;
		mask = mask1604_0;
		offset = offset1064_0;
	}

	for (int i = 0; i < shopController->CodePageCount(); i++)
	{
		int size = shopController->GetCodePageSize(i);
		if (size)
		{
			uintptr_t address = GTAmemory::FindPattern(pattern, mask, (const char*)shopController->GetCodePageAddress(i), size);
			if (address)
			{
				int globalindex = *(int*)(address + offset) & 0xFFFFFF;
				addlog(ige::LogType::LOG_INFO,  "Setting Global Variable " + std::to_string(globalindex) + " to true", __FILENAME__);
				*GTAmemory::GetGlobalPtr<INT32>(globalindex) = 1;
				return;
			}
		}
	}

	addlog(ige::LogType::LOG_ERROR,  "Global Variable not found, check game version >= 1.0.678.1", __FILENAME__);
}

// from EnableMPCars by drp4lyf
bool GTAmemory::FindShopController() {
	__int64 patternAddr = FindPattern("\x48\x03\x15\x00\x00\x00\x00\x4C\x23\xC2\x49\x8B\x08", "xxx????xxxxxx");
	if (!patternAddr) {
		addlog(ige::LogType::LOG_ERROR,  "ERROR: finding address 1", __FILENAME__);
		addlog(ige::LogType::LOG_ERROR,  "Aborting...", __FILENAME__);
		return false;
	}
	scriptTable = (ScriptTable*)(patternAddr + *(int*)(patternAddr + 3) + 7);
    
	ScriptTableItem* Item = scriptTable->FindScript(0x39DA738B);
	if (Item == NULL) {
		addlog(ige::LogType::LOG_ERROR,  "ERROR: finding script 0x39DA738B", __FILENAME__);
		addlog(ige::LogType::LOG_ERROR,  "Aborting...", __FILENAME__);
		return false;
	}
	while (!Item->IsLoaded())
		Sleep(100);
    
	shopController = Item->Header;
	//addlog(ige::LogType::LOG_INFO,  "Found shopcontroller", __FILENAME__);
	return true;
}

void** GeneralGlobalHax::WorldPtrPtr()
{
	static DWORD64 __dwWorldPtrAddr = 0x0U;
	if (!__dwWorldPtrAddr)
	{
		__dwWorldPtrAddr = MemryScan::PatternScanner::FindPattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
		if (__dwWorldPtrAddr)
		{
			__dwWorldPtrAddr = __dwWorldPtrAddr + *reinterpret_cast<int*>(__dwWorldPtrAddr + 3) + 7;
		}
	}
	return reinterpret_cast<void**>(__dwWorldPtrAddr);
}
float GeneralGlobalHax::GetPlayerHeight()
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_2802_0)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x88}));
	}
	return 1.0f;
}
void GeneralGlobalHax::SetPlayerHeight(float value)
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_2802_0)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x88})) = value;
	}
}
float GeneralGlobalHax::GetPlayerSwimSpeed()
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_791_2_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x1088, 0xE4}));
		else if (gameVersion <= eGameVersion::VER_1_0_877_1_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10A8, 0xE4}));
		else if (gameVersion <= eGameVersion::VER_1_0_1103_2_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0xE4}));
		else if (gameVersion <= eGameVersion::VER_1_0_1868_1_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0x148}));
		else if (gameVersion <= eGameVersion::VER_1_0_2215_0_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0x150}));
		else if (gameVersion <= eGameVersion::VER_1_0_2245_0_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0x170}));
	}
	return 1.0f;
}
void GeneralGlobalHax::SetPlayerSwimSpeed(float value)
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_791_2_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x1088, 0xE4})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_877_1_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10A8, 0xE4})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_1103_2_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0xE4})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_1868_1_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0x148})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_2215_0_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0x150})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_2245_0_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0x170})) = value;
	}
}
float GeneralGlobalHax::GetPlayerMovementSpeed()
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_791_2_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x1088, 0xE8}));
		else if (gameVersion <= eGameVersion::VER_1_0_877_1_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10A8, 0xE8}));
		else if (gameVersion <= eGameVersion::VER_1_0_1103_2_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0xE8}));
		else if (gameVersion <= eGameVersion::VER_1_0_1868_1_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0x14C}));
		else if (gameVersion <= eGameVersion::VER_1_0_2215_0_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0xCD0}));
		else if (gameVersion <= eGameVersion::VER_1_0_2245_0_NOSTEAM)
			return *(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0xCF0}));
		
	}
	return 1.0f;
}
void GeneralGlobalHax::SetPlayerMovementSpeed(float value)
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_791_2_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x1088, 0xE8})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_877_1_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10A8, 0xE8})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_1103_2_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0xE8})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_1868_1_NOSTEAM)
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10B8, 0x14C})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_2215_0_NOSTEAM) 
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0xCD0})) = value;
		else if (gameVersion <= eGameVersion::VER_1_0_2245_0_NOSTEAM) 
			*(GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0x10C8, 0xCF0})) = value;
	}
}

int GeneralGlobalHax::GetVehicleBoostState()
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_2372_0_NOSTEAM)
			return *(GetMultilayerPointer<int*>(baddr, std::vector<DWORD>{0x8, 0xD28, 0x318}));
	}
	return 0;
}
void GeneralGlobalHax::SetVehicleBoostState(int value)
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_2372_0_NOSTEAM)
			*(GetMultilayerPointer<int*>(baddr, std::vector<DWORD>{0x8, 0xD28, 0x318})) = value;
	}
}
float* GeneralGlobalHax::GetVehicleBoostChargePtr()
{
	auto baddr = *GeneralGlobalHax::WorldPtrPtr();
	if (baddr)
	{
		auto gameVersion = GTAmemory::GetGameVersion();
		if (gameVersion <= eGameVersion::VER_1_0_1103_2_NOSTEAM)
			return (GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0xD28, 0x31C}));
		if (gameVersion <= eGameVersion::VER_1_0_2372_0_NOSTEAM)//VER_1_0_1868_1_NOSTEAM
			return (GetMultilayerPointer<float*>(baddr, std::vector<DWORD>{0x8, 0xD28, 0x320})); // Might be off
	}
	return nullptr;
}


