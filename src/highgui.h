#ifndef MRUBY_OPENCV_HIGHGUI_H
#define MRUBY_OPENCV_HIGHGUI_H

#include <mruby.h>

#if defined(__cplusplus)
extern "C" {
#endif

void mrb_mruby_opencv_highgui_init(mrb_state* mrb, struct RClass *class_cv);
void mrb_mruby_opencv_highgui_final(mrb_state* mrb, struct RClass *class_cv);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* MRUBY_OPENCV_HIGHGUI_H */
