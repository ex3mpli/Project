#include <windows.h>

#define DllExport   __declspec(dllexport)
#define WallArray   0x467F74

bool Game()
{
  if(GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("Clientfx.fxd") != NULL);
  return  true;
  return  false;
}

void Exempli(void)
{
  DWORD cs = cshell;
  DWORD Wall = *(DWORD)(WallArray + 0xA);
  
  int wall, cghost = 0;
  
  if(GetAsyncKeyState(VK_f2) &1) wall=!wall;
  if(wall)
    memcpy((void*)Wall + 0xA4), "\x01\x01\x01\x01", 4;
  else
    memcpy((void*)Wall + 0xA4), "\x00\x00\x00\x00", 4;
  
  if(GetAsyncKeyState(VK_f3) &1) cghost=!cghost;
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
      CreateStealthThread((threadFunc_t)start, NULL);
    break;
  }
  return bSuccess;
}
