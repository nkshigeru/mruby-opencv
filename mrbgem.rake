MRuby::Gem::Specification.new('mruby-opencv') do |spec|
  spec.license = 'MIT'
  spec.authors = 'nkshigeru'
  
  #TODO find library
  
  #test
  spec.test_args = {'test_jpeg' => File.expand_path(File.dirname(__FILE__)) + '/test/test.jpg'}

end
