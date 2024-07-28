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

#include "..\main.h" //getGameVersion getGlobalPtr

//#include <cstddef>
#include <vector>
#include <array>
#include <Windows.h>
#include <Psapi.h>
#include <string>

typedef unsigned char UINT8, BYTE;
typedef signed int INT32;
typedef unsigned long DWORD;
typedef unsigned long long size_t;
typedef unsigned __int64 DWORD64, UINT64;
typedef void *LPVOID;
typedef const char *LPCSTR;
typedef int Entity;
typedef unsigned long Hash;
typedef uint8_t eModelType;
typedef uint32_t eVehicleType;
typedef uint32_t eVehicleFlag1;
typedef uint32_t eVehicleFlag2;
typedef uint32_t eVehicleFlag3;
typedef uint32_t eVehicleFlag4;
typedef uint32_t eVehicleFlag5;
typedef uint32_t eVehicleFlag6;
// Various snippets from FiveM source and Unknown Modder
namespace rage {
    class fwArchetype {
    public:
        virtual ~fwArchetype() = default;

        char _0x0008[0x10]; // 0x0000
        Hash m_hash; // 0x0018
        char _0x001C[0x10]; // 0x001C
        float m_radius; // 0x002C
        float m_aabbMin[4]; // 0x0030
        float m_aabbMax[4]; // 0x0040
        uint32_t m_flags; // 0x0050
        char _0x0054[0x12]; // 0x0054
        uint16_t m_index; // 0x0066
    };

    class fwEntity
    {
    public:
        virtual ~fwEntity() = 0;
    };

    class fwArchetypeDef
    {
    public:
        virtual ~fwArchetypeDef();

        virtual int64_t GetTypeIdentifier();

        float lodDist;
        uint32_t flags; // 0x10000 = alphaclip
        uint32_t specialAttribute; // lower 5 bits == 31 -> use alpha clip, get masked to 31 in InitializeFromArchetypeDef
        uint32_t pad;
        void* pad2;
        float bbMin[4];
        float bbMax[4];
        float bsCentre[4];
        float bsRadius;
        float hdTextureDist;
        uint32_t name;
        uint32_t textureDictionary;
        uint32_t clipDictionary;
        uint32_t drawableDictionary;
        uint32_t physicsDictionary;
        uint32_t assetType;
        uint32_t assetName;
        uint32_t pad5[7];

    public:
        fwArchetypeDef()
        {
            flags = 0x10000; // was 0x2000
            lodDist = 299.0f;
            hdTextureDist = 375.0f;

            drawableDictionary = 0;
            assetType = 3;
            assetName = 0x12345678;

            specialAttribute = 31;

            pad = 0;
            pad2 = 0;
            clipDictionary = 0;
            physicsDictionary = 0;
            memset(pad5, 0, sizeof(physicsDictionary));
        }
    };

}

class CBaseModelInfo : public rage::fwArchetype
{
public:
    virtual ~CBaseModelInfo() {}
    virtual void Initialize() {}
    virtual void InitializeFromArchetypeDef(uint32_t, rage::fwArchetypeDef*, bool) {}
    virtual rage::fwEntity* CreateEntity() { return nullptr; }
    // and lots of other functions...

public:
    eModelType GetModelType() const
    {
        return m_modelType & 0x1F;
    }

protected:
    char _0x0068[0x35];    // 0x0068
    eModelType m_modelType;    // 0x009D (& 0x1F)
    char _0x009E[0x2];    // 0x009E
    uint32_t m_unkFlag;    // 0x00A0
    char _0x00A4[0x4];    // 0x00A4
    void* m_0x00A8;        // 0x00A8
};

