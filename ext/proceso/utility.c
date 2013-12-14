#include <stdlib.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <signal.h>
#include <libproc.h>

#define FCPU_USR 0
#define FCPU_SYS 1

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

int rb_process_exists(int pid) {
  if (pid < 0)
    return 0;
  int ret = kill(pid, 0);
  if ((ret == 0) || (ret == EPERM))
    return 1;
  return 0;
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
  char *process, *name;
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

char * rb_process_command(int pid) {
  char *process_name;
  int ret, argmax;
  argmax = rb_sysctl_kern_argmax();
  if (argmax) {
    ret = rb_sysctl_kern_procargs2(pid, &process_name, argmax, (size_t)argmax);
    if (ret == 1)
      return process_name;
  }
  return NULL;
}

int rb_process_memory_size(int pid, int flag) {
  int result = 0;
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
  return result;
}

// /* List of Processes */
// static VALUE
// diablo__process_list(VALUE self) {
//   VALUE h_process_list = rb_hash_new();
//   int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
//   size_t buf_size;
//   int result;
//   result = sysctl(mib, 4, NULL, &buf_size, NULL, 0);
//   if (result >= 0) {
//     struct kinfo_proc *processes = NULL;
//     int i, nb_entries;
//     nb_entries = buf_size / sizeof(struct kinfo_proc);
//     processes = (struct kinfo_proc*) malloc(buf_size);
//     if (processes != NULL) {
//       result = sysctl(mib, 4, processes, &buf_size, NULL, 0);
//       if (result >= 0) {
//         for (i = 0; i < nb_entries; i++) {
//           int pid = processes[i].kp_proc.p_pid;
//           char *process_name = get_process_name(pid);
//           fixpt_t cpu = rb_process_cpu_usage(pid);
//           printf("pid=%d cpu=%lu\n", pid, cpu);
//           //rb_hash_aset(h_process_list, INT2NUM(pid), rb_str_new2(process_name));
//         }
//       }
//       free(processes);
//     }
//   }
//   return h_process_list;
// }

// fixpt_t rb_process_cpu_usage(int pid) {
//   struct kinfo_proc *kp;
//   int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, pid };
//   size_t bufSize = 0;
//   if ( sysctl(mib, 4, NULL, &bufSize, NULL, 0) >= 0 ) {
//     kp = (struct kinfo_proc *)malloc( bufSize );
//     if (kp == NULL)
//       return -1;
//     if (sysctl(mib, 4, kp, &bufSize, NULL, 0) < 0) {
//       free( kp );
//       return -1;
//     }
//   }
//   return kp->kp_proc.p_pctcpu;
// }
