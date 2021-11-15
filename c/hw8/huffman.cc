
#include <cassert>
#include "huffman.hh"
#include "hforest.hh"

Huffman::Huffman() : table_(ALPHABET_SIZE, 0), scratch_(), scratch_tree_(nullptr) {}

Huffman::bits_t Huffman::encode(int symbol) {
  auto symb = this->construct_tree();
  auto path = symb->path_to(symbol);
  //Update the table
  table_[symbol]++;
  // Create Huffman::bits_t
  // Change the result from the list of Directions to the list of Booleans
  auto result = std::vector<bool>();
  for (const auto value : *path) {
    result.push_back(static_cast<bool>(value));
  }
  return result;
}

HTree::tree_ptr_t Huffman::construct_tree() const {
  int index = -1;
  HForest forest{};
  for (size_t i = 0; i < table_.size(); i++) {
    // For each character in the alphabet, create a Tree node with that character and the number of uses of it
    forest.add_tree(std::make_unique<HTree>(i, table_[i]));
  }

  // Connect independent leaves
  while (forest.size() > 1) {
    //Remove two lowest trees
    auto left = forest.pop_tree();
    auto right = forest.pop_tree();
    //Calculate sum of their values
    auto count = left->get_value() + right->get_value();
    //Construct a new tree
    forest.add_tree(std::make_unique<HTree>(index--, count, left, right));
  }
  //Return the constructed tree
  return forest.pop_tree();
}

// Helper function, static bc it isn't the part of any class
// Returns a child for a specified direction by walking a path
static HTree::tree_ptr_t get_children(HTree::tree_ptr_t& parent, std::vector<HTree::Direction>& path) {
  auto current = parent;
  for (const auto& x : path) {
    if (!current) {
      return nullptr;
    } else {
      current = current->get_child(x);
    }
  }
  return current;
}

int Huffman::decode(bool bit) {
  // If scratch_tree_ is empty, our scratch path must be too (either they're both empty or both non-empty)
  assert(scratch_tree_ != nullptr ^ scratch_.empty());
  // If the table did not change, then we don't need to reconstruct the tree
  if (!scratch_tree_) {
    auto tree = construct_tree();
    scratch_tree_ = tree;
  }
  scratch_.push_back(HTree::Direction(bit));
  auto child = get_children(scratch_tree_, scratch_);
  if (!child) {
    return -1;
  } else if (child->get_key() >= 0){
    // Update the table based on the new found symbol
    table_[child->get_key()]++;
    scratch_.clear();
    scratch_tree_ = nullptr;
    // Return the decoded character
    return child->get_key();
  } else {
    return -1;
  }
}

// Optimized Huffman encoding that uses a heap instead of a binary tree

static bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
  if (t1->get_value() != t2->get_value()) {
    return t1->get_value() > t2->get_value();
  } else if (t1->child_count() != t2->child_count()) {
    return t1->child_count() > t2->child_count();
  } else {
    return t1->get_key() > t2->get_key();
  }
}
