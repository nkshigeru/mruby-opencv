#include "mruby_opencv_core.h"

void
mrb_mruby_opencv_gem_init(mrb_state* mrb) {
  struct RClass *class_cv = mrb_define_module(mrb, "CV");
  mrb_mruby_opencv_core_init(mrb, class_cv);
}

void
mrb_mruby_opencv_gem_final(mrb_state* mrb) {
  // finalizer
}