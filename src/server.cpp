#include "server.h"

using namespace std;

vector<Client> Server::clients;

Server::Server() {
    Threading::initMutex();
    int success = 1;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddress, 0, sizeof(sockaddr_in));

    serverAddress.sin_family        = AF_INET;
    serverAddress.sin_addr.s_addr   = INADDR_ANY;
    serverAddress.sin_port          = htons(PORT);

    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &success, sizeof(int));

    if(bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(sockaddr_in)) < 0)
        cerr << "Failed to bind socket";

    listen(serverSocket, 5);
}

void Server::Accept() {
    Client      *client;
    Threading   *thread;

    socklen_t clientSize = sizeof(sockaddr_in);

    while(1) {
        client = new Client();
        thread = new Threading();


        client->socket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientSize);

        if(client->socket < 0)
            cerr << "Client unable to accept";
        else
            thread->Create((void *)Server::AcceptHandler, client);
    }
}

void *Server::AcceptHandler(void *args) {
    Client *client = (Client *)args;
    char buffer[(256-25)], message[256];
    int index, received;

    Threading::lockMutex((const char *)client->name);

    client->setId((int)Server::clients.size());
    sprintf(buffer, "Client n.%d", client->id);

    client->setName(buffer);
    Server::clients.push_back(*client);

    Threading::unlockMutex((const char *)client->name);

    while(1) {
        memset(buffer, 0, sizeof buffer);

        received = recv(client->socket, buffer, sizeof buffer, 0);

        if(received == 0) {
            close(client->socket);

            Threading::lockMutex((const char *)client->name);

            index = Server::clientIndex(client);
            Server::clients.erase(Server::clients.begin() + index);

            Threading::unlockMutex((const char *)client->name);

            break;
        }
        else if(received < 0) {
            cerr << "Error receiving message from " << client->name << endl;
        }
        else {
            snprintf(message, sizeof message, "%s :: %s", client->name, buffer);

            Server::Broadcast(message);
        }
    }

    return NULL;
}

void Server::Broadcast(char *message) {
    int sending;

    Threading::lockMutex("'Broadcast()'");

    for(size_t index = 0; index < clients.size(); index++)
        sending = send(Server::clients[index].socket, message, strlen(message), 0);

    Threading::unlockMutex("'Broadcast()'");
}

void Server::ClientList() {
    for(size_t index = 0; index < clients.size(); index++)
        cout << clients.at(index).name << endl;
}

int Server::clientIndex(Client *client) {
    for(size_t index = 0; index < clients.size(); index++)
        if((Server::clients[index].id) == client->id)
            return (int)index;

    cerr << "Client not found" << endl;

    return -1;
}





