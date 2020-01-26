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
    Node* find          (std::string word);
    Node* maximum       ();
    Node* minimum       ();
    void inOrderPrint   (Node* currentNode);
    Node* successor     (std::string word);
    Node* predecessor   (std::string word);


public:
    BSTree();                       //Constructor
    ~BSTree();                      //Destructor, as C++ does not have it's own garbage collection
    void search(std::string word);  //Search functions, calls find private function and output the data of the node
    void insert(std::string word);  //Insert function, either updates count or insert new node with given word
    void max();                     //Calls the private function maximum and outputs the value
    void min();                     //Returns the left-most node in the tree
    void printTree();               //Calls private inOrderPrint function, after checking that the tree is not empty
    void next(std::string word);
    void previous(std::string word);
};


#endif //BST_BSTREE_H
