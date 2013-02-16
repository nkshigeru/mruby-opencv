#ifndef MRUBY_OPENCV_CORE_H
#define MRUBY_OPENCV_CORE_H

#include <mruby.h>

#if defined(__cplusplus)
extern "C" {
#endif

void mrb_mruby_opencv_core_init(mrb_state* mrb, struct RClass *class_cv);
void mrb_mruby_opencv_core_final(mrb_state* mrb, struct RClass *class_cv);

extern struct mrb_data_type mrb_mruby_opencv_type;

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* MRUBY_OPENCV_CORE_H */
