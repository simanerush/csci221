#include <cassert>
#include <iostream>

#include "htree.hh"


std::unique_ptr<HTree> create_sample_tree() {

  std::unique_ptr<HTree>(new HTree(9,34));
  auto tree_a  = std::make_shared<HTree>(9, 34);
  auto tree_b = std::make_shared<HTree>(6, 33, tree_a);
  auto tree_c = std::make_shared<HTree>(12, 44);
  auto tree_d = std::make_shared<HTree>(3, 43);
  auto tree_e = std::make_shared<HTree>(-5, 22, tree_c, tree_b);
  auto tree_f = std::make_shared<HTree>(12, 222, tree_d);

  return std::make_unique<HTree>(126,1, tree_e, tree_f);
}

void test_create() {
  auto tree_a = std::make_unique<HTree>(0,57);
  assert(tree_a->get_key() == 0);
  assert(tree_a->get_value() == 57);
  assert(tree_a->get_child(HTree::Direction::LEFT) == nullptr);
  assert(tree_a->get_child(HTree::Direction::RIGHT) == nullptr);

  auto tree_bl = std::make_shared<HTree>(2, 80);
  auto tree_br = std::make_shared<HTree>(13, 30);
  auto tree_b = std::make_unique<HTree>(23, 45, tree_bl, tree_br);
  assert(tree_b->get_key() == 23);
  assert(tree_b->get_value() == 45);
  assert(tree_b->get_child(HTree::Direction::LEFT)== tree_bl);
  assert(tree_b->get_child(HTree::Direction::RIGHT)== tree_br);
}

void test_path_to() {
  auto test_tree = create_sample_tree();
  /*
              126
             /   \
            /     \
          -5       12
          / \     /
        12   6   3
            /
           9
  */

  assert(*test_tree->path_to(9) == HTree::path_t({HTree::Direction::LEFT,
  HTree::Direction::RIGHT, HTree::Direction::LEFT}));
  assert(*test_tree->path_to(3) == HTree::path_t({HTree::Direction::RIGHT,
  HTree::Direction::LEFT}));
  assert(*test_tree->path_to(126) == HTree::path_t());
  assert(test_tree->path_to(0) == nullptr);
}


int main() {
  std::cout << "Tests begin" << std::endl;
  test_create();
  std::cout << "test_create() successful" << std::endl;
  test_path_to();
  std::cout << "test_path_to() successful" << std::endl;
  std::cout << "Tests ended" << std::endl;
  return 0;
}
