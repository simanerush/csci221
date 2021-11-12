#include <cassert>
#include <fstream>
#include <iostream>

#include "bitio.hh"
#include "huffman.hh"

int main(int argc, char* argv[]) {
    assert(argc >= 2);
    auto file = argv[1];
    std::fstream fs{file};
    BitInput bitIn{fs};
    // Vector of decoded values
    std::vector<char> value {};
    Huffman huffman{};
    while(true) {
        auto bit = bitIn.input_bit();
        auto huff = huffman.decode(bit);
        if (huff == Huffman::HEOF) {
            break;
        // If huuf doesn't return a negative symbol, we push it to the decoded value.
        } else if (huff >= 0) {
            value.push_back(huff);
        }
    }

    auto fileOut = std::string(file) + ".plaintext";
    // Create a standard file stream out
    std::fstream out{fileOut, std::ios_base::out | std::fstream::trunc};
    // Push all the values out
    for (const auto chr : value) {
        out << chr;
    }
    return 0;
}
