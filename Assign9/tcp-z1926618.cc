/************************************************************
 * @file tcp-z1926618.cc
 * @author Alexander Kashyap (z1926618@students.niu.edu)
 * @version Assign 9
 * @date 2021-04-09
 * CSCI 330 section 1
 ************************************************************/
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

/************************************************************
 * Removes trailing newline or carriage return from string s
 * @param s 
 ************************************************************/
void chomp(char *s)
{
	for (char *p = s + strlen(s) - 1; // start at the end of string
		 *p == '\r' || *p == '\n';	  // while there is a trailing \r or \n
		 p--)						  // check next character from back
		*p = '\0';					  // change \r or \n to \0
}

int main(int argc, char *argv[])
{
	// The user MUST specify port and directory
	if (argc != 3)
	{
		cerr << "error usage: ./z1918266 port directory" << endl;
		exit(1);
	}
	char buffer[257];
    char path[256];
	socklen_t serverlen, clientlen;
	ssize_t received;
	int sock, newSock;
	struct sockaddr_in echoserver; // structure for the address of the server
	struct sockaddr_in echoclient;
	struct stat s;

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
	if (bind(sock, (struct sockaddr *)&echoserver, sizeof(echoserver)) < 0)
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

	if (stat(argv[2], &s) == -1)
	{
		perror("Error in stat");
		exit(1);
	}

	if (!S_ISDIR(s.st_mode))
	{
		perror("Argument must be directory");
		exit(1);
	}

    clientlen = sizeof(echoclient);
	newSock = accept(sock, (struct sockaddr *)&echoclient, &clientlen);
	struct stat path_s;
	// Fork to handle the client (now child)
	int pid = fork();
	if (pid == 0)
	{
		cout << "Client connected: " << inet_ntoa(echoclient.sin_addr) << endl;
		char path[256];
		if ((received = read(newSock, path, sizeof(path))) < 0)
		{
			perror("Failed to reveive message");
			exit(1);
		}
		// Cleaning and formating
		path[received] = '\0';
		chomp(path);
		string st(path);
		char *pathname = strcat(argv[2], st.substr(st.find("/")).c_str());

		// cout << pathname << endl;

		// Check if it exist
		if (stat(pathname, &path_s) != -1)
		{
			// Now, is it a dir?
			if (S_ISDIR(path_s.st_mode))
			{
				// Does this dir contain index.html?
				struct stat indexcheck;
				char buf[1024];
				strcpy(buf, pathname);
				strcat(buf, "/index.html");
				if (stat(buf, &indexcheck) != -1)
				{
					// Print out contents of index.html
					int fd;
					if ((fd = open(buf, O_RDONLY, 0644)) == -1)
					{
						perror("open");
						exit(1);
					}

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
					cout << endl;
					close(fd);
				}
				else
				{
					// print everything from the dir
					DIR *dirp = opendir(pathname);
					if (dirp == 0)
					{
						perror("error opening dir: ");
						exit(1);
					}

					// Getting all directory entry
					struct dirent *dirEntry;
					while ((dirEntry = readdir(dirp)) != NULL)
					{

						if (dirEntry->d_name[0] != '.')
						{
							strcpy(buffer, dirEntry->d_name);
							strcat(buffer, ", ");
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
			else if (S_ISREG(path_s.st_mode))
			{
				// this is a reg file
				// print the contents of the regular file
				int fd;
				if ((fd = open(pathname, O_RDONLY, 0644)) == -1)
				{
					perror("open");
					exit(1);
				}

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
				close(fd);
			}
		}
		else
		{
			// file/dir doesnt exist
			perror("file not found");
			exit(1);
		}
	}
	else
	{
		// Parent
		close(newSock);
	}
	// close connection
	close(sock);
}
