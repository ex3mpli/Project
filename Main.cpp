#include <windows.h>

#define DllExport   __declspec(dllexport)
#define cshell      (DWORD)GetModuleHandleW(L"CShell.dll");
#define clientfx    (DWORD)GetModuleHandleW(L"Clientfx.fxd");
#define WallArray   0x467F74

bool Game()
{
  BOOLEAN success = true; BOOLEAN fail = false;
  cshell    = (GetModuleHandleW(L"CShell.dll") != NULL);
  clientfx  = (GetModuleHandleW(L"Clientfx.fxd") != NULL);
  return  sucess;
  return  fail;
}

void Exempli(DWORD Cshell)
{
  Cshell = (DWORD)GetModuleHandleW(L"CShell.dll");
  DWORD Wall = *(DWORD)(WallArray + 0xA);
  
  int wall, cghost = 0;
  
  if(GetAsyncKeyState(VK_f2) &1) wall=!wall;
  if(wall)
    memcpy((void*)Wall + 0xA4), "\x01\x01\x01\x01", 4;
  else
    memcpy((void*)Wall + 0xA4), "\x00\x00\x00\x00", 4;
  
  if(GetAsyncKeyState(VK_f3) &1) cghost=!cghost;
  if(cghost)
    *(DWORD*)(Wall + 0xB8) = 14;
  else
    *(DWORD*)(Wall + 0xB8) = 5;
}

void start()
{
  DWORD cs = cshell;
  if(cs==NULL)
  {
    Exempli();
  }
}

extern "C" DllExport BOOLEAN APIENTRY DllMain( IN HINSTANCE hDllHandle, IN DWORD fwdReason, IN LPVOID lpReserved )
{
  BOOLEAN bSuccess = TRUE;
  if( fwdReason == DLL_PROCESS_ATTACH )
  {
    DisableThreadLibraryCalls( hDllHandle );
    _beginthread( NULL, NULL, &start, hDllHandle, NULL, NULL );
  }
  return bSuccess;
}
