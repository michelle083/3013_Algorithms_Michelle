/*************************************************************************
 *
 *  Author:           Michelle Orru
 *  Label:            P03
 *  Title:            Processing in Trie Tree Time
 *  Course:           CMPS 3013
 *  Semester:         Spring 2023
 *
 *  Description:
 *        This project is about loading a singly linked list with dictionary
 *        words, then timing how it takes to look them up.
 *
 *  Files:
 *       main.cpp           : driver program
 *       termcolor.hpp      : file used to color the text
 *       timer.hpp          : implementations for timer
 *       mygetch.hpp        : file to get character, without printing it
 *       dictionary.txt     : file containing all the dictionary words
 *
 *************************************************************************/
#include "termcolor.hpp"
#include "timer.hpp"
#include "mygetch.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

class triesTree {
private:
    ifstream infile;
    int matchesFound;

    struct myWord_Node {

        char myLetter;  //letter held in word
        bool isWord; //bool to check if node has the word
        unordered_map<char, myWord_Node*> child;           

        myWord_Node(char l = 'a', bool myWord = false) {
            myLetter = l;
            isWord = myWord;
        }
    };

    myWord_Node* root; //root of the node

public:
    //Tries Tree Constructor
    triesTree() {
        root = new myWord_Node('0');
        matchesFound = 0;

        //open input file
        infile.open("dictionary.txt");
    }

    //Read all the words from the input file 
    //Makes the trie tree from the words in the dictionary.
    void createTree() {
        string myWord;

        while (!infile.eof()) {
            infile >> myWord; //read in all the words
            myWord_Node* temp = root; //start at the root of the tree

            //loop through the letters of the word
            for (int i = 0; i < myWord.size(); i++) { 
                char myLetter = myWord[i]; //grabs the letter
                temp = newChild(myLetter, temp); //goes to the child of the node
            }
            temp->isWord = true;
        }

    }

    //instance node of the child
    myWord_Node* newChild(char const myLetter, myWord_Node*& parent) {

        if (!isChild(myLetter, parent)) { //if the letter is not a child
            parent->child.insert({ myLetter, new myWord_Node(myLetter) }); //add the letter to it's children
        }

        return parent->child[myLetter]; //return the child
    }


    //check if the letters in the input match the words in the tree
    void searchWord(string myWord) {
        Timer myTime;
        bool inTree = true;  

        matchesFound = 0;  //reset the number of matches found

        myWord_Node* parent = root; //start the search at the root
        vector<string> currentPlace = { myWord }; //holds a list of word suggestions


        myTime.Start();//start the timer

        //check to see if input is in the tree or not
        for (int i = 0; i < myWord.size(); i++) { 
            if (isChild(myWord[i], parent)) { //check if substring exists in the tree
                parent = parent->child[myWord[i]]; //go to the parents child  
            }
            else {
                inTree = false; //if the substring doesn't exist
                break; //break from the loop
            }
        }

        //if in the tree
        if (inTree) { 
            matchesFound++; //add to the number of matches
            findWord(parent, 'a', currentPlace, myWord); //go look for it's child nodes                       
        }
        //if it's not in the tree
        else {  
            currentPlace.empty();  //take the current substring out of the vector
        }

        myTime.End();                                                   

        //output the number of matches found and the time it took to find them
        //use termcolor to change colors of the numbers accordingly
        cout << termcolor::white << "Number of matches found:" << termcolor::reset << " "
            << termcolor::yellow << matchesFound << termcolor::reset << "\n";

        cout << termcolor::white << "Time taken to find matches:" << termcolor::reset << " "
            << termcolor::magenta << myTime.Seconds() << termcolor::reset << " "
            << termcolor::white << "seconds" << termcolor::reset << "\n\n";

        for (int i = 0; i < currentPlace.size(); i++) {

            for (int j = 0; j < myWord.size(); j++) {
                //prints letter matching input in green
                cout << termcolor::green << currentPlace[i][j];
            }
            cout << termcolor::reset;

            for (int k = myWord.size(); k < currentPlace[i].size(); k++) {
                //prints the remaining letters that haven't been inputted in a different color
                cout << termcolor::bright_blue << currentPlace[i][k] << termcolor::reset << "";
            }
            cout << " ";
        }
        cout << endl;
    }

    //bool to check if it's in the parent function
    bool isChild(char const myLetter, myWord_Node*& parent) {
        return parent->child.find(myLetter) != parent->child.end();
    }

    //check if it's a word
    bool isWord(myWord_Node* const& myWord) {
        return myWord->isWord;
    }

    //function to find the word
    void findWord(myWord_Node*& currentNode, char found, vector<string>& suggestedMatches, string currentSubstring) {

        //if the letter is lower or equal to 'z' then the parent has kids
        if (currentNode->child.size() && found < 123) {

            if (isChild(found, currentNode)) {

                //if it's a word then add to the number of matches
                if (isWord(currentNode->child[found])) {                               
                    matchesFound++;
                    if (suggestedMatches.size() < 10) // if there are less than 10 words in the vector
                        suggestedMatches.push_back(currentSubstring + found); //add myWord to vector of suggestedMatches
                }

                //recall the function with a new "root"
                findWord(currentNode->child[found], 'a', suggestedMatches, currentSubstring + found); 
            }

            //go to the next letter in the alphabet 
            //see if the parent has that letter for the child
            findWord(currentNode, ++found, suggestedMatches, currentSubstring); 
        }
    }
};


//Main Driver for the program
int main() {

    triesTree myTree; //Create a tries tree object
    Timer myTime;  //Create the timer

    char l;  //variable used for letters being typed in the input
    string myWord;  //word the user is typing in

    myTime.Start(); //Start the timer
    myTree.createTree(); //Read words into linked list dictionary
    myTime.End(); //End Timer

    //output welcome message and rules for the program
    cout << termcolor::white << "Welcome to Michelle's Dictionary, "
        << termcolor::reset << "\n\n";

    cout << termcolor::white << "* Remember, you can press 'Enter' at any time to exit the program"
        << termcolor::reset << "\n";

    cout << termcolor::white << "* It took" << termcolor::reset << " "
        << termcolor::cyan << (myTime.Seconds()) << termcolor::reset << " "
        << termcolor::white << "seconds to read in dictionary." << termcolor::reset << "\n\n";

    cout << termcolor::white << "Please start typing in your word:\n" << termcolor::reset << "";

    //while the user doesn't type enter to end the program
    while ((l = getch()) != 10)
    {
        system("clear"); //clears the welcome screen 

        //checks if input is lowercase
        l = tolower(l); 

        //if input is a backspace
        if (l == 127) {
            if (myWord.size()) {
                myWord.erase(myWord.size() - 1);
            }
        }

        //if input is not a letter
        else if (l < 97 || l > 122) { 
            cout << termcolor::red << "PLEASE MAKE SURE YOU ARE ONLY TYPING LETTERS!" << 
                termcolor::reset << "\n\n";
        }

        else {
            myWord += l;
        }

        //the word has at least one letter
        if (myWord.size()) {  
            cout << termcolor::white << "Current String:" << termcolor::reset
                << " " << termcolor::blue << myWord << termcolor::reset
                << "\n\n"; //prints out the word found till this point

            myTime.Start();
            myTree.searchWord(myWord);
            myTime.End();
        }

        //if there's no letters in the input
        else {
            cout << termcolor::white << "Please type in your word: " << termcolor::reset << "\n";
        }
    }
}
