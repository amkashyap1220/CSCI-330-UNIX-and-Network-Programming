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

// Function Prototype
// void readandwrite(int fd);

/**
 * The purpose of this program is to recreate a portion of the cat
 * command using some of unix system calls, open,read,write,close
 * 
 * @param argc number of arguments passed
 * @param argv arugments
 */
int main(int argc, char* argv[]) {

    // Check options with getopt
    // flag and value 
    bool sflag , nflag, cflag, rflag, xflag, bflag;
    sflag = nflag = cflag = rflag = xflag = bflag = false;
    char* svalue, nvalue, cvalue, rvalue;

    int opt;
    while ((opt = getopt(argc, argv, "s:n:c:r:xb")) != -1) // optarg for argument :
    {
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

    if (rflag && cflag) // -r and -c ERROR
    {
        exit(1);
    }
    else if (bflag && xflag) // -b and -x ERROR
    {
        exit(1);
    }

    // START OF OLD CAT

    int fd;

    // With no FILE, or when FILE is -, read standard in <
    cout << "optind: "<< optind << endl;
    if (argc == optind || strcmp(argv[optind], "-") == 0) {
        char buffer[256];
        ssize_t number_read;

        number_read = read(0, buffer, 100);
        while (number_read != 0) {
            if(number_read == -1) {
                perror("read");
                exit(3);
            }
            //buffer[number_read] = '\0';
            write(1, buffer, number_read);
            number_read = read(0, buffer, 100);
        }
    } else {

        // loop through each argument passed and open
        for (int i = optind; i < argc; i++) {
            fd = open(argv[i], O_RDONLY, 0644);
            if (fd == -1) {
                perror("open");
                exit(1);
            }

            // Concatenate FILE(s) to standard output.
            if (sflag)
            {
                cat(fd, stoi(svalue));
            }
            else if (nflag)
            {
                catonly(fd, stoi(nvalue));
            }
            else
            {
                cat(fd);
            }

            // Clean up
            close(fd);
        }
    }
    
    exit(0);
}

// /**
//  * This method concatenate files or standard input to standard output
//  * @param fd file destination
//  */
// void readandwrite(int fd) {
//     char buffer[256];
//     ssize_t number_read;

//     number_read = read(fd, buffer, 10);
//     while (number_read != 0) {
//         buffer[number_read] = '\0';
//         if(number_read == -1) {
//             perror("read");
//             exit(3);
//         }
//         write(1, buffer, number_read);
//         number_read = read(fd, buffer, 10);
//     }
// }