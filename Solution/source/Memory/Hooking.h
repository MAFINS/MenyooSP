#pragma once

#include <windows.h>
#include <inttypes.h>

template <typename T>
class Hook
{
public:
    Hook(uintptr_t addr, T func) : address(addr), fn(func) { }
    virtual ~Hook();
    virtual void remove() = 0;
    uintptr_t address;
    T fn;
};

template <typename T>
Hook<T>::~Hook()
{
}

template <typename T>
class CallHook : public Hook<T>
{
public:
    CallHook(uintptr_t addr, T func) : Hook<T>(addr, func) { }
    ~CallHook();
    virtual void remove();
};

template <typename T>
void CallHook<T>::remove()
{
    *reinterpret_cast<int32_t*>(this->address + 1) = static_cast<int32_t>((intptr_t)this->fn - (intptr_t)this->address - 5);
}

template <typename T>
CallHook<T>::~CallHook()
{
    remove();
}

class HookManager
{
public:
    template <typename T>
    static inline CallHook<T> *SetCall(uintptr_t address, T target)
    {
        T orig = reinterpret_cast<T>(*reinterpret_cast<int *>(address + 1) + (address + 5));

        HMODULE hModule = GetModuleHandle(NULL);

        auto pFunc = AllocateFunctionStub((void*)(hModule), (void*)target, 0);

        *reinterpret_cast<BYTE*>(address) = 0xE8;

        *reinterpret_cast<int32_t*>(address + 1) = static_cast<int32_t>((intptr_t)pFunc - (intptr_t)address - 5);

        return new CallHook<T>(address, orig);
    }

    static void *AllocateFunctionStub(void *origin, void *function, int type);

    static LPVOID FindPrevFreeRegion(LPVOID pAddress, LPVOID pMinAddr, DWORD dwAllocationGranularity);
};
