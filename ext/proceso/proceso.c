#include <ruby.h>
#include <unistd.h>

#include "utility.h"

#define PROCESS_RSS 0
#define PROCESS_VMS 1

static VALUE rb_mProceso;
static VALUE rb_cProcesoPID;

int iv2pid(VALUE self) {
  return FIX2INT(rb_iv_get(self, "@pid"));
}

static VALUE
proceso__process_init(VALUE self, VALUE pid) {
  rb_iv_set(self, "@pid", pid);
  return self;
}

/* PID running? */
static VALUE
proceso__process_running(VALUE self) {
  int pid = iv2pid(self);
  rb_pid_t i = getpgid(pid);
  if (i < 0) {
    return Qfalse;
  }
  return Qtrue;
}

/* PID name */
static VALUE
proceso__process_name(VALUE self) {
  int pid = iv2pid(self);
  char *process_name = rb_process_name(pid);
  return rb_str_new2(process_name);
}

/* PID Resource Usage */
static VALUE
proceso__process_rusage(VALUE self) {
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


/* PID Resident Size (bytes) */
static VALUE
proceso__process_rss(VALUE self) {
  int ret = rb_process_memory_size(iv2pid(self), PROCESS_RSS);
  return INT2NUM(ret);
}

/* PID Virtual Size (bytes) */
static VALUE
proceso__process_vms(VALUE self) {
  int ret = rb_process_memory_size(iv2pid(self), PROCESS_VMS);
  return INT2NUM(ret);
}

/* PID User CPU */
static VALUE
proceso__process_user_cpu(VALUE self) {
  float val = rb_process_cpu_times(iv2pid(self), FCPU_USR);
  return rb_float_new(val);
}

/* PID System CPU */
static VALUE
proceso__process_system_cpu(VALUE self) {
  float val = rb_process_cpu_times(iv2pid(self), FCPU_SYS);
  return rb_float_new(val);
}

static VALUE
proceso__process_cpu_usage(VALUE self) {
  int ncpu = rb_ncpu();
  float u1, u2;
  float usage;
  u1 = rb_process_cpu_times(iv2pid(self), FCPU_USR);
  usleep(100000);
  u2 = rb_process_cpu_times(iv2pid(self), FCPU_USR);
  usage = ncpu * ((u2 - u1) * 100);
  return rb_float_new(usage);
}

void Init_proceso() {
  rb_mProceso        = rb_define_module("Proceso");
  rb_define_const(rb_mProceso, "NCPU", INT2NUM(rb_ncpu()));

  rb_cProcesoPID = rb_define_class_under(rb_mProceso, "PID", rb_cObject);

  rb_define_method(rb_cProcesoPID, "initialize", proceso__process_init, 1);
  rb_define_method(rb_cProcesoPID, "running?", proceso__process_running, 0);
  rb_define_method(rb_cProcesoPID, "name", proceso__process_name, 0);
  rb_define_method(rb_cProcesoPID, "rusage", proceso__process_rusage, 0);
  rb_define_method(rb_cProcesoPID, "resident_size", proceso__process_rss, 0);
  rb_define_method(rb_cProcesoPID, "virtual_size", proceso__process_vms, 0);
  rb_define_method(rb_cProcesoPID, "user_cpu_times", proceso__process_user_cpu, 0);
  rb_define_method(rb_cProcesoPID, "system_cpu_times", proceso__process_system_cpu, 0);
  rb_define_method(rb_cProcesoPID, "cpu_usage", proceso__process_cpu_usage, 0);
}


