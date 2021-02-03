/**********************************************************
 * CSCI 330         Assignment 4      Spring 2021
 * @author Alexander Kashyap
 * @file a4-z1926618.cc
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
#include <sys/stat.h>
#include <cstring>

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
    // If no arguments are passed
    if (argc == 1)
    {
        printUsage();
        exit(1);
    }

    // Checking to see if the -c option exist
    int cflag = 0;
    int opt;
    while ((opt = getopt(argc, argv, "c:")) != -1)
    {
        switch (opt) 
        {
        case 'c':
            cflag = 1;
            break;
        default: /* Wrong argument  */
            printUsage();
            exit(1);
        }
    }

    // Depending on if cflag is tripped call the secret task function
    // with the parameters
    if (cflag == 1) 
    {
        if (argc != 4) 
        {
            printUsage();
            exit(1);
        }
        performSecretTask(2, argv);
    } 
    else 
    {
        if (argc != 3) 
        {
            printUsage();
            exit(1);
        }
        performSecretTask(1, argv);
    }
    return 0;
}

/**
 * Opens/creates a file, checks permissions, and then writes
 * the secret messege to the file
 * @param argi index of the path argument
 * @param argv array of pointers to chars of arguments
 */
void performSecretTask(int argi, char *argv[])
{
    // Stat struct 
    struct stat filestatus;

    // If the file doesnt exist, create it
    if ((stat(argv[argi], &filestatus) == -1))
    {
        int fd = open(argv[argi], O_CREAT, 0000);
        if (fd == -1)
        {
            perror("open");
            exit(1);
        }
        close(fd);
    }

    // Checking the files permissions (if any exit)
    if (stat(argv[argi], &filestatus) == -1) 
    {
        perror("stat");
        exit(1);
    }

    mode_t &mode = filestatus.st_mode;
    if ((mode & 0777) != 0) // if file has any priv
    {
        cerr << "log is not secure. Ignoring." << endl;
        exit(1);
    }

    // Change the permissions of the file to write
    if (chmod(argv[argi], 0200) == -1) 
    {
        perror("chmod");
        exit(1);
    }

    // Open the file (if -c then trunc)
    int fd = 0;
    if (argi == 1) 
    {
        fd = open(argv[argi], O_WRONLY | O_APPEND);
    } 
    else 
    {
        fd = open(argv[argi], O_WRONLY | O_TRUNC);
    }

    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    // Write the secret messege to the file, followed by a newline
    ssize_t howmany = write(fd, argv[argi + 1], strlen(argv[argi + 1]));
    howmany = write(fd, "\n", 1);
    if (howmany == -1) 
    {
        perror("Write");
        exit(1);
    }

    // Close the file and change the permissions back
    close(fd);
    chmod(argv[argi], 0000);
}

/**
 * Prints the usage of the command
 */
void printUsage() 
{
    cerr << "Usage: seclog [-c] out_file message_string\n"
        << "       where the message_string is appended to file out_file.\n"
        << "       The -c option clears the file before the message is appended" 
        << endl;
}