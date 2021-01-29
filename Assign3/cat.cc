/**********************************************************
 * CSCI 330         Assignment 3      Spring 2021
 * @author Alexander Kashyap
 * @file cat.cc
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

using namespace std;

// Function Prototype
void readandwrite(int fd);

/**
 * The purpose of this program is to recreate a portion of the cat
 * command using some of unix system calls, open,read,write,close
 * 
 * @param argc number of arguments passed
 * @param argv arugments
 */
int main(int argc, char* argv[]) {
    int fd;

    // With no FILE, or when FILE is -, read standard input.
    if (argc == 1 || strcmp(argv[1], "-") == 0) {
        readandwrite(0);

    } else {

        // loop through each argument passed and open
        for (int i = 1; i < argc; i++) {
            fd = open(argv[i], O_RDONLY, 0644);
            if (fd == -1) {
                perror("open");
                exit(2);
            }

            // Concatenate FILE(s) to standard output.
            readandwrite(fd);

            // Clean up
            close(fd);
        }
    }
    
    exit(0);
}

/**
 * This method concatenate files or standard input to standard output
 * @param fd file destination
 */
void readandwrite(int fd) {
    char buffer[256];
    ssize_t number_read;

    number_read = read(fd, buffer, 10);
    while (number_read != 0) {
        buffer[number_read] = '\0';
        if(number_read == -1) {
            perror("read");
            exit(3);
        }
        write(1, buffer, number_read);
        number_read = read(fd, buffer, 10);
    }
}