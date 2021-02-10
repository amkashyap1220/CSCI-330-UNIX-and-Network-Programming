/**********************************************************
 * CSCI 330         Assignment 3      Spring 2021
 * @author Alexander Kashyap
 * @file main.cc
 * @version 1.0
 * Section: 1
 * Date Due: 1/29/2021
 * Z-id: z1926618  
 **********************************************************/
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>

#include "dataprocess.h"

using namespace std;

bool sflag, nflag, cflag, rflag, xflag, bflag;
char *svalue;
char *nvalue;
char *cvalue;
char *rvalue;
// Function Prototype
void cat(int fd);
void dog(char str[]);

/**
 * The purpose of this program is to recreate a portion of the cat
 * command using some of unix system calls, open,read,write,close
 * 
 * @param argc number of arguments passed
 * @param argv arugments
 */
int main(int argc, char *argv[])
{

    // Check options with getopt
    sflag = nflag = cflag = rflag = xflag = bflag = false;

    int opt;
    while ((opt = getopt(argc, argv, "s:n:c:r:xb")) != -1)
    { // optarg for argument :
        switch (opt)
        {
        case 's':
            sflag = true;
            svalue = optarg;
            break;

        case 'n':
            nflag = true;
            nvalue = optarg;
            break;

        case 'c':
            cflag = true;
            cvalue = optarg;
            break;

        case 'r':
            rflag = true;
            rvalue = optarg;
            break;

        case 'x':
            xflag = true;
            break;

        case 'b':
            bflag = true;
            break;

        default: // ERROR NOT CORRECT ARGUMENT
            exit(1);
        }
    }

    if (rflag && cflag)
    { // -r and -c ERROR
        exit(1);
    }
    else if (bflag && xflag)
    { // -b and -x ERROR
        exit(1);
    }

    // With no FILE, or when FILE is -, read standard in <
    if (argc == optind || strcmp(argv[optind], "-") == 0)
    {
        cat(0);
    }
    else
    {
        int fd;
        // loop through each argument passed and open
        for (int i = optind; i < argc; i++)
        {
            fd = open(argv[i], O_RDONLY, 0644);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }

            // Concatenate FILE(s) to standard output.
            cat(fd);
            // Clean up
            close(fd);
        }
    }

    exit(0);
}

void cat(int fd)
{
    int buffersize = 256;
    if (sflag)
    {
        buffersize = stoi(svalue);
    }
    char buffer[buffersize];
    ssize_t number_read;
    if (nflag)
    {
        cout << stoi(nvalue);
        number_read = read(fd, buffer, stoi(nvalue));
        if (number_read == -1)
        {
            perror("read");
            exit(1);
        }
        dog(buffer);
        write(1, buffer, number_read);
    }
    else
    {
        number_read = read(fd, buffer, 100);
        while (number_read != 0)
        {
            if (number_read == -1)
            {
                perror("read");
                exit(1);
            }
            dog(buffer);
            write(1, buffer, number_read);
            number_read = read(fd, buffer, 100);
        }
    }
}

void dog(char str[])
{
    if (cflag)
    {
        }
}
