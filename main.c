#include <windows.h>
#include <tlhelp32.h>

const char LOLCLIENT_EXECUTABLE[] = "lolclient.exe";
const char INGAMECLIENT_EXECUTABLE[] = "league of legends.exe";

void set_lol_priority() {
    HANDLE snapshot;
    PROCESSENTRY32 process;
    int ingameclient_found;
    
    // make process snapshot
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    ingameclient_found = 0;
    
    // try to find the in-game client
    if (Process32First(snapshot, &process)) {
        do {
            if (!_stricmp(process.szExeFile, INGAMECLIENT_EXECUTABLE)) {
                ingameclient_found = 1;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    // try to find lol client and adjust priority
    if (Process32First(snapshot, &process)) {
        do {
            if (!_stricmp(process.szExeFile, LOLCLIENT_EXECUTABLE)) {
                HANDLE lolclient = OpenProcess(PROCESS_SET_INFORMATION, FALSE, process.th32ProcessID);
                
                if (ingameclient_found) {
                    SetPriorityClass(lolclient, IDLE_PRIORITY_CLASS);
                } else {
                    SetPriorityClass(lolclient, NORMAL_PRIORITY_CLASS);
                }
                
                CloseHandle(lolclient);
                
                break;
            }
        } while (Process32Next(snapshot, &process));
    }
    
    CloseHandle(snapshot);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    while (1) {
        set_lol_priority();
        Sleep(1000);
    }

    return 0;
}