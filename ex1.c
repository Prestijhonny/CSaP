#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

static int counter = 0;

int searchDirRec(const char *startDir){
    struct dirent *dirent;
    DIR * dir = opendir(startDir);
    char destString[1024];
    if (dir == NULL){
        //printf("Error to open dir %s\n",startDir);
        return -1;
    }
    while ((dirent = readdir(dir)) != NULL){
        if (dirent->d_type == DT_REG ){ // Regualar file
            counter++;
            printf("Filename: %s\n", dirent->d_name);
        }else if (dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0){ // Regular directory
            printf("Directory: %s\n", dirent->d_name);
            strcpy(destString, startDir);
            strcat(destString, "/");
            strcat(destString, dirent->d_name);
            searchDirRec(destString);
        }
    }
    closedir(dir);
    return 0;
}

int main()
{
    const char *folder = "/";
    searchDirRec(folder);
    printf ("Number of file counted on system %d\n", counter);

}