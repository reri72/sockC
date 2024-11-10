#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "sockC.h"
#include "sockTcp.h"

int CreateTcpSock()
{
    int sockfd = -1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Tcp socket create failed \n");
        return -1;
    }

    return sockfd;
}

int TcpServerProcess(int sockfd, unsigned short port, char *svrip)
{
    int ret = FAILED;
    struct sockaddr_in server_addr, client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(svrip); // INADDR_ANY;
    server_addr.sin_port = htons(port);

    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == FAILED)
    {
        printf("server sock bind failed \n");
        close(sockfd);
        return ret;
    }

    ret = listen(sockfd, BACKLOG);
    if (ret == FAILED)
    {
        // printf("server sock listen failed \n");
        perror("server sock listen failed \n");
        close(sockfd);
        return ret;
    }

    return SUCCESS;
}

int TcpClientProcess(int sockfd, unsigned short port, char *svrip)
{
    int ret = -1;
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    ret = inet_pton(AF_INET, svrip, &serv_addr.sin_addr);
    if (ret < SUCCESS)
    {
        printf("server ip setting failed \n");
        close(sockfd);
        return FAILED;
    }

    ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < SUCCESS)
    {
        printf("server ip setting failed \n");
        close(sockfd);
        return FAILED;
    }

    return SUCCESS;
}