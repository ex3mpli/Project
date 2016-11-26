#include <windows.h>
#include <process.h>

#define DllExport   __declspec(dllexport)
#define WallArray       0xB8AFD4  //need to update
#define ModelNode       0x1ACB7D4  //need to update

bool wall, cghost = false;

bool Game() //we are checking if CShell.dll & Clientfx.fxd are not equal to NULL or 0 
{
  if(GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("Clientfx.fxd") != NULL)
  return  true;
  return  false;
}

void Exempli(void) //void has no parameter/value
{
  DWORD cshell    = (DWORD)GetModuleHandleA("CShell.dll");
  DWORD pNodeMgr  = *(DWORD*)(cshell + 0x1ACB7D4);
  DWORD Wall      = *(DWORD*)(WallArray + 0xA);
  
  if(GetAsyncKeyState('T') &1) wall=!wall;
  if(wall)
    memcpy((void*)(Wall + 0xA4), "\x00\x00\x00\x00", 4);
  else
    memcpy((void*)(Wall + 0xA4), "\x01\x01\x01\x01", 4);
  
  if(GetAsyncKeyState('T') &1) cghost=!cghost;
  if(cghost)
    *(DWORD*)(Wall + 0xB8) = 5;
  else
    *(DWORD*)(Wall + 0xB8) = 14;
  if(pNodeMgr != NULL)
  {
    for(int i = 0; i < 87; i++)
    {
      for(int x = 0; x < 3; x++)
      {
        *(float*)((pNodeMgr + 0x38 + x*4 ) + (i*0x9c)) = 250.0f;
      }
    }
  }
  }

void start(void) //void has no parameter/value
{
  while(!Game()) Sleep(200); //while game doesn't ready sleep 200, 200 is equivalent for 2 seconds
  while(1) //while 1 game is ready!
  {
    Exempli();
  }
}

extern "C" DllExport BOOLEAN APIENTRY DllMain( IN HINSTANCE Dll, IN DWORD fwdReason, IN LPVOID lpReserved )
{
  BOOLEAN Success = TRUE;
  switch( fwdReason )
  {
    case DLL_PROCESS_ATTACH:
    DisableThreadLibraryCalls(Dll);
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)Start,0,0,0);
    ShellExecute(0,0,L"RAMLeague.net",0,0,0);
    break;
  }
  return Success;
}
