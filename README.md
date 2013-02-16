mruby-opencv
=========

Interface to OpenCV on mruby.
This project has just begun.

Install
---------

1. Install OpenCV
2. Edit your `build_config.rb`.

```ruby
  conf.gem 'path/to/here' do |g|
    g.cxx.include_paths << 'path/to/OpenCV/modules/core/include'
    g.cxx.include_paths << 'path/to/OpenCV/modules/highgui/include'
    g.linker.library_paths << 'path/to/OpenCV libraries'
  end
```


