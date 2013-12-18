#define PROCESS_RSS 0
#define PROCESS_VMS 1
#define FCPU_USR 0
#define FCPU_SYS 1

#include <ruby.h>
#include <unistd.h>
#include <ruby.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <signal.h>

#if defined(__APPLE__)
#  include <mach/mach.h>
#  include <libproc.h>
#endif

#include "utility.h"