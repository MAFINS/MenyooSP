/* Copyright(c) 2014 Bas Timmer / NTAuthority et al.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "Hooking.h"

// Size of each memory block. (= page size of VirtualAlloc)
const uint64_t MEMORY_BLOCK_SIZE = 0x1000;

// Max range for seeking a memory block. (= 1024MB)
const uint64_t MAX_MEMORY_RANGE = 0x40000000;

void * HookManager::AllocateFunctionStub(void *origin, void *function, int type)
{
    static void* g_currentStub = nullptr;

    if (!g_currentStub) {
        ULONG_PTR minAddr;
        ULONG_PTR maxAddr;

        SYSTEM_INFO si;
        GetSystemInfo(&si);
        minAddr = (ULONG_PTR)si.lpMinimumApplicationAddress;
        maxAddr = (ULONG_PTR)si.lpMaximumApplicationAddress;

        if ((ULONG_PTR)origin > MAX_MEMORY_RANGE &&
            minAddr < (ULONG_PTR)origin - MAX_MEMORY_RANGE)
            minAddr = (ULONG_PTR)origin - MAX_MEMORY_RANGE;

        if (maxAddr >(ULONG_PTR)origin + MAX_MEMORY_RANGE)
            maxAddr = (ULONG_PTR)origin + MAX_MEMORY_RANGE;

        LPVOID pAlloc = origin;

        while ((ULONG_PTR)pAlloc >= minAddr) {
            pAlloc = FindPrevFreeRegion(pAlloc, (LPVOID)minAddr,
                si.dwAllocationGranularity);
            if (pAlloc == NULL)
                break;

            g_currentStub =
                VirtualAlloc(pAlloc, MEMORY_BLOCK_SIZE, MEM_COMMIT | MEM_RESERVE,
                    PAGE_EXECUTE_READWRITE);
            if (g_currentStub != NULL)
                break;
        }
    }
    if (!g_currentStub)
        return nullptr;

    char* code = (char*)g_currentStub;

    *(uint8_t*)code = 0x48;
    *(uint8_t*)(code + 1) = 0xb8 | type;

    *(uint64_t*)(code + 2) = (uint64_t)function;

    *(uint16_t*)(code + 10) = 0xE0FF | (type << 8);

    *(uint64_t*)(code + 12) = 0xCCCCCCCCCCCCCCCC;

    g_currentStub = (void*)((uint64_t)g_currentStub + 20);

    return code;
}

LPVOID HookManager::FindPrevFreeRegion(LPVOID pAddress,
    LPVOID pMinAddr,
    DWORD dwAllocationGranularity) {
    ULONG_PTR tryAddr = (ULONG_PTR)pAddress;

    // Round down to the next allocation granularity.
    tryAddr -= tryAddr % dwAllocationGranularity;

    // Start from the previous allocation granularity multiply.
    tryAddr -= dwAllocationGranularity;

    while (tryAddr >= (ULONG_PTR)pMinAddr) {
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery((LPVOID)tryAddr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) ==
            0)
            break;

        if (mbi.State == MEM_FREE)
            return (LPVOID)tryAddr;

        if ((ULONG_PTR)mbi.AllocationBase < dwAllocationGranularity)
            break;

        tryAddr = (ULONG_PTR)mbi.AllocationBase - dwAllocationGranularity;
    }

    return NULL;
}