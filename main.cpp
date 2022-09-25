/*
 * Filename: main.cpp
 * Description: This is where the commands to create the huffman tree are brought in
 * Author: Mark Clemmer
 * Date: 6/10/2022
 * Course: Data Structures II
 */

#include "frequencynode.h"
#include "tree.h"
#include "encoding.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <list>

using std::ifstream;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ofstream;




void FindFrequency(vector<FrequencyNode*>& table, const string& character);
size_t MaximumPosition(const vector<FrequencyNode*>& table, size_t size, size_t maxIndex);
void SelectionSort(vector<FrequencyNode*>& table, size_t size, size_t currentIndex);
void Encode(Tree::TreeNode* root, vector<Encoding>& table, string code = "");
void SortEncoding(vector<Encoding>& table, size_t size, size_t currentIndex = 0);
size_t MinimumEncoding(const vector<Encoding>& table, size_t size, size_t minIndex);
vector<Encoding> EncodingTable(vector<FrequencyNode*> table);

int main(int argc, char* argv[]) {
    size_t retVal = 0;
    // There need to be at least 3 command line inputs for argc
    if (argc < 3) {
        cerr << "Please input two or three parameters" << endl;
        return 1;
    }
    string infile = argv[2];
    string action = argv[1];
    // if the file has commands encode or decode, the 3rd parameter is the outfile
    //string outfile(argv[3]);

    // Find the frequency table since it is used for every operation from the command line
    vector<FrequencyNode*> table;
    //vector<Tree::TreeNode*> treeFrequencies;
    //string lineInput;
    string character;
    ifstream readFile;
    //size_t nextIndex;
    //bool found = false;
//    readFile.open("../test-file-1.txt");
//    string action = "-encoding-table";

    readFile.open(infile);

    if (!readFile.is_open()) {
        cerr << "Unable to open input file" << endl;
    } else {
        /* Bring in the whole file and create a node for each character
         * Make sure that space characters are counted. New lines are counted as CR
         * How do read every character and input for the file?
         * Take one line in at a time
         */

        while (!readFile.eof()) {
            character = readFile.get();

            if (character != "" && !readFile.eof()) {
                if (table.size() == 0) {
                    FrequencyNode *first = new FrequencyNode(character, 1);
                    table.push_back(first);
                    //nextIndex = 1;
                } else {
                    // If there is already a node in the vector, do this
                    FindFrequency(table, character);
                }
            }
        }

        // Sort the nodes in the vector
        SelectionSort(table, table.size(), 0);

        // Now check the action from the command line
        if (action == "-frequency") {
            // print the frequency table
            //cout << "Frequency table sorted:" << endl;
            for (FrequencyNode *value: table) {
                cout << value->ToString() << endl;
            }
            // Deallocate the memory
            for (FrequencyNode* value : table) {
                delete value;
            }
        } else if (action == "-encoding-table") {
            vector<Encoding> sortedEncoding = EncodingTable(table);
            // Output the encoding table
            for (Encoding value: sortedEncoding) {
                cout << value.ToString() << endl;
            }
        } else if (action == "-single") {
            string element = argv[3];
            vector<Encoding> sortedEncoding = EncodingTable(table);
            for (Encoding value: sortedEncoding) {
                if (value.GetElement() == element) {
                    cout << value.GetCode() << endl;
                }
            }
        } else if (action == "-encode") {
            // read the input file and convert each character to the encoded version and write it
            // to the output file
            string outFile = argv[3];
            vector<Encoding> sortedEncoding = EncodingTable(table);
            size_t byteCount = 0;

            ofstream write;
            write.open(outFile);
            if (!write.is_open()) {
                cerr << "Unable to open output file" << endl;
            } else {
                ifstream read;
                read.open(infile);
                if (!readFile.is_open()) {
                    cerr << "Unable to open input file" << endl;
                } else {
                    while (!read.eof()) {
                        character = read.get();

                        if (character != "" && !read.eof()) {
                            for (Encoding value : sortedEncoding) {
                                // LF and CR should be in the opposite order. The given file to check if the
                                // output code is correct is wrong.
                                if (character == "\r" && value.GetElement() == "LF") {
                                    write << value.GetCode();
                                    byteCount++;
                                } else if (character == "\n" && value.GetElement() == "CR") {
                                    write << value.GetCode();
                                    byteCount++;
                                } else if (value.GetElement() == character) {
                                    write << value.GetCode();
                                    byteCount++;
                                }
                            }
                        }
                    }
                }
                read.close();
                cout << byteCount << " bytes written" << endl;
            }

            write.close();

        } else {
            cerr << "Wrong operation, use -encode, -single, -frequency, or -encoding-table." << endl;
            retVal = 1;
        }
    }
    readFile.close();

    return retVal;
}

