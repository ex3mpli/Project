#include <windows.h>
#include <process.h>

#define DllExport   __declspec(dllexport)
#define WallArray   0x467F74 //need to update
#define WeaponMgr   0x1A16B2C //need to update
#define Bypass28_3  0x5A1841 //need to update
#define Bypass31_0  0x5A2285 //need to update

typedef struct {
    float damage;
    int orignal;
} BACKUP;

BACKUP Backup[1802]; //Weapon Count should be 1802
bool init = false

int wall = 0; int cghost = 0; int wm4a1 = 1;

bool Game() //we are checking if CShell.dll & Clientfx.fxd are not equal to NULL or 0 
{
  if(GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("Clientfx.fxd") != NULL)
  return  true; //return true if true
  return  false; //return false if false
}

void Exempli(void) //void has no parameter/value
{
  DWORD cshell  = (DWORD)GetModuleHandleW(L"CShell.dll");
  DWORD bypass8 = DWORD(cshell + 0x5A1841);
  DWORD bypass3 = DWORD(cshell + 0x5A2285);
  DWORD m4a1    = *(DWORD*)((*(DWORD*)(cshell+WeaponMgr))+(4*11)); //M4A1
  DWORD m4a1v   = *(DWORD*)((*(DWORD*)(cshell+WeaponMgr))+(4*856)); //M4
  DWORD Wall    = *(DWORD*)(WallArray + 0xA);
  
  if(bypass8!=NULL)
  {
    memcpy((void*)(bypass8), "\xE9\xe3\x01\x00\x00\x90", 6);
  }
  
  if(bypass3!=NULL)
  {
    memcpy((void*)(bypass3), "\xEB\x48",2);
  }
  
  if(!init)
  {
    for(int i = 1; i < 1802; ++i)
    {
      *(DWORD*)(m4a1 + i) = *(DWORD*)(m4a1v + i);
      init = true;
    }
  }
  else
  {
    for(int i = 1; i < 1802; ++i)
    {
      *(DWORD*)(m4a1 + i) = Backup[i].original;
      init = true;
    }
  }
  
  if(GetAsyncKeyState(VK_F2) &1) wall=!wall;
  if(wall)
    memcpy((void*)(Wall + 0xA4), "\x00\x00\x00\x00", 4);
  else
    memcpy((void*)(Wall + 0xA4), "\x01\x01\x01\x01", 4);
  
  if(GetAsyncKeyState(VK_F3) &1) cghost=!cghost;
  if(cghost)
    *(DWORD*)(Wall + 0xB8) = 5;
  else
    *(DWORD*)(Wall + 0xB8) = 14;
}

void start(void) //void has no parameter/value
{
  while(!Game()) Sleep(200); //while game doesn't ready sleep 200
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
		  MessageBoxA(NULL,"YOUR MESSAGE", "YOUR TITLE", MB_OK | MB_ICONEXCLAMATION);
		  CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)start, NULL, NULL, NULL);
      /* _beginthreadex(NULL,NULL,start,NULL,NULL,NULL); */ //required header process.h
    break;
  }
  return Success;
}
