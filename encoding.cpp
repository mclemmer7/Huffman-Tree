/*
 * Filename: Encoding.cpp
 * Description: Definition of the class Encoding that creates the encoding node to be put in the
 * encoding table generated from the huffman tree
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include "encoding.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

/**
 * Default Constructor
 * Sets the element and code to an empty string
 */
Encoding::Encoding() : _element(""), _code("") {
}

/**
 * Constructor
 * Sets the element and code to the given values
 * @param element the element for the encoding node
 * @param code the code of 0s and 1s for the encoding table
 */
Encoding::Encoding(string element, string code) : _element(element), _code(code) {
}

/**
 * ToString
 * Creates a string representation of the encoding node
 * @return the string with the key and code for the encoding node
 */
string Encoding::ToString() const {
    stringstream retVal;
    if (_element == "CR" || _element == "LF") {
        retVal << "{key: " << _element << ", code: " << _code << "}";
    } else {
        retVal << "{key:  " << _element << ", code: " << _code << "}";
    }
    return retVal.str();
}

/**
 * Element Accessor
 * @return the element of encoding
 */
string Encoding::GetElement() {
    return _element;
}

/**
 * Code Accessor
 * @return the code of encoding
 */
string Encoding::GetCode() {
    return _code;
}