class CVehicleModelInfo : public CBaseModelInfo
{
public:
    virtual ~CVehicleModelInfo() {}
    virtual void Initialize() {}
    virtual void InitializeFromArchetypeDef(uint32_t, rage::fwArchetypeDef*, bool) {}
    virtual rage::fwEntity* CreateEntity() { return nullptr; }
    // and lots of other functions...

public:
    void* m_0x00B0; // 0x00B0
    char _0x00B8[0x40]; // 0x00B8
    uint8_t m_primaryColorCombinations[25]; // 0x00F8
    uint8_t m_secondaryColorCombinations[25]; // 0x0111
    uint8_t m_unkColor1Combinations[25]; // 0x012A
    uint8_t m_unkColor2Combinations[25]; // 0x0143
    uint8_t m_interiorColorCombinations[25]; // 0x015C
    uint8_t m_dashboardColorCombinations[25]; // 0x0175
    char _0x018E[0xE2]; // 0x018E
    char m_displayName[12]; // 0x0270 (aka gameName)
    char m_manufacturerName[12]; // 0x027C (aka makeName)
    uint8_t* m_modKits; // 0x0288
    uint16_t m_modKitsCount; // 0x0290
    char _0x0292[0x46]; // 0x0292
    void* m_driverInfo; // 0x02D8
    uint8_t m_numDrivers; // 0x02E0
    char _0x02E1[0x37]; // 0x02E1
    eVehicleType m_vehicleType; // 0x0318
    uint32_t m_unkVehicleType; // 0x031C
    uint32_t m_diffuseTint; // 0x0320
    char _0x0324[0x90]; // 0x0324
    uint8_t m_unkModKitVal; // 0x03B4
    char _0x03B5[0xA7]; // 0x03B5
    float m_wheelScale; // 0x045C
    float m_wheelScaleRear; // 0x0460
    float m_defaultBodyHealth; // 0x0464
    char _0x0468[0x20]; // 0x0468
    uint32_t m_handlingIndex; // 0x0488
    uint32_t m_identicalModelSpawnDistance; // 0x048C
    char _0x0490[0x4]; // 0x0490
    uint32_t m_numColorCombinations; // 0x0494
    char _0x0498[0x30]; // 0x0498
    void* m_0x04C8; // 0x04C8 (wheel data? 0xAC -> burnout mult?)
    char _0x04D0[0x3B]; // 0x04D0
    uint8_t m_sirenInfoId; // 0x050B
    char _0x050C[0xC]; // 0x050C
    uint8_t m_vehicleClass; // 0x0518 (& 0x1F; (>> 5) & 3 -> plate type)
    char _0x0519[0x2F]; // 0x0519
    int m_seatCount; // 0x0548
    eVehicleFlag1 m_flags1; // 0x054C
    eVehicleFlag2 m_flags2; // 0x0550
    eVehicleFlag3 m_flags3; // 0x0554
    eVehicleFlag4 m_flags4; // 0x0558
    eVehicleFlag5 m_flags5; // 0x055C
};

