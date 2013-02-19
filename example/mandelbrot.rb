mat = CV::Mat.new 500, 500, CV::CV_8UC1

E = 4.0
LEFT = -1.5
RIGHT = 0.5
TOP = 1.0
BOTTOM = -1.0

def calc(a, b)

  x = 0.0
  y = 0.0
  
  100.times do
    x1 = x*x - y*y + a
    y1 = 2*x*y + b
    if x1 > E || y1 > E then
      return 255
    end
    x = x1
    y = y1
  end
  return 0

end

for i in 0..(mat.rows-1) do
  for j in 0..(mat.cols-1) do
    mat[i*mat.cols+j] = calc((RIGHT-LEFT)*j/mat.cols+LEFT, (BOTTOM-TOP)*i/mat.rows+TOP)
  end
end

CV::imshow 'mandelbrot', mat
CV::waitKey

