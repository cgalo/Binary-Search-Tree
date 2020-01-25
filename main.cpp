#include <iostream>
#include <string>

void menu (std::string cmd, std::string word);  //Declaring the menu method
void toUpper (std::string* word);               //Declaring the toUpper method, makes any word into uppercase

int main()
{
    std::string input;  //Create string to accept the input of the user
    do
    {
        std::cout<< "";
        std::cin >> input;
        //Now we need to split the input to get the cmd and the word we want to store


    } while (input == "EXIT");

    return 0;
}

void menu(std::string cmd, std::string word)
{

}

//Function takes pointer/reference of a string and converts it into uppercase
void toUpper (std::string* word)
{
    for (auto & c: *word) c = toupper(c);
}   //End of toUpper function