#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include "mruby_opencv_imgproc.h"
#include "mruby_opencv_common.h"
#include <opencv2/imgproc.hpp>

static mrb_value
mrb_mruby_opencv_resize(mrb_state *mrb, mrb_value self)
{
  mrb_value src_value, dst_value, dsize_value;
  cv::Size dsize;
  mrb_float fx = 0;
  mrb_float fy = 0;
  mrb_int interpolation = cv::INTER_LINEAR;
  int argc = mrb_get_args(mrb, "ooo|ffi", &src_value, &dst_value, &dsize_value, &fx, &fy, &interpolation);
  mrb_value width_value = mrb_iv_get(mrb, dsize_value, mrb_intern_lit(mrb, "@width"));
  if (mrb_fixnum_p(width_value)) {
    dsize.width = mrb_fixnum(width_value);
  }
  mrb_value height_value = mrb_iv_get(mrb, dsize_value, mrb_intern_lit(mrb, "@height"));
  if (mrb_fixnum_p(height_value)) {
    dsize.height = mrb_fixnum(height_value);
  }
  cv::Mat* src = mrb_mruby_opencv_mat(mrb, src_value);
  if (!src) {
		mrb_raisef(mrb, E_ARGUMENT_ERROR, "%S is not CV::Mat", src_value);
	}
  cv::Mat* dst = mrb_mruby_opencv_mat(mrb, dst_value);
  if (!dst) {
		mrb_raisef(mrb, E_ARGUMENT_ERROR, "%S is not CV::Mat", dst_value);
	}
  cv::resize(*src, *dst, dsize, fx, fy, interpolation);
  return mrb_nil_value();
}

void
mrb_mruby_opencv_imgproc_init(mrb_state* mrb, struct RClass *cv_class) {

  //module method
  mrb_define_module_function(mrb, cv_class, "resize", mrb_mruby_opencv_resize, MRB_ARGS_REQ(3) | MRB_ARGS_OPT(3));

  //constants
  mrb_define_const(mrb, cv_class, "INTER_LINEAR ", mrb_fixnum_value(cv::INTER_LINEAR));
}

void
mrb_mruby_opencv_imgproc_final(mrb_state* mrb, struct RClass *cv_class) {
  // finalizer
}
