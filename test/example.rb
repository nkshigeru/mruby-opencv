mat = CV::imread 'lena.jpg'
p mat
p mat.width
p mat.height
CV::namedWindow 'testwindow'
CV::imshow 'testwindow', mat
CV::waitKey