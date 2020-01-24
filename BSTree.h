//
// Created by Carlos Galo on 1/22/20.
//

#ifndef BST_BSTREE_H
#define BST_BSTREE_H

#include <string>   //Utilized to save data as string

class BSTree {
private:
    //Create node struct that holds a string, frequency of the string, and reference to its left and right child
    struct Node
    {
        std::string data;                           //Word stored in the node
        int count;                                  //Frequency of the occurrence
        Node *leftChild, *rightChild, *parentNode;  //Reference node, to the node's parent and children

        Node(std::string word)  //Constructor given a word
        {
            data = word;
            count = 1;
            parentNode = leftChild = rightChild = NULL;
        }   //End of constructor
    };  //End of Node struct
    Node* root; //Root, or beginning, of the tree
    Node* find(std::string word);

public:
    BSTree();                       //Constructor
    ~BSTree();                      //Destructor, as C++ does not have it's own garbage collection
    void search(std::string word);  //Search functions, calls private find private function and outputs message
    void insert(std::string word);  //Insert function, either updates count or insert new node with given word
    void max(std::string word);     //Returns the right-most node in the tree
    void min(std::string word);     //Returns the left-most node in the tree

};


#endif //BST_BSTREE_H
