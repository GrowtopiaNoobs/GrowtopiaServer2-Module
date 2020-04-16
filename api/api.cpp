void registerEvent(std::string name, EventHandler handler) {
	__registerEvent((char*)name.c_str(), (void*)handler);
}

void registerGuard(std::string name, GuardHandler handler) {
	__registerGuard((char*)name.c_str(), (void*)handler);
}

void registerFunction(std::string name, FucntionHandler handler) {
	__registerFunction((char*)name.c_str(), (void*)handler);
}

extern void InitModule();

void __macrocall_create_event_self(void* ptr, uint8_t** __currentDataPtr, std::string name, EventUnpack data, long long int msTime=0) {
	__create_event_self(ptr, (char*)name.c_str(), data.getData(), msTime, __currentDataPtr);
}

void __macrocall_create_event_global(void* ptr, uint8_t** __currentDataPtr, std::string name, EventUnpack data, long long int msTime=0) {
	__create_event_global(ptr, (char*)name.c_str(), data.getData(), msTime, __currentDataPtr);
}

void __macrocall_create_event_self_and_global(void* ptr, uint8_t** __currentDataPtr, std::string name, EventUnpack data, long long int msTime=0) {
	__create_event_self_and_global(ptr, (char*)name.c_str(), data.getData(), msTime, __currentDataPtr);
}

#ifdef _WIN32
#define EXPORT_FUNC_MODIFIER extern "C" __declspec(dllexport) 
#else
#define EXPORT_FUNC_MODIFIER extern "C"
#endif

EXPORT_FUNC_MODIFIER void ModuleExecuteSetup(void* eventRegistrator, void* eventGuardRegistrator, void* functionRegistrator, void* create_event_self__, void* create_event_global__, void* create_event_self_and_global__, void* call_function__) {
	__registerEvent = (void (*)(char*, void*))eventRegistrator;
	__registerGuard = (void (*)(char*, void*))eventGuardRegistrator;
	__registerFunction = (void (*)(char*, void*))functionRegistrator;
	__create_event_self = (void (*)(void*, char*, uint8_t*, long long int, uint8_t**))create_event_self__;
	__create_event_global = (void (*)(void*, char*, uint8_t*, long long int, uint8_t**))create_event_global__;
	__create_event_self_and_global = (void (*)(void*, char*, uint8_t*, long long int, uint8_t**))create_event_self_and_global__;
	__call_function = (uint8_t* (*)(void*, char*, uint8_t*, char*, void*, uint8_t**))call_function__;
	registerEvent("__MallocPeer", __MallocPeer);
	registerEvent("__DestroyPeer", __DestroyPeer);
	registerEvent("__MallocServer", __MallocServer);
	InitModule();
}

EXPORT_FUNC_MODIFIER int ModuleGetVersion(void)
{
	return 1;
}
