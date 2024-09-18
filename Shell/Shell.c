#define READ_LINE_BLOCK_SIZE 512

int main(int argc, char const *argv[])
{
    shell_loop_run();

    return 0;
}


void shell_loop_run(void) {
    char *line; // this points to the line containing the command (essentially a string)
    char **args; // this holds the words separated by whitespace (essentially an array of string)
    int status = 1; // status flag from executing commands, set to 1 to make sure loop runs

    while (status)
    {
        printf("> "); //executes at the start of each command
        line = shell_line_read(); 
        args = shell_parse_line(line);
        status = shell_execute(**args);

        free(line);
        free(args);

    }
    
}

