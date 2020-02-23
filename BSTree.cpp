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
    if (root != NULL)           //If the tree is not empty
        treeDestructor(root);   //Traverse and destroy
}   //End of destructor function

/* treeDestructor, needs a node in the parameter as it is a recursive function
 *  it doesn't return anything, but deletes all the nodes in the tree for us
 * */
////This function should be only called by the destructor ~BST() after checking that tree is not empty
void BSTree::treeDestructor(BSTree::Node *currentNode)
{
    if (currentNode != NULL)
    {
        treeDestructor(currentNode->leftChild);
        currentNode = currentNode->leftChild;
        treeDestructor(currentNode->rightChild);
        currentNode = currentNode->rightChild;
        delete currentNode;
    }   //End of if the currentNode is not NULL
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
    if (root == NULL)                   //If the tree is empty
        std::cout << word << ": " << 0 << std::endl;    //Output word and 0 count
    else                                //Else the tree is not empty
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

void BSTree::max()
{
    /* Max public function, parameter(s): N/A
     * Objective: Output the right-most node of the tree
     * Cases:
     *  1. Tree is empty, output empty line
     *  2. Call maximum private method and output result's data
     * */
    if (root == NULL)                           //First check if the tree is empty
        std::cout << std::endl;                 //Print empty line (no output)
    else                                        //Else the tree is not empty, we call maximum function
    {
        Node* max = maximum(root);  //Get and save the result of the maximum function
        std::cout << max->data << std::endl;   //Print the node's word
    }   //End of else, if the tree is not empty
}   //End of max function

BSTree::Node * BSTree::maximum(BSTree::Node * currentNode)
{
    while (currentNode->rightChild != NULL)     //Traverse the right side of the tree
        currentNode = currentNode->rightChild;  //Keep moving until the right-most node
    return currentNode;                         //Return the right-most node
}   //End of maximum function

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


/* printTree()
 * */
void BSTree::printTree()
{
    if (root == NULL)                   //If the tree is empty
        std::cout << std::endl;         //Print empty line
    else                                //Else the tree is not empty
        inOrderPrint(root, 0); //Call the inOrderPrint function to prin the tree's nodes in-order traversal
}   //End of printTree function


/* inOrderPrint private function, prints in-order traversal node's data and count tree
 *  It utilizes recursion to traverse the tree
 *  It is called only by the printTree() public function
 * */
void BSTree::inOrderPrint(BSTree::Node *currentNode, int count)
{
    if (currentNode == NULL)    //If we reach a leaf
        return;                 //Exit
    inOrderPrint(currentNode->leftChild, count);   //Traverse through the left side
    count++;

    if (count > 1)
        std::cout << ", (" << count << ")" << currentNode->data << " " << currentNode->count;
    else
        std::cout << "(1)" << currentNode->data << " " << currentNode->count;

    //count++;
    inOrderPrint(currentNode->rightChild, count);  //Traverse through the right side

}   //End of inOrderPrint function

void BSTree::next(std::string word)
{
    if (root == NULL)                  //If the tree is empty
        std::cout << std::endl;        //Output empty line
    else                               //Else the tree is not empty
    {
        Node *findNode = find(word);    //Call find method to get the node from the tree
        if (findNode->data == word)     //If the word was found in the tree
        {
            Node* successorNode = successor(findNode);
            if (successorNode == NULL)  //If the findNode has no successor
                std::cout << std::endl; //Output empty line
            else                        //Else it has a successor, print successor's data
                std::cout << successorNode->data << std::endl;
        }   //End of if the word is in the tree
        else                            //Else the word was not in the tree
            std::cout << std::endl;     //Output empty line
    }   //End of else, if the tree is not empty
}   //End of next function

BSTree::Node * BSTree::successor(BSTree::Node * currentNode)
{
    ////Call this method after checking that the word is in the tree with find()
    /* Successor private function, parameter(s): string
     * Objective: Return successor node from the node w/ the given word
     * Cases:
     *  1. If the node has a right child (RCH)
     *      A. We traverse to node's RCH most left-most node and return it
     *      B. If the node doesn't have a left child, then we return the node's RCH
     *  2. The node has no RCH, then we return the node's recent ancestor whose LCH is an ancestor of the node
     * */

    if (currentNode->rightChild != NULL)        //If the currentNode has a right-child (RCH)
    {
        currentNode = currentNode->rightChild;  //Move the current node pointer to its RCH
        return minimum(currentNode);            //Return the left-most node of currentNode or RCH
    }   //End of if the current node has a right-child
    else                                        //Else the current node has no right child
    {
        //We have to traverse up from the current node to get the successor
        if (currentNode == root)                //If the current node is the root of the tree
            return NULL;                        //Output NULL as it doesn't have a parent node
        Node* parentNode = currentNode->parentNode; //Save the current node's parent
        // Keep traversing up until we hit the root or the current node is the LCH of its parent node
        while (parentNode != NULL && currentNode == parentNode->rightChild)
        {
            if (parentNode == root) //If we got to the root of the tree
                break;              //Break from the while-loop as we can't keep traversing up
            currentNode = parentNode;               //Update the current to the node above
            parentNode = parentNode->parentNode;    //Update the parent to the node above
        }   //End of while-loop
        return parentNode;  //Return the parentNode as its the successor
    }   //End of else the current node has no right child
}   //End of successor function

void BSTree::previous(std::string word)
{
    /* Previous public function, parameter(s): string
     * Objective: Find a node w/ the given word in the tree, output the predecessor of that node
     * Cases:
     *  1. If tree is empty, output empty line
     *  2. Call the predecessor private function, passing the given string/word as a parameter
     *      A. If the predecessor method return NULL then we output an empty line
     *      B. Else print the predecessor method result data
     * */
    if (root == NULL)                   //If the tree is empty
        std::cout << std::endl;         //Return empty line as the tree is empty
    else                                //Else the tree isn't empty
    {
        Node* findNode = find(word);    //Call the find method to get the node w/ the given word in the tree
        if (findNode->data == word)     //If the word was found in the tree
        {
            Node* prev = predecessor(findNode); //Get the predecessor of the findNode
            if (prev == NULL)                   //If the findNode has no predecessor
                std::cout << std::endl;         //Output empty line
            else                                //Else the findNode has a predecessor
                std::cout << prev->data << std::endl;   //Output the predecessor's data
        }   //End of if the word was found in the tree
        else                            //Else the word was not in the tree
            std::cout << std::endl;     //Output empty line

    }   //End of else, if the tree isn't empty
}   //End of previous function

BSTree::Node * BSTree::predecessor(BSTree::Node * currentNode)
{
    ////Call this method after checking that the word is in the tree with find()
    /* Predecessor private function, parameter(s): string
     * Objective: Find a node with the given word and return the predecessor of that node
     * Cases:
     *  1. If the node has a left child (LCH)
     *      A. We traverse to node LCH's most right-most node and return it
     *      B. If the node doesn't have a right child, then we return the node's LCH
     *  2. The node has no LCH, then we return the node's recent ancestor whose RCH is an ancestor of the node
     * */

    if (currentNode->leftChild != NULL) //If the current node has a left-child (LCH)
    {
        currentNode = currentNode->leftChild;   //Move the pointer to the left-child
        return maximum(currentNode);            //Return the right-most node of the current node
    }   //End of if the current node has a left-child (LCH)
    else                                //Else the current node doesn't have a LCH
    {
        //We are going to traverse up of the current node
        if (currentNode == root)        //If the node is the root of the tree, then we can't go up
            return NULL;                //Return NULL as it has no predecessor
        else                            //Else the current node is not the root of the tree
        {
            Node* parentNode = currentNode->parentNode; //Get the parent of the current node
            while (parentNode != NULL && currentNode == parentNode->leftChild)
            {
                if (parentNode == root) //If we reach the root of the tree
                    break;              //Break from the while-loop, as we can't traverse up
                currentNode = parentNode;               //Update the current to the node above
                parentNode  = parentNode->parentNode;   //Update the parent to the node above
            }   //End of while-loop
            return parentNode;
        }   //End of else, if the current node is not the root of the tree
    }   //End of else, if the current node doesn't have a LCH
}   //End of predecessor function

void BSTree::remove(std::string word)
{
    /* Remove public function, parameter(s): string
     * Objective: Decrease count of node w/ given word, if count hits 0 then remove node from tree
     * Cases:
     *  1. Tree empty, output empty line
     *  2. If node w/ given word is not in the tree output <string> : -1
     *  3. Else the node is in the tree
     *      A. Decrease count of the node
     *          -If node gets to 0 then remove the node from tree
     * */
    if (root == NULL)                       //If tree is empty
        std::cout << std::endl;             //Output empty line if tree is empty
    else                                    //Else the tree is not empty
    {
        Node* searchNode = find(word);      //Call the search() to get the node with the word in the tree
        if (searchNode->data == word)       //If the word is in the tree, search() found it in the tree
        {
            searchNode->count--;            //Update the count word
            std::cout << searchNode->data << ": " << searchNode->count << std::endl;   //Output node info
            if (searchNode->count == 0)     //If the node count gets to 0
                discardNode(searchNode);    //Remove the node from the tree by calling the discardNode private function
        }   //End of if the word is in the tree
        else                                //Else the searchNode does not have the word, the word is not in the tree
            std::cout << word  << ": -1" << std::endl;  //Output <word> with -1 count
    }   //End of else, if the tree is empty
}   //End of remove function

/* discardNode (node) is a private function called by the public remove(string) function
 * The purpose of this function is to remove a node from the tree and adjust the tree accordingly
 * There are three base cases:
 *  -If the given node has
 * */
BSTree::Node* BSTree::discardNode(BSTree::Node *deleteNode)
{
    //We have three cases: deleteNode has no children, has both children, has one children
    //Case 1: node has no children
    if (deleteNode->leftChild == NULL && deleteNode->rightChild == NULL)
    {
        if (deleteNode == root) //If the deleteNode is the root of the tree
            root = NULL;        //Set the root pointer back to NULL
        else                    //Else the deleteNode is not the root of the tree
        {
            //DeleteNode has a parent node
            Node* parentNode = deleteNode->parentNode;  //Save the parent node pointer of the deleteNode
            if (deleteNode == parentNode->leftChild)    //If the deleteNode is the LCH
                parentNode->leftChild = NULL;   //Remove pointer to the deleteNode
            else                                        //Else the deleteNode is the RCH
                parentNode->rightChild = NULL;  //Remove pointer to the deleteNode
        }   //Else the deleteNode is not the root of the tree
        delete deleteNode;  //GC to get the memory back from the deleteNode
    }   //End of if the deleteNode has no children
    //Case 2: node has both children
    else if (deleteNode->leftChild != NULL && deleteNode->rightChild != NULL)
    {
        Node* succNode = successor(deleteNode); //Get the successor node of the deleteNode
        //succNode has no LCH as it is the left-most node, it's either deleteNode's RCH or LCH of the RCH's
        if (deleteNode->rightChild == succNode) //If the succNode is the right-child (RCH) of the deleteNode
        {
            //If the deleteNode has a parent, then replace the child pointer to the deleteNode with the succNode
            if (deleteNode->parentNode != NULL)             //If the deleteNode has a parent, aka not the root
            {
                Node* parentNode = deleteNode->parentNode;  //Save the deleteNode's parent pointer
                succNode->parentNode = parentNode;          //Set the parent of succNode to deleteNode's parent
                if (parentNode->leftChild == deleteNode)    //If the deleteNode is a LCH
                    parentNode->leftChild = succNode;       //Set the succNode as its new LCH for the parent
                else                                        //Else the deleteNode is the RCH
                    parentNode->rightChild = succNode;      //Set the succNode as its new RCH for the parent
            }   //If the deleteNode has a parent, aka it's not the root of the tree
            else                                            //Else the deleteNode is the root of the tree
                root = succNode;                            //Set root pointer to the succNode
            //Now readjust the deleteNode's left-child (LCH) pointer
            succNode->leftChild = deleteNode->leftChild;    //Set succNode's LCH to the deleteNode's LCH
            succNode->leftChild->parentNode = succNode;     //Change the LCH parent pointer to the succNode
        }   //End of if the succNode is deleteNode's right-child (RCH)
        else                                    //Else the succNode is a LCH of the deleteNode's RCH
        {
            //First we unlink the succNode to its parent node
            Node* parentNode = succNode->parentNode;        //Save the pointer to the succNode's parent
            if (succNode->rightChild != NULL)               //If the succNode's RCH is not null
            {
                parentNode->leftChild = succNode->rightChild;   //Change the parent LCH's pointer to succNode's RCH
                succNode->rightChild->parentNode = parentNode;  //Change the RCH's parent pointer to succNode's parent
            }
            else                                            //Else the succNode does not have a RCH
                parentNode->leftChild = NULL;               //Set the parentNode's RCH as NULL
            //Finished unlinking on the bottom of the tree, now link the succNode to where the deleteNode is located
            if (deleteNode != root)     //If the deleteNode is not the root of the tree, it does have a parent node
            {
                //Copy the pointers from the deleteNode to the succNode
                succNode->parentNode = deleteNode->parentNode;  //Copy the parent pointer from the deleteNode
                succNode->leftChild = deleteNode->leftChild;    //Copy the LCH pointer from the deleteNode
                succNode->rightChild = deleteNode->rightChild;  //Copy the RCH pointer from the deleteNode
                succNode->rightChild->parentNode = succNode;    //Set the RCH's parent pointer to the succNode
                //Check if the deleteNode is a RCH or LCH and adjust the child pointer to point to the succNode
                parentNode = deleteNode->parentNode;            //Save the parent pointer of the deleteNode
                if (parentNode->leftChild == deleteNode)         //If the deleteNode is a LCH
                    parentNode->leftChild = succNode;           //Change the parent's LCH pointer to the succNode
                else                                            //Else the deleteNode is a RCH
                    parentNode->rightChild = succNode;          //Change the parent's RCH pointer to the succNode
            }   //End of if the deleteNode is not the root of the tree
            else                        //Else the deleteNode is the root of the tree, it does not have a parent node
            {
                //Set the children of the deleteNode to the succNode
                succNode->leftChild = deleteNode->leftChild;        //Adjust the LCH
                succNode->rightChild = deleteNode->rightChild;      //Adjust the RCH
                succNode->parentNode = NULL;                        //Set the parent pointer to NULL
                root = succNode;                                    //Set the succNode as new root
            }   //End of else, if the deleteNode is the root of the tree
        }   //End of else, if the succNode is the left-most children of the deleteNode's RCH
        delete deleteNode;                                          //GC to get memory back from the deleteNode
    }   //End of else-if the delete node has both children
    //Case 3: node has only one child
    else
    {
        //Get the child that is not NULL
        Node* child = (deleteNode->leftChild != NULL) ? deleteNode->leftChild : deleteNode->rightChild;
        if (deleteNode == root) //If the deleteNode is the root of the tree
        {
            //Make the child node the new root
            child->parentNode = NULL;  //Set reference to parent node to null as root shouldn't have a parent
            root = child;               //Set the child as new root of the tree
        }   //End of if the deleteNode is the root
        else                    //Else the deleteNode is not the root of the tree, deleteNode has a parent
        {
            Node* parentNode = deleteNode->parentNode;  //Get the parent node of the node we are going to delete
            //Now remove pointer to the deleteNode and set the new pointer to the deleteNode's child
            if (parentNode->leftChild == deleteNode)    //If the removeNode is the left child of its parent
                parentNode->leftChild = child;          //Set the child node as parentNode's new LCH
            else                                        //Else the removeNode is the right-child of the parent
                parentNode->rightChild = child;         //Set the child not as parentNode's new RCH
        }   //End of else, if the deleteNode is not the root
        delete deleteNode;                              //Perform garbage collection on the deleteNode
    }   //End of else, the deleteNode has only one children
}   //End of discardNode function


void BSTree::parent(std::string word)
{
    /* Parent public function, parameter(s): string
     * Objective: Find a node with the given string and output that node's parent
     * Cases:
     *  1.  A. We found the node with the string and it has a parent node, we output parent node's data
     *      B. We found the node in the tree but it has no parent node (root) we output blank line
     *  2. There is no node w/ the given string, we output a blank line
     * */

    if (root == NULL)               //If the tree is empty
        std::cout << std::endl;     //Output empty line
    else                            //Else the tree is not empty
    {
        Node* searchNode = find(word);  //Call find function to look for the node w/ given string
        if (searchNode->data == word)   //If the search found the word in the tree
        {
            Node *currentNode = searchNode; //Change variable name for easier understanding
            if (currentNode->parentNode != NULL)    //If the current node has a parent node
                std::cout << currentNode->parentNode->data << std::endl;    //Output the parent node's data
            else                                    //Else if the current node does not have a parent node
                std::cout << std::endl;             //Output blank line
        }   //End of if the find function found a node w/ the given string in the tree
        else                                        //Else the search did not find the
            std::cout << std::endl;                 //Output an empty line

    }   //End of else, if the tree is not empty
}   //End of parent function


void BSTree::children(std::string word)
{
    /* Children public function, parameter(s): string
     * Objective: Output the node's, containing the given word, children data
     * Cases:
     *  1. The tree is empty, output empty line
     *  2. We get the find() and get a node w/ the given word
     *      A. The node has both children (LCH & RCH) with data, we output both children's data
     *      B. The node has no children, both are NULL, then we output an empty line
     *      C. The node has one child, the other is NULL, we output the child's data and string NULL
     *  3. The find method did not find a node w/ the given word, output empty line
     * */
    if (root == NULL)                   //If the tree is empty
        std::cout << std::endl;         //Output empty line
    else                                //Else the tree is not empty
    {
        Node* searchNode = find(word);  //Try to find a node w/ the given word in the tree
        if (searchNode->data == word)   //If we found a node w/ the given word
        {
            Node* currentNode = searchNode; //Rephrasing variables for easier understanding
            //If the current node has two children (not null), then output children's data from left to right
            if (currentNode->leftChild != NULL && currentNode->rightChild != NULL)
                std::cout << currentNode->leftChild->data << ", " << currentNode->rightChild->data << std::endl;
            //If both children are NULL then output empty line
            else if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
                std::cout << std::endl;
            else    //Else the current node has either the LCH or RCH with values, but not both
            {
                if (currentNode->leftChild == NULL)     //If the LCH is null
                    std::cout << "NULL, " << currentNode->rightChild->data << std::endl;
                else                                    //Else the RCH is null
                    std::cout << currentNode->leftChild->data << ", NULL"  << std::endl;
            }   //End of else, if the current node has at least a not null children
        }   //End of if the searchNode contains given word
        else                            //Else the search did not find a node w/ the word in the tree
            std::cout << std::endl;     //Output an empty line
    }   //End of else, if the tree is not empty
}