#ifndef MRUBY_OPENCV_COMMON_H
#define MRUBY_OPENCV_COMMON_H

#include <mruby.h>
#include <opencv2/core.hpp>

cv::Mat* mrb_mruby_opencv_mat(mrb_state* mrb, mrb_value value);
struct RData* mrb_mruby_opencv_mat_object_alloc(mrb_state* mrb, cv::Mat* mat);

#endif  /* MRUBY_OPENCV_COMMON_H */
