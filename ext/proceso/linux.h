#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <signal.h>

#ifndef __LINUX__
#  define __LINUX__
#endif

struct proc_pid_stat {
    int pid;      // %d
    char comm[256];   // %s
    char state;     // %c
    int ppid;     // %d
    int pgrp;     // %d
    int session;    // %d
    int tty_nr;     // %d
    int tpgid;      // %d
    unsigned long flags;  // %lu
    unsigned long minflt; // %lu
    unsigned long cminflt;  // %lu
    unsigned long majflt; // %lu
    unsigned long cmajflt;  // %lu
    unsigned long utime;  // %lu
    unsigned long stime;  // %lu
    long cutime;    // %ld
    long cstime;    // %ld
    long priority;    // %ld
    long nice;      // %ld
    long num_threads;   // %ld
    long itrealvalue;   // %ld
    unsigned long starttime;  // %lu
    unsigned long vsize;  // %lu
    long rss;     // %ld
    unsigned long rlim;   // %lu
    unsigned long startcode;  // %lu
    unsigned long endcode;  // %lu
    unsigned long startstack; // %lu
    unsigned long kstkesp;  // %lu
    unsigned long kstkeip;  // %lu
    unsigned long signal; // %lu
    unsigned long blocked;  // %lu
    unsigned long sigignore;  // %lu
    unsigned long sigcatch; // %lu
    unsigned long wchan;  // %lu
    unsigned long nswap;  // %lu
    unsigned long cnswap; // %lu
    int exit_signal;    // %d
    int processor;    // %d
    unsigned long rt_priority;  // %lu
    unsigned long policy; // %lu
    unsigned long long delayacct_blkio_ticks; // %llu
};

int rb_proc_ncpu();
int rb_proc_pid_vsize(int pid);
int rb_proc_pid_rss(int pid);
float rb_proc_pid_stime(int pid);
float rb_proc_pid_utime(int pid);
char * rb_proc_pid_cmdline(int pid);
char * rb_proc_pid_name(int pid);
