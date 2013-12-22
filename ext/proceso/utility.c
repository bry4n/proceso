#include "proceso.h"

int rb_hw_ncpu() {
  int ncpu = 0;
#if defined(__APPLE__)
  int mib[2] = { CTL_HW, HW_NCPU };
  int ret;
  size_t len;
  len = sizeof(ncpu);
  ret = sysctl(mib, 2, &ncpu, &len, NULL, 0);
  if (ret == -1) {
    return 0;
  }
#elif defined(__LINUX__)
  ncpu = rb_proc_ncpu();
#endif
  return ncpu;
}

float rb_process_cpu_times(int pid, int flag) {
  int ret;
#if defined(__APPLE__)
  struct proc_taskinfo pti;
  ret = rb_process_info(pid, PROC_PIDTASKINFO, &pti, sizeof(pti));
  if (ret == 0)
    return 0.0;
  if (flag == FCPU_SYS) { // total system
    return (float)pti.pti_total_system / 1000000000.0;
  } else {
    return (float)pti.pti_total_user / 1000000000.0;
  }
#elif defined(__LINUX__)
  if (flag == FCPU_SYS) {
    return rb_proc_pid_stime(pid);
  } else {
    return rb_proc_pid_utime(pid);
  }
#endif
  return 0.0;
}

char * rb_process_command(int pid) {
  int ret;
  char *process_name;
#if defined(__APPLE__)
  int argmax;
  argmax = rb_sysctl_kern_argmax();
  if (argmax) {
    ret = rb_sysctl_kern_procargs2(pid, &process_name, argmax, (size_t)argmax);
    if (ret == 1)
      return process_name;
  }
#elif defined(__LINUX__)
  process_name = rb_proc_pid_cmdline(pid);
  return process_name;
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
#elif defined(__LINUX__)
  if (flag == 1) {
    result = rb_proc_pid_vsize(pid);
  } else {
    result = rb_proc_pid_rss(pid);
  }
#endif
  return result;
}