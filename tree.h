/*
 * Filename: tree.h
 * Description: Declaration of the tree class that creates the huffman tree
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include "frequencynode.h"

#include <string>
#include <vector>

using std::vector;

#ifndef HUFFMAN_MCLEMMER7_TREE_H
#define HUFFMAN_MCLEMMER7_TREE_H


class Tree {
public:
    struct TreeNode{

        FrequencyNode* data;
        TreeNode* leftChild = nullptr;
        TreeNode* rightChild = nullptr;
    };
private:
    TreeNode* _root;

    Tree& operator=(const Tree& rhs);
    Tree();

public:
    Tree(const Tree& other);
    explicit Tree(const vector<FrequencyNode*>& table);
    ~Tree();
    void DestroyTree(TreeNode* current);
    TreeNode* Create(const vector<FrequencyNode*>& table);
    size_t MaxPosition(const vector<TreeNode*>& table, size_t size, size_t maxIndex);
    void SelectionSort(vector<TreeNode*>& table, size_t size, size_t currentIndex);
    bool FindGreater(const TreeNode* one, const TreeNode* two) const;
    TreeNode* GetRoot();
};


#endif //HUFFMAN_MCLEMMER7_TREE_H
