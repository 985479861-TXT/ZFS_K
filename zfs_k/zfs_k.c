#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HI 1
#define ML 20

void banner(){
    printf("______________________________          ____  __.\n");
    printf("\\____    /\\_   _____/   _____/         |    |/ _|\n");
    printf("  /     /  |    __) \\_____  \\   ______ |      <  \n");
    printf(" /     /_  |     \\  /        \\ /_____/ |    |  \\ \n");
    printf("/_______ \\ \\___  / /_______  /         |____|__ \\\n");
    printf("        \\/     \\/          \\/                  \\/\n");
    printf("\t\tBy- 985479861_TXT");
}

void read(){
    char str[ML];  
    char fstr[ML + 10];

    AllocConsole();
    FILE * fpOut = freopen("CONOUT$", "w", stdout);
    FILE * fpIn = freopen("CONIN$", "r", stdin);

    SetConsoleTitleA("ZFS-by-TXT");
    system("color 0A && cls");

    SetForegroundWindow(GetConsoleWindow());

    banner();
    printf("\n>> ");
    if(fgets(str, ML, stdin) == NULL) { // safty measure only(fgets stores in str buff)
        FreeConsole();
        return;
    }

    str[strcspn(str, "\n")] = '\0'; // rm \n with \0(end)
    snprintf(fstr, sizeof(fstr), "zfs %s", str); // format

    if (fpOut){fclose(fpOut);}
    if (fpIn){fclose(fpIn);}
    FreeConsole();

    STARTUPINFOA SI;
    PROCESS_INFORMATION PI;
    ZeroMemory(&SI, sizeof(SI));
    SI.cb = sizeof(SI);
    ZeroMemory(&PI, sizeof(PI));

    if (CreateProcessA(NULL, fstr, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &SI, &PI)){
        WaitForSingleObject(PI.hProcess, INFINITE);
        CloseHandle(PI.hProcess);
        CloseHandle(PI.hThread);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)<%

    if (!RegisterHotKey(NULL, HI, MOD_ALT, 0x53)) {
        return 1;
    }

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == 1){
                read();
            }
        }
    }

    UnregisterHotKey(NULL, HI);
    return 0;
%>

// gcc kpl.c -o zfs_k -mwindows     => compile
// taskkill /f /im zfs_k.exe        => close