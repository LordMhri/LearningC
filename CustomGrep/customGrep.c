#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8192


/*
program is called like ./programName 'check' file.txt for now
where 'check' is the string to be searched 
and file.txt is where that string is searched
*/

void searchInFile(const char *filename,const char *pattern){
    FILE * fptr = fopen(filename,"r");

    if (fptr == NULL)
    {
        perror("Mhri's Grep Says Error Opening File");
        return;
    }

    int bufferSize = BUFFER_SIZE;

    char *myString = malloc(sizeof(char) * bufferSize); //allocate space for myString
    if (myString == NULL) //if allocation fails
    {
        perror("Mhri's Grep Says Error Allocating Memory");
        return;
    }

    const char *checkString = pattern;
    size_t checkStringLength = strlen(checkString);

    
    
    while (fgets(myString,bufferSize,fptr)) // this reads until the first BUFFER_SIZE characters - 1
    {
        size_t len = strlen(myString);

        /*
        if the end of the myString is not a newline character and
        if the end of the file is not reached
        that means the line still has more characters 
        but we've reached the end i.e len - 1 so the line was truncated 
        so it exceeds the bufferSize
        */
        while (myString[len-1] != '\n' && !feof(fptr))
        {
           bufferSize*=2;//double buffer size
           myString = realloc(myString,bufferSize);
           if (myString == NULL)
           {
           perror("Mhri's Grep Says Error Allocating Memory");
           return;
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
        
        char * subString = strstr(myString, checkString);
      if ( subString != NULL) { // if substring is found
        char *match = myString;
        char *originalString = myString;  // Save the original pointer

        while ((match = strstr(match,checkString)) != NULL) {
            int matchStartIndex = match - originalString;

            // Print the string before the match
            printf("%.*s", matchStartIndex, originalString);

            // Print the matching part in red
            printf("\e[1;31m%.*s\e[0m", (int)checkStringLength , match);

            // Move past the current match
            match += checkStringLength ;
            originalString = match;
        }

        // Print the rest of the line after the last match
        printf("%s\n", originalString);
        }
        
    }

    fclose(fptr);
    free(myString);
   
}


int main(int argc, char const *argv[])
{

    if (argc < 3)
    {
        printf("Arg count less than %d\n", 2);
        exit(0); // exits if arguments are less than 2
    }
    

   const char *pattern = argv[1];

   for (int i = 2; i < argc; i++)
   {
        printf(" Searching in File: %s\n",argv[i]);
        searchInFile(argv[i],pattern);
   }
   
    return 0;
}