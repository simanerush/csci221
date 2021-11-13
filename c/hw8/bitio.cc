
#include <cassert>
#include <iostream>
#include "bitio.hh"

BitInput::BitInput(std::istream &is) : is_(&is), value_(0), index_(-1) {}


// Takes a character and deconstructs it to a sequence of bits
bool BitInput::input_bit() {
  assert(is_);
  // Sets the index to the most significant value in the character
  if (index_ < 0) {
    // Get the next value from the source
    value_ = is_->get();
    index_ = CHAR_BIT - 1;
  }
  // Bit-wise shift by index and anding
  auto bit = value_ & (1 << index_);
  index_--;
  return bool(bit);
}

BitOutput::BitOutput(std::ostream &os) : os_(&os), value_(0), index_(CHAR_BIT-1) {}

// Send any additional bits to the output string
BitOutput::~BitOutput() {
  if (index_ != CHAR_BIT - 1) {
    assert(os_);
    os_->put(value_);
  }
}

// Takes bits and turns them into a character
void BitOutput::output_bit(bool bit) {
  assert(os_);
  // Rewriting the individual bit 
  value_ |= char(bit) << index_;
  // Decrease index by 1 to rewrite the next bit
  index_--;
  // When we got the character, put it to the ostream
  if (index_ < 0) {
    os_->put(value_);
    // Clear the intermediate  value
    value_ = 0;
    index_ = CHAR_BIT - 1;
  }
}
