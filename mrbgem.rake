MRuby::Gem::Specification.new('mruby-opencv') do |spec|
  spec.license = 'MIT'
  spec.authors = 'nkshigeru'
 
  # TODO !!!!!
  spec.cxx.include_paths << 'C:/workspace/thirdparty/OpenCV/modules/core/include'
  spec.cxx.include_paths << 'C:/workspace/thirdparty/OpenCV/modules/highgui/include'
  spec.linker.libraries << 'C:/workspace/thirdparty/OpenCV/build/x86/lib/Release/opencv_core243'
  spec.linker.libraries << 'C:/workspace/thirdparty/OpenCV/build/x86/lib/Release/opencv_highgui243'

end
