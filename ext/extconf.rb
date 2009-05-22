# -*- coding: utf-8 -*-
require 'mkmf'

%w[Magick++ zbar].each do |header|
  dir_config(header)
end

$CFLAGS =     ENV['CFLAGS'].to_s + ' ' + "-I/opt/local/include -I/usr/local/include"
$CPPFLAGS =   ENV['CPPFLAGS'].to_s + ' ' + `Magick-config --cppflags`.chomp
$CPPFLAGS =   $CPPFLAGS + ' ' + "-I/opt/local/include -I/usr/local/include"
$LDFLAGS =    ENV['LDFLAGS'].to_s  + ' ' + `Magick-config --ldflags`.chomp
$LDFLAGS =    $LDFLAGS + ' ' + "-L/opt/local/lib -L/usr/local/lib"
$LOCAL_LIBS = ENV['LIBS'].to_s + ' ' + `Magick-config --libs`.chomp

depends = []
%w[stdc++ Magick++ zbar].each do |lib|
  depends << have_library(lib)
end

%w[string zbar].each do |header|
  depends << have_header("#{header}.h")
end
if depends.all? then
  create_makefile('barcodescanner')
end


