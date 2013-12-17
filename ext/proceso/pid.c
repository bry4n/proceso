#include "proceso.h"

static VALUE rb_cProcesoPID;

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

/* PID command line */
static VALUE
proceso__process_command(VALUE self) {
  int pid = iv2pid(self);
  char *process_cmd = rb_process_command(pid);
  if (process_cmd == NULL)
    return Qnil;
  return rb_str_new2(process_cmd);
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
  int ncpu = rb_hw_ncpu();
  float u1, u2;
  float usage;
  u1 = rb_process_cpu_times(iv2pid(self), FCPU_USR);
  usleep(100000);
  u2 = rb_process_cpu_times(iv2pid(self), FCPU_USR);
  usage = ncpu * ((u2 - u1) * 100);
  return rb_float_new(usage);
}

void Init__proceso_pid() {

  VALUE rb_mProceso  = rb_define_module("Proceso");
  rb_cProcesoPID = rb_define_class_under(rb_mProceso, "PID", rb_cObject);

  rb_define_method(rb_cProcesoPID, "initialize", proceso__process_init, 1);
  rb_define_method(rb_cProcesoPID, "running?", proceso__process_running, 0);
  rb_define_method(rb_cProcesoPID, "command", proceso__process_command, 0);
  rb_define_method(rb_cProcesoPID, "resident_size", proceso__process_rss, 0);
  rb_define_method(rb_cProcesoPID, "virtual_size", proceso__process_vms, 0);
  rb_define_method(rb_cProcesoPID, "user_cpu_times", proceso__process_user_cpu, 0);
  rb_define_method(rb_cProcesoPID, "system_cpu_times", proceso__process_system_cpu, 0);
  rb_define_method(rb_cProcesoPID, "cpu_usage", proceso__process_cpu_usage, 0);
}
