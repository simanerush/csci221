
#include <cassert>
#include <fstream>
#include <iostream>

#include "bitio.hh"
#include "huffman.hh"

// Get paramenters from command-line
int main(int argc, char* argv[]) {
    assert(argc >= 2);
    auto file = argv[1];
    std::fstream fs{file};
    // Results - bit string
    Huffman::bits_t value {};
    Huffman huffman{};
    auto fileOut =std::string(file) + ".comp";
    std::fstream out{fileOut, std::fstream::out | std::fstream::trunc};
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
    // Write ever yencoded bit to the output
    for (const auto x : huffman.encode(Huffman::HEOF)) {
        bitOut.output_bit(x);
    }
    return 0;
}
