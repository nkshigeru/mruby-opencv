assert('CV::Mat constructor1') do
  mat = CV::Mat.new
  mat.rows == 0 && mat.cols == 0
end

assert('CV::Mat constructor2') do
  mat = CV::Mat.new 480, 640, 0
  mat.rows == 480 && mat.cols == 640
end

assert('imread') do
  mat = CV::imread TEST_ARGS['test_jpeg']
  mat.rows == 240 && mat.cols == 320
end


