#include <stdio.h>
#include <Ws2tcpip.h>
#include <Winsock2.h>
#include <unistd.h>
#include <string.h>
#define PORT 80

int main(int argc, char const *argv[]) {

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "GET / HTTP/1.0 \n \n";
    char buffer[1024] = {0};

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        int i = WSAGetLastError();
        printf("%d\n", i);
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //struct hostent *remoteHost = gethostbyname("tai.ro");
    //&serv_addr.sin_addr = *(u_long *) remoteHost->h_addr_list[0];

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "89.39.246.32", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        int i = WSAGetLastError();
        printf("%d\n", i);
        return -1;
    }

    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    return 0;
}
