# -*- coding: utf-8 -*-
require 'mkmf'

%w[Magick++ Magick Wand zebra].each do |header|
  dir_config(header)
end

depends = []
%w[stdc++ Magick++ Magick Wand zebra].each do |lib|
  depends << have_library(lib)
end

%w[string magick/MagickCore zebra].each do |header|
  depends << have_header("#{header}.h")
end
if depends.all? then
  create_makefile('barcodescanner')
end


