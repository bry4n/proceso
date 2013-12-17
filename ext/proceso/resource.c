#include "proceso.h"

static VALUE rb_cProcesoResource;

static VALUE
proceso__resource_init(VALUE self, VALUE pid) {
  rb_iv_set(self, "@pid", pid);
  return self;
}

#ifdef __APPLE__
/* PID Resource Usage */
static VALUE
proceso__resource_usage(VALUE self) {
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
#endif

void Init_resource(VALUE rb_mProceso) {

  rb_cProcesoResource = rb_define_class_under(rb_mProceso, "Resource", rb_cObject);

  rb_define_method(rb_cProcesoResource, "initialize", proceso__resource_init, 1);
#ifdef __APPLE__
  rb_define_method(rb_cProcesoResource, "usage", proceso__resource_usage, 0);
#endif

}