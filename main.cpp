#include <iostream>
#include <string>

void menu           (std::string cmd, std::string word);    //Declaring the menu function
void toUpper        (std::string* word);                    //Declaring the toUpper function
std::string getWord (std::string line, int wordIndex);      //Declaring getWord function

int main()
{
    std::string input;  //Create string to accept the input of the user
    do
    {
        std::cout<< "";
        std::cin >> input;
        //Now we need to split the input to get the cmd and the word we want to store

        std::string cmd = getWord(input, 1);
        std::string word = getWord(input, 2);

        std::cout << "cmd: " << cmd << std::endl;
        std::cout << "word: " << word << std::endl;

    } while (input != "EXIT");

    return 0;
}

void menu(std::string cmd, std::string word)
{

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
        if (line[i] == ' ') { // if this character is a space we might be done reading a word from 'line'
            if (line[i+1] != ' ') { // next character is not a space, so we are done reading a word
                countWord++; // increase number of read words
                if (countWord == wordIndex) { // was this the word we were looking for?
                    break; // yes it was, so return it
                }
                returnWord =""; // nope it wasn't .. so reset word and start over with the next one in 'line'
            }
        }
        else { // not a space .. so append the character to 'word'
            returnWord += line[i];
        }
    }
    return returnWord;
}   //End of getWord function


