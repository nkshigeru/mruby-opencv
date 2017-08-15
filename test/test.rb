assert('CV::Mat constructor') do
  mat = CV::Mat.new
  assert_equal mat.rows, 0
  assert_equal mat.cols, 0
  assert_equal mat.size, CV::Size.new()
end

assert('CV::Mat constructor 8UC1') do
  mat = CV::Mat.new(480, 640, CV::CV_8UC1)
  assert_equal mat.rows, 480
  assert_equal mat.cols, 640
  assert_equal mat.size, CV::Size.new(640, 480)
  assert_equal mat.type, CV::CV_8UC1
end

assert('CV::Mat constructor 32FC1') do
  mat = CV::Mat.new(480, 640, CV::CV_32FC1)
  assert_equal mat.rows, 480
  assert_equal mat.cols, 640
  assert_equal mat.size, CV::Size.new(640, 480)
  assert_equal mat.type, CV::CV_32FC1
end

assert('CV::Mat copyTo') do
  src = CV::Mat.new(480, 640, CV::CV_8UC1)
  dst = CV::Mat.new()
  src.copyTo(dst)
  assert_equal dst.size, CV::Size.new(640, 480)
  assert_equal dst.type, CV::CV_8UC1
end

assert('CV::Mat array access1 8UC1') do
  mat = CV::Mat.new(480, 640, CV::CV_8UC1)
  mat[0] = 1
  mat[480*640-1] = 255
  assert_equal mat[0], 1
  assert_equal mat[480*640-1], 255
end

assert('CV::Mat array access2 8UC1') do
  mat = CV::Mat.new(480, 640, CV::CV_8UC1)
  mat[0,0] = 1
  mat[479,639] = 255
  assert_equal mat[0,0], 1
  assert_equal mat[479,639], 255
end

assert('CV::Mat array access1 32FC1') do
  mat = CV::Mat.new(480, 640, CV::CV_32FC1)
  mat[0] = 1
  mat[480*640-1] = 0.5
  assert_equal mat[0], 1
  assert_equal mat[480*640-1], 0.5
end

assert('CV::Mat array access2 32FC1') do
  mat = CV::Mat.new 480, 640, CV::CV_32FC1
  mat[0,0] = 1
  mat[479,639] = 0.5
  assert_equal mat[0,0], 1
  assert_equal mat[479,639], 0.5
end

# resize
assert('CV::Mat resize by dsize 8UC1') do
  src = CV::Mat.new(480, 640, CV::CV_8UC1)
  dst = CV::Mat.new()
  CV::resize(src, dst, CV::Size.new(320, 240))
  assert_equal dst.size, CV::Size.new(320, 240)
  assert_equal dst.type, CV::CV_8UC1
end

assert('CV::Mat resize by factor 8UC1') do
  src = CV::Mat.new(480, 640, CV::CV_8UC1)
  dst = CV::Mat.new()
  CV::resize(src, dst, CV::Size.new(), 0.5, 0.5)
  assert_equal dst.size, CV::Size.new(320, 240)
  assert_equal dst.type, CV::CV_8UC1
end

