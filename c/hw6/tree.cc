#include "tree.hh"

//////////////////////////////////////////////////////////////////////////////
tree_ptr_t
create_tree(const key_type& key,
            const value_type& value,
            tree_ptr_t left,
            tree_ptr_t right)
{
  return new Tree({key, value, left, right});
}


//////////////////////////////////////////////////////////////////////////////
void
destroy_tree(tree_ptr_t tree)
{
  if (tree) {
    destroy_tree(tree->left_);
    destroy_tree(tree->right_);
    delete tree;
  }
}


//////////////////////////////////////////////////////////////////////////////
std::string
path_to(tree_ptr_t tree, key_type key)
{
  if (tree) {
    if (key == tree->key_) {
      return "";
    } else {
      auto left = path_to(tree->left_, key);
      if (left != "-") {
        return "L" + left;
      }
      auto right = path_to(tree->right_, key);
      if (right != "-") {
        return "R" + right;
      } else {
        return "-";
      }
    }
  } else {
    return "-";
  }
}


//////////////////////////////////////////////////////////////////////////////
tree_ptr_t
node_at(tree_ptr_t tree, std::string path)
{
  if (!tree) {
    return nullptr;
  } else if (path.empty()) {
    return tree;
  }
  switch (path[0]) {
    case 'L':
      return node_at(tree->left_, path.substr(1));
    case 'R':
      return node_at(tree->right_, path.substr(1));
    default:
      return nullptr;
  }
}
