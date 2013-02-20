#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include "core.h"
#include <opencv2/core/core.hpp>

static void
mrb_mruby_opencv_free(mrb_state *mrb, void *p) {
  delete static_cast<cv::Mat*>(p);
}

struct mrb_data_type mrb_mruby_opencv_data_type = {
  "mrb_mruby_opencv_mat", mrb_mruby_opencv_free,
};

static mrb_value
mrb_mruby_opencv_initialize(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat;
  mrb_int rows, cols, type;
  int argc = mrb_get_args(mrb, "|iii", &rows, &cols, &type);
  if (argc == 3)
  {
    mat = new cv::Mat(rows, cols, type);
  }
  else
  {
    mat = new cv::Mat();
  }

  DATA_PTR(self) = static_cast<void*>(mat);
  DATA_TYPE(self) = &mrb_mruby_opencv_data_type;
  return self;
}

static mrb_value
mrb_mruby_opencv_copyTo(mrb_state *mrb, mrb_value self)
{
  mrb_value dst_value, mask_value;
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_data_type);
  if (mat) {
    int argc = mrb_get_args(mrb, "o|o", &dst_value, &mask_value);
    if (argc == 1) {
      cv::Mat* dst = (cv::Mat*)mrb_get_datatype(mrb, dst_value, &mrb_mruby_opencv_data_type);
      mat->copyTo(*dst);
    } else if (argc == 2) {
      cv::Mat* dst = (cv::Mat*)mrb_get_datatype(mrb, dst_value, &mrb_mruby_opencv_data_type);
      cv::Mat* mask = (cv::Mat*)mrb_get_datatype(mrb, mask_value, &mrb_mruby_opencv_data_type);
      mat->copyTo(*dst, *mask);
    }
  }
  return self;
}

static mrb_value
mrb_mruby_opencv_aget(mrb_state *mrb, mrb_value self)
{
  int index;
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_data_type);
  if (mat) {
    int argc = mrb_get_args(mrb, "i", &index);
    if (argc == 1) {
      if (0 <= index && index < mat->rows * (int)mat->step) {
        return mrb_fixnum_value(mat->data[index]);
      }
      //TODO raise exception ?
    }
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_aset(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_data_type);
  if (mat) {
    int index, value;
    int argc = mrb_get_args(mrb, "ii", &index, &value);
    if (argc == 2) {
      unsigned char bvalue = (unsigned char)value;
      if (0 <= index && index < mat->rows * (int)mat->step) {
        mat->data[index] = bvalue;
        return mrb_fixnum_value(bvalue);
      }
      //TODO raise exception ?
    }
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_rows(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_data_type);
  if (mat) {
    return mrb_fixnum_value(mat->rows);
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_cols(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_data_type);
  if (mat) {
    return mrb_fixnum_value(mat->cols);
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_type(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = (cv::Mat*)mrb_get_datatype(mrb, self, &mrb_mruby_opencv_data_type);
  if (mat) {
    return mrb_fixnum_value(mat->type());
  }
  return mrb_nil_value();
}


void
mrb_mruby_opencv_core_init(mrb_state* mrb, struct RClass *cv_class) {
  
  //---------
  //cv::Mat
  //---------
  struct RClass *mat_class = mrb_define_class_under(mrb, cv_class, "Mat", mrb->object_class);
  MRB_SET_INSTANCE_TT(mat_class, MRB_TT_DATA);
  mrb_define_method(mrb, mat_class, "initialize", mrb_mruby_opencv_initialize, ARGS_OPT(3));
  
  //method
  mrb_define_method(mrb, mat_class, "copyTo", mrb_mruby_opencv_copyTo, ARGS_REQ(1)|ARGS_OPT(1));
  
  //array access
  mrb_define_method(mrb, mat_class, "[]", mrb_mruby_opencv_aget, ARGS_NONE());
  mrb_define_method(mrb, mat_class, "[]=", mrb_mruby_opencv_aset, ARGS_NONE());
  //properties
  mrb_define_method(mrb, mat_class, "rows", mrb_mruby_opencv_rows, ARGS_NONE());
  mrb_define_method(mrb, mat_class, "cols", mrb_mruby_opencv_cols, ARGS_NONE());
  mrb_define_method(mrb, mat_class, "type", mrb_mruby_opencv_type, ARGS_NONE());


  //constants
  mrb_define_const(mrb, cv_class, "CV_8UC1", mrb_fixnum_value(CV_8UC1));
  mrb_define_const(mrb, cv_class, "CV_8UC2", mrb_fixnum_value(CV_8UC2));
  mrb_define_const(mrb, cv_class, "CV_8UC3", mrb_fixnum_value(CV_8UC3));
  mrb_define_const(mrb, cv_class, "CV_8UC4", mrb_fixnum_value(CV_8UC4));
}

void
mrb_mruby_opencv_core_final(mrb_state* mrb, struct RClass *cv_class) {
  // finalizer
}
