#ifndef _SOCKUTILES_H_
#define _SOCKUTILES_H_

int SockSetLinger(int sockfd);
int SockSetBufferSize(int sockfd);
int SockSetKeepAlive(int sockfd);
int SockSetNoDelay(int sockfd);
int SockSetReUse(int sockfd);

int SockSetNonBlocking(int sockfd);

#endif