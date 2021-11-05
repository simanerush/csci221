
#include "hforest.hh"

//Tree comparison: 1. value 2. number of children 3. key value
static bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
  if (t1->get_value() != t2->get_value()) {
    return t1->get_value() > t2->get_value();
  } else if (t1->child_count() != t2->child_count()) {
    return t1->child_count() > t2->child_count();
  } else {
    return t1->get_key() > t2->get_key();
  }
}

std::size_t HForest::size() const {
  return trees.size();
}

void HForest::add_tree(HTree::tree_ptr_t tree) {
  trees.push_back(tree);
  std::push_heap(trees.begin(), trees.end(), compare_trees);
}

HTree::tree_ptr_t HForest::pop_tree() {
  if (trees.empty()) {
    return nullptr;
  }
  std::pop_heap(trees.begin(), trees.end(), compare_trees);
  HTree::tree_ptr_t last = trees.back(); // Get the pointer to the last element
  trees.pop_back();
  return last;
}
