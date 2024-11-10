#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "sockTcp.h"

int main(int argc, char **argv)
{
    int clisockfd = -1;

    clisockfd = CreateTcpSock();
    if (clisockfd < 0)
    {
        return 1;
    }

    int ret = TcpClientProcess(clisockfd, 1234, "10.0.2.5");
    if (ret == 0)
    {
        char buffer[1024] = {0};
        char *message = "Hello, Server!";
        
        int valread = recv(clisockfd, buffer, 1024, 0);
        if (valread < 0)
        {
            perror("recv failed !!");
        }
        else
        {
            printf("recv from server: %s\n", buffer);
        }

        send(clisockfd, message, strlen(message), 0);
        printf("send to server: %s\n", message);

        close(clisockfd);
    }
    else
    {
        printf("client socket failed \n");
    }

    return 0;
}