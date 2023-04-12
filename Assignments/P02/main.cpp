/*************************************************************************
 *
 *  Author:           Michelle Orru
 *  Label:            P02
 *  Title:            AutoComplete in Linear Time
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

using namespace std;

class Dictionary {
private:
    ifstream infile; 

    //Create node for the dictionary
    struct myWord_Node {
        string myWord; //create string to hold words

        myWord_Node* next; //points to the next node

        myWord_Node(string w = "", myWord_Node* n = nullptr) {

            myWord = w;
            next = n;            
        }
    };

    myWord_Node* head; //points to the head of the node
    myWord_Node* tail; //points to the tail of the node

    myWord_Node* currentPlace; //tells us where the current place is

public:
    //Dictionary Constructor
    Dictionary() {
        head = tail = nullptr;

        infile.open("dictionary.txt"); //open file containing the dictionary words
    }

    //Read all the words from the input file
    void myVocabulary() {
        string myWord;

        while (!infile.eof()) { 
            infile >> myWord; //read in all the words

            push(myWord); //push all the words in the ll
        }
    }

    //Add a node to the back of the list
    void push(string myWord) {

        myWord_Node* temp = new myWord_Node(myWord); //create the node being added

        if (head == nullptr) { //if the list is empty
            head = tail = temp; 
        }
        else {               
            tail->next = temp;   // add node to the back of the list
            tail = tail->next;
        }
    }

    //check if the letters in the input match the words in the dictionary
    void searchWord(string const& letters) {
        Timer myTime;                
        bool match = true; 

        vector<string> matches; //vector for the matches found

        myTime.Start(); //starts the timer

        //set current place at the beginning of the list
        currentPlace = head; 
        
        //loop that checks every letter being passed in
        for (int i = 0; i < letters.size(); i++) { 
            while (currentPlace->next && currentPlace->myWord[i] != letters[i]) 
            {
                currentPlace = currentPlace->next;
            }
            if (i > 0 && currentPlace->myWord[i - 1] != letters[i - 1]) {
                match = false;
            }
        }

        int matchesFound = 0; //create variable for the number of matches found
        
        //finds all the words that match the letter in the input
        while (currentPlace && match) { 

            matchesFound++; //keep count of the number of matches found

            if (matchesFound <= 10){
                //while matches are less than 10, keep adding suggestions
                matches.push_back(currentPlace->myWord); 
            }

            if (!currentPlace->next)
                break;
            else
                currentPlace = currentPlace->next;
            
            //checks to see if all the letters are a match
            for (int i = 0; i < letters.size(); i++) { 

                if (currentPlace->myWord[i] != letters[i]) { // will go to false if they don't match
                    match = false;
                }
            }
        }

        myTime.End(); //stop the timer

        //output the number of matches found and the time it took to find them
        //use termcolor to change colors of the numbers accordingly
        cout << termcolor::white << "Number of matches found:" << termcolor::reset << " "
            << termcolor::yellow << matchesFound << termcolor::reset << "\n";

        cout << termcolor::white << "Time taken to find matches:" << termcolor::reset << " "
            << termcolor::magenta << myTime.Seconds() << termcolor::reset << " "
            << termcolor::white << "seconds" << termcolor::reset << "\n\n";

        //check through the words in the string that match the input
        for (int i = 0; i < matches.size(); i++) { 

            for (int j = 0; j < letters.size(); j++) {
                //prints letter matching input in green
                cout << termcolor::green << matches[i][j]; 
            }
            cout << termcolor::reset;

            for (int k = letters.size(); k < matches[i].size(); k++) {
                //prints the remaining letters that haven't been inputted in a different color
                cout << termcolor::bright_blue << matches[i][k] << termcolor::reset << "";
            }
            cout << " ";
        }
        cout << endl;
    }
};

//Main Driver of the program
int main() {

    Dictionary myDictionary; //create the linked list with the dictionary words
    Timer myTime; //timer used for the program
    char l; //variable used for letters being typed in the input


    myTime.Start(); //Start the timer
    myDictionary.myVocabulary(); 
    myTime.End(); //End the timer

    //output welcome message and rules for the program
    cout << termcolor::white << "Welcome to Michelle's Dictionary, "
        << termcolor::reset << "\n\n";

    cout << termcolor::white << "* Remember, you can press 'Enter' at any time to exit the program"
        << termcolor::reset << "\n";

    cout << termcolor::white << "* It took" << termcolor::reset << " "
        << termcolor::cyan << (myTime.Seconds()) << termcolor::reset << " "
        << termcolor::white << "seconds to read in dictionary." << termcolor::reset << "\n\n";

    cout << termcolor::white << "Please start typing in your word:\n" << termcolor::reset << "";

    string myWord = ""; //word the user is typing in

    //while the user doesn't type enter to end the program
    while ((l = getch()) != 10) { 
        system("clear"); //clears the welcome screen

        l = tolower(l); //checks if char is lowercase
        if (l == 127) { //if input is a backspace
            if (myWord.size()) { 
                myWord.erase(myWord.size() - 1);
            }
        }

        else if (l < 97 || l > 122) { //if input is not a letter output this
            cout << termcolor::red << "PLEASE MAKE SURE YOU ARE ONLY TYPING LETTERS!" << termcolor::reset << "\n\n";
        }
        else {
            myWord += l;
        }

        if (myWord.size()) { // the word has at least one letter
            cout << termcolor::white << "Current String:" << termcolor::reset
                << " " << termcolor::blue << myWord << termcolor::reset
                << "\n\n"; //prints out the word found till this point

            myTime.Start();
            myDictionary.searchWord(myWord);
            myTime.End();
        }
        else {
            cout << termcolor::white << "Please type in your word: " << termcolor::reset << "\n";
        }
    }
}

