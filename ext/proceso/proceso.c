#include "proceso.h"

static VALUE rb_mProceso;

int iv2pid(VALUE self) {
  return FIX2INT(rb_iv_get(self, "@pid"));
}

void Init_proceso() {

  rb_mProceso        = rb_define_module("Proceso");

  rb_define_const(rb_mProceso, "NCPU", INT2NUM(rb_hw_ncpu()));

  Init__proceso_pid();
}


