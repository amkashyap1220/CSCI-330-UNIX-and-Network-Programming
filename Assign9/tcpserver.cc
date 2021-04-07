#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
 #include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char * argv[])
{
    int sock;
    struct sockaddr_in echoserver; // structure for the address of the server
    // Create the TCP socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Failed to Create socket");
        exit(1);
    }

    // Construct the servder sockaddr_in structure
    memset(&echoserver, 0, sizeof(echoserver)); // Clear
    echoserver.sin_family = AF_INET;            // Internet IP
    echoserver.sin_addr.s_addr = INADDR_ANY;    // Any IP address
    echoserver.sin_port = htons(atoi(argv[1])); // Server Port

    // Bind the socket
    int serverlen = sizeof(echoserver);
    if (bind(sock, (struct sockaddr *) &echoserver, serverlen)<0)
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

    struct sockaddr_in echoclient;
    socklen_t clientlen = 0; 
    int received;
    char buffer[256];
    // Run until cancelled
    while (int newSock=accept(sock, (struct sockaddr *) &echoclient, &clientlen))
    {
        // Read a message from the client
        if ((received = read(newSock, buffer, 256)) < 0)
        {
            perror("Failed to reveive message");
            exit(1);
        }
        cerr << "Client connected: " << inet_ntoa(echoclient.sin_addr) << endl;

        //write the message back to the client
        if(write(newSock, buffer ,received) != received)
        {
            perror("missmatch in number of echo's bytes");
            exit(1);
        }        
        close(newSock);
    }
}