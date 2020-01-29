#include "BSTree.h"
//
// Created by Carlos Galo on 1/22/20.
//

#include "BSTree.h"
#include <iostream> //For cout and endl

//BSTree basic constructor
BSTree::BSTree()
{
    root = NULL;                //Set the root of the tree to initialize as NULL
}   //End of constructor

//Destructor for BSTree object
//  -Goes through the tree and deletes all nodes in the tree
BSTree::~BSTree()
{
    treeDestructor(root);
}   //End of destructor function

void BSTree::treeDestructor(BSTree::Node *currentNode)
{
    if (currentNode != NULL)
    {
        treeDestructor(currentNode->leftChild);
        treeDestructor(currentNode->rightChild);
        delete currentNode;
    }   //End of if the currentNode is not NULL
    root == NULL;
}   //End of treeDestructor function

//Find function, returns a node struct
//  -Searches the tree to find the node holding the word in the parameter. Two cases to return:
//  1. If tree holds the node with the given word, it'll return that node
//  2. Else returns the parent node of where we should insert the new node
////ONLY call this function after checking if the root is not null
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
    }   //End of else, if the tree is not empty
}   //End of max function

BSTree::Node * BSTree::minimum()
{
    Node* currentNode = root;                   //Start from the root to traverse the tree
    while (currentNode->leftChild != NULL)      //Traverse the left side of the tree
        currentNode = currentNode->leftChild;   //Keep moving until the left-most node
    return currentNode;                         //Return the left-most node
}   //End of minimum function

void BSTree::min()
{
    if (root == NULL)                           //First we check if the tree is empty
        std::cout << std::endl;                 //Print empty line
    else                                        //Else the tree is not empty
    {
        Node* min = minimum();                  //Call and save the maximum private function results
        std::cout << min->data << std::endl;    //Print the min node data
    }   //End of else, if the tree is not empty
}   //End of min function

void BSTree::inOrderPrint(BSTree::Node *currentNode)
{
    if (currentNode == NULL)    //If we reach a leaf
        return;                 //Exit
    inOrderPrint(currentNode->leftChild);   //Traverse through the left side
    std::cout << currentNode->data << ": " << currentNode->count << std::endl;  //Print node's data and count
    inOrderPrint(currentNode->rightChild);  //Traverse through the right side
}   //End of inOrderPrint function

void BSTree::printTree()
{
    if (root == NULL)                   //If the tree is empty
        std::cout << std::endl;         //Print empty line
    else                                //Else the tree is not empty
        inOrderPrint(root); //Call the inOrderPrint function to prin the tree's nodes in-order traversal
}   //End of printTree function

BSTree::Node * BSTree::successor(std::string word)
{
    Node* findNode = find (word);       //Search if the word exists in the tree using find function
    if (findNode->data == word)         //If the find returned a node with the word in the parameter
    {
        //Now we need to check if the node has a rightChild, and if that rightChild has a leftChild
        if (findNode->rightChild == NULL || findNode->rightChild->leftChild == NULL)
            return NULL;     //Return null as the node does not have a successor
        else                //Else if findNode has a rightChild, and that rightChild has a leftChild
        {
            Node* currentNode = findNode;
            currentNode = currentNode->rightChild;      //Move to the rightChild
            while (currentNode->leftChild != NULL)      //Traverse until the left-most node
                currentNode = currentNode->leftChild;   //Move the currentNode to the next leftChild
            return currentNode;                         //Return the successor node
        }   //Else if there is a rightChild, and that rightChild has a leftChild
    }   //End of if the find function found the word in the tree
    else                                //Else the find function did not find the word in the tree
        return NULL;                    //Return null, as we did not find the word in the tree
}   //End of successor function

void BSTree::next(std::string word)
{
    if (root == NULL)                  //If the tree is empty
        std::cout << std::endl;        //Print empty line
    else                               //Else the tree is not empty
    {
        Node* next = successor(word);
        if (next == NULL)                           //If the successor function returned NULL, as there is no successor
            std::cout << std::endl;                 //Print empty line
        else                              //Else successor function found the successor of the word in the parameter
            std::cout << next->data << std::endl;   //Print the successor data (word)
    }   //End of else, if the tree is not empty
}   //End of next function

BSTree::Node * BSTree::predecessor(std::string word)
{
    Node* findNode = find(word);    //Call and save find function result
    if (findNode->data == word)     //If Find function returned a node with the word
    {
       //Now we need to check if the node has a leftChild, and that leftChild has a rightChild
       if (findNode->leftChild == NULL || findNode->leftChild->rightChild == NULL)
           return NULL;     //Return null as the node have a predecessor
       else                 //Else it has a predecessor
       {
           Node* currentNode = findNode;
           currentNode = currentNode->leftChild;        //Move to the leftChild
           while (currentNode->rightChild != NULL)      //Traverse until the right-most node
               currentNode = currentNode->rightChild;   //Move the currentNode to the next rightNode
           return currentNode;                          //Return the predecessor node
       }    //End of else, if there is a predecessor
    }   //End of if findNode contains the word in the parameter
    else                            //Else if the findNode did not find the word in the tree
    {
        return NULL;                                    //Return Null as the word is not in the tree
    }   //End of else, if the findNode doesn't contain the word
}   //End of predecessor function

void BSTree::previous(std::string word)
{
    if (root == NULL)                   //If the tree is empty
        std::cout << std::endl;         //Return empty line as the tree is empty
    else                                //Else the tree isn't empty
    {
        Node *prev = predecessor(word);
        if (prev == NULL)               //If there is no predecessor, or the word wasn't found
            std::cout << std::endl;     //Print empty line
        else                            //Else the predecessor returned a successful node
            std::cout << prev->data << std::endl;   //Display the node data
    }   //End of else, if the tree isn't empty
}   //End of previous function

BSTree::Node * BSTree::discard(std::string word)
{
    //First we check if the word is in the tree before trying to remove it
    Node* findNode = find(word);
    if (findNode->data == word)         //If the findNode result has the
    {
        findNode->count--;              //Remove one instance of the count
        if (findNode->count == 0)       //If the count of the node goes to 0
        {
            if (findNode == root)       //If the findNode is the root of the tree
            {
                //We make the root's rightChild the new root
                Node* oldRoot = findNode;

            }   //End of if the findNode is the root of the tree
        }   //End of if the node's count hits 0
        else
            return findNode;            //Return the node with updated count
    }   //If the find function found the word in the tree
    else                                //Else the findNode did not find the word in the tree
        return NULL;                    //Return NULL
}   //End of discard function

void BSTree::remove(std::string word)
{
    if (root == NULL)                   //If tree is empty
        std::cout << std::endl;         //Output empty line
    else                                //Else the tree is not empty
    {
        Node* removeNode = discard(word);   //Call and get result from discard function
        if (removeNode == NULL)             //If the the word is not in the tree
            std::cout << std::endl;         //Output empty line
        else                                //Else the discard function returned a non-null node
        {

        }   //End of else, if the removeNode returned a non-null node

    }   //End of else, if the tree is empty
}   //End of remove function