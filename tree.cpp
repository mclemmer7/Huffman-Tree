/*
 * Filename: tree.cpp
 * Description: Definition of the tree class that creates the huffman tree
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include "tree.h"

#include <vector>
#include <iostream>

using std::vector;
using std::endl;
using std::cout;

/**
 * Copy Assignment Operator
 * Enables the deep copy assignment using the operator = overload. This
 * method is kept private to avoid usage from clients of the class.
 * This method also relies on the Clone method to create copies of the
 * elements.
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
Tree& Tree::operator=(const Tree& rhs) {
    return *this;
}
/**
 * Copy Constructor
 * @param other the tree to be copied
 */
Tree::Tree(const Tree& other) {}

/**
 * Default constructor that is private, so can't be used
 */
Tree::Tree() : _root(nullptr) {}

/**
 * Constructor
 * Sets the root to be the returned value from Create, which is the root node of the tree that
 * has just been created.
 * @param table the frequency table that is brought in to create the tree
 */
Tree::Tree(const vector<FrequencyNode*>& table) {
    _root = Create(table);
}

/**
 * Destructor
 * It frees the dynamic memory allocated for the tree, and does so by traversing the vector of
 * tree nodes and releasing the memory of each element and then its tree node.
 */
Tree::~Tree() {
    if (_root != nullptr) {
        DestroyTree(_root);
    }
}

/**
 * Part of the destructor that uses recursion to traverse the tree and delete all tree nodes.
 * @param current
 */
void Tree::DestroyTree(TreeNode* current) {
    if (current->leftChild) {
        DestroyTree(current->leftChild);
    }
    if (current->rightChild) {
        DestroyTree(current->rightChild);
    }

    delete current->data;
    delete current;
}

/**
 * This creates the huffman tree by making a table of tree nodes and 2 nodes are removed from the
 * table to make a parent node with the merged elements and frequencies. This function then stops
 * when there is one TreeNode left in the vector, which is the root of the tree, which is returned.
 * @param table the frequency table brought in to turn into the tree node table
 * @return the root of the tree
 */
Tree::TreeNode* Tree::Create(const vector<FrequencyNode*>& table) {
    vector<TreeNode*> treeTable;
    string newElement;
    size_t newFrequency;

    // Make a frequency table of tree nodes
    for (FrequencyNode* value : table) {
        TreeNode* leaf = new TreeNode;
        leaf->data = value;
        leaf->leftChild = nullptr;
        leaf->rightChild = nullptr;
        treeTable.push_back(leaf);
    }

    // Make the tree by pulling in the smallest two elements at a time to make a parent, then insert
    // that parent into the frequency table after removing the two elements. Resort the frequency table
    while (treeTable.size() > 1) {
        TreeNode* left = treeTable.back();
        treeTable.pop_back();
        TreeNode* right = treeTable.back();
        treeTable.pop_back();

        newElement = left->data->GetElement() + right->data->GetElement();
        newFrequency = left->data->GetFrequency() + right->data->GetFrequency();
        FrequencyNode* father = new FrequencyNode(newElement, newFrequency);

        TreeNode* parent = new TreeNode;
        parent->data = father;
        parent->leftChild = left;
        parent->rightChild = right;

        // Put the parent into the tree
        treeTable.push_back(parent);

        // Sort the table again
        SelectionSort(treeTable, treeTable.size(), 0);
    }

    // table size is equal to 1 now, so return the last treeNode
    return treeTable.at(0);
}

/**
 * Finds the position of the greatest node in the vector
 * @param table the vector of nodes to search through
 * @param size the last element in the vector that you can compare
 * @param maxIndex the index of the greatest node
 * @return the position of the greatest node
 */
size_t Tree::MaxPosition(const vector<TreeNode*>& table, size_t size, size_t maxIndex) {
    if (size == maxIndex) {
        return maxIndex;
    } else {
        if (FindGreater(table.at(size-1), table.at(maxIndex))) {
            // If the treeNode at size-1 is greater than the treeNode at maxIndex, increase max index
            return MaxPosition(table, size, maxIndex+1);
        } else {
            return MaxPosition(table, size-1, maxIndex);
        }
    }
}

/**
 * Selection Sort
 * Sorts the input table of TreeNodes recursively and uses MaxPosition() to find the greatest
 * TreeNode.
 * @param table the input table to sort
 * @param size the current size of the table
 * @param currentIndex the index that is being compared
 */
void Tree::SelectionSort(vector<TreeNode*>& table, size_t size, size_t currentIndex) {
    size_t max;
    TreeNode* tmp;
    if (currentIndex == size) {
        // base case
        return;
    } else {
        max = MaxPosition(table, size, currentIndex);
        // Swap the first array element with the minimum element
        // use size as the index

        if (currentIndex == max) {
            // go to the next call
            SelectionSort(table, size, currentIndex + 1);
        } else {

            tmp = table.at(max);
            table.at(max) = table.at(currentIndex);
            table.at(currentIndex) = tmp;

            SelectionSort(table, size, currentIndex + 1);
        }
    }
}

/**
 * Compares the two nodes to see which is greater
 * @param other the input node to compare
 * @return true if the current node is greater than the input node and false if it is not
 */
bool Tree::FindGreater(const TreeNode* one, const TreeNode* two) const {
    if (one->data->GetFrequency() == two->data->GetFrequency()) {
        // Only compare the first letter of the elements
        return one->data->GetElement().at(0) > two->data->GetElement().at(0);
    } else {
        return one->data->GetFrequency() > two->data->GetFrequency();
    }
}

/**
 * Root Accessor
 * @return the root of the tree
 */
Tree::TreeNode* Tree::GetRoot() {
    return _root;
}
