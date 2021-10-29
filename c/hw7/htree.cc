/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"

HTree::HTree(key_t key, value_t value, tree_ptr_t left, tree_ptr_t right)
  : key_(key), value_(value), left_(left), right_(right) {}

HTree::key_t HTree::get_key() const {
  return key_;
}

HTree::value_t HTree::get_value() const {
  return value_;
}

HTree::tree_ptr_t HTree::get_child(Direction dir) const {
  switch (dir) {
    case Direction::LEFT:
      return left_;
    case Direction::RIGHT:
      return right_;
  }
}

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr
HTree::possible_path_t HTree::path_to(key_t key) const
{
  if (key == key_) {
    return std::make_unique<HTree::path_t>();
  } else {
    if (left_) {
      auto left = left_->path_to(key);
      if (left) {
        left->push_front(Direction::LEFT);
        return left;
      }
    }
    if (right_) {
      auto right = right_->path_to(key);
      if (right) {
        right->push_front(Direction::RIGHT);
        return right;
      }
    }
    return nullptr;
  }
}
