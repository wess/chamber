
#include "client.h"

using namespace std;

Client::Client() {
    this->name = (char *) malloc(MAX_NAME_LENGTH + 1);
}

void Client::setName(const char *name) {
    snprintf(this->name, (MAX_NAME_LENGTH + 1), name);
}

void Client::setId(int id) {
    this->id = id;
}