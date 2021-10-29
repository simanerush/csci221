
#pragma once

#include <vector>
#include "htree.hh"

class HForest {
  public:
    std::size_t size() const;
    void add_tree(HTree::tree_ptr_t tree);
    HTree::tree_ptr_t pop_tree();

  private:
    std::vector<HTree::tree_ptr_t> trees;
};