class CVehicleModelInfo1290 : public CBaseModelInfo
{
public:
    virtual ~CVehicleModelInfo1290() {}
    virtual void Initialize() {}
    virtual void InitializeFromArchetypeDef(uint32_t, rage::fwArchetypeDef*, bool) {}
    virtual rage::fwEntity* CreateEntity() { return nullptr; }
    // and lots of other functions...

public:
    void* m_0x00B0; // 0x00B0
    char _0x00B8[0x40]; // 0x00B8
    uint8_t m_primaryColorCombinations[25]; // 0x00F8
    uint8_t m_secondaryColorCombinations[25]; // 0x0111
    uint8_t m_unkColor1Combinations[25]; // 0x012A
    uint8_t m_unkColor2Combinations[25]; // 0x0143
    uint8_t m_interiorColorCombinations[25]; // 0x015C
    uint8_t m_dashboardColorCombinations[25]; // 0x0175
    char _0x018E[0x10A]; // 0x018E
    char m_displayName[12]; // 0x0298 (aka gameName)
    char m_manufacturerName[12]; // 0x02A4 (aka makeName)
    uint16_t* m_modKits; // 0x02B0
    uint16_t m_modKitsCount; // 0x02B8
    char _0x02BA[0x46]; // 0x02BA
    void* m_driverInfo; // 0x0300
    uint8_t m_numDrivers; // 0x0308
    char _0x0309[0x37]; // 0x02E3
    eVehicleType m_vehicleType; // 0x0340
    uint32_t m_unkVehicleType; // 0x0344
    uint32_t m_diffuseTint; // 0x0348
    char _0x034C[0x90]; // 0x034C
    uint8_t m_unkModKitVal; // 0x03DC (also uint16_t now?)
    char _0x03DD[0xA7]; // 0x03DD
    float m_wheelScale; // 0x0484
    float m_wheelScaleRear; // 0x0488
    float m_defaultBodyHealth; // 0x048C
    char _0x0490[0x20]; // 0x0490
    uint32_t m_handlingIndex; // 0x04B8
    uint32_t m_identicalModelSpawnDistance; // 0x04BC
    char _0x04C0[0x4]; // 0x04C0
    uint32_t m_numColorCombinations; // 0x04C4
    uint32_t m_fragmentIndex; // 0x04C8
    char _0x04CC[0x2C]; // 0x04CC
    void* m_0x04F8; // 0x04F8 (wheel data? 0xAC -> burnout mult?)
    char _0x0500[0x3B]; // 0x0500
    uint8_t m_sirenInfoId; // 0x053B
    char _0x053C[0x7]; // 0x053C
    uint8_t m_0x0543; // 0x0543
    char _0x0544_[0x4]; // 0x0544
    uint8_t m_vehicleClass; // 0x0548 (& 0x1F; (>> 5) & 3 -> plate type)
    char _0x0549[0x2F]; // 0x0549
    int m_seatCount; // 0x0578 (use only if unk_0x00B0->seatCount can't be used)
    eVehicleFlag1 m_flags1; // 0x057C
    eVehicleFlag2 m_flags2; // 0x0580
    eVehicleFlag3 m_flags3; // 0x0584
    eVehicleFlag4 m_flags4; // 0x0588
    eVehicleFlag5 m_flags5; // 0x058C
    eVehicleFlag6 m_flags6; // 0x0590
    char _0x0594[0xC]; // 0x0594
};

struct ScriptHeader {
	char padding1[16];                    //0x0
	unsigned char** codeBlocksOffset;    //0x10
	char padding2[4];                    //0x18
	int codeLength;                        //0x1C
	char padding3[4];                    //0x20
	int localCount;                        //0x24
	char padding4[4];                    //0x28
	int nativeCount;                    //0x2C
	__int64* localOffset;                //0x30
	char padding5[8];                    //0x38
	__int64* nativeOffset;                //0x40
	char padding6[16];                    //0x48
	int nameHash;                        //0x58
	char padding7[4];                    //0x5C
	char* name;                            //0x60
	char** stringsOffset;                //0x68
	int stringSize;                        //0x70
	char padding8[12];                    //0x74
	//END_OF_HEADER

	bool IsValid() const { return codeLength > 0; }
	int CodePageCount() const { return (codeLength + 0x3FFF) >> 14; }
	int GetCodePageSize(int page) const {
		return (page < 0 || page >= CodePageCount() ? 0 : (page == CodePageCount() - 1) ? codeLength & 0x3FFF : 0x4000);
	}
	unsigned char* GetCodePageAddress(int page) const { return codeBlocksOffset[page]; }
	unsigned char* GetCodePositionAddress(int codePosition) const {
		return codePosition < 0 || codePosition >= codeLength ? NULL : &codeBlocksOffset[codePosition >> 14][codePosition & 0x3FFF];
	}
	char* GetString(int stringPosition)const {
		return stringPosition < 0 || stringPosition >= stringSize ? NULL : &stringsOffset[stringPosition >> 14][stringPosition & 0x3FFF];
	}

};

struct ScriptTableItem {
	ScriptHeader* Header;
	char padding[4];
	int hash;

	inline bool IsLoaded() const {
		return Header != NULL;
	}
};

struct ScriptTable {
	ScriptTableItem* TablePtr;
	char padding[16];
	int count;
	ScriptTableItem* FindScript(int hash) {
		if (TablePtr == NULL) {
			return NULL;//table initialisation hasnt happened yet
		}
		for (int i = 0; i<count; i++) {
			if (TablePtr[i].hash == hash) {
				return &TablePtr[i];
			}
		}
		return NULL;
	}
};

