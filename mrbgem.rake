MRuby::Gem::Specification.new('mruby-opencv') do |spec|
  spec.license = 'MIT'
  spec.authors = 'nkshigeru'
  
  spec.linker.flags_before_libraries << `pkg-config --libs opencv4`.chomp
end
