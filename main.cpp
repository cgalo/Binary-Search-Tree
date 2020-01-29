#include <iostream>
#include <string>
#include "BSTree.h" //Call the BST header file

BSTree tree;        //Initiate the BSTree
void menu           (std::string cmd, std::string word);    //Declaring the menu function
void toUpper        (std::string* word);                    //Declaring the toUpper function
std::string getWord (std::string line, int wordIndex);      //Declaring getWord function
bool checkWord      (std::string word);                     //Declaring checkWord function
void showHelp       ();                                     //Declaring showHelp function

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

        if (cmd == "EXIT")                                  //If the command entered was 'EXIT'
            break;                                          //Exit the while-loop/ the program
        else                                                //Else the command was not 'EXIT'
        {
            std::string word = getWord (input, 2);//Get the second word of the input
            //Now we can call the menu and check the input
            menu(cmd, word);
        }
    }   //End of while-loop
    //We are here if 'Exit' was entered as cmd
    return 0;
}   //End of main function

void menu(std::string cmd, std::string word)
{
    //Check if the user input a word with the cmd
    bool wordCheck = checkWord(word);
    //C++ does not support switch statement with a string/char array so I'll use if-else statements through out
    if (cmd == "INSERT")                        //If the cmd is delete
    {
        if (wordCheck == false)                 //If the user did not input a word to insert with the cmd
            std::cout << std::endl;             //Print empty line, do not insert
        else                                    //Else the user did provide a word to insert with the cmd
            tree.insert(word);                  //Insert the provided word to the BST
    }   //End of if the cmd == "INSERT"
    else if (cmd == "DELETE")                   //Else if the cmd is delete
    {
        if (wordCheck == false)                 //If the user did not input a second word
            std::cout << std::endl;             //Output empty line, as we need a word w/ the cmd
        else                                    //Else user input a cmd w/ a word
            tree.remove(word);                  //We call the tree's remove method and pass the word given
    }   //End of else-if cmd == "DELETE"
    else if (cmd == "SEARCH")                   //Else if the cmd is search
    {
        if (wordCheck == false)                 //If the user did not input a second word
            std::cout << std::endl;
        else
            tree.search(word);
    }   //End of else-if cmd == "SEARCH"
    else if (cmd == "MIN")                      //Else if the cmd is min
    {
        tree.min();                             //Call the min method in the tree
    }   //End of else-if cmd == "MIN"
    else if (cmd == "MAX")                      //Else if the cmd is max
    {
        tree.max();                             //
    }   //End of else-if cmd == "MAX"
    else if (cmd == "NEXT")
    {
        if (wordCheck == false)                 //If the user did not input a second word
            std::cout << std::endl;
        else
            tree.next(word);

    }   //End of else-if cmd == "NEXT"
    else if (cmd == "PREV")
    {
        if (wordCheck == false)
            std::cout << std::endl;
        else
            tree.previous(word);
    }   //End of else-if cmd == "PREV"
    else if (cmd == "LIST")
    {
        tree.printTree();       //Prints in-order traversal of the tree node's, outputs all the node's data and count
    }   //End of else-if cmd == "LIST
    else if (cmd == "HELP")
    {
        showHelp();
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

    int countWord = 0;      //Will be used the keep tracks of the amount of words read in the string
    std::string returnWord; //To store the word and return it
    for (int i = 0 ; i < line.length(); i++)            //Iterate through the string char by char
    {
        if (line[i] == ' ' || i == line.length() - 1)   //If the char is a space or the last one in the string
        {
            if (line[i+1] != ' ' || i == line.length() - 1 )    //If the next char is not a space
            {                                                   //  Or the char is the last char in the string
                countWord++;                                    //We reach the end of the word, update countWord
                if (countWord == wordIndex)                     //If we reached the word number we wanted in the string
                {
                    if (i == line.length() - 1)
                    {
                        returnWord += line [i];
                    }
                    return returnWord; // yes it was, so return it
                }   //End of if
                returnWord =""; // nope it wasn't .. so reset word and start over with the next one in 'line'
            }
        }
        else                                            //Else the char is not a space
            returnWord += line[i];                      //We append the char at the end of the returnWord string
    }   //End of if the char is a space or the last char in the string
    return "wordIndex error";   //If the line does not have the # of word requested in the wordIndex
}   //End of getWord function

bool checkWord (std::string word)
{
    if (word == "wordIndex error")  //If the user did not provide another word with the cmd
        return false;
    else                            //Else the user did input a cmd with a word
        return true;

}   //End of checkWord function

void showHelp()
{

}   //End of showHelp function