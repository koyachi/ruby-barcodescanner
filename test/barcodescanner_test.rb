require File.dirname(__FILE__) + '/test_helper.rb'

require "test/unit"
class BarcodescannerTest < Test::Unit::TestCase
  def setup
  end

  def teardown
  end

  def test_1
    expected = '9784087204254'
    result = BarcodeScanner.process_image_file("#{expected}.jpg")
    assert_equal(expected, result)
  end
end
