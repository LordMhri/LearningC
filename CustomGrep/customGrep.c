#include <stdio.h>
#include <stdlib.h>

#define FILE_CONTENT 128


int main(int argc, char const *argv[])
{
    FILE *fptr;
    int fileSize = FILE_CONTENT;
    int pos = 0;

    fptr = fopen("check.txt","r");

    char *myString = malloc(sizeof(char) * fileSize);


    while (fgets(myString,fileSize,fptr))
    {
        pos += 1;
        if (pos >= fileSize)
        {
            fileSize += FILE_CONTENT;
            myString = realloc(myString,fileSize);
            
        }

        printf("content : %s", myString);

    }


    return 0;
}