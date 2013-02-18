assert('CV::Mat constructor') do
  mat = CV::Mat.new
  mat.width == 0 && mat.height == 0
end

assert('imread') do
  mat = CV::imread TEST_ARGS['test_jpeg']
  mat.width == 320 && mat.height == 240
end
