

#pragma once

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

class Threading {
public:
    pthread_t identifier;

private:
    static pthread_mutex_t mutex;

public:
    Threading();
    int Create(void *callback, void *args);
    int Join();

    static int initMutex();
    static int lockMutex(const char *identifier);
    static int unlockMutex(const char *identifier);
};




