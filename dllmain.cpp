// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

void WriteBytes(LPVOID address, const char* bytes, int length)
{
    DWORD origProtect;
    VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &origProtect);
    memcpy(address, bytes, length);
}

void PatchMW2()
{
    const char* main = "main" + (const char)0x00;
    const char* mainshared = "main_shared" + (const char)0x00;
    WriteBytes((LPVOID)0x006ABCC0, main, 5);
    WriteBytes((LPVOID)0x006925E0, mainshared, 12);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PatchMW2, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


