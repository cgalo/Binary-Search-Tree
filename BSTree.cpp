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

//Insert function - private function, only called by the insert() public function
//  -Uses find function to check if the tree contains the word we are looking for
//      -- If we find the node, we update the count by adding +1 and returning this node
//      -- Else we insert the new Node as a child of the returned result of the find function, we return the new node
BSTree::Node * BSTree::insertion(std::string word)
{
    if (root == NULL)   //If the tree is empty, we insert node as root
    {
        root = new Node(word);
        return root;    //Return root with the new data and count
    }   //End of if the tree is empty
    else                //Else the tree is not empty
    {
        Node* findNode = find(word);    //Call and save the result of the find function
        if (findNode->data == word)     //If the findNode contains the word we are looking for, update count
        {
            findNode->count++;          //Update the count by adding 1
            return findNode;            //Return the findNode with updated count
        }   //End of if the findNode contains the word
        else                            //Else the findNode is the parentNode we have to insert new child
        {
            Node* parentNode = findNode;            //Save the findNode as parentNode
            Node* insertNode = new Node(word);      //Create a new node to insert as a child
            insertNode->parentNode   = parentNode;  //Connect the insertNode to the parentNode
            if (word < parentNode->data)
            {
                parentNode->leftChild = insertNode; //Insert the new node as left child
            }   //End of if the word being inserted is less than the parentNode, insert left
            else                        //Else the word is greater than parentNode's data, insert right
            {
                parentNode->rightChild = insertNode;//Insert new node as right child;
            }   //Else if the word is greater than parentNode, insert right
            return insertNode;                      //Return the insertNode
        }   //End of else, if the findNode is the parentNode
    }   //End of else, if the the tree is not empty
}   //End of insertion

//Insert function - it is public function
//  Calls the insertion() private function by passing the string and getting back a node.
//  This node is either an existing node in the tree, with a count > 1 or a new node with count == 1
//  It displays the data in the node with the count
void BSTree::insert(std::string word)
{
    Node* insertNode = insertion(word);
    std::cout << insertNode->data << ": " << insertNode->count << std::endl;
}   //End of insert function

BSTree::Node * BSTree::maximum(BSTree::Node * currentNode)
{
    while (currentNode->rightChild != NULL)     //Traverse the right side of the tree
        currentNode = currentNode->rightChild;  //Keep moving until the right-most node
    return currentNode;                         //Return the right-most node
}   //End of maximum function

void BSTree::max()
{
    if (root == NULL)                           //First check if the tree is empty
        std::cout << std::endl;                 //Print empty line (no output)
    else                                        //Else the tree is not empty, we call maximum function
    {
        Node* max = maximum(root);  //Get and save the result of the maximum function
        std::cout << max->data << std::endl;   //Print the node's word
    }   //End of else, if the tree is not empty
}   //End of max function

/* Minimum private function, requires to be passed a node pointer
 *  This function traverses to the left-most child of the given tree
 *  - If the given node has not child then it will return the given node
 * */
BSTree::Node * BSTree::minimum(BSTree::Node *currentNode)
{
    while (currentNode->leftChild != NULL)      //Traverse the left side of the tree
        currentNode = currentNode->leftChild;   //Keep moving until the left-most node
    return currentNode;                         //Return the left-most node
}   //End of minimum function

/* Min public function, displays the left-most node'data and count of the tree
 *  This function does not require any parameters
 *  -If the tree is empty, if it is then it will output an empty line
 *  -Else it will call the minimum() private function, and output the returned node's data and count
 * */
void BSTree::min()
{
    if (root == NULL)                           //First we check if the tree is empty
        std::cout << std::endl;                 //Print empty line
    else                                        //Else the tree is not empty
    {
        Node* min = minimum(root);              //Call the minimum function to traverse left of the tree
        std::cout << min->data << std::endl;    //Print the min node data
    }   //End of else, if the tree is not empty
}   //End of min function

/* inOrderPrint private function, prints in-order traversal node's data and count tree
 *  It utilizes recursion to traverse the tree
 *  It is called only by the printTree() public function
 * */
