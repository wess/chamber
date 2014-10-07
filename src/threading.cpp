
#include "threading.h"

using namespace std;

pthread_mutex_t Threading::mutex;

Threading::Threading() {}

int Threading::Create(void *callback, void *args) {
    int tstat   = 0;
    tstat       = pthread_create(&this->identifier, NULL, (void *(*)(void *))callback, args);

    if(tstat) {
        cerr << "Unable to create threads" << endl;
        return tstat;
    }
    else {
        cout << "Thread created." << endl;
        return 0;
    }
}

int Threading::Join() {
    pthread_join(this->identifier, NULL);
    return 0;
}

int Threading::initMutex() {
    if(pthread_mutex_init(&Threading::mutex, NULL) < 0) {
        cerr << "Unable to create threading mutex" << endl;
        return -1;
    }
    else {
        cout << "Mutex created." << endl;
        return 0;
    }
}

int Threading::lockMutex(const char *identifier) {
    return (pthread_mutex_lock(&Threading::mutex) == 0)? 0 : -1;
}

int Threading::unlockMutex(const char *identifier) {
    return (pthread_mutex_unlock(&Threading::mutex) == 0)? 0 : -1;
}



