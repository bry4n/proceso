#ifndef PROCESO_H

#define PROCSEO_H

#define PROCESS_RSS 0
#define PROCESS_VMS 1
#define FCPU_USR 0
#define FCPU_SYS 1

#include <ruby.h>

#if defined(__APPLE__)
#  include "darwin.h"
#elif defined(__linux) || defined(__linux__) || defined(__LINUX__)
#  include "linux.h"
#endif

#include "utility.h"

#endif // PROCESO_H