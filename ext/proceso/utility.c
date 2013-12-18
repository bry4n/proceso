#include "proceso.h"

#ifdef __APPLE__
int rb_hw_ncpu() {
  int mib[2] = { CTL_HW, HW_NCPU };
  int ncpu, ret;
  size_t len;
  len = sizeof(ncpu);
  ret = sysctl(mib, 2, &ncpu, &len, NULL, 0);
  if (ret != -1) {
    return ncpu;
  } else {
    return 0;
  }
}

int rb_process_info(int pid, int flavor, void *pti, int size) {
  int ret = proc_pidinfo(pid, flavor, 0, pti, size);
  if ((ret == 0) || (ret != size)) {
    return 0;
  } else {
    return 1;
  }
}

float rb_process_cpu_times(int pid, int flag) {
  struct proc_taskinfo pti;
  int ret;
  ret = rb_process_info(pid, PROC_PIDTASKINFO, &pti, sizeof(pti));
  if (ret == 0) {
    return 0.0;
  }
  if (flag == FCPU_SYS) { // total system
    return (float)pti.pti_total_system / 1000000000.0;
  } else {
    return (float)pti.pti_total_user / 1000000000.0;
  }
  return 0.0;
}


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
#endif

char * rb_process_command(int pid) {
  char *process_name;
#if defined(__APPLE__)
  int ret, argmax;
  argmax = rb_sysctl_kern_argmax();
  if (argmax) {
    ret = rb_sysctl_kern_procargs2(pid, &process_name, argmax, (size_t)argmax);
    if (ret == 1)
      return process_name;
  }
#elif defined(__linux__) || defined(__LINUX__)
  PROCTAB *proc;
  proc_t proc_info;
  proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
  memset(&proc_info, pid, &proc_info);
  if (readproc(proc, &proc_info) != NULL) {
    process_name = proc_info.cmd;
    return process_name;
  }
#endif
  return NULL;
}

int rb_process_memory_size(int pid, int flag) {
  int result = 0;
#if defined(__APPLE__)
  kern_return_t kr;
  task_t task;
  kr = task_for_pid(mach_task_self(), pid, &task);
  if (kr == KERN_SUCCESS) {
    task_basic_info_data_t basic_info;
    mach_msg_type_number_t count = TASK_BASIC_INFO_COUNT;
    kr = task_info(task, TASK_BASIC_INFO, (task_info_t)&basic_info, &count);
    if (kr == KERN_SUCCESS) {
      if (count == TASK_BASIC_INFO_COUNT) {
        if (flag == 1) {
          result = (int)basic_info.virtual_size;
        } else {
          result = (int)basic_info.resident_size;
        }
      }
    }
  }
#elif defined(__linux__)
#endif
  return result;
}

#ifdef __APPLE__
/* List of Processes */
int rb_process_list(int **pids) {
  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
  size_t buf_size;
  int ret;
  int list[sizeof(int)];
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
        *pids = list;
        free(processes);
        return 1;
      }
      free(processes);
      return 0;
    }
  }
  return 0;
}
#endif