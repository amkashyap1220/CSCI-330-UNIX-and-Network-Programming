/**********************************************************
 * CSCI 330         Assignment 5      Spring 2021
 * @author Alexander Kashyap
 * @file main.cc
 * Section: 1
 * Date Due: 2/12/2021
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

// Flags and argument values for options
bool sflag, nflag, cflag, rflag, xflag, bflag;
char *svalue; char *nvalue; char *cvalue; char *rvalue;

// Function Prototype
void cat(int fd);
void dog(char str[], int numbers_read);

/**
 * The purpose of this program is to recreate a portion of the cat
 * that also has the functionality to output the data with a caesar cipher, in binary, in hex, normal binary rotation
 * with the option to specify a buffer size and the amount of bytes to read
 * 
 * @param argc number of arguments passed
 * @param argv arugments
 */
int main(int argc, char *argv[])
{
    // Dealing with options, getopt()
    int opt;
    while ((opt = getopt(argc, argv, "s:n:c:r:xb")) != -1)
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

        default: // ERROR Invalid Argument
            cerr << "Invalid Argument" << endl;
            exit(1);
        }
    }

    if (rflag && cflag) // ERROR -r and -c
    { 
        cerr << "Invalid Combination of Arguments -r -c" << endl;
        exit(1);
    }
    else if (bflag && xflag) // ERROR -b and -x
    { 
        cerr << "Invalid Combination of Arguments -b -x" << endl;
        exit(1);
    }

    // Check if no file specified or if argument -
    if (argc == optind || strcmp(argv[optind], "-") == 0)
    {
        // Concatenate from standard input
        cat(0);
    }
    else
    {
        int fd;

        // Loop through each file argument passed
        for (int i = optind; i < argc; i++)
        {
            // Open the file
            if ((fd = open(argv[i], O_RDONLY, 0644)) == -1)
            {
                perror("open");
                exit(1);
            }

            // Concatenate files).
            cat(fd);

            // Clean up
            close(fd);
        }
    }

    exit(0); // Program finished successfully
}

/**
 * This method concatenate to standard output
 * @param fd file descriptor to read from
 */
void cat(int fd)
{
    ssize_t number_read;

    // Creating buffer that will have the file read into
    int buffersize = sflag ? stoi(svalue) : 256; // If -s N, N for buffer size
    char buffer[buffersize];

    if (nflag) // If -n N, only read N bytes 
    {
        // Read
        if ((number_read = read(fd, buffer, stoi(nvalue))) == -1)
        {
            perror("read");
            exit(1);
        }

        // Dog the buffer
        dog(buffer, number_read);
    }
    else
    {
        // Read from file until nothing is left to be read
        while ((number_read = read(fd, buffer, buffersize)) != 0)
        {
            if (number_read == -1)
            {
                perror("read");
                exit(1);
            }

            // Dof the buffer
            dog(buffer, number_read);
        }
    }
}

/**
 * This method checks dog specific data processing options and writes to standard output
 * @param buffer buffer to be manipulated
 * @param number_read how many characters are in the buffer
 */
void dog(char buffer[], int number_read)
{
    // Manipulating the buffer itself
    if (cflag) // -c k, First check if caesars cipher needs to be applied with k shift
    {
        caesarCipher(buffer, number_read, stoi(cvalue));
    }
    else if (rflag) // -r k, check if general binary rotation with k shift
    {
        rotation(buffer, number_read, stoi(rvalue));
    }

    // Checking if output should be normal, -b (binary), or -x (hex)
    if (bflag)
    {
        // Create a empty string that will contain the translated buffer
        char binary[number_read * 8];
        
        // Translate the buffer to binary
        toBinary(buffer, number_read, binary);

        // Write the new string (that has the binary) out
        if (write(1, binary, number_read * 8) == -1)
        {
            perror("write");
            exit(1);
        }
    }
    else if (xflag)
    {
        // Create a empty string that will contain the translated buffer
        char hex[number_read * 2];

        // Translate the buffer to hex
        toHex(buffer, number_read, hex);

        // Write the new string out
        if (write(1, hex, number_read * 2) == -1) 
        {
            perror("write");
            exit(1);
        }
    }
    else
    {
        // Otherwise write the buffer normally like cat
        write(1, buffer, number_read);
    }
    
    // Writing a newline
    if (write(1, "\n", 1) == -1)
    {
        perror("write");
        exit(1);
    }
}