////psapi.h
//typedef struct _MODULEINFO {
//	LPVOID lpBaseOfDll;
//	DWORD SizeOfImage;
//	LPVOID EntryPoint;
//} MODULEINFO, *LPMODULEINFO;

enum eGameVersion : int;
class Vector3;

extern HMODULE g_MainModule;
extern MODULEINFO g_MainModuleInfo;

static inline bool IsBitSet(int& i, int bitNum) { return ((i & (1 << bitNum)) != 0); }
static inline void SetBit(int& i, int bitNum) { i |= (1 << bitNum); }
static inline void ClearBit(int& i, int bitNum) { i &= ~(1 << bitNum); }
static void SetClearBit(int& i, int bitNum, bool setAction) { if (setAction) SetBit(i, bitNum); else ClearBit(i, bitNum); }

template<typename R> R GetMultilayerPointer(void* base, std::vector<DWORD>& offsets);

namespace MemryScan
{
	struct PatternByte
	{
		PatternByte();

		PatternByte(std::string byteString, bool ignoreThis = false);

		bool ignore;
		UINT8 data;

	private:
		UINT8 StringToUint8(std::string str);
	};

	class Pattern final
	{
	public:
		static DWORD64 Scan(DWORD64 dwStart, DWORD64 dwLength, const std::string& s);
		static DWORD64 Scan(MODULEINFO mi, const std::string& s);
	};

	class PatternScanner final
	{
	public:
		static bool CompareMemory(const BYTE *data, const BYTE *pattern, const char *mask);

		static DWORD64 FindPattern(std::vector<unsigned short> pattern);
		static DWORD64 FindPattern(const char* bMaskc, const char* sMaskc);
		static DWORD64 FindPattern(const char* pattern, const char* mask, DWORD64 startAddress, size_t size);
		static DWORD64 FindPattern(const std::string& patternString);
		static DWORD64 FindPattern(MODULEINFO moduleInfo, const std::string& patternString);
	};
}

// citizenfx
class Blipx
{
public:
	__int32 iID; //0x0000 
	__int8 iID2; //0x0004 
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	float x;
	float y;
	float z;
	char _0x001C[6];
	BYTE bFocused; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	int iIcon; //0x0040
	char _0x0044[4];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050 
	__int16 iRotation; //0x0054 Heading
	BYTE bInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE bZIndex; //0x0057 
	BYTE bDisplay; //0x0058  Also Visibility 0010
	BYTE bAlpha; //0x0059
};//Size=0x005A
class BlipList
{
public:
	Blipx* m_Blips[1500]; //0x0000
	char _0x2EE0[56];

};//Size=0x2F18

// ScriptHookVDotNet
class GTAmemory final
{
public:
	static unsigned int(*_getHashKey)(const char* stringPtr, unsigned int initialHash);
	static UINT64(*_entityAddressFunc)(int handle);
	static UINT64(*_playerAddressFunc)(int handle);
	static UINT64(*_ptfxAddressFunc)(int handle);
	static int(*_addEntityToPoolFunc)(UINT64 address);
	static UINT64(*_entityPositionFunc)(UINT64 address, float *position);
	static UINT64(*_entityModel1Func)(UINT64 address), (*_entityModel2Func)(UINT64 address);
	static UINT64 *_entityPoolAddress, *_vehiclePoolAddress, *_pedPoolAddress, *_objectPoolAddress, *_cameraPoolAddress, *_pickupObjectPoolAddress;
	static unsigned char(*SetNmBoolAddress)(__int64, __int64, unsigned char);
	static unsigned char(*SetNmIntAddress)(__int64, __int64, int);
	static unsigned char(*SetNmFloatAddress)(__int64, __int64, float);
	static unsigned char(*SetNmVec3Address)(__int64, __int64, float, float, float);
	static unsigned char(*SetNmStringAddress)(__int64, __int64, __int64);
	static UINT64 CreateNmMessageFunc, GiveNmMessageFunc;
	static UINT64(*CheckpointBaseAddr)();
	static UINT64(*CheckpointHandleAddr)(UINT64 baseAddr, int Handle);
	static UINT64 *checkpointPoolAddress;
	static float *_readWorldGravityAddress, *_writeWorldGravityAddress;
	static UINT64 *_gamePlayCameraAddr;
	static int* _cursorSpriteAddr;
	static bool* _isMultiplayer;
	static INT32* _transitionStatus;

