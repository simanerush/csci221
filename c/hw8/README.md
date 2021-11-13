# Documentation for HW8: Huffman Encoding
Serafima Nerush, Patrick Norton

## Code Design

# Huffman.hh and Huffman.cc

In `huffman.hh` class private section, we declared the symbol frequency table, as well as `scratch_` and `scratch_tree_` variables for recording intermediate directions and tree. 

in `huffman.cc`, the first function is `encode`, which constructs a tree pointer and calculates path to a given symbol, updating the frequency table. Then is returns a sequence of boolean values representing a path.

`construct_tree` function creates a tree node for every character in the frequency table. Then, it connects those nodes together until all nodes are connected to each other.

Helper function `get_children` returns a child for a given path by walking this path.

`decode` function creates a `scratch_tree_` if needed. We also add the direction to the given bit to `scratch_`. We also get a child for a given `scratch_` and `scratch_tree_`. If we cannot find it, we return -1. Else, we update the frequency table for the new found character, clear `scratch_` and `scratch_tree_`, and return the decoded value. 

# Bitio.h and Bitio.cc

In both classes in `Bitio.hh` in private methods, we defined stream, value and index variables.

In `bitio.cc`, in `input_bit` function we are getting the next bit from the input, while setting index to the first character in the value. Note that we are initializing index to -1. To get the current bit, we are shifting the value by index and ANDing it with 1. 

Destructor of output also puts any leftover values that are less than length of char to the stream. 

`output_bit` turns every individual bit into a character. When index becomes less than 0, we are putting the value to the stream and clearing the intermediate value.

# Encoder.cc and Decoder.cc

The `main` function of `Encoder.cc` and `Decoder.cc` are well-documented with code comments in those files





