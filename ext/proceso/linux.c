#if defined(__linux) || defined(__LINUX__) || defined(__linux__)

#include "linux.h"

int rb_proc_stat(int pid, struct proc_pid_stat *stat) {
  char buf[256];
  const char *format = "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu %llu";
  FILE *proc;
  int ret;
  sprintf(buf,"/proc/%d/stat",pid);
  proc = fopen(buf,"r");
  if (proc) {
    ret = fscanf(proc, format,  &stat->pid, stat->comm, &stat->state, &stat->ppid,
                                  &stat->pgrp, &stat->session, &stat->tty_nr, &stat->tpgid,
                                  &stat->flags, &stat->minflt, &stat->cminflt, &stat->majflt,
                                  &stat->cmajflt, &stat->utime, &stat->stime, &stat->cutime,
                                  &stat->cstime, &stat->priority, &stat->nice, &stat->num_threads,
                                  &stat->itrealvalue, &stat->starttime, &stat->vsize, &stat->rss,
                                  &stat->rlim, &stat->startcode, &stat->endcode, &stat->startstack,
                                  &stat->kstkesp, &stat->kstkeip, &stat->signal, &stat->blocked,
                                  &stat->sigignore, &stat->sigcatch, &stat->wchan, &stat->nswap,
                                  &stat->cnswap, &stat->exit_signal, &stat->processor,
                                  &stat->rt_priority, &stat->policy, &stat->delayacct_blkio_ticks);
    if (ret == 42) {
      fclose(proc);
      return 1;
    } else {
      fclose(proc);
      return 0;
    }
  } else {
    return 0;
  }
}
#endif