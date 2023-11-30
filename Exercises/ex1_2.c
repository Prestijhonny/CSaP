// Create a program that reads all file from a root dir
// and count number of files in the dir (Window version)

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

static int counter = 0;

int searchDirRec(const char *startDir)
{
    WIN32_FIND_DATAA FindFileData;
    char destString[MAX_PATH];
    strcpy(destString, startDir);
    strcat(destString, "\\*");
    HANDLE hDir = FindFirstFileA(destString, &FindFileData);
    if (hDir == INVALID_HANDLE_VALUE)
    {
        printf("Error to open dir %s\n", startDir);
        return -1;
    }
    while (FindNextFileA(hDir, &FindFileData) != 0)
    {
        if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0){
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("Directory: %s\n", FindFileData.cFileName);
                char newBasePath[MAX_PATH];
                sprintf(newBasePath, "%s\\%s", startDir, FindFileData.cFileName);
                searchDirRec(newBasePath);
            }
            else if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)){
                counter++;
                printf("File: %s\n", FindFileData.cFileName);
            }
        }
    }
    FindClose(hDir);
    return 0;
}

int main()
{
    char *drives = malloc(sizeof(char)*MAX_PATH);
    DWORD len = GetLogicalDriveStrings(MAX_PATH, drives);

    if (len == 0)
    {
        printf("Error to retrive logical drive information.\n");
        return 1;
    }
    // For each drive, the character is 4 byte  
    for(int i=0;i<len;i+=4){ 
        printf("The search of file/dir start in %c:\\ drive\n", (*drives)++);
        searchDirRec(drives);
        printf("Number of file counted on system %d\n", counter);
    }
    
}