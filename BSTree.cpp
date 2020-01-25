//
// Created by Carlos Galo on 1/22/20.
//

#include "BSTree.h"
#include <iostream> //For cout and endl

//BSTree basic constructor
BSTree::BSTree()
{
    root = NULL;
}   //End of constructor

//Destructor for BSTree object
//  -Goes through the tree and deletes all nodes in the tree
BSTree::~BSTree()
{

}   //End of destructor

//Find function, returns a node struct
//  -Searches the tree to find the node holding the word in the parameter. Two cases to return:
//  1. If tree holds the node with the given word, it'll return that node
//  2. Else returns the parent node of where we should insert the new node
//ONLY call this function after checking if the root is not null
BSTree::Node * BSTree::find(std::string word)
{
    Node* currentNode = root;   //Start from the root of the tree and we work ourselves down
    Node* parentNode  = NULL;   //This will be returned if we do not find the word in the tree
    while (currentNode != NULL) //Traverse until we hit a leaf in the tree
    {
        if (currentNode->data == word)  //First case, the word is in the tree
        {
            return currentNode; //Return the node that contains the word we are looking for
        }   //End of if the current Node contains the word we are looking for
        else    //Else the node does not contain the word, we traverse either left or right
        {
            parentNode = currentNode;   //Save the parentNode before moving the currentNode reference

            if (word < currentNode->data)   //If the word is lesser than the currentNode's data
                currentNode = currentNode->leftChild;   //We move to the left child
            else                            //Else the word is greater than the currentNode's data
                currentNode = currentNode->rightChild;  //We move to the right child
        }   //End of else, if the word was not in the currentNode
    }   //End of while-loop, we finished traversing the tree
    //We get here if we did not find the Node containing the word, we return the parentNode
    return parentNode;  //Return parentNode
}   //End of find function, returns struct Node

//Search function
//  -Calls find function and checks the result, prints information in the node
void BSTree::search(std::string word)
{
    if (root == NULL)   //If the tree is empty
    {
        std::cout << "Error!Empty Tree" << std::endl; //Print empty line
    }   //End of if the tree is empty
    else                //Else the tree is not empty
    {
        Node* findNode = find(word);    //Call and save the node returned by the find function
        if (findNode->data == word)     //If the find returned a node with the word we are looking for
        {
            std::cout << findNode->data << ": " << findNode->count << std::endl;    //Print node's information
        }   //End of if the find returned a node with the word we were looking for
        else    //Else the find did not returned the node we are looking for
        {
            std::cout << word << ": " << 0 << std::endl;
        }   //End of else, if the findNode does not contain the word
    }   //End of else, if the tree is not empty
}   //End of search function

//Insert function
//  -Uses find function to check if the tree contains the word we are looking for
//      -- If we find the node, we update the count by adding 1 int
//      -- Else we insert the new Node as a child of the returned result of the find function
void BSTree::insert(std::string word)
{
    if (root == NULL)   //If the tree is empty, we insert node as root
    {
        root = new Node(word);
    }   //End of if the tree is empty
    else                //Else the tree is not empty
    {
        Node* findNode = find(word);    //Call and save the result of the find function
        if (findNode->data == word)     //If the findNode contains the word we are looking for, update count
        {
            findNode->count++;  //Update the count by adding 1
        }   //End of if the findNode contains the word
        else                            //Else the findNode is the parentNode we have to insert new child
        {
            Node* parentNode = findNode;        //Save the findNode as parentNode
            Node* insertNode = new Node(word);  //Create a new node to insert as a child
            insertNode->parentNode   = parentNode;  //Connect the insertNode to the parentNode
            if (word < parentNode->data)
            {
                parentNode->leftChild = insertNode; //Insert the new node as left child
            }   //End of if the word being inserted is less than the parentNode, insert left
            else                        //Else the word is greater than parentNode's data, insert right
            {
                parentNode->rightChild = insertNode;    //Insert new node as right child;
            }   //Else if the word is greater than parentNode, insert right
        }   //End of else, if the findNode is the parentNode
    }   //End of else, if the the tree is not empty
}   //End of insert function

BSTree::Node * BSTree::maximum()
{
    Node* currentNode = root;                   //Start from the root to traverse the tree
    while (currentNode->rightChild != NULL)     //Traverse the right side of the tree
        currentNode = currentNode->rightChild;  //Keep moving until the right-most node
    return currentNode;                         //Return the right-most node

}   //End of maximum function

void BSTree::max()
{

    if (root == NULL)   //First check if the tree is empty
    {
        std::cout << std::endl; //Print empty line (no output)
    }   //End of if tree is empty
    else                //Else the tree is not empty, we call maximum function
    {
        Node* max = maximum();  //Get and save the result of the maximum function
        std::cout << max->data << std::endl;    //Print the node's word
    }
}