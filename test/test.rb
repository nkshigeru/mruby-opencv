assert('CV::Mat constructor 1') do
  mat = CV::Mat.new
  mat.rows == 0 && mat.cols == 0
end

assert('CV::Mat constructor 2') do
  mat = CV::Mat.new 480, 640, CV::CV_8UC1
  mat.rows == 480 && mat.cols == 640 && mat.type == CV::CV_8UC1
end

assert('CV::Mat copyTo') do
  mat1 = CV::Mat.new 480, 640, CV::CV_8UC1
  mat2 = CV::Mat.new
  mat1.copyTo mat2
  mat2.rows == 480 && mat2.cols == 640 && mat2.type == CV::CV_8UC1
end

assert('CV::Mat array access') do
  mat = CV::Mat.new 480, 640, CV::CV_8UC1
  mat[0] = 0
  mat[480*640-1] = 255
  mat[0] == 0 && mat[480*640-1] == 255
end

assert('imread') do
  mat = CV::imread TEST_ARGS['test_jpeg']
  mat.rows == 240 && mat.cols == 320
end


