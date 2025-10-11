#ifndef GAIAILOGIC_H 
#define GAIAILOGIC_H 

#include <string>
#include <cmath>

#if defined(_WIN32)
#define FLOWBRIDGER_DELEGATE_CALLTYPE __declspec(dllimport)
#elif defined(__GNUC__) || defined(__clang__)
#define FLOWBRIDGER_DELEGATE_CALLTYPE __attribute__((visibility("default")))
#else
#define FLOWBRIDGER_DELEGATE_CALLTYPE
#endif

extern "C" FLOWBRIDGER_DELEGATE_CALLTYPE bool initialize_game(const char* language);

extern "C" FLOWBRIDGER_DELEGATE_CALLTYPE bool run_timer();

extern "C" FLOWBRIDGER_DELEGATE_CALLTYPE bool stop_timer();

#endif // GAIAILOGIC_H 