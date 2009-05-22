require File.dirname(__FILE__) + '/test_helper.rb'

require "test/unit"
class BarcodescannerTest < Test::Unit::TestCase
  def setup
  end

  def teardown
  end

  def test_1
    expected = 
      [{:type=>"EAN-13", :data=>"1920222007009"},
       {:type=>"ISBN-10", :data=>"4087204251"}]
    result = BarcodeScanner.process_image_file("#{File.expand_path(File.dirname(__FILE__))}/test.png")
    assert_equal(expected, result)
  end
end