	static BlipList* _blipList;
	static BlipList* GetBlipList();

	// Unknown_Modder
	struct GXT2Entry
	{
		DWORD labelHash;
		DWORD strOffset;
	};
	static UINT64 _globalTextBlockAddr;
	static std::vector<GXT2Entry> _vecGXT2Entries;
	static void LoadGlobalGXTEntries();
	static void EditGXTLabel(DWORD labelHash, LPCSTR string);
	static UINT64 _gxtLabelFromHashAddr1;
	// Zorg
	static char*(__fastcall *_gxtLabelFromHashFuncAddr)(UINT64 address, unsigned int hash);
	static inline char* GetGXTEntry(unsigned int labelHash)
	{
		return _gxtLabelFromHashFuncAddr(_gxtLabelFromHashAddr1, labelHash);
	}

	static std::array<std::vector<unsigned int>, 0x20> const& VehicleModels()
	{
		return vehicleModels;
	}
	static bool IsModelAPed(unsigned int modelHash);

	static void Init();

	static inline eGameVersion GetGameVersion()
	{
		static eGameVersion __getGameVersion_value = getGameVersion();
		return __getGameVersion_value;
	}

	template <typename T> static inline T* GetGlobalPtr(int globalId)
	{
		//auto addr = getGameVersion() == VER_1_0_678_1_STEAM ? 142B15D00 : 0x142B11810;
		//return reinterpret_cast<T*>((ULONG64*)(*(ULONG64*)(addr + 8 * ((globalId >> 18) & 0x3F) + (INT64)(GetModuleHandleA(NULL) - 0x50000000)) + 8 * (globalId & 0x3FFFF)));

		return reinterpret_cast<T*>(getGlobalPtr(globalId));
	}

	static inline char ReadSByte(UINT64 address)
	{
		return *(char*)address;
	}
	static inline unsigned char ReadByte(UINT64 address)
	{
		return *(unsigned char*)address;
	}
	static inline short ReadShort(UINT64 address)
	{
		return *(short*)address;
	}
	static inline unsigned short ReadUShort(UINT64 address)
	{
		return *(unsigned short*)address;
	}
	static inline int ReadInt(UINT64 address)
	{
		return *(int*)address;
	}
	static inline unsigned int ReadUInt(UINT64 address)
	{
		return *(unsigned int*)address;
	}
	static inline float ReadFloat(UINT64 address)
	{
		return *(float*)address;
	}
	static inline std::string ReadString(UINT64 address)
	{
		return (char*)address;
	}
	static Vector3 ReadVector3(UINT64 address);
	/*static inline Matrix GTAmemory::ReadMatrix(UINT64 address)
	{
	return *(Matrix*)address;
	}*/
	static inline void WriteSByte(UINT64 address, char value)
	{
		*(char*)address = value;
	}
	static inline void WriteByte(UINT64 address, unsigned char value)
	{
		*(unsigned char*)address = value;
	}
	static inline void WriteShort(UINT64 address, short value)
	{
		*(short*)address = value;
	}
	static inline void WriteUShort(UINT64 address, unsigned short value)
	{
		*(unsigned short*)address = value;
	}
	static inline void WriteInt(UINT64 address, int value)
	{
		*(int*)address = value;
	}
	static inline void WriteUInt(UINT64 address, unsigned int value)
	{
		*(unsigned int*)address = value;
	}
	static inline void WriteFloat(UINT64 address, float value)
	{
		*(float*)address = value;
	}
	static void WriteVector3(UINT64 address, const Vector3& value);
	static inline unsigned int GetHashKey(const std::string& toHash)
	{
		return _getHashKey(toHash.c_str(), 0);
	}

	static UINT64 GetEntityAddress(int handle);
	static UINT64 GetPlayerAddress(int handle);
	static UINT64 GetCheckpointAddress(int handle);
	static UINT64 GetPtfxAddress(int handle);

