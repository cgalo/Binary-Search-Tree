//
// Created by Carlos Galo on 1/22/20.
//

#ifndef BST_BSTREE_H
#define BST_BSTREE_H

#include <string>   //Utilized to save data as string
#include <iostream>
class BSTree {
private:
    //Create node struct that holds a string, frequency of the string, and reference to its left and right child
    struct Node
    {
        std::string data;                           //Word stored in the node
        int count;                                  //Frequency of the occurrence of the word
        Node *leftChild, *rightChild, *parentNode;  //Reference nodes, to the node's parent and children

        Node(std::string word)  //Constructor given a string
        {
            data = word;
            count = 1;
            parentNode = leftChild = rightChild = NULL;
        }   //End of constructor
    };  //End of Node struct
    Node* root = NULL; //Root, or beginning, of the tree
    Node* find          (std::string word); //Looks for node w/ word in the tree, returns node or parent node
    Node* insertion     (std::string word); //
    Node* maximum       (Node* currentNode);
    Node* minimum       (Node* currentNode);
    void inOrderPrint   (Node* currentNode, int count);
    Node* successor     (Node* currentNode);
    Node* predecessor   (Node* currentNode);
    Node* discardNode   (Node* deleteNode);
    ////The following method should never be called besides by the destructor -> ~BST()
    void treeDestructor (Node* currentNode);    //Traverses the tree to destroy every node in the tree


public:
    BSTree();                       //Constructor
    ~BSTree();                      //Destructor, as C++ does not have it's own garbage collection
    void search(std::string word);  //Search functions, calls find private function and output the data of the node
    void insert(std::string word);  //Insert function, either updates count or insert new node with given word
    void max();                     //Calls the private function maximum and outputs the value
    void min();                     //Returns the left-most node in the tree
    void printTree();               //Calls private inOrderPrint function, after checking that the tree is not empty
    void next(std::string word);    //Calls private successor function, after checking that the tree is not empty
    void previous(std::string word);//Calls private predecessor function, after checking that the tree is not empty
    void remove(std::string word);  //Calls private discard function, after checking that the tree is not empty
    void parent(std::string word);
    void children(std::string word);
};


#endif //BST_BSTREE_H
