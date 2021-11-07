
#include "huffman.hh"
#include "hforest.hh"

Huffman::Huffman() : table_(ALPHABET_SIZE, 0) {}

Huffman::bits_t Huffman::encode(int symbol) {
  auto symb = this->construct_tree();
  auto path = symb->path_to(symbol);
  //Update the table
  table_[symbol]++;
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
    forest.add_tree(std::make_unique<HTree>(i, table_[i]));
  }
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
  auto symb = construct_tree();
  scratch_.push_back(HTree::Direction(bit));
  auto child = get_children(symb, scratch_);
  if (!child) {
    return -1;
  } else if (child->get_key() >= 0){
    table_[child->get_key()]++;
    scratch_.clear();
    return child->get_key();
  } else {
    return -1;
  }
}
