# -*- coding: utf-8 -*-
require 'mkmf'

%w[Magick++ Magick zebra].each do |header|
  dir_config(header)
end

$CFLAGS =     ENV['CFLAGS'].to_s   + ' ' + `Magick-config --cflags`.chomp
$CPPFLAGS =   ENV['CPPFLAGS'].to_s + ' ' + `Magick-config --cppflags`.chomp
$LDFLAGS =    ENV['LDFLAGS'].to_s  + ' ' + `Magick-config --ldflags`.chomp
$LOCAL_LIBS = ENV['LIBS'].to_s     + ' ' + `Magick-config --libs`.chomp

depends = []
%w[stdc++ Magick++ Magick zebra].each do |lib|
  depends << have_library(lib)
end

%w[string zebra].each do |header|
  depends << have_header("#{header}.h")
end
if depends.all? then
  create_makefile('barcodescanner')
end


