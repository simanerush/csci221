# Homework 7 Documentation

## htree.hh

For the ``` ~HTree ```, I've added the default behavior for C++ to get rid of the object.
In ``` private ``` section, I've added ``` key_ ```, ``` value_ ```, ``` left_ ``` and ``` right_ ``` properties of ``` HTree ``` class.

## htree.cc

The constructor assigns the ``` HTree ``` object properties the desired ones.

The ``` get_value() ``` method returns the ``` value_ ``` property of the object.

In ``` get_child ``` method, I used ``` switch ``` statement to return the appropriate child based on the ``` Direction ``` object passed.

The ``` path_to ``` method uses recursion. If the passed ``` key ``` matches the current ``` key_ ```, it returns a pointer to an empty ``` path_t ``` list. If there is a ``` left_ ``` child, it calls ``` path_to ``` method on it and pushes the ``` LEFT ``` direction to the beginning of the return list. It does the identical work for ``` right_ ``` child.

## test_htree.cc

``` create_sample_tree ``` returns a unique pointer pointing to a sample tree. ``` test_create() ``` creates a tree and asserts that the properties are the same as they were defined. ``` test_path_to() ``` uses assertion methods to dereference a pointer to a path and assert that this path is a desired list of ``` Direction ``` objects. 

## hforest.cc

In ``` private ``` section, I've defined a ``` trees ``` vector of ``` HTree::tree_ptr_t ``` objects.  
