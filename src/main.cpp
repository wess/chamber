#include <iostream>
#include "threading.h"
#include "server.h"

using namespace std;

int main() {

	cout << "Running..." << endl;

	Server *server = new Server();
	server->Accept();

	return 0;
}