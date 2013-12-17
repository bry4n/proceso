#include <ruby.h>
#include <unistd.h>

#if defined(__linux__)
#include "linux_utility.h"
#elif defined(__APPLE__)
#include "osx_utility.h"
#endif

#define PROCESS_RSS 0
#define PROCESS_VMS 1

int iv2pid(VALUE self);