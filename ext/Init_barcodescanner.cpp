// BarcodeScanner
// zebra binding for ruby
// 
// 2008-11-10 t.koyachi

#include "ruby.h"
#include <stdio.h>
#include <string.h>
#include <Magick++.h>
#include <zebra.h>

typedef VALUE RubyType(...); 

VALUE mod;

VALUE
brcdscnr_s_process_image_file(VALUE self, VALUE filename)
{
    const char* fn = StringValuePtr(filename);
    // そのうちclass変数にしたい
    zebra::Processor* processor = new zebra::Processor(false, NULL, false);
//    zebra::Processor* processor = new zebra::Processor(false);

    Magick::Image image;
    image.read(fn);
    image.modifyImage();

    Magick::Blob scan_data;
    image.write(&scan_data, "GRAY", 8);
    unsigned width = image.columns();
    unsigned height = image.rows();
    if (scan_data.length() != width * height) {
        rb_raise(rb_eException, "scan_data.length(%d) != width(%d) * height(%d)",
                 scan_data.length(), width, height);
    }

    zebra::Image zimage(width, height, "Y800",
                        scan_data.data(), scan_data.length());
    processor->process_image(zimage);

    std::string result;
    for (zebra::Image::SymbolIterator sym = zimage.symbol_begin();
         sym != zimage.symbol_end();
         ++sym)
    {
        result += sym->get_data();
    }
    delete processor;
    return rb_str_new2(result.c_str());
}

#ifdef __cplusplus
extern "C" {
#endif 

void
Init_barcodescanner(void)
{
    mod = rb_define_module("BarcodeScanner");
    rb_define_singleton_method(mod, "process_image_file", (RubyType*)brcdscnr_s_process_image_file, 1);
}

#ifdef __cplusplus
}
#endif  
