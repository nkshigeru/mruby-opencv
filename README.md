mruby-opencv
=========

OpenCV binding for mruby.

Install
---------

1. Install OpenCV
2. Edit your `build_config.rb`. For example,

```ruby
  conf.gem 'path/to/here' do |g|
    g.cxx.include_paths << 'path/to/OpenCV/include'
    g.linker.library_paths << 'path/to/OpenCV/lib'
    g.linker.libraries << %w(opencv_core320)
  end
```