void BSTree::inOrderPrint(BSTree::Node *currentNode)
{
    if (currentNode == NULL)    //If we reach a leaf
        return;                 //Exit
    inOrderPrint(currentNode->leftChild);   //Traverse through the left side
    std::cout << currentNode->data << ": " << currentNode->count << std::endl;  //Print node's data and count
    inOrderPrint(currentNode->rightChild);  //Traverse through the right side
}   //End of inOrderPrint function

/* printTree()
 * */
void BSTree::printTree()
{
    if (root == NULL)                   //If the tree is empty
        std::cout << std::endl;         //Print empty line
    else                                //Else the tree is not empty
        inOrderPrint(root); //Call the inOrderPrint function to prin the tree's nodes in-order traversal
}   //End of printTree function


BSTree::Node * BSTree::successor(std::string word)
{
    Node* searchNode = find(word);              //Search a node with the word in the tree
    if (searchNode->data == word)               //If the search found the node with the word
    {
        Node* currentNode = searchNode;
        if (currentNode->rightChild != NULL)    //If the currentNode has a rightChild
            return minimum(currentNode);        //Return the left-most node of currentNode
        Node* parentNode = currentNode->parentNode; //currentNode has no RCH; go up
        while (parentNode != NULL && currentNode == parentNode->rightChild)
        {
            currentNode = parentNode;
            parentNode = parentNode->parentNode;
        }   //End of while-loop
        return parentNode;
    }   //End of if the search found the word in the tree
    else                                        //Else the word is not in the tree
        return NULL;                            //Return NULL
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
        return NULL;                //Return Null as the word is not in the tree
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

//Transplant helper function
//  -Moves a subtree, and handles the "root problem"
//  -Node u's parent becomes v's parent, and u's parent gets u as the appropriate child
void BSTree::transplant(BSTree::Node *u, BSTree::Node *v)
{
    if (u == NULL)                  //If u is the root
    {
        root = v;                   //v becomes the new root
    }   //End of if u is the root of the tree
    else if (u == u->parentNode->leftChild) //If u is a leftChild of its parent
        u->parentNode->leftChild = v;       //Then v becomes that left child
    else                                    //Else v becomes the rightChild
        u->parentNode->rightChild = v;
    if (v !=  NULL)                         //If v is not null, then v's parent
        v->parentNode = u->parentNode;      //Becomes u's parent (even if u was the root)
}   //End of transplant function

BSTree::Node* BSTree::discardNode(BSTree::Node *currentNode)
{
    if (currentNode->leftChild == NULL)                     //If currentNode has no left child
        transplant(currentNode, currentNode->rightChild);   //Replace currentNode with its right child
    else if (currentNode->rightChild == NULL)               //If currentNode's RCH null, but has a LCH
        transplant(currentNode, currentNode->leftChild);
    else
    {
        Node* successorNode = successor(currentNode->data); //Get the successor of the currentNode
        if (successorNode != NULL)                          //If the currentNode had a successor
        {
            if (successorNode->parentNode != currentNode);  //If successor isn't currentNode's rightChild
        }
    }


}   //End of discardNode function


void BSTree::remove(std::string word)
{
    if (root == NULL)                       //If tree is empty
        std::cout << std::endl;             //Output empty line if tree is empty
    else                                    //Else the tree is not empty
    {
        Node* searchNode = find(word);      //Call the search() to get the node with the word in the tree
        if (searchNode->data == word)       //If the word is in the tree, search() found it in the tree
        {
            searchNode->count--;            //Update the count word
            std::cout << searchNode->count << ": " << searchNode->count << std::endl;   //Output node info
            if (searchNode->count == 0)     //If the node count gets to 0
                discardNode(searchNode);    //Remove the node from the tree by calling the discardNode private function
        }   //End of if the word is in the tree
        else                                //Else the searchNode does not have the word, the word is not in the tree
            std::cout << std::endl;         //Output empty line as word is not in the tree

    }   //End of else, if the tree is empty
}   //End of remove function