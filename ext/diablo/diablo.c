#include <ruby.h>
#include <sys/sysctl.h>

static VALUE rb_mDiablo;
static VALUE rb_cDiabloProcess;

int iv2pid(VALUE self) {
  return FIX2INT(rb_iv_get(self, "@pid"));
}

char * get_process_name(int pid) {
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

static VALUE
diablo__process_init(VALUE self, VALUE pid) {
  rb_iv_set(self, "@pid", pid);
  return self;
}

static VALUE
diablo__process_running(VALUE self) {
  VALUE pid;
  rb_pid_t i;
  pid = rb_iv_get(self, "@pid");
  i = getpgid(NUM2PIDT(pid));
  if (i < 0) {
    return Qfalse;
  }
  return Qtrue;
}

static VALUE
diablo__process_name(VALUE self) {
  int pid = iv2pid(self);
  char *process_name = get_process_name(pid);
  return rb_str_new2(process_name);
}

static VALUE
diablo__process_list(VALUE self) {
  VALUE h_process_list = rb_hash_new();
  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
  size_t buf_size;
  int result;
  result = sysctl(mib, 4, NULL, &buf_size, NULL, 0);
  if (result >= 0) {
    struct kinfo_proc *processes = NULL;
    int i, nb_entries;
    nb_entries = buf_size / sizeof(struct kinfo_proc);
    processes = (struct kinfo_proc*) malloc(buf_size);
    if (processes != NULL) {
      result = sysctl(mib, 4, processes, &buf_size, NULL, 0);
      if (result >= 0) {
        for (i = 0; i < nb_entries; i++) {
          int pid = processes[i].kp_proc.p_pid;
          char *process_name = get_process_name(pid);
          rb_hash_aset(h_process_list, INT2NUM(pid), rb_str_new2(process_name));
        }
      }
      free(processes);
    }
  }
  return h_process_list;
}

static VALUE
diablo__process_rusage(VALUE self) {
  int pid = iv2pid(self);
  VALUE hash_rusage = rb_hash_new();
  struct rusage r;
  int status;

  wait4(pid, &status, 0, &r);

  rb_hash_aset(hash_rusage, rb_str_new2("utime"), INT2FIX(r.ru_utime.tv_sec + (r.ru_utime.tv_usec/1000.0)));
  rb_hash_aset(hash_rusage, rb_str_new2("stime"), INT2FIX(r.ru_stime.tv_sec + (r.ru_stime.tv_usec/1000.0)));
  rb_hash_aset(hash_rusage, rb_str_new2("maxrss"), INT2FIX(r.ru_maxrss));
  rb_hash_aset(hash_rusage, rb_str_new2("ixrss"), INT2FIX(r.ru_ixrss));
  rb_hash_aset(hash_rusage, rb_str_new2("idrss"), INT2FIX(r.ru_idrss));
  rb_hash_aset(hash_rusage, rb_str_new2("isrss"), INT2FIX(r.ru_isrss));
  rb_hash_aset(hash_rusage, rb_str_new2("minflt"), INT2FIX(r.ru_minflt));
  rb_hash_aset(hash_rusage, rb_str_new2("majflt"), INT2FIX(r.ru_majflt));
  rb_hash_aset(hash_rusage, rb_str_new2("nswap"), INT2FIX(r.ru_nswap));
  rb_hash_aset(hash_rusage, rb_str_new2("inblock"), INT2FIX(r.ru_inblock));
  rb_hash_aset(hash_rusage, rb_str_new2("oublock"), INT2FIX(r.ru_oublock));
  rb_hash_aset(hash_rusage, rb_str_new2("msgsnd"), INT2FIX(r.ru_msgsnd));
  rb_hash_aset(hash_rusage, rb_str_new2("msgrcv"), INT2FIX(r.ru_msgrcv));
  rb_hash_aset(hash_rusage, rb_str_new2("nsignals"), INT2FIX(r.ru_nsignals));
  rb_hash_aset(hash_rusage, rb_str_new2("nvcsw"), INT2FIX(r.ru_nvcsw));
  rb_hash_aset(hash_rusage, rb_str_new2("nivcsw"), INT2FIX(r.ru_nivcsw));

  return hash_rusage;
}

void Init_diablo() {
  rb_mDiablo        = rb_define_module("Diablo");
  rb_cDiabloProcess = rb_define_class_under(rb_mDiablo, "Process", rb_cObject);

  rb_define_method(rb_cDiabloProcess, "initialize", diablo__process_init, 1);
  rb_define_method(rb_cDiabloProcess, "running?", diablo__process_running, 0);
  rb_define_method(rb_cDiabloProcess, "name", diablo__process_name, 0);
  rb_define_method(rb_cDiabloProcess, "rusage", diablo__process_rusage, 0);
  //rb_define_method(rb_cDiabloProcess, "list", diablo__process_list, 0);
}

