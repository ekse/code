/* Slightly modified version of http://www.circl.lu/pub/tr-12/
*/

#include <stdio.h>
#include <windows.h>

void pause()
{
        int key;
        printf("Press RETURN to continue (attach debugger, wait for breakpoint)");
        key = getchar();
}

int main(int argc, char *argv[])
{
        DWORD NumberOfBytesRead = 0;
        int result = -1;
        HANDLE hFile = NULL;
        void (*buffer)(void);

        if (argc != 2)
        {
            printf("usage: LoadShellcode.exe <filename>\n");
        }

        pause();
        printf("Loading and starting file %s\n", argv[1]);
        hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
        if (hFile == (HANDLE)-1)
        {
                result = GetLastError();
                printf("Error: %d (%s)\n", result, &argv[1]);
        }
        else
        {
                buffer = (void (*)(void))VirtualAlloc(0, 0x100000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                if (buffer && ReadFile(hFile, buffer, 0x100000, &NumberOfBytesRead, NULL))
                {
                        CloseHandle(hFile);
                        __asm int 3
                        buffer();
                        Sleep(-1);
                        result = 0;
                }
                else
                {
                        result = GetLastError();
                }
        }
        printf("Result: %d\n", result);
        return result;
}
