
#pragma once

#include <iostream>
#include <cstdlib>

#define MAX_NAME_LENGTH 20

using namespace std;

class Client {
public:
    char *name;
    int id;
    int socket;

public:
    Client();
    void setName(const char *name);
    void setId(int id);
};

