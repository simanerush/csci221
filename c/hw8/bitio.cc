
#include <cassert>
#include <iostream>
#include "bitio.hh"

BitInput::BitInput(std::istream &is) : is_(&is), value_(0), index_(-1) {}

bool BitInput::input_bit() {
  assert(is_);
  if (index_ < 0) {
    value_ = is_->get();
    index_ = CHAR_BIT - 1;
  }
  // Bit-wise shift
  auto bit = value_ & (1 << index_);
  index_--;
  return bool(bit);
}

BitOutput::BitOutput(std::ostream &os) : os_(&os), value_(0), index_(CHAR_BIT-1){}

BitOutput::~BitOutput() {
  if (index_ != CHAR_BIT - 1) {
    os_->put(value_);
  }
}

void BitOutput::output_bit(bool bit) {
  assert(os_);
  //OR
  value_ |= (bit << index_);
  index_--;
  if (index_ < 0) {
    os_->put(value_);
    //clear the intermediate  value
    value_ = 0;
    index_ = CHAR_BIT - 1;
  }
}
