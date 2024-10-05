#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_CONTENT 128


/*
program is called like ./programName 'check' file.txt for now
where 'check' is the string to be searched 
and file.txt is where that string is searched
*/

int main(int argc, char const *argv[])
{
    FILE *fptr;
    int bufferSize = FILE_CONTENT;
    int pos = 0;

    if (argc < 3)
    {
        printf("Arg count less than %d\n", 2);
        exit(0); // exits if arguments are less than 2
    }
    
    fptr = fopen(argv[2],"r");

    if (fptr == NULL) // file doesn't exist
    {
        perror("Mhri's Grep Says Error Opening File");
        return 0;
    }


    char *myString = malloc(sizeof(char) * bufferSize); //allocate space for myString
    if (myString == NULL) //if allocation fails
    {
        perror("Mhri's Grep Says Error Allocating Memory");
        return 0;
    }

    const char *checkString = argv[1];

    
    
    while (fgets(myString,bufferSize,fptr)) // this reads until the first 127 characters
    {
        pos += 1;
        size_t len = strlen(myString);

        /*
        if the end of the myString is not a newline character and
        if the end of the file is not reached
        that means the line still has more characters 
        but we've reached the end i.e len - 1 so the line was truncated 
        it exceeds 127 character
        */
        while (myString[len-1] != '\n' && !feof(fptr))
        {
           bufferSize*=2;//double buffer size
           myString = realloc(myString,bufferSize);
           if (myString == NULL)
           {
           perror("Mhri's Grep Says Error Allocating Memory");
           return 0;
           }
           fgets(myString+len,bufferSize-len,fptr);
           len = strlen(myString);
        }

        //if fgets leaves a newline at the end
        if (myString[len-1] == '\n') 
        {
            //this is needed because it may interfere with subsequent loop calls
            myString[len-1] = '\0'; // replace with endline char
        }

        if (strstr(myString, checkString) != NULL) {
            printf("Found: %s at line %d\n", myString, pos);
        } //print where we found it and at what line
        
    }

    fclose(fptr);
    free(myString);


    return 0;
}