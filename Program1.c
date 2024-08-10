// Program statment : 

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

void Count(char Char, char *FileName)
{
    int Line_Count = 0;
    int Word_Count = 0;
    int Character_Count = 0;
    int Handel = 0;
    char Character = '\0';

    if((Handel = open(FileName,O_RDONLY)) == -1)
    {
        printf("File %s not found\n",FileName);
        return;
    }

    while (read(Handel,&Character,1) !=0)
    {
        if(Character == ' ')
        {
            Word_Count ++;
        }
        else if(Character == '\n')
        {
            Line_Count ++;
            Word_Count ++;
        }
        else
        {
            Character_Count ++;
        }
    }    
    close(Handel);

    switch(Character)
    {
        case 'c':
            printf("Total no. of Characters = %d\n",Character_Count);
            break;

        case 'w':
            printf("Total no. of Words = %d\n",Word_Count);
            break;

        case 'l':
            printf("Total no. of Lines = %d\n",Line_Count);
            break;
        default:
            printf("Command not found..!");
    }
}

int main()
{
    char command[80],T1[20],T2[20],T3[20],T4[20];
    int n;
    system("clear");

    while(1)
    {
        printf("MY PROMPT>");
        fflush(stdin);
        fgets(command,80,stdin);
        n = sscanf(command,"%s %s %s %s",T1, T2, T3, T4);

        switch(n)
        {
            case 1: if(fork() == 0)
                    {
                        execlp(T1,T1,NULL);
                        perror(T1);
                    }
                    break;
            
            case 2: if(!fork())
                    {
                        execlp(T1,T1,T2,NULL);
                        perror(T1);
                    }
                    break;

            case 3: if(strcmp(T1,"count") == 0)
                    {
                        Count(T2[0], T3);
                    }
                    else
                    {
                        if(!fork())
                        {
                            execlp(T1,T1,T2,T3, NULL);
                            perror(T1);
                        }
                    }
            case 4 : if(!fork())
            {
                execlp(T1,T1,T2,T3,T4, NULL);
                perror(T1);
            }
        }
    }
}