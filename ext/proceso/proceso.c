#include "proceso.h"

static VALUE rb_mProceso;

int iv2pid(VALUE self) {
  return FIX2INT(rb_iv_get(self, "@pid"));
}

static VALUE
proceso__pids(VALUE self) {
  int pids[sizeof(int)];
  rb_process_list(&pids);
  VALUE processes = rb_ary_new();
  int i;
  for(i = 0; i < pids; i++) {
    rb_ary_push(processes, INT2NUM(pids[i]));
  }
  return processes;
}

void Init_proceso() {

  rb_mProceso        = rb_define_module("Proceso");

  rb_define_const(rb_mProceso, "NCPU", INT2NUM(rb_hw_ncpu()));
  rb_define_method(rb_mProceso, "pids", proceso__pids, 0);

  Init__proceso_pid();
  Init__proceso_resource();
}


