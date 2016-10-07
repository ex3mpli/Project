#include <windows.h>
#include <process.h>

#define DllExport   __declspec(dllexport)
#define WallArray   0x467F74


int wall = 0; int cghost = 0; int wm4a1 = 1;

bool Game()
{
  if(GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("Clientfx.fxd") != NULL)
  return  true;
  return  false;
}

void Exempli(void)
{
  DWORD cshell  = (DWORD)GetModuleHandleW(L"CShell.dll");
  DWORD m4a1    = *(DWORD*)((*(DWORD*)(CShell+WeaponMgr))+(4*11));
  DWORD m4a1v   = *(DWORD*)((*(DWORD*)(CShell+WeaponMgr))+(4*856));
  DWORD Wall    = *(DWORD*)(WallArray + 0xA);
  
  if(wm4a1)
  {
    for(int i = 1; i < 1802; ++i)
    {
      *(DWORD*)(m4a1 + i) = *(DWORD)(m4a1v + i);
    }
  }
  
  if(GetAsyncKeyState(VK_F2) &1) wall=!wall;
  if(wall)
    memcpy((void*)(Wall + 0xA4), "\x01\x01\x01\x01", 4);
  else
    memcpy((void*)(Wall + 0xA4), "\x00\x00\x00\x00", 4);
  
  if(GetAsyncKeyState(VK_F3) &1) cghost=!cghost;
  if(cghost)
    *(DWORD*)(Wall + 0xB8) = 5;
  else
    *(DWORD*)(Wall + 0xB8) = 14;
}

void start(void)
{
  while(!Game()) Sleep(200);
  while(1)
  {
    Exempli();
  }
}

extern "C" DllExport BOOLEAN APIENTRY DllMain( IN HINSTANCE hDllHandle, IN DWORD fwdReason, IN LPVOID lpReserved )
{
  BOOLEAN bSuccess = TRUE;
  switch( fwdReason )
  {
    case DLL_PROCESS_ATTACH:
    DisableThreadLibraryCalls( hDllHandle );
	  MessageBoxA(NULL,"RAML\n\tPUBLIC HACK", "Made by: Chain",NULL MB_OK);
	  CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)start, NULL, NULL, NULL);
    break;
  }
  return bSuccess;
}
