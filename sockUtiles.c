#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#include "sockC.h"

int SockSetLinger(int sockfd)
{
    int ret = FAILED;
    struct linger linger_opt;

    linger_opt.l_onoff  = 1;    //on
    linger_opt.l_linger = 5;    // 5sec

    ret = setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));
    if (ret != SUCCESS)
    {
        perror("Linger option failed.");
        close(sockfd);
        return FAILED;
    }

    return SUCCESS;
}

int SockSetBufferSize(int sockfd)
{
    int ret = FAILED;
    int bufsize = BUFFER_SIZE;

    ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));
    if (ret != SUCCESS)
    {
        perror("Sendbuffer size option failed.");
        close(sockfd);
        return FAILED;
    }

    ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));
    if (ret != SUCCESS)
    {
        perror("Recv buffer size option failed.");
        close(sockfd);
        return FAILED;
    }

    return SUCCESS;
}

int SockSetKeepAlive(int sockfd)
{
    int ret = FAILED;
    int opt = 1;

    ret = setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt));
    if (ret != SUCCESS)
    {
        perror("KeepAlive option failed.");
        close(sockfd);
        return FAILED;
    }

    return SUCCESS;
}

int SockSetNoDelay(int sockfd)
{
    int ret = FAILED;
    int opt = 1;

    ret = setsockopt(sockfd, SOL_SOCKET, TCP_NODELAY, &opt, sizeof(opt));
    if (ret != SUCCESS)
    {
        perror("NoDelay option failed.");
        close(sockfd);
        return FAILED;
    }

    return SUCCESS;
}

int SockSetReUse(int sockfd)
{
    int ret = FAILED;
    int opt = 1;

    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (ret != SUCCESS)
    {
        perror("ReUseAddr option failed.");
        close(sockfd);
        return FAILED;
    }

    return SUCCESS;
}

int SockSetNonBlocking(int sockfd)
{
    int ret = FAILED;
    int flags = -1;

    flags = fcntl(sockfd, F_GETFL, 0);      //get file flag
    if (flags == -1)
    {
        perror("fcntl(get) failed.");
        close(sockfd);
        return FAILED;
    }

    flags |= O_NONBLOCK;

    ret = fcntl(sockfd, F_SETFL, flags);    // set file flag
    if (ret == -1)
    {
        perror("fcntl(set) failed.");
        close(sockfd);
        return FAILED;
    }
    
    return SUCCESS;
}