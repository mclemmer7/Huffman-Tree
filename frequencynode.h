/*
 * Filename: frequencynode.h
 * Description: Declaration of the frequencynode class to represent the frequency node to put in
 * the frequency table generated from a file
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include <string>
using std::string;

#ifndef HUFFMAN_MCLEMMER7_NODE_H
#define HUFFMAN_MCLEMMER7_NODE_H


class FrequencyNode {
    string _element;
    size_t _frequency;

public:
    FrequencyNode();
    FrequencyNode(string element, size_t frequency);
    void IncreaseFrequency();
    string ToString()const;
    string GetElement()const;
    size_t GetFrequency()const;
    bool FindGreater(const FrequencyNode *other)const;
};


#endif //HUFFMAN_MCLEMMER7_NODE_H
