/**
 * @file pipes.cpp
 * @author Alexander Kashyap (z1926618@students.niu.edu)
 * @date 2021-02-18
 * 
 * Assignment 6
 * Course: CSCI 330
 * Section: 1
 */
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

// Max sizes for the c strings and array
#define MAXCMDSIZE 256
#define MAXARGCOUNT 6

using namespace std;

// Function Prototype
void fillargv(char *cmd, char *argv[]);

/**
 * @brief The purpose of the program is to simulate what command1 | command2 will do using the fork pipe and dup system calls
 * 
 * @return int exit code
 */
int main()
{
    // Defining the array to hold up to 255 chars + 1 \0, and defining each cmds argv
    char cmd1[MAXCMDSIZE], cmd2[MAXCMDSIZE];
    char *argv1[MAXARGCOUNT], *argv2[MAXARGCOUNT];

    // Initializing the pipe and essentially variables to hold return status's of system calls to error check with later
    int pipefd[2], rs = 0, status = 0;
    pid_t pid;

    // Get the first command and call the argv processing function
    cout << "command 1? ";
    cin.getline(cmd1, MAXCMDSIZE);
    fillargv(cmd1, argv1);

    // Get the 2nd command and call the argv processing function
    cout << "command 2? ";
    cin.getline(cmd2, MAXCMDSIZE);
    fillargv(cmd2, argv2);

    // Main logic loop, loops until a cmd is "done"
    while (strcmp(cmd1, "done") != 0 && strcmp(cmd2, "done") != 0)
    {
        // Duplicate off to a child
        pid = fork();
        if (pid == -1) // Failure in fork
        {
            perror("fork");
            exit(1);
        }

        /**
         * The first child, 
         * this child serves a purpose to make a grandchild, it then (along with the grandchild) will be morfed
         * into the two commands that were inputed
         */
        if (pid == 0) // "If we are in the first child process"
        {
            // Now that we are in the child, we create a pipe
            rs = pipe(pipefd);
            if (rs == -1) // Failure in pipe
            {
                perror("pipe");
                exit(1);
            }

            // This child must fork now with its pipe (so we can ensure the main program still runs)
            pid = fork();
            if (pid == -1) // Failure in fork
            {
                perror("fork");
                exit(1);
            }

            if (pid == 0) // "If we are in the child of the child (grandchild)"
            { 
                // Close the write end of the pipe
                close(pipefd[1]);

                // close standard input
                close(0);

                // duplicate read end ofthe pipe into standard input
                dup(pipefd[0]);

                // close the read end of the pipe
                close(pipefd[1]);

                // Run the cmd
                rs = execvp(argv2[0], argv2);
                if (rs == -1) // Failure in exec
                {
                    perror("exec");
                    exit(1);
                }
            }
            else
            {
                // close the read end of the pipe
                close(pipefd[0]);

                // close standard output
                close(1);

                // duplicate write end of the pipe into standard output
                dup(pipefd[1]);

                // close the wrirte end of the pipe
                close(pipefd[1]);

                rs = execvp(argv1[0], argv1);
                if (rs == -1) // Failure in exec
                {
                    perror("exec");
                    exit(1);
                }

                // This parent will wait for the child to finish before it signals its done itself to its own parent
                pid = wait(&status); // not doing anything w the return code of the child stored in status
                if (pid == -1)
                { 
                    perror("wait");
                    exit(1);
                }
            }
        }

        // Waiting for its child (and its child by extention) before it ask for new cmd's again
        pid = wait(&status); // not doing anything w the return code of the child
        if (pid == -1) // Error in wait
        { 
            perror("wait");
            exit(1);
        }

        // getting both commands 1 and 2 acts the same as the initial get, only checking again to loop
        cout << "command 1? ";
        cin.getline(cmd1, MAXCMDSIZE);
        fillargv(cmd1, argv1);

        cout << "command 2? ";
        cin.getline(cmd2, MAXCMDSIZE);
        fillargv(cmd2, argv2);
    }

    // Finished success
    exit(0);
}

/**
 * @brief This function serves to parse the cmd entered and fill a passed argv array with the options given
 * 
 * @param cmd cmd that needed to be parsed
 * @param argv argv array that will be filled with the arguments
 */
void fillargv(char *cmd, char *argv[])
{
    int count = 0;

    // Using strtok with " " as a delimeter
    char *token = strtok(cmd, " ");
    argv[0] = token;

    // Loop until no more
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        argv[++count] = token;
    }
}