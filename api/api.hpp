#pragma once

#include "Events/Event.h"
#include <vector>
#include <map>

#define _X_ __currentDataPtr

typedef void (*EventHandler)(uint8_t* pack, char* serverName, void* serverPtr, void* current_event_caller, uint8_t** currentDataPtr);
typedef char (*GuardHandler)(uint8_t* pack, char* serverName, void* serverPtr, void* current_event_caller, uint8_t** currentDataPtr);
typedef uint8_t* (*FucntionHandler)(uint8_t* pack, char* serverName, void* serverPtr, void* current_event_caller, uint8_t** currentDataPtr);

void (*__registerEvent)(char* name, void* func);
void (*__registerGuard)(char* name, void* func);
void (*__registerFunction)(char* name, void* func);

void (*__create_event_self)(void* eventGeneratorPtr, char* name, uint8_t* data, long long int msTime, uint8_t** __currentDataPtr);
void (*__create_event_global)(void* eventGeneratorPtr, char* name, uint8_t* data, long long int msTime, uint8_t** __currentDataPtr);
void (*__create_event_self_and_global)(void* eventGeneratorPtr, char* name, uint8_t* data, long long int msTime, uint8_t** __currentDataPtr);

#define create_event_self(...) __macrocall_create_event_self(__current_event_caller, __currentDataPtr, ##__VA_ARGS__);

#define create_event_global(...) __macrocall_create_event_global(__current_event_caller, __currentDataPtr, ##__VA_ARGS__);

#define create_event_self_and_global(...) __macrocall_create_event_self_and_global(__current_event_caller, __currentDataPtr, ##__VA_ARGS__);



uint8_t* (*__call_function)(void* eventGeneratorPtr, char* name, uint8_t* data, char* serverName, void* serverPtr, uint8_t** __currentDataPtr);

#define call_function(...) __macrocall_call_function(__current_event_caller, __currentDataPtr, server, ##__VA_ARGS__)

EventUnpack __macrocall_call_function(void* ptr, uint8_t** __currentDataPtr, ENetServerRemote server, std::string name, EventUnpack data) {
	return EventUnpack(__call_function(ptr, (char*)name.c_str(), data.getData(), (char*)server.getServerID().c_str(), server.getPtr(), __currentDataPtr));
}


void registerEvent(std::string name, EventHandler handler);
void registerGuard(std::string name, GuardHandler handler);
void registerFunction(std::string name, FucntionHandler handler);

extern void InitModule();

#ifndef MODULE_STORAGE_TYPE
#define MODULE_STORAGE_TYPE int
#warning "Module storage type is undefined, int choosed by default"
#endif

std::vector<MODULE_STORAGE_TYPE*> moduleStorage;

#ifndef PEER_STORAGE_TYPE
#define PEER_STORAGE_TYPE int
#warning "Peer storage type is undefined, int choosed by default"
#endif

std::map<std::string, PEER_STORAGE_TYPE*> peerStorage;

inline int serverIDtoInt(const char* name) {
	int ret = 0;
	int inc = 0;
	while(*name) {
		int retTmp = *(name++);
		if(retTmp>'9') {
			ret += (retTmp-'A')<<inc;
		} else {
			ret += (retTmp-'0')<<inc;
		}
		inc+=4;
	}
	return ret;
}

#define getModuleData() __getModuleData(server.getServerID().c_str())

MODULE_STORAGE_TYPE* __getModuleData(const char* serverID) {
	return moduleStorage[serverIDtoInt(serverID)];
}


PEER_STORAGE_TYPE* getPeerData(std::string peer) {
	return peerStorage[peer];
}

EVENT(__MallocPeer) {
	PEER_STORAGE_TYPE* x = new PEER_STORAGE_TYPE;
	peerStorage.insert(std::pair<std::string, PEER_STORAGE_TYPE*>(pack["peer"], x));
}

EVENT(__DestroyPeer) {
	std::string peer = pack["peer"];
	delete peerStorage[peer];
	peerStorage.erase(peer);
}

int __serverCount = 0;

EVENT(__MallocServer) {
	MODULE_STORAGE_TYPE* x = new MODULE_STORAGE_TYPE;
	moduleStorage.push_back(x);
	__serverCount++;
}

struct ServerData { // add variables under existing ones, so compatibility isn't broken
	char* serverUrl;
	int serverPort;
};

#define serverData ((ServerData*)server.getData())

#include "api.cpp"
