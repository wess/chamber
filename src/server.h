
#pragma once

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include "threading.h"
#include "client.h"

#define PORT 3030

using namespace std;

class Server {
private:
    static vector<Client> clients;

    int serverSocket;

    struct sockaddr_in serverAddress,
                       clientAddress;

    
public:
    Server();
    void Accept();
    static void *AcceptHandler(void *args);

private:
    static void ClientList();
    static void Broadcast(char *message);
    static int clientIndex(Client *client);
};