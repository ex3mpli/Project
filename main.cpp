#include <windows.h>

bool client(DWORD cshell, DWORD clientfx)
{
  BOOLEAN success = true; BOOLEAN failed = false;
  cshell    = (GetModuleHandleW(L"CShell.dll") != NULL);
  clientfx  = (GetModuleHandleW(L"Clientfx.fxd") != NULL);
  return  sucess;
  return  failed;
}

void main(DWORD cshell)
{
  cshell = GetModuleHandleW(L"CShell.dll");
}

void start()
{
  
}

BOOLEAN APIENTRY DllMain( IN HINSTANCE hDllHandle, IN DWORD fwdReason, IN LPVOID lpReserved )
{
  BOOLEAN bSuccess = TRUE;
  
  switch ( fwdReason )
  {
    case DLL_PROCESS_ATTACH:
    DisableThreadLibraryCalls ( hDllHandle );
    _beginthread(NULL,NULL,&start,NULL,NULL,NULL);
    break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    break;
  }
  return bSuccess;
}
