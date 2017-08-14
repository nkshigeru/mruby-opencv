#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include "mruby_opencv_core.h"
#include "mruby_opencv_common.h"

static void
mrb_mruby_opencv_free(mrb_state *mrb, void *p) {
  delete static_cast<cv::Mat*>(p);
}

struct mrb_data_type mrb_mruby_opencv_data_type = {
  "mrb_mruby_opencv_mat", mrb_mruby_opencv_free,
};

cv::Mat*
mrb_mruby_opencv_mat(mrb_state* mrb, mrb_value value) {
  cv::Mat* mat = (cv::Mat*)mrb_data_check_get_ptr(mrb, value, &mrb_mruby_opencv_data_type);
  return mat;
}

struct RData*
mrb_mruby_opencv_mat_object_alloc(mrb_state* mrb, cv::Mat* mat)
{
  struct RClass* cv_class = mrb_class_get(mrb, "CV");
  struct RClass* mat_class = mrb_class_ptr(mrb_iv_get(mrb, mrb_obj_value(cv_class), mrb_intern_lit(mrb, "Mat")));
  struct RData* data = mrb_data_object_alloc(mrb, mat_class, mat, &mrb_mruby_opencv_data_type);
  return data;
}

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
  cv::Mat* mat = mrb_mruby_opencv_mat(mrb, self);
  if (mat) {
    int argc = mrb_get_args(mrb, "o|o", &dst_value, &mask_value);
    if (argc == 1) {
      cv::Mat* dst = mrb_mruby_opencv_mat(mrb, dst_value);
      mat->copyTo(*dst);
    } else if (argc == 2) {
      cv::Mat* dst = mrb_mruby_opencv_mat(mrb, dst_value);
      cv::Mat* mask = mrb_mruby_opencv_mat(mrb, mask_value);
      mat->copyTo(*dst, *mask);
    }
  }
  return self;
}

static mrb_value
mrb_mruby_opencv_aget_1b_1(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  if ((unsigned int)i >= (unsigned int)(mat.rows * mat.step)) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d is out of range", mrb_fixnum_value(i));
  }
  return mrb_fixnum_value(mat.data[i]);
}

static mrb_value
mrb_mruby_opencv_aget_1b_2(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i, j;
  mrb_get_args(mrb, "ii", &i, &j);
  if ((unsigned int)i >= (unsigned int)mat.rows || (unsigned int)j >= (unsigned int)mat.cols) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d,%d is out of range", mrb_fixnum_value(i), mrb_fixnum_value(j));
  }
  return mrb_fixnum_value(mat.at<unsigned char>(i, j));
}

static mrb_value
mrb_mruby_opencv_aget_1f_1(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i;
  mrb_get_args(mrb, "i", &i);
  if ((unsigned int)i >= (unsigned int)(mat.rows * mat.step)) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d is out of range", mrb_fixnum_value(i));
  }
  return mrb_float_value(mrb, ((float*)mat.data)[i]);
}

static mrb_value
mrb_mruby_opencv_aget_1f_2(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i, j;
  mrb_get_args(mrb, "ii", &i, &j);
  if ((unsigned int)i >= (unsigned int)mat.rows || (unsigned int)j >= (unsigned int)mat.cols) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d,%d is out of range", mrb_fixnum_value(i), mrb_fixnum_value(j));
  }
  return mrb_float_value(mrb, mat.at<float>(i, j));
}

static mrb_value
mrb_mruby_opencv_aget(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = mrb_mruby_opencv_mat(mrb, self);
  if (!mat) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "%S is not CV::Mat", self);
  }
  int argc = mrb->c->ci->argc;
  switch(mat->type()) {
    case CV_8UC1:
      switch(argc) {
        case 1:
          return mrb_mruby_opencv_aget_1b_1(mrb, *mat);
        case 2:
          return mrb_mruby_opencv_aget_1b_2(mrb, *mat);
      }
      break;
    case CV_32FC1:
      switch(argc) {
        case 1:
          return mrb_mruby_opencv_aget_1f_1(mrb, *mat);
        case 2:
          return mrb_mruby_opencv_aget_1f_2(mrb, *mat);
      }
      break;
  }
  //TODO raise exception ?
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_aset_1b_1(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i, value;
  mrb_get_args(mrb, "ii", &i, &value);
  if ((unsigned int)i >= (unsigned int)(mat.rows * mat.step)) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d is out of range", mrb_fixnum_value(i));
  }
  mat.data[i] = value;
  return mrb_fixnum_value(value);
}