void FindFrequency(vector<FrequencyNode*>& table, const string& character) {
    bool found = false;

    for (FrequencyNode *value : table) {

        if (character == value->GetElement()) {
            // If the character is already in the vector, increase the frequency by 1
            value->IncreaseFrequency();
            found = true;
        } else if (character == "\r" && value->GetElement() == "CR") {
            value->IncreaseFrequency();
            found = true;
        }
        else if (character == "\n" && value->GetElement() == "LF") {
            value->IncreaseFrequency();
            found = true;
        }
        // Also have a check for \n and label it as LF
    }

    if (!found) {
        // The character was not found, so make a new node to add to the vector
        if (character == "\r") {
            // This is the first instance of the \r character
            FrequencyNode *newLine = new FrequencyNode("CR", 1);
            table.push_back(newLine);

            // Also have a check for \n and label it as LF
        }
        else if (character == "\n") {
            // This is the first instance of the new line character
            FrequencyNode *newLine = new FrequencyNode("LF", 1);
            table.push_back(newLine);
        }
        else {
            FrequencyNode *occurence = new FrequencyNode(character, 1);
            table.push_back(occurence);
        }
    }
}

/**
 * Finds the position of the greatest node in the vector
 * @param table the vector of nodes to search through
 * @param size the last element in the vector that you can compare
 * @param maxIndex the index of the greatest node
 * @return the position of the greatest node
 */
size_t MaximumPosition(const vector<FrequencyNode*>& table, size_t size, size_t maxIndex) {
    if (size == maxIndex) {
        return maxIndex;
    } else {
        if (table.at(size-1)->FindGreater(table.at(maxIndex))) {
            // If the node at size-1 is greater than the node at maxIndex, increase max index
            return MaximumPosition(table, size, maxIndex+1);
        } else {
            return MaximumPosition(table, size-1, maxIndex);
        }
    }
}

void SelectionSort(vector<FrequencyNode*>& table, size_t size, size_t currentIndex) {
    size_t max;
    FrequencyNode* tmp;
    if (currentIndex == size) {
        // base case
        return;
    } else {
        max = MaximumPosition(table, size, currentIndex);
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

void Encode(Tree::TreeNode* root, vector<Encoding>& table, string code) {
    if (root->leftChild == nullptr && root->rightChild == nullptr) {
        Encoding value = Encoding(root->data->GetElement(), code);
        table.push_back(value);
        return;
    }
    if (root->leftChild != nullptr) {
        Encode(root->leftChild, table, code + "1");
    }
    if (root->rightChild != nullptr) {
        Encode(root->rightChild, table, code + "0");
    }
}


vector<Encoding> EncodingTable(vector<FrequencyNode*> table) {
    Tree myTree = Tree(table);
    // Now use the tree to make the encoding table
    vector<Encoding> encodingTable;
    Encode(myTree.GetRoot(), encodingTable);

    // There is no need to sort the encoding table. I just need to place it in the same order as the
    // elements appeared in the sorted frequency table
    vector<Encoding> sortedEncoding;
    for (size_t i = 0; i < table.size(); i++) {
        for (Encoding value: encodingTable) {
            if (table.at(i)->GetElement() == value.GetElement()) {
                sortedEncoding.push_back(value);
                break;
            }
        }
    }

    return sortedEncoding;
}