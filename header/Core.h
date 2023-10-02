#ifdef ENTITY_COMPONENT_SYSTEM_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif // !ENTITY_COMPONENT_SYSTEM_EXPORTS

#include <iostream>
#include <bitset>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#define String std::string


