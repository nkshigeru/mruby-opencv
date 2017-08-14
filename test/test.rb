assert('CV::Mat constructor') do
  mat = CV::Mat.new
  mat.rows == 0 && mat.cols == 0
end

assert('CV::Mat constructor 8UC1') do
  mat = CV::Mat.new 480, 640, CV::CV_8UC1
  mat.rows == 480 && mat.cols == 640 && mat.type == CV::CV_8UC1
end

assert('CV::Mat constructor 32FC1') do
  mat = CV::Mat.new 480, 640, CV::CV_32FC1
  mat.rows == 480 && mat.cols == 640 && mat.type == CV::CV_32FC1
end

assert('CV::Mat copyTo') do
  mat1 = CV::Mat.new 480, 640, CV::CV_8UC1
  mat2 = CV::Mat.new
  mat1.copyTo mat2
  mat2.rows == 480 && mat2.cols == 640 && mat2.type == CV::CV_8UC1
end

assert('CV::Mat array access1 8UC1') do
  mat = CV::Mat.new 480, 640, CV::CV_8UC1
  mat[0] = 1
  mat[480*640-1] = 255
  mat[0] == 1 && mat[480*640-1] == 255
end

assert('CV::Mat array access2 8UC1') do
  mat = CV::Mat.new 480, 640, CV::CV_8UC1
  mat[0,0] = 1
  mat[479,639] = 255
  mat[0,0] == 1 && mat[479,639] == 255
end

assert('CV::Mat array access1 32FC1') do
  mat = CV::Mat.new 480, 640, CV::CV_32FC1
  mat[0] = 1
  mat[480*640-1] = 0.5
  mat[0] == 1 && mat[480*640-1] == 0.5
end

assert('CV::Mat array access2 32FC1') do
  mat = CV::Mat.new 480, 640, CV::CV_32FC1
  mat[0,0] = 1
  mat[479,639] = 0.5
  mat[0,0] == 1 && mat[479,639] == 0.5
end
