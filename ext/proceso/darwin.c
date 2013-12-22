#ifdef __APPLE__

#include "darwin.h"

int rb_sysctl_kern_argmax() {
  int ret, argmax;
  int mib[2] = { CTL_KERN, KERN_ARGMAX };
  size_t buf_size = sizeof(argmax);
  ret = sysctl(mib, 2, &argmax, &buf_size, NULL, 0);
  if (ret == 0) {
    return argmax;
  }
  return 0;
}

int rb_sysctl_kern_procargs2(int pid, char **process_name, int argmax, size_t buf_size) {
  int ret, nargs;
  int mib[3] = { CTL_KERN, KERN_PROCARGS, pid };
  char *process;
  process = (char *)malloc(argmax);
  ret = sysctl(mib, 3, process, &buf_size, NULL, 0);
  if (ret < 0) {
    free(process);
    return 0;
  }
  memcpy(&nargs, process, sizeof(nargs));
  *process_name = process + sizeof(nargs);
  return 1;
}

int rb_process_info(int pid, int flavor, void *pti, int size) {
  int ret = proc_pidinfo(pid, flavor, 0, pti, size);
  if ((ret == 0) || (ret != size)) {
    return 0;
  } else {
    return 1;
  }
}

/* List of Processes */
int * rb_process_list() {
  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
  size_t buf_size;
  int ret;
  int list[4096];
  ret = sysctl(mib, 4, NULL, &buf_size, NULL, 0);
  if (ret >= 0) {
    struct kinfo_proc *processes = NULL;
    int i, nb_entries;
    nb_entries = buf_size / sizeof(struct kinfo_proc);
    processes = (struct kinfo_proc*) malloc(buf_size);
    if (processes != NULL) {
      ret = sysctl(mib, 4, processes, &buf_size, NULL, 0);
      if (ret >= 0) {
        for (i = 0; i < nb_entries; i++) {
          int pid = processes[i].kp_proc.p_pid;
          list[i] = pid;
        }
        free(processes);
        return list;
      }
      free(processes);
      return 0;
    }
  }
  return 0;
}

#endif