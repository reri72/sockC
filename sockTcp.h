#ifndef _SOCKTCP_H_
#define _SOCKTCP_H_

int CreateTcpSock();

int TcpServerProcess(int sockfd, unsigned short port, char *svrip);
int TcpClientProcess(int sockfd, unsigned short port, char *svrip);

#endif