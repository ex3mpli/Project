#include <windows.h>
#include <process.h>
#include "class.h"

#define DllExport   __declspec(dllexport)
#define address   0x467F74

BOOL project::myProject(DWORD cshell, DWORD clientfx)
{
  cshell = (GetModulehandleW(L"CShell.dll") != NULL);
  clientfx = (GetModuleHandleW(L"ClientFx.fxd") != NULL);
  return true;
  return fasle;
}

void project::main(void)
{
  DWORD adres = *(DWORD)(address + 10);
  
  if(GetAsyncKeyState(VK_F2) &1) ady = !ady;
  if(ady)
    memcpy((void*)(adres + 164), "\x01\x01\x01\x01", 4);
  else
    memcpy((void*)(adres + 164), "\x00\x00\x00\x00", 4);

  if(GetAsyncKeyState(VK_F2) &1) dy = !dy;
  if(dy)
    *(DWORD*)(adres + 184) = 5;
  else
    *(DWORD*)(adres + 184) = 14;
}

void project::func(void)
{
  while(!this->myProject())
  Sleep(200);
  while(true)
  {
    this->main();
  }
}

extern "C" DllExport
BOOL WINAPI DllMain( IN HINSTANCE hDllHandle, IN DWORD fwdReason, IN LPVOID lpReserved )
{
  BOOLEAN bSuccess = TRUE;
  
  switch ( fwdReason )
  {
    case DLL_PROCESS_ATTACH:
    DisableThreadLibraryCalls ( hDllHandle );
    _beginthread(NULL,NULL,&this->func,NULL,NULL);
    break;
    
    case DLL_PROCESS_DETACH:
    breack;
    
    case DLL_THREAD_ATTACH:
    breack;
    
    case DLL_THREAD_DETACH:
    break;
  }
  return bSuccess;
}
