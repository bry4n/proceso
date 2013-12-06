#include <ruby.h>
#include <sys/resource.h>

/*#include <libproc.h> */


static VALUE rb_mDiablo;
static VALUE rb_cDiabloBase;

static VALUE
diablo_base_init(VALUE self, VALUE name) {
  rb_iv_set(self, "@name", name);
  return self;
}

void Init_diablo() {
  rb_mDiablo     = rb_define_module("Diablo");
  rb_cDiabloBase = rb_define_class_under(rb_mDiablo, "Base", rb_cObject);
  rb_define_method(rb_cDiabloBase, "initialize", diablo_base_init, 1);
}

