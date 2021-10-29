# Homework 7 Documentation

## htree.hh

For the ` ~HTree `, I've added the default behavior for C++ to get rid of the object.
In ` private ` section, I've added ` key_ `, ` value_ `, ` left_ ` and ` right_ ` properties of ` HTree ` class.

## htree.cc

The constructor assigns the ` HTree ` object properties the desired ones.

The ` get_value() ` method returns the ` value_ ` property of the object.

In ` get_child ` method, I used ` switch ` statement to return the appropriate child based on the ` Direction ` object passed.

The ` path_to ` method uses recursion. If the passed ` key ` matches the current ` key_ `, it returns a pointer to an empty ` path_t ` list. If there is a ` left_ ` child, it calls ` path_to ` method on it and pushes the ` LEFT ` direction to the beginning of the return list. It does the identical work for ` right_ ` child.

## test_htree.cc

` create_sample_tree ` returns a unique pointer pointing to a sample tree. ` test_create() ` creates a tree and asserts that the properties are the same as they were defined. ` test_path_to() ` uses assertion methods to dereference a pointer to a path and assert that this path is a desired list of ` Direction ` objects.

## hforest.hh

In ` private ` section, I've defined a ` trees ` vector of ` HTree::tree_ptr_t ` objects.

## hforest.cc

` compare_trees ` returns the boolean value indicating if the second tree value is bigger than the first tree value.

` size() ` method returns the ` .size ` property of ` trees ` vector.

` add_tree ` method returns nothing and adds a ` HTree ` object to ` trees ` vector by using ` push_back ` method. After that, we push trees to the heap, passing in the previously written ` compare_trees ` method.

` pop_tree() ` method returns a pointer to a removed ` HTree ` object with the highest value. First, it checks if ` trees ` vector is empty, and if it is, returns ` nullptr `. Then, it uses ` pop_heap ` method to move the ` HTree ` object with the highest value to the back of the heap. After that, it gets the pointer to the last element, removes it from the back and returns the pointer.

## test_hforest

` test_single() ` initializes a ` HForest ` object and adds two ` HTree ` objects to it. Then, it checks if ` pop_tree ` method removes the ` HTree ` with the highest value and returns the pointer to it. ` test_double() ` initializes the empty ` HForest ` object and the empty ` vector ` of ` HTree ` objects. The ` HTree ` objects are initialized in a ` for ` loop. In the second ` for ` loop, initialized trees are added to the forest. Then it makes sure that for every tree that gets popped, the pointer to the popped tree is in ` trees ` vector.  
