// BarcodeScanner
// zbar binding for ruby
// 
// 2008-11-10 t.koyachi

#include "ruby.h"
#include <stdio.h>
#include <string.h>
#include <Magick++.h>
#include <zbar.h>

typedef VALUE RubyType(...); 

VALUE mod;

VALUE
brcdscnr_s_process_image_file(VALUE self, VALUE filename)
{
    const char* fn = StringValuePtr(filename);
    
		// create a reader
		zbar::ImageScanner scanner;
		
		// configure the reader
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

		// read image file
    Magick::Image image(fn); 
		
		// convert to gray
		image.modifyImage();
		Magick::Blob scan_data;
    image.write(&scan_data, "GRAY", 8);
    
		// obtain image data
		unsigned width = image.columns();
    unsigned height = image.rows();

		// image error
    if (scan_data.length() != width * height) {
        rb_raise(rb_eException, "scan_data.length(%d) != width(%d) * height(%d)",
                 scan_data.length(), width, height);
    }

		// wrap image data
		const void *raw = scan_data.data();
		
    zbar::Image zimage(width, height, "Y800",
                        raw, scan_data.length());
    
		// scan the image for barcodes
    int n = scanner.scan(zimage);

		// support multiple values
		VALUE return_array = rb_ary_new();
		
    std::string type, data;
    for (zbar::Image::SymbolIterator sym = zimage.symbol_begin();
         sym != zimage.symbol_end();
         ++sym)
    {				
				type = sym->get_type_name();
				data = sym->get_data();
	
				VALUE hash_for_type_and_data = rb_hash_new();
				rb_hash_aset(hash_for_type_and_data, 
					ID2SYM(rb_intern("type")), rb_str_new2(type.c_str()));
				
				rb_hash_aset(hash_for_type_and_data, 
					ID2SYM(rb_intern("data")), rb_str_new2(data.c_str()));
				
				rb_ary_push(return_array, hash_for_type_and_data);
    }

		// clean up
    zimage.set_data(NULL, 0);

		// return data
    //return rb_str_new2(result.c_str());

		return return_array;
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
