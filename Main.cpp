#include <windows.h>

#define DllExport   __declspec(dllexport)
#define cshell      (DWORD)GetModuleHandleW(L"CShell.dll");
#define clientfx    (DWORD)GetModuleHandleW(L"Clientfx.fxd");
#define WallArray   0x467F74

bool Game()
{
  BOOLEAN success = true; bool BOOLEAN = false;
  if(GetModuleHandleW(L"CShell.dll") != NULL);
  if(GetModuleHandleW(L"Clientfx.fxd") != NULL);
  return  success;
  return  fail;
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
  DWORD cs = cshell;
  if(cs==NULL)
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
