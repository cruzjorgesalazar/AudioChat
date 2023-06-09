#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <unp.h>

#define PORT 8080
#define MAXLINE 100

int main() {
    // Createing server socket
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in servAddr = SocketAddrAny(AF_INET, PORT);
    Bind(sockfd, servAddr);

    // Client address, needed for reply
    sockaddr_in cliAddr;
    socklen_t lenCliAddr;
    mZero(&cliAddr, sizeof(cliAddr));

    // Buffer message
    char* buffer = new char[MAXLINE];
    std::cout << sizeof(buffer) << std::endl;

    // Server cycle
    while (true) {
        int n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (SA*)&cliAddr,
                         &lenCliAddr);
        buffer[n] = '\0';
        char* cliIP = inet_ntoa(cliAddr.sin_addr);
        printf("client IP: %s\n", cliIP);
        printf("client msg: %s\n", buffer);

        sendto(sockfd, buffer, n, MSG_CONFIRM, (SA*)&cliAddr, lenCliAddr);
    }

    return 0;
}