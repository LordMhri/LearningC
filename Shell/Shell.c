#include <stdio.h> // for EOF
#include <unistd.h> // for execvp function
#include <sys/wait.h> // for system wait datatypes and functions
#include <stdlib.h> // for free,malloc and realloc
#include <string.h> //for strtok


void shell_loop_run(void);
char *shell_line_read(void);
char **shell_parse_line(char *line);
int shell_execute(char **args);

#define READ_LINE_BLOCK_SIZE 512 //inital size of a line
#define TOKEN_BUFFER_SIZE 64     // initial size of a string ( token )
#define DELIMITERS " \n\t\r\a"   // delimiters for splitting a string 

int main(int argc, char const *argv[])
{
    shell_loop_run();

    return 0;
}


void shell_loop_run() {
    char *line;     // this points to the line containing the command (essentially a string)
    char **args;    // this holds the words separated by whitespace (essentially an array of string)
    int status = 1; // status flag from executing commands, set to 1 to make sure loop runs

    while (status)
    {
        printf("lordmhri's shell> "); //printed at the start of each command
        line = shell_line_read(); 
        args = shell_parse_line(line);
        status = shell_execute(args);

        free(line);
        free(args);

    }
    
}


char *shell_line_read(){
    int bufferSize = READ_LINE_BLOCK_SIZE;
    int pos = 0; //keep track of position so we don't exceed block size
    char *buffer = malloc(sizeof(char) * bufferSize);//allocate memory for the input line
    int checker;                                     // checks for EOF

    while (1)
    {
        checker = getchar();
        // if checker gets to EOF or if the last input is '\n', replace with null char and return
        if (checker == EOF || checker == '\n') 
        {
            buffer[pos] = '\0';
            return buffer;
        } else {
            buffer[pos] = checker;
        }
        pos += 1;

        if (pos >= bufferSize) // if we exceed buffersize, allocate more memory
        {
            bufferSize += READ_LINE_BLOCK_SIZE;
            buffer = realloc(buffer, bufferSize);
        }
        
    }  
}


char **shell_parse_line(char *line){
    //identify delimiters
    int bufferSize = TOKEN_BUFFER_SIZE;
    int pos = 0; //keep track of position for tokens
    char **tokens = malloc(sizeof(char *) * bufferSize); // array of tokens
    char *token; //one string

    //tokenize using strtok()
    token = strtok(line, DELIMITERS); //strtok takes a string and splits it

    while (token != NULL) // while we haven't reached the end
    {
        tokens[pos] = token;
        pos += 1;

        if (pos >= bufferSize) // check if pos exceeds bufferSize and allocate more memory
        {
            bufferSize += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, sizeof(char *) * bufferSize);
        }
        token = strtok(NULL, DELIMITERS); // continues from the string where we left off
       
    }
    tokens[pos] = NULL; //reached end of array , valuable for the other functions

    return tokens;

}

int shell_cd(char ** args) {
    if (args[0] == NULL) //no arguments were passed to the cd command, cd *blank*
    {
        fprintf(stderr, " shell, expected argument to  \"cd\"\n"); //fprintf prints the string given to the error stream stderr
    } else {
        //chdir attemps to change cd to the next string given
        //if chdir returns anything other than zero,it means an error has occurred
        //so it prints out an error
        if (chdir(args[1]) != 0) 
        {
            perror("shell");
        }
    }
    
    return 1;
}


int shell_execute(char **args) {
    if (args[0] == NULL) //empty command
    {
        return 1;
    }


    if (strcmp(args[0],"cd") == 0) //strcmp compares two strings, if they're the same returns 0
    {
        return shell_cd(args); //executes the command
    } else if (strcmp(args[0], "exit") == 0) { 
        return 0;
    } 
    
    __pid_t pid, wpid; //process identifers 

    int status;

    pid = fork(); // duplicating an existing process

    if (pid == 0) // child process if pid = 0, if pid > 0 child running in parent and -1 if error
    {
        //execvp is used to run another process inside a C program
        if (execvp(args[0],args )  == -1 ) // in my case a command extracted from user
        {
           perror("Error in shell command execution");
        }
        _exit(0);
    } else if (pid  == -1) {
        perror("Error creating Fork");
    } else {
        do
        {
            wpid = waitpid(pid, &status,WUNTRACED); //wait for child to change state
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // continue until child is terminated or exits
        
    }
    return 1;
   
}