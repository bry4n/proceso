#include <errno.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <signal.h>
#include <libproc.h>

int rb_process_exists(int pid) {
  if (pid < 0) {
    return 0;
  }
  int ret = kill(pid, 0);
  if ((ret == 0) || (ret == EPERM)) {
    return 1;
  }
  return 0;
}

int rb_process_info(int pid, int flavor, void *pti, int size) {
  int ret = proc_pidinfo(pid, flavor, 0, pti, size);
  if (ret == 0) {
  }
}

char * rb_process_name(int pid) {
  int argmax, nargs;
  char *process, *process_name;
  size_t buf_size;
  int result;
  int mib[2] = { CTL_KERN, KERN_ARGMAX };
  int mib2[3] = { CTL_KERN, KERN_PROCARGS2, pid };
  buf_size = sizeof(argmax);
  result = sysctl(mib, 2, &argmax, &buf_size, NULL, 0);
  if (result >= 0) {
    process = (char *)malloc(argmax);
    if (process != NULL) {
      buf_size = (size_t)argmax;
      result = sysctl(mib2, 3, process, &buf_size, NULL, 0);
      if (result >= 0) {
        memcpy(&nargs, process, sizeof(nargs));
        process_name = process + sizeof(nargs);
      }
      free(process);
    }
  }
  return process_name;
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
          result = basic_info.virtual_size;
        } else {
          result = basic_info.resident_size;
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
