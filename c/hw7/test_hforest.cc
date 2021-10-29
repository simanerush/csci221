
#include "hforest.hh"
#include <iostream>
#include <cassert>

void test_single() {
  HForest forest{};
  auto tree = std::make_shared<HTree>(9,8);
  forest.add_tree(tree);
  assert(forest.pop_tree() == tree);
}

void test_double(std::size_t count) {
  HForest forest{};
  auto trees = std::vector<HTree::tree_ptr_t>();
  for (std::size_t i = 0; i < count; i++) {
    trees.push_back(std::make_shared<HTree>(i,3));
  }
  for (const auto& tree: trees) {
    forest.add_tree(tree);
  }
  for (auto tree = forest.pop_tree(); tree != nullptr; tree = forest.pop_tree()) {
    assert(std::find(trees.begin(), trees.end(), tree) != trees.end());
  }
}

int main() {
  std::cout << "test_single begins" << std::endl;
  test_single();
  std::cout << "test_single() passed!" << std:: endl;
  std::cout << "test_double begins" << std::endl;
  test_double(5);
  std::cout << "test_double(5) passed!" << std:: endl;
  test_double(3);
  std::cout << "test_double(3) passed!" << std:: endl;
  test_double(10);
  std::cout << "test_double(10) passed!" << std:: endl;
  std::cout << "Tests ended" << std::endl;
  return 0;
}
