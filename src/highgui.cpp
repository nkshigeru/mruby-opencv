#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include "highgui.h"
#include "core.h"
#include "common.h"
#include <opencv2/highgui/highgui.hpp>

static mrb_value
mrb_mruby_opencv_imshow(mrb_state *mrb, mrb_value self)
{
  char* name;
  mrb_value mat_value;
  int argc = mrb_get_args(mrb, "zo", &name, &mat_value);
  if (argc == 2) {
    cv::Mat* mat = mrb_mruby_opencv_mat(mrb, mat_value);
    if (mat) {
      //cv::imshow(name, *mat);
      IplImage iplImg = *mat;
      cvShowImage(name, &iplImg);
    }
  }
  return self;
}

static mrb_value
mrb_mruby_opencv_namedWindow(mrb_state *mrb, mrb_value self)
{
  char* name;
  int argc = mrb_get_args(mrb, "z", &name);
  if (argc == 1) {
    //cv::namedWindow(name);
    cvNamedWindow(name);
  }
  return self;
}

static mrb_value
mrb_mruby_opencv_waitKey(mrb_state *mrb, mrb_value self)
{
  cv::waitKey();
  return self;
}

static mrb_value
mrb_mruby_opencv_imread(mrb_state *mrb, mrb_value self)
{
  char* name;
  int argc = mrb_get_args(mrb, "z", &name);
  if (argc == 1) {
    cv::Mat* mat = new cv::Mat();
    mrb_value mat_value = mrb_obj_value(mrb_mruby_opencv_mat_object_alloc(mrb, mat));

    //*mat = cv::imread(name);
    IplImage* iplImg = cvLoadImage(name);
    *mat = cv::Mat(iplImg);
    cvReleaseImage(&iplImg);
    return mat_value;
  }
  
  return mrb_nil_value();
}

void
mrb_mruby_opencv_highgui_init(mrb_state* mrb, struct RClass *class_cv) {
  mrb_define_class_method(mrb, class_cv, "imshow", mrb_mruby_opencv_imshow, ARGS_OPT(2));
  mrb_define_class_method(mrb, class_cv, "namedWindow", mrb_mruby_opencv_namedWindow, ARGS_ANY());
  mrb_define_class_method(mrb, class_cv, "waitKey", mrb_mruby_opencv_waitKey, ARGS_ANY());
  mrb_define_class_method(mrb, class_cv, "imread", mrb_mruby_opencv_imread, ARGS_OPT(1));
}

void
mrb_mruby_opencv_highgui_final(mrb_state* mrb, struct RClass *class_cv) {
  // finalizer
}
