#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void caesarCipher(char str[])
{
}
void binary(char str[])
{
}
void hex(char str[])
{
}
void rotation(char str[])
{
}

// /**
//  * This method concatenate files or standard input to standard output
//  * @param fd file destination
//  */
// void cat(int fd, int buffer_size = 256) {
//     char buffer[buffer_size];
//     ssize_t number_read;

//     number_read = read(fd, buffer, 100);
//     while (number_read != 0) {
//         if(number_read == -1) {
//             perror("read");
//             exit(3);
//         }
//         //buffer[number_read] = '\0';
//         write(1, buffer, number_read);
//         number_read = read(fd, buffer, 100);
//     }
// }

// void catonly(int fd, ssize_t howmuch)
// {
//     char buffer[howmuch];
//     ssize_t number_read;

//     number_read = read(fd, buffer, howmuch);
//     if(number_read == -1) {
//         perror("read");
//         exit(1);
//     }
//     write(1, buffer, number_read);
// }