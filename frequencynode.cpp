/*
 * Filename: frequencynode.cpp
 * Description: Definition of the frequencynode class that creates the frequency node to store in
 * the frequency table generated from a file
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include "frequencynode.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

/**
 * Default Constructor
 * Sets the element to an empty string and the frequency to 0
 */
FrequencyNode::FrequencyNode() : _element(""), _frequency(0) {
}

/**
 * Constructor
 * Sets the element and frequency to the given values
 * @param element the element for the frequency node
 * @param frequency the frequency for the frequency node
 */
FrequencyNode::FrequencyNode(string element, size_t frequency) : _element(element), _frequency(frequency) {

}

/**
 * Increases the frequency of the character by 1
 */
void FrequencyNode::IncreaseFrequency() {
    _frequency++;
}

/**
 ToString
 * Creates a string representation of the frequency node
 * @return the string with the element and code for the frequency node
 */
string FrequencyNode::ToString() const {
    stringstream retVal;
    if (_element == "CR" || _element == "LF") {
        retVal << "{element: " << _element << ", frequency: " << _frequency << "}";
    } else {
        retVal << "{element:  " << _element << ", frequency: " << _frequency << "}";
    }
    return retVal.str();
}

/**
 * Element Accessor
 * @return the element of the node
 */
string FrequencyNode::GetElement() const {
    return _element;
}

/**
 * Frequency Accessor
 * @return the frequency of the node
 */
size_t FrequencyNode::GetFrequency() const {
    return _frequency;
}

/**
 * Compares the two nodes to see which is greater
 * @param other the input node to compare
 * @return true if the current node is greater than the input node and false if it is not
 */
bool FrequencyNode::FindGreater(const FrequencyNode* other) const {
    if (_frequency == other->GetFrequency()) {
        return _element > other->GetElement();
    } else {
        return _frequency > other->GetFrequency();
    }
}