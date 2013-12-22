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

#endif