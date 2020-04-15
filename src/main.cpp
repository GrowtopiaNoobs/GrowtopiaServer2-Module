struct ModuleStorage {
	// server dependent variables goes here
};

#define MODULE_STORAGE_TYPE ModuleStorage

struct PeerStorage {
	// peer dependent variables goes here
};

#define PEER_STORAGE_TYPE PeerStorage

#include "../api/api.hpp"

void InitModule() {
	// setup your functions and events here
}
