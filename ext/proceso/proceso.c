#include "proceso.h"

static VALUE rb_mProceso;

void Init_proceso() {
  rb_mProceso        = rb_define_module("Proceso");
  rb_define_const(rb_mProceso, "NCPU", INT2NUM(rb_hw_ncpu()));

  Init_pid(rb_mProceso);
  Init_resource(rb_mProceso);
}


