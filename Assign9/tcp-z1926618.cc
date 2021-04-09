<<<<<<< HEAD
#include <sys/types.h> /* See NOTES */
#include <dirent.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/stat.h>
#include <string>
#include <fcntl.h>

using namespace std;

void chomp(char *s)
{
	for (char *p = s + strlen(s) - 1; // start at the end of string
		 *p == '\r' || *p == '\n';	  // while there is a trailing \r or \n
		 p--)						  // check next character from back
		*p = '\0';					  // change \r or \n to \0
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cerr << "error usage: ./z1918266 port directory" << endl;
		exit(1);
	}
	char buffer[257];
	socklen_t serverlen, clientlen;
	ssize_t received;
	int sock, newSock;
	struct sockaddr_in echoserver; // structure for the address of the server
	struct sockaddr_in echoclient;
	// Create the TCP socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Failed to Create socket");
		exit(1);
	}

	// Construct the servder sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver)); // Clear
	echoserver.sin_family = AF_INET;			// Internet IP
	echoserver.sin_addr.s_addr = INADDR_ANY;	// Any IP address
	echoserver.sin_port = htons(atoi(argv[1])); // Server Port

	// Bind the socket
	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *)&echoserver, serverlen) < 0)
	{
		perror("failed to bind server socket");
		exit(1);
	}

	// listen: make socket passive and set klength of queue
	if (listen(sock, 64) < 0)
	{
		perror("failure in listen");
		exit(1);
	}
	struct stat s;
	if (stat(argv[2], &s) == -1)
	{
		perror("Error in stat");
		exit(1);
	}
	if ((s.st_mode & S_IFMT) != S_IFDIR)
	{
		perror("Argument must be directory");
		exit(1);
	}
	char path[256];

	// Run until cancelled
	clientlen = sizeof(echoclient);
	while (int newSock = accept(sock, (struct sockaddr *)&echoclient, &clientlen) != -1)
	{
		int pid = fork();
		if (pid == 0)
		{
			cerr << "Client connected: " << inet_ntoa(echoclient.sin_addr) << endl;
			char path[256];
			if ((received = read(newSock, path, sizeof(path))) < 0)
			{
				perror("Failed to reveive message");
				exit(1);
			}
			chomp(path);
			string st(path);
			if (stat(strcat(argv[2], st.c_str()), &s) == 0)
			{
				if (s.st_mode & S_IFDIR)
				{
					struct stat indexcheck;
					char buf[1024];
					strcpy(buf, argv[2]);
					strcat(buf, st.c_str());
					strcat(buf, "index.html");
					if (stat(buf, &indexcheck) == 0)
					{
						int fd;
						if ((fd = open(buf, O_RDONLY, 0644)) == -1)
						{
							perror("open");
							exit(1);
						}

						close(fd);
						int number_read;
						while ((number_read = read(fd, buffer, 256)) != 0)
						{
							if (number_read == -1)
							{
								perror("read");
								exit(1);
							}

							if (write(newSock, buffer, number_read) == -1)
							{
								perror("write");
								exit(1);
							}
						}
					}
					else
					{
						DIR *dirp = opendir(strcat(argv[2], st.c_str()));
						if (dirp == 0)
						{
							perror("error opening dir: ");
							exit(1);
						}

						// read directory entries

						struct dirent *dirEntry;
						while ((dirEntry = readdir(dirp)) != NULL)
						{

							if (dirEntry->d_name[0] != '.')
							{
								strcpy(buffer, dirEntry->d_name);
								strcat(buffer, "\n");
								if (write(newSock, buffer, strlen(buffer)) < 0)
								{
									perror("error in write: ");
									exit(1);
								}
							}
						}

						closedir(dirp);
						close(newSock);
						exit(0);
					}
				}
				else if (s.st_mode & S_IFREG)
				{
					int fd;
					if ((fd = open(strcat(argv[2], st.c_str()), O_RDONLY, 0644)) == -1)
					{
						perror("open");
						exit(1);
					}

					close(fd);
					int number_read;
					while ((number_read = read(fd, buffer, 256)) != 0)
					{
						if (number_read == -1)
						{
							perror("read");
							exit(1);
						}

						if (write(newSock, buffer, number_read) == -1)
						{
							perror("write");
							exit(1);
						}
					}
				}
			}
			else
			{
				perror("file not found");
				exit(1);
			}
		}
		else
		{
			close(newSock);
		}
	}
	close(sock);
}
=======

using namespace std;

int main(int argc, char * argv[])
{

}
>>>>>>> 1ddff558acc079fa63030a4426d8b99d2c9575cd
