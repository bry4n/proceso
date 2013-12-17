#ifndef PROCESO_NATIVE
#define PROCESO_NATIVE

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


int iv2pid(VALUE self);

#if defined(__linux__)
#  include "platform/linux.h"
#elif defined(__APPLE__)
#  include <mach/mach.h>
#  include <libproc.h>
#  include "platform/osx.h"
#endif

#endif