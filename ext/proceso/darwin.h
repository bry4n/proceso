#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <signal.h>

#if defined(__APPLE__)
#  include <mach/mach.h>
#  include <libproc.h>
#endif


int rb_sysctl_kern_argmax();
int rb_sysctl_kern_procargs2(int pid, char **process_name, int argmax, size_t buf_size);
int rb_process_info(int pid, int flavor, void *pti, int size);
int * rb_process_list();
