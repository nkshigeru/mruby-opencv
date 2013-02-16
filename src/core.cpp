#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include "core.h"
#include <opencv2/core/core.hpp>

static void
mrb_mruby_opencv_free(mrb_state *mrb, void *p) {
  delete static_cast<cv::Mat*>(p);
}

struct mrb_data_type mrb_mruby_opencv_type = {
  "mrb_mruby_opencv_mat", mrb_mruby_opencv_free,
};

static mrb_value
mrb_mruby_opencv_initialize(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = new cv::Mat();
  DATA_PTR(self) = static_cast<void*>(mat);
  DATA_TYPE(self) = &mrb_mruby_opencv_type;
  return self;
}

static mrb_value
mrb_mruby_opencv_width(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_type);
  if (mat) {
    return mrb_fixnum_value(mat->cols);
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_height(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_type);
  if (mat) {
    return mrb_fixnum_value(mat->rows);
  }
  return mrb_nil_value();
}

void
mrb_mruby_opencv_core_init(mrb_state* mrb, struct RClass *class_cv) {
  struct RClass *class_mat = mrb_define_class_under(mrb, class_cv, "Mat", mrb->object_class);
  MRB_SET_INSTANCE_TT(class_mat, MRB_TT_DATA);
  mrb_define_method(mrb, class_mat, "initialize", mrb_mruby_opencv_initialize, ARGS_ANY());
  mrb_define_method(mrb, class_mat, "width", mrb_mruby_opencv_width, ARGS_ANY());
  mrb_define_method(mrb, class_mat, "height", mrb_mruby_opencv_height, ARGS_ANY());
}

void
mrb_mruby_opencv_core_final(mrb_state* mrb, struct RClass *class_cv) {
  // finalizer
}
