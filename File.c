#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

void Count(char Char, char *FileName)
{
    int Line_Count = 0;
    int Word_Count = 0;
    int Character_Count = 0;
    int File_Descrepter = 0;
    char Character = '\0';

    if((File_Descrepter = open(FileName, _O_RDONLY)) == -1)
    {
        printf("File %s not found\n", FileName);
        return;
    }

    while (read(File_Descrepter, &Character, 1) != 0)
    {
        if(Character == ' ')
        {
            Word_Count++;
        }
        else if(Character == '\n')
        {
            Line_Count++;
            Word_Count++;
        }
        else
        {
            Character_Count++;
        }
    }    
    close(File_Descrepter);

    switch(Char)
    {
        case 'c':
            printf("Total no. of Characters = %d\n", Character_Count);
            break;

        case 'w':
            printf("Total no. of Words = %d\n", Word_Count);
            break;

        case 'l':
            printf("Total no. of Lines = %d\n", Line_Count);
            break;

        default:
            printf("Command not found..!");
    }
}

int main()
{
    char command[80], T1[20], T2[20], T3[20], T4[20];
    int n;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    system("cls");

    while(1)
    {
        printf("MY PROMPT>");
        fflush(stdin);
        fgets(command, 80, stdin);
        n = sscanf(command, "%s %s %s %s", T1, T2, T3, T4);

        switch(n)
        {
            case 1:
                if(CreateProcess(NULL, T1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
                {
                    WaitForSingleObject(pi.hProcess, INFINITE);
                    CloseHandle(pi.hProcess);
                    CloseHandle(pi.hThread);
                }
                else
                {
                    printf("Failed to execute command: %s\n", T1);
                }
                break;
            
            case 2:
                if(CreateProcess(NULL, T1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
                {
                    WaitForSingleObject(pi.hProcess, INFINITE);
                    CloseHandle(pi.hProcess);
                    CloseHandle(pi.hThread);
                }
                else
                {
                    printf("Failed to execute command: %s %s\n", T1, T2);
                }
                break;

            case 3:
                if(strcmp(T1, "count") == 0)
                {
                    Count(T2[0], T3);
                }
                else
                {
                    if(CreateProcess(NULL, T1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
                    {
                        WaitForSingleObject(pi.hProcess, INFINITE);
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                    }
                    else
                    {
                        printf("Failed to execute command: %s %s %s\n", T1, T2, T3);
                    }
                }
                break;

            case 4:
                if(CreateProcess(NULL, T1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
                {
                    WaitForSingleObject(pi.hProcess, INFINITE);
                    CloseHandle(pi.hProcess);
                    CloseHandle(pi.hThread);
                }
                else
                {
                    printf("Failed to execute command: %s %s %s %s\n", T1, T2, T3, T4);
                }
                break;

            default:
                printf("Invalid command.\n");
        }
    }
}
