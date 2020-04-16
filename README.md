# GrowtopiaServer2-Module [![Build status](https://ci.appveyor.com/api/projects/status/ev5y2qr1fg2gbdg6?svg=true)](https://ci.appveyor.com/project/GrowtopiaNoobs/growtopiaserver2-module)

To build module execute command: `g++ -fPIC -shared -rdynamic module_name.cpp -o module_name.so`

## Module development
### Module initialization
To initialize module, your module needs to contain function `void InitModule()`, which should perform setup of your module and also bind events, guards and function. Please keep in mind that events, guards and functions can be binded only when all server threads (except the one which performs binding) are stoped.
```C++
void InitModule() {
	std::cout << "We are doing initialization of module here..." << std::endl;
	registerEvent("ExampleEvent", ExampleEvent);
	registerGuard("ExampleEvent", ExampleEventGuard);
	registerFunction("ExampleFunction", ExampleFunction);
}
```
### Events
Events are core compoment of this server. Important features of events are ability of delays, executing events on other servers and allowing use of guards.
```C++
EVENT(ExampleEvent) {
	std::string exampleText = pack["exampleText"];
	std::cout << "Here is some example message from event: " << exampleText << std::endl;
}
```
### Guards
```C++
GUARD(ExampleEventGuard) {
	try {
		std::string exampleText = exampleText = pack["exampleText"];
		return true; // event data contains variable exampleText which is string type, so we let the event execute
	} catch(...) { // event doesn't contain correct data, so we got exception
		std::cout << "ExampleEvent contains bad data" << std::endl;
		return false;
	} 
	std::cout << "Here is some example message from event: " << exampleText << std::endl;
}
```
### Functions
```C++
FUNCTION(ExampleFunction) {
	try {
		std::string exampleText = pack["exampleText"];
		std::cout << "Here is some example message from function: " << exampleText << std::endl;
		EventPack ret(_X_);
		ret["status"] = "success";
		return ret;
	} catch(...) {
		EventPack ret(_X_);
		ret["status"] = "failed";
		return ret;
	}
}
```
### Executing event
```C++
EventPack p(_X_);
p["exampleText"] = "Hello world!";
create_event_self("ExampleEvent", p); // this executes event only on current sever
// or
create_event_global("ExampleEvent", p); // this executes event on all servers, except current server
// or
create_event_self_and_global("ExampleEvent", p); // this executes event on all servers
```
### Executing delayed event
In this example delay of event will be one second.
```C++
EventPack p(_X_);
p["exampleText"] = "Hello world!";
create_event_self("ExampleEvent", p, 1000); // this executes event only on current sever
// or
create_event_global("ExampleEvent", p, 1000); // this executes event on all servers, except current server
// or
create_event_self_and_global("ExampleEvent", p, 1000); // this executes event on all servers
```
### Executing function
```C++
EventPack p(_X_);
p["exampleText"] = "Hello world!";
EventUnpack p2 = call_function("ExampleFunction", p);
std::string status = p2["status"];
std::cout << "Function execution status: " << status << std::endl;
### Peer storage
In all events, functions and guards it is possible to access peer storage. It has to be defined at structure at first, before including `api.hpp`.
Definition of peer storage:
```C++
struct PeerStorage {
	std::string peerName = "empty_name";
};

#define PEER_STORAGE_TYPE PeerStorage
```
Usage of peer storage:
```C++
std::string peer = pack["peer"];
std::cout << "Peer name is: " << getPeerData(peer) << std::endl;
```
### Module (server) storage
Definition of module storage:
```C++
struct ModuleStorage {
	std::string counter = 0;
};

#define MODULE_STORAGE_TYPE ModuleStorage
```
Usage of module storage:
```C++
ModuleStorage* moduleData = getModuleData();
std::cout << "This code was executed " << ++moduleData->counter << " times on current server." << std::endl;
```
### Standard events supplied by server
| Event                  | Parameters |
| ---------------------- | ---------- |
| `OnPlayerConnect`      | peer |
| `OnPlayerActionPacket` | peer, data |
| `OnServerActionPacket` | peer, data |
| `OnTankPacket`         | peer, packetType, netID, plantingTree, characterState, x, y, xSpeed, ySpeed, puchX, punchY, data |
| `ConsoleLog`           | text |
| `OnPlayerDisconnect`   | peer |
### Standard events handled by server
| Event                    | Parameters |
| ------------------------ | ---------- |
| `SendLoginRequestPacket` | peer |
| `SendTankPacket`         | peer, packetType, netID, padding1, characterState, padding2, plantingTree, x, y, XSpeed, YSpeed, padding3, punchX, punchY, data |
| `SendVariantPacket`      | peer, name, 1, 2, 3, ... |
### Example code of whole module
```C++
#include <iostream>

struct ModuleStorage {
	std::string counter = 0;
};

#define MODULE_STORAGE_TYPE ModuleStorage

struct PeerStorage {
	std::string peerName = "empty_name";
};

#define PEER_STORAGE_TYPE PeerStorage

#include "api/api.hpp"

EVENT(ExampleEvent) {
	std::string exampleText = pack["exampleText"];
	std::cout << "Here is some example message from event: " << exampleText << std::endl;
}

GUARD(ExampleEventGuard) {
	try {
		std::string exampleText = exampleText = pack["exampleText"];
		return true; // event data contains variable exampleText which is string type, so we let the event execute
	} catch(...) { // event doesn't contain correct data, so we got exception
		std::cout << "ExampleEvent contains bad data" << std::endl;
		return false;
	} 
	std::cout << "Here is some example message from event: " << exampleText << std::endl;
}

FUNCTION(ExampleFunction) {
	try {
		std::string exampleText = pack["exampleText"];
		std::cout << "Here is some example message from function: " << exampleText << std::endl;
		EventPack ret(_X_);
		ret["status"] = "success";
		return ret;
	} catch(...) {
		EventPack ret(_X_);
		ret["status"] = "failed";
		return ret;
	}
}

EVENT(OnPlayerConnect) {
	EventPack p(_X_);
	p["exampleText"] = "New player has connected!";
	call_function("ExampleFunction", p);
	
	EventPack p(_X_);
	p["exampleText"] = "There was some player, which connected one minute ago.";
	create_event_self("ExampleEvent", p, 60000);

}

void InitModule() {
	std::cout << "We are doing initialization of module here..." << std::endl;
	registerEvent("ExampleEvent", ExampleEvent);
	registerGuard("ExampleEvent", ExampleEventGuard);
	registerFunction("ExampleFunction", ExampleFunction);

	registerEvent("OnPlayerConnect", OnPlayerConnect);
}
```
