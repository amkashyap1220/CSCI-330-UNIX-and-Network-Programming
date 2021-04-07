#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char * argv[])
{
    // Lookup FQDN
    struct addrinfo *res;
    int error = getaddrinfo(argv[1], nullptr, nullptr, &res);
    if (error)
    {
        cerr << argv[1] << ": " << gai_strerror(error) << endl;
        exit(1);
    }

    char buffer[256];
    int echolen, received = 0;

    int sock;
    struct sockaddr_in echoserver; // structure for the address of the server

    // Create the TCP socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Failed to Create socket");
        exit(1);
    }

    // convert generic sockaddr to Internet sockaddr_in
    struct sockaddr_in *addr = (struct sockaddr_in *) res ->ai_addr;

    // Construct the servder sockaddr_in structure
    memset(&echoserver, 0, sizeof(echoserver)); // Clear
    echoserver.sin_family = AF_INET;            // Internet IP
    echoserver.sin_addr = addr->sin_addr;       // IP address
    echoserver.sin_port = htons(atoi(argv[2])); // Server Port

    // Connect to the server
    if (connect(sock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0)
    {
        perror("Cant connect");
        exit(1);
    }

    // Send the message to the server
    echolen = strlen(argv[3]);
    if (write(sock, argv[3], echolen) != echolen)
    {
        perror("missmatch in number of sent bytes");
        exit(1);
    }

    //REceive the message back from the server
    if ((received = read(sock, buffer, 256)) != echolen)
    {
        perror("missmatch in number of received bytes");
        exit(1);
    }
}