	static UINT64 GetEntityBoneMatrixAddress(int handle, int boneIndex);
	static int GetEntityBoneCount(int handle);

	static int CursorSprite_get();

	static UINT64 GetGameplayCameraAddress();
	static UINT64 GetCameraAddress(int handle);

	static void GetVehicleHandles(std::vector<Entity>& result);
	static void GetVehicleHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes);
	static void GetVehicleHandles(std::vector<Entity>& result, const Vector3& position, float radius);
	static void GetVehicleHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes);

	static void GetPedHandles(std::vector<Entity>& result);
	static void GetPedHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes);
	static void GetPedHandles(std::vector<Entity>& result, const Vector3& position, float radius);
	static void GetPedHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes);

	static void GetPropHandles(std::vector<Entity>& result);
	static void GetPropHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes);
	static void GetPropHandles(std::vector<Entity>& result, const Vector3& position, float radius);
	static void GetPropHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes);

	static void GetEntityHandles(std::vector<Entity>& result);
	static void GetEntityHandles(std::vector<Entity>& result, std::vector<DWORD> modelHashes);
	static void GetEntityHandles(std::vector<Entity>& result, const Vector3& position, float radius);
	static void GetEntityHandles(std::vector<Entity>& result, const Vector3& position, float radius, std::vector<DWORD> modelHashes);

	static void GetCheckpointHandles(std::vector<int>& result);

	static void GetPickupObjectHandles(std::vector<int>& result);
	static void GetPickupObjectHandles(std::vector<int>& result, const Vector3& position, float radius);

	static int GetNumberOfVehicles();
	
	static float WorldGravity_get();
	static void WorldGravity_set(float value);

	static inline bool bittest(int data, unsigned char index)
	{
		return (data & (1 << index)) != 0;
	}

	static void GenerateVehicleModelList();

	static INT32 TransitionStatus();
	
	static uintptr_t FindPattern(const char *pattern, const char *mask, const char *startAddress, size_t size);
	static uintptr_t FindPattern(const char *pattern, const char *mask);
	
    static bool FindShopController();
	static std::string GetVehicleModelName(Hash modelHash);
	static std::string GetVehicleMakeName(Hash modelHash);

private:
	static UINT64 modelHashTable, modelNum2, modelNum3, modelNum4;
	static int modelNum1;
	static unsigned short modelHashEntries;
	static std::array<std::vector<unsigned int>, 0x20> vehicleModels;

	static const UINT16 poolCount_vehicles;
	static const UINT16 poolCount_peds;
	static const UINT16 poolCount_objects;

};

class SpSnow final// This is for sp since the global doesn't work in sp
{
private:
	bool bDisabled, loop_spsnow, bInitialized;
	bool bUseAddr13, bUseAddr22;
	bool tracks_available;
	DWORD64 traxp; //pedTracks
	DWORD64 traxp_call; //pedTracks_first call
	DWORD64 traxpt; //pedTrackTypes
	DWORD64 traxv; //vehicleTracks
	DWORD64 traxv_call; //vehicleTracks_first call
	DWORD64 traxvt; //vehicleTrackTypes
	UINT8 original1[14];
	UINT8 original2[15];
	void EnableSnow(bool bEnable);
	void EnableTracks(bool tracksPed, bool deepTracksPed, bool tracksVehicle, bool deepTracksVehicle);
public:
	SpSnow();
	bool IsSnow();
	void ToggleSnow(bool bEnable);
	void Tick();
};
extern SpSnow _SpSnow;

class GeneralGlobalHax final
{
public:
	static void DisableAnnoyingRecordingUI(bool uSure);
	static void EnableBlockedMpVehiclesInSp();

	static void** WorldPtrPtr();
	static float GetPlayerHeight();
	static void SetPlayerHeight(float value);
	static float GetPlayerSwimSpeed();
	static void SetPlayerSwimSpeed(float value);
	static float GetPlayerMovementSpeed();
	static void SetPlayerMovementSpeed(float value);

	static int GetVehicleBoostState();
	static void SetVehicleBoostState(int value);
	static float* GetVehicleBoostChargePtr();

};

void setupHooks();
void removeHooks();





