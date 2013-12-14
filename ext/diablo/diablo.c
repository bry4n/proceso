#include <ruby.h>
#include "process.h"

#define PROCESS_RSS 0
#define PROCESS_VMS 1

static VALUE rb_mDiablo;
static VALUE rb_cDiabloProcess;

int iv2pid(VALUE self) {
  return FIX2INT(rb_iv_get(self, "@pid"));
}

static VALUE
diablo__process_init(VALUE self, VALUE pid) {
  rb_iv_set(self, "@pid", pid);
  return self;
}

/* Process running? */
static VALUE
diablo__process_running(VALUE self) {
  int pid = iv2pid(self);
  rb_pid_t i = getpgid(pid);
  if (i < 0) {
    return Qfalse;
  }
  return Qtrue;
}

/* Process name */
static VALUE
diablo__process_name(VALUE self) {
  int pid = iv2pid(self);
  char *process_name = rb_process_name(pid);
  return rb_str_new2(process_name);
}

/* Process Resource Usage */
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


/* Process Resident Size (bytes) */
static VALUE
diablo__process_rss(VALUE self) {
  int ret = rb_process_memory_size(iv2pid(self), PROCESS_RSS);
  return INT2NUM(ret);
}

/* Process Virtual Size (bytes) */
static VALUE
diablo__process_vms(VALUE self) {
  int ret = rb_process_memory_size(iv2pid(self), PROCESS_VMS);
  return INT2NUM(ret);
}

void Init_diablo() {
  rb_mDiablo        = rb_define_module("Diablo");
  rb_cDiabloProcess = rb_define_class_under(rb_mDiablo, "Process", rb_cObject);

  rb_define_method(rb_cDiabloProcess, "initialize", diablo__process_init, 1);
  rb_define_method(rb_cDiabloProcess, "running?", diablo__process_running, 0);
  rb_define_method(rb_cDiabloProcess, "name", diablo__process_name, 0);
  rb_define_method(rb_cDiabloProcess, "rusage", diablo__process_rusage, 0);
  rb_define_method(rb_cDiabloProcess, "resident_size", diablo__process_rss, 0);
  rb_define_method(rb_cDiabloProcess, "virtual_size", diablo__process_vms, 0);
}


