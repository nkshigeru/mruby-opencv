MRuby::Gem::Specification.new('mruby-opencv') do |spec|
  spec.license = 'MIT'
  spec.authors = 'nkshigeru'
 
  spec.linker.libraries << %w(opencv_core243 opencv_highgui243)

end
