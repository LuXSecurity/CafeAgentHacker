// I am not responsible for any user's damage
//                                  -Lyka

#include <iostream>
#include <string>
#include <tchar.h>
#include <process.h>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

BOOL GetProcessList( );
BOOL TerminateMyProcess( DWORD dwProcessId, UINT uExitCode );

int main( void ) {
 printf( "Coded by -Lyka\n" );
 printf( "(c) LuX Security - 2017" );
 
 GetProcessList( );

 return 0;
}

BOOL GetProcessList( ) {
 HANDLE hProcessSnap;
 HANDLE hProcess;
 PROCESSENTRY32 pe32;
 DWORD dwPriorityClass;

 hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
 if( hProcessSnap == INVALID_HANDLE_VALUE ) {   
  return( FALSE );
 }

 pe32.dwSize = sizeof( PROCESSENTRY32 );

 if( ! Process32First( hProcessSnap, &pe32 ) ) {   
  CloseHandle( hProcessSnap );
  return( FALSE );
 }

  do {  
   string str( pe32.szExeFile );

   if( str == "CafeAgent.exe" ) {
    TerminateMyProcess( pe32.th32ProcessID, 1 );
   } 
  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return( TRUE );
}

BOOL TerminateMyProcess( DWORD dwProcessId, UINT uExitCode ) {
 DWORD dwDesiredAccess = PROCESS_TERMINATE;
 BOOL  bInheritHandle  = FALSE;
 HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
 
 if( hProcess == NULL )
  return FALSE;

 BOOL result = TerminateProcess( hProcess, uExitCode );
 CloseHandle(hProcess);

 return result;
}
