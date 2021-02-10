#ifndef DATAPROCESS_H
#define DATAPROCESS_H

void cat(int fd, int buffer_size = 256);
void catonly(int fd, ssize_t howmuch);

#endif // !DATAPROCESS_H 