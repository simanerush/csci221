#include <cassert>
#include <iostream>

#include "tree.hh"


void test_create() {
  auto tree_a = create_tree(0, 57);
  assert(tree_a->key_ == 0);
  assert(tree_a->value_ == 57);
  assert(tree_a->left_ == nullptr);
  assert(tree_a->right_ == nullptr);
  destroy_tree(tree_a);

  auto tree_bl = create_tree(2, 80);
  auto tree_br = create_tree(13, 30);
  auto tree_b = create_tree(23, 45, tree_bl, tree_br);
  assert(tree_b->key_ == 23);
  assert(tree_b->value_ == 45);
  assert(tree_b->left_ == tree_bl);
  assert(tree_b->right_ == tree_br);
  destroy_tree(tree_b);
}

void test_destroy() {

}

void test_path_to() {
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
  auto tree_a  = create_tree(9, 34);
  auto tree_b = create_tree(6, 33, tree_a);
  auto tree_c = create_tree(12, 44);
  auto tree_d = create_tree(3, 43);
  auto tree_e = create_tree(-5, 22, tree_c, tree_b);
  auto tree_f = create_tree(12, 222, tree_d);

  auto test_tree = create_tree(126,1, tree_e, tree_f);

  assert(path_to(test_tree, 9) == "LRL");
  assert(path_to(test_tree, 3) == "RL");
  assert(path_to(test_tree, 126) == "");
  assert(path_to(test_tree, 0) == "-");
}

void test_node_at() {
  auto tree_a  = create_tree(9, 34);
  auto tree_b = create_tree(6, 33, tree_a);
  auto tree_c = create_tree(12, 44);
  auto tree_d = create_tree(3, 43);
  auto tree_e = create_tree(-5, 22, tree_c, tree_b);
  auto tree_f = create_tree(12, 222, tree_d);

  auto test_tree = create_tree(126,1, tree_e, tree_f);

  assert(node_at(test_tree, "LRL") && node_at(test_tree, "LRL")->key_ == 9);
  assert(node_at(test_tree, "RL") && node_at(test_tree, "RL")->key_ == 3);
  assert(node_at(test_tree, "") && node_at(test_tree, "")->key_ == 126);
  assert(node_at(test_tree, "hi") == nullptr);
}

int main() {
  std::cout << "Tests begin" << std::endl;
  test_create();
  std::cout << "test_create() successful" << std::endl;
  test_destroy();
  std::cout << "test_destroy() successful" << std::endl;
  test_path_to();
  std::cout << "test_path_to() successful" << std::endl;
  test_node_at();
  std::cout << "test_node_at() successful" << std::endl;
  std::cout << "Tests ended" << std::endl;
  return 0;
}