static mrb_value
mrb_mruby_opencv_aset_1b_2(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i, j, value;
  mrb_get_args(mrb, "iii", &i, &j, &value);
  if ((unsigned int)i >= (unsigned int)mat.rows || (unsigned int)j >= (unsigned int)mat.cols) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d,%d is out of range", mrb_fixnum_value(i), mrb_fixnum_value(j));
  }
  mat.at<unsigned char>(i, j) = value;
  return mrb_fixnum_value(value);
}

static mrb_value
mrb_mruby_opencv_aset_1f_1(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i;
  mrb_float value;
  mrb_get_args(mrb, "if", &i, &value);
  if ((unsigned int)i >= (unsigned int)(mat.rows * mat.step)) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d is out of range", mrb_fixnum_value(i));
  }
  ((float*)mat.data)[i] = (float)value;
  return mrb_float_value(mrb, value);
}

static mrb_value
mrb_mruby_opencv_aset_1f_2(mrb_state *mrb, cv::Mat& mat)
{
  mrb_int i, j;
  mrb_float value;
  mrb_get_args(mrb, "iif", &i, &j, &value);
  if ((unsigned int)i >= (unsigned int)mat.rows || (unsigned int)j >= (unsigned int)mat.cols) {
    mrb_raisef(mrb, E_INDEX_ERROR, "%d,%d is out of range", mrb_fixnum_value(i), mrb_fixnum_value(j));
  }
  mat.at<float>(i, j) = (float)value;
  return mrb_float_value(mrb, value);
}

static mrb_value
mrb_mruby_opencv_aset(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = mrb_mruby_opencv_mat(mrb, self);
  if (!mat) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "%S is not CV::Mat", self);
  }
  int argc = mrb->c->ci->argc;
  switch(mat->type()) {
    case CV_8UC1:
      switch(argc) {
        case 2:
          return mrb_mruby_opencv_aset_1b_1(mrb, *mat);
        case 3:
          return mrb_mruby_opencv_aset_1b_2(mrb, *mat);
      }
      break;
    case CV_32FC1:
      switch(argc) {
        case 2:
          return mrb_mruby_opencv_aset_1f_1(mrb, *mat);
        case 3:
          return mrb_mruby_opencv_aset_1f_2(mrb, *mat);
      }
      break;
  }
  //TODO raise exception ?
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_rows(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = mrb_mruby_opencv_mat(mrb, self);
  if (mat) {
    return mrb_fixnum_value(mat->rows);
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_cols(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = mrb_mruby_opencv_mat(mrb, self);
  if (mat) {
    return mrb_fixnum_value(mat->cols);
  }
  return mrb_nil_value();
}

static mrb_value
mrb_mruby_opencv_type(mrb_state *mrb, mrb_value self)
{
  cv::Mat* mat = mrb_mruby_opencv_mat(mrb, self);
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
  mrb_define_method(mrb, mat_class, "initialize", mrb_mruby_opencv_initialize, MRB_ARGS_OPT(3));
  
  //method
  mrb_define_method(mrb, mat_class, "copyTo", mrb_mruby_opencv_copyTo, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  
  //array access
  mrb_define_method(mrb, mat_class, "[]", mrb_mruby_opencv_aget, MRB_ARGS_ANY());
  mrb_define_method(mrb, mat_class, "[]=", mrb_mruby_opencv_aset, MRB_ARGS_ANY());
  //properties
  mrb_define_method(mrb, mat_class, "rows", mrb_mruby_opencv_rows, MRB_ARGS_NONE());
  mrb_define_method(mrb, mat_class, "cols", mrb_mruby_opencv_cols, MRB_ARGS_NONE());
  mrb_define_method(mrb, mat_class, "type", mrb_mruby_opencv_type, MRB_ARGS_NONE());


  //constants
  mrb_define_const(mrb, cv_class, "CV_8UC1", mrb_fixnum_value(CV_8UC1));
  mrb_define_const(mrb, cv_class, "CV_8UC2", mrb_fixnum_value(CV_8UC2));
  mrb_define_const(mrb, cv_class, "CV_8UC3", mrb_fixnum_value(CV_8UC3));
  mrb_define_const(mrb, cv_class, "CV_8UC4", mrb_fixnum_value(CV_8UC4));
  mrb_define_const(mrb, cv_class, "CV_32FC1", mrb_fixnum_value(CV_32FC1));
  mrb_define_const(mrb, cv_class, "CV_32FC2", mrb_fixnum_value(CV_32FC2));
  mrb_define_const(mrb, cv_class, "CV_32FC3", mrb_fixnum_value(CV_32FC3));
  mrb_define_const(mrb, cv_class, "CV_32FC4", mrb_fixnum_value(CV_32FC4));
}

void
mrb_mruby_opencv_core_final(mrb_state* mrb, struct RClass *cv_class) {
  // finalizer
}
