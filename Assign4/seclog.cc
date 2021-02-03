/**********************************************************
 * CSCI 330         Assignment 4      Spring 2021
 * @author Alexander Kashyap
 * @file seclog.cc
 * @version 1.0
 * Section: 1
 * Date Due: 2/5/2021
 * Z-id: z1926618  
 **********************************************************/
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

// Function Prototypes
void performSecretTask(int argi, char *argv[]);
void printUsage();

/**
 * The purpose of this program to take a message as a 
 * command line argument and append that message to the 
 * end of a file
 * 
 * @param argc number of arguments passed
 * @param argv arugments
 */
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printUsage();
        exit(EXIT_FAILURE);
    }

    int cflag = 0;
    int opt;
    
    while ((opt = getopt(argc, argv, "c:")) != -1) {
        switch (opt) {
        case 'c':
            cflag = 1;
            break;
        default: /* Wrong argument  */
            printUsage();
            exit(EXIT_FAILURE);
        }
    }

    if (cflag == 1) {
        performSecretTask(2, argv);
    } else {
        performSecretTask(1, argv);
    }
    return 0;
}

void performSecretTask(int argi, char *argv[])
{
    int fd = open(argv[argi], O_WRONLY | O_CREAT, 0000);
    if (fd == -1)
    {
        perror("open");
        exit(2);
    }
    close(fd);   
}

void printUsage() 
{
    cerr << "Usage: seclog [-c] out_file message_string\n"
        << "       where the message_string is appended to file out_file.\n"
        << "       The -c option clears the file before the message is appended" 
        << endl;
}