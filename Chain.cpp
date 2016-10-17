#include <windows.h>

#define DllExport   __declspec(dllexport)
#define WallArray         0x469404  //need to update
#define dwPlayerPointer   0xC857A0
#define DamageZone        0xA02C2C
#define DamagePerSec      0xA02C1C
#define DamagePerMeter    0x1ACB884


typedef struct {
    float damage;
    int original;
} BACKUP;

BACKUP Backup[1802];

int wall = 0; int cghost = 0; int bug = 0;
bool wtw = 0;

bool Game() //we are checking if CShell.dll & Clientfx.fxd are not equal to NULL or 0 
{
  if(GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("Clientfx.fxd") != NULL)
  return  true; //return true if true
  return  false; //return false if false
}

void Exempli(void) //void has no parameter/value
{
  DWORD cshell  = (DWORD)GetModuleHandleA("CShell.dll");
  DWORD dwPlayerPointer = (DWORD*)(CShell + 0xC857A0 + 0x70);
  DWORD ModelN  = *(DWORD*)(cshell + Model);
  DWORD Wall    = *(DWORD*)(WallArray + 0xA);
  PFLOAT wtw1 = *(PFLOAT)( dwPlayerPointer + 0x440);
  PFLOAT wtw2 = *(PFLOAT)( dwPlayerPointer + 0x444);
  PFLOAT wtw3 = *(PFLOAT)( dwPlayerPointer + 0x448);
  DWORD nDamageZone = *(DWORD*)(cshell + 0xA02C2C);
  DWORD nDamagePerSec = *(DWORD*)(cshell + 0xA02C1C);
  DWORD nDamagePerMeter = *(DWORD*)(cshell + 0x1ACB884);
  
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
  
  if(wtw)
  {
    if()
    {
      if(GetAsyncKeyState('V'))
			{
			  if (*wtw1) *wtw1 = 56;
			  if (*wtw2) *wtw2 = 140;
			  if (*wtw3) *wtw3 = 56;
        wtw = true;
			}
    }
    
   if(bug==0)
   {
     if(dwPlayerPointer!=0)
     {
       *(float*)(cshell + 0xA02C2C) = 0.0f;
       *(char*)(cshell + 0xA02C1C) = 'E';
       *(float*)(cshell + 0x1ACB884) = 0.0f;
     }
   }
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
    char message[25] = {'R','A','L','M',' ','P','U','B','L','I','C',' ','H','A','C','K','\0'};
    //MessageBoxA(NULL,"YOUR MESSAGE", "YOUR TITLE", MB_OK | MB_ICONEXCLAMATION);
    CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)start, NULL, NULL, NULL);
    break;
  }
  return Success;
}
