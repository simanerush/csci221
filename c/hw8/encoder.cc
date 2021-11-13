
#include <cassert>
#include <fstream>
#include <iostream>

#include "bitio.hh"
#include "huffman.hh"

// Get parameters from command-line
int main(int argc, char* argv[]) {
    assert(argc >= 2);
    auto file = argv[1];
    // Create a file stream that reads from the file name that's given
    std::fstream fs{file};
    // Results - bit string
    Huffman::bits_t value {};
    Huffman huffman{};
    auto fileOut = std::string(file) + ".comp";
    // Creates another stream for output which path is fileOut, we want it to be writable, clears the file when we open it
    std::fstream out{fileOut, std::fstream::out | std::fstream::trunc};
    // Creating an instance of BitOutput
    BitOutput bitOut{out};
    while (true) {
        auto byte = fs.get();
        if (fs.eof()) {
            break;
        }
        // Adding the encoded bytes vector to value
        auto encoded = huffman.encode(byte);
        for (const auto x : encoded) {
            bitOut.output_bit(x);
        }
    }
    // Write eof in the ned
    for (const auto x : huffman.encode(Huffman::HEOF)) {
        bitOut.output_bit(x);
    }
    return 0;
}
