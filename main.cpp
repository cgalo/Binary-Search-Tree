#include <iostream>
#include <string>
#include "BSTree.h" //Call the BST header file

BSTree tree;        //Initiate the BSTree
void menu           (std::string cmd, std::string word);    //Declaring the menu function
void toUpper        (std::string* word);                    //Declaring the toUpper function
std::string getWord (std::string line, int wordIndex);      //Declaring getWord function
bool checkWord      (std::string word);                     //Declaring checkWord function

int main()
{
    while (true)
    {
        std::string input;  //Create string to accept the input of the user
        std::cout<< "";
        std::getline (std::cin, input); //Get the whole input of the user

        //Now we need to split the input to get the cmd and the word we want to store
        std::string cmd = getWord(input, 1);      //Get the first word in the input and save as cmd
        toUpper(&cmd);                                      //Convert the cmd into upper case
        std::cout << "cmd: " << cmd << std::endl;   //Check cmd entered

        if (cmd == "EXIT")                                  //If the command entered was 'EXIT'
            break;                                          //Exit the while-loop/ the program
        else                                                //Else the command was not 'EXIT'
        {
            std::string word = getWord (input, 2);//Get the second word of the input
            std::cout << "Word: " << word << std::endl;
            //Now we can call the menu and check the input
            menu(cmd, word);

        }
    }   //End of while-loop

    //We are here if 'Exit' was entered as cmd

    return 0;
}

void menu(std::string cmd, std::string word)
{
    //Check if the user input a word with the cmd
    bool wordCheck = checkWord(word);
    //C++ does not support switch statement with a string so I'll use if-else statements through out
    if (cmd == "INSERT")
    {
        if (wordCheck == false)                 //If the user did not input a word to insert with the cmd
        {
            std::cout << std::endl;             //Print empty line, do not insert
        }   //End of if the user did not provide a word w/ the cmd
        else                                    //Else the user did provide a word to insert with the cmd
        {
            tree.insert(word);                  //Insert the provided word to the BST
        }   //End of else, if the user input a word w/ the cmd
    }   //End of if the cmd == "INSERT"
    else if (cmd == "DELETE")
    {

    }   //End of else-if cmd == "DELETE"
    else if (cmd == "SEARCH")
    {
        if (wordCheck == false)
        {
            std::cout << std::endl;
        }
        else
        {
            tree.search(word);
        }
    }   //End of else-if cmd == "SEARCH"
    else if (cmd == "MIN")
    {
        tree.min();
    }   //End of else-if cmd == "MIN"
    else if (cmd == "MAX")
    {
        tree.max();
    }   //End of else-if cmd == "MAX"
    else if (cmd == "NEXT")
    {

    }   //End of else-if cmd == "NEXT"
    else if (cmd == "PREV")
    {

    }   //End of else-if cmd == "PREV"
    else if (cmd == "LIST")
    {
        tree.printTree();       //Prints in-order traversal of the tree node's, outputs all the node's data and count
    }   //End of else-if cmd == "LIST
    else if (cmd == "HELP")
    {

    }   //End of else-if cmd == "HELP"
    else
    {
        std::cout << std::endl; //Print empty line
    }   //End of else, the user input a wrong cmd

}   //End of menu function

//Function takes pointer/reference of a string and converts it into uppercase
void toUpper (std::string* word)
{
    for (auto & c: *word) c = toupper(c);
}   //End of toUpper function

std::string getWord (std::string line, int wordIndex)
{

    int countWord = 0;      //Total read words
    std::string returnWord; //To store the word to return

    for (int i = 0 ; i < line.length(); i++) { // iterate over all characters in 'line'
        if (line[i] == ' ' || i == line.length() - 1)   // if this character is a space we might be done reading a word from 'line'
        {
            if (line[i+1] != ' ' || i == line.length() - 1 )    // next character is not a space, so we are done reading a word
            {
                countWord++; // increase number of read words
                if (countWord == wordIndex) // was this the word we were looking for?
                {
                    if (i == line.length() - 1)
                    {
                        returnWord += line [i];
                    }
                    return returnWord; // yes it was, so return it
                }
                returnWord =""; // nope it wasn't .. so reset word and start over with the next one in 'line'
            }
        }
        else { // not a space .. so append the character to 'word'
            returnWord += line[i];
        }
    }
    return "wordIndex error";   //If the line does not have the # of word requested in the wordIndex
}   //End of getWord function

bool checkWord (std::string word)
{
    if (word == "wordIndex error")  //If the user did not provide another word with the cmd
        return false;
    else                            //Else the user did input a cmd with a word
        return true;

}   //End of checkWord function
