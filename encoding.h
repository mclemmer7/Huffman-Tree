/*
 * Filename: Encoding.h
 * Description: Declaration of the class Encoding to represent the encoding table nodes from the huffman tree
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include "tree.h"

#include <string>
using std::string;

#ifndef HUFFMAN_MCLEMMER7_ENCODING_H
#define HUFFMAN_MCLEMMER7_ENCODING_H


class Encoding {
    string _element;
    string _code;

public:
    Encoding();
    Encoding(string element, string code);
    string ToString() const;
    string GetElement();
    string GetCode();
};


#endif //HUFFMAN_MCLEMMER7_ENCODING_H
