/*************************************************************************
 *
 *  Author:           Michelle Orru
 *  Label:            P01
 *  Title:            Database Indexes
 *  Course:           CMPS 3013
 *  Semester:         Spring 2023
 *
 *  Description:
 *       Using random_person_data we created using Mockaroo, build 1 or more 
 *       data that can be searched using specified keys in the random data.
 *
 *  Files:
 *       main.cpp                       : main driver program
 *       json.hpp                       : file containing json implementations
 *       timer.hpp                      : implementations for timer
 *       methods.hpp                    : file with BST and LL implementations
 *       person.hpp                     : file initializing a person
 *       random_person_data_01.json     : input file
 *
 *************************************************************************/

// importing required libraries
#include "json.hpp"
#include "methods.hpp"
#include "timer.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

using json = nlohmann::json;

// function to display options to either check menu or exit
void searchOptions() {
  cout << "Please select an option below: " << endl;
  cout << "1) New search" << endl;
  cout << "2) Exit" << endl;
  cout << "Selection : ";
}

// menu used for user to chose what they want to search
void searchMenu() {
  cout << "Select based in which key you wants to search:\n"
       << "0.Id\n"
       << "1.First Name\n"
       << "2.Last Name\n"
       << "3.Email\n"
       << "4.Address\n"
       << "5.City\n"
       << "6.State\n"
       << "7.Coordinates\n"
       << "8.Car\n"
       << "9.Favorite Movie\n"
       << "10.Pet\n"
       << "11.Job Title\n"
       << "12.Phone number\n"
       << "13.Exit\n";
  cout << "Enter Your Choice:";
}

// Main method
int main() {
  // variables
  string str;
  Timer T;
  double seconds;
  int choice;
  int selection;
  string searchString;
  BST *b;
  LLNode *l;
  int id;
  double latitude;
  double longitude;
  string stocks;

  // Vector for saving person data
  vector<Person> people;

  // open input file
  ifstream infile;
  infile.open("random_person_data_01.json");

  // different binary search trees used to save data
  BST *bst_id = NULL;
  BST *bst_fname = NULL;
  BST *bst_lname = NULL;
  BST *bst_email = NULL;
  BST *bst_address = NULL;
  BST *bst_city = NULL;
  BST *bst_state = NULL;
  BST *bst_coordinates = NULL;
  BST *bst_car = NULL;
  BST *bst_fmovie = NULL;
  BST *bst_pet = NULL;
  BST *bst_job = NULL;
  BST *bst_phone_number = NULL;

  LLNode *linkedlist = NULL;

  //reading data from json and adding it to vector
  json data;
  infile >> data;
  for (size_t i = 0; i < data.size(); i++) {
    vector<string> stocks;

    //iterate through the elements of an array of stocks stored in the json file
    for (const auto &elem : data[i]["stocks"]) {
      stocks.push_back(elem.get<std::string>());
    }

    Person individual = {data[i]["id"],
                         data[i]["first_name"],
                         data[i]["last_name"],
                         data[i]["email"],
                         data[i]["address"],
                         data[i]["city"],
                         data[i]["state"],
                         data[i]["latitude"],
                         data[i]["longitude"],
                         data[i]["car"],
                         data[i]["car_model"],
                         data[i]["car_color"],
                         data[i]["favorite_movie"],
                         data[i]["pet"],
                         data[i]["job_title"],
                         data[i]["phone_number"],
                         stocks};
    people.push_back(individual);
  }

  //Inserting data to BST and Linked List
  for (auto individual : people) {
    insert(bst_id, individual, individual.id);
    insert(bst_fname, individual, get_lower(individual.first_name));
    insert(bst_lname, individual, get_lower(individual.last_name));
    insert(bst_address, individual, get_lower(individual.address));
    insert(bst_email, individual, get_lower(individual.email));
    insert(bst_city, individual, get_lower(individual.city));
    insert(bst_state, individual, get_lower(individual.state));
    insert(bst_coordinates, individual,
           (individual.latitude + individual.longitude));
    insert(bst_car, individual, get_lower(individual.car));
    insert(bst_fmovie, individual, get_lower(individual.favorite_movie));
    insert(bst_pet, individual, get_lower(individual.pet));
    insert(bst_job, individual, get_lower(individual.job_title));
    insert(bst_phone_number, individual, get_lower(individual.phone_number));

    insert_in_LinkedList(&linkedlist, individual);
  }

  //display options
  searchMenu();
  cin >> choice;
  cout << endl;
  cout << "Choice is " << choice << endl;
  cin.ignore();

  //while the user doesn't choose to exit, continue
  while (choice != 13) {
    if (choice == 0) {
      cout << "Enter ID number to be searched:";
      cin >> id;
      cin.ignore();
    } else if (choice == 7) {
      cout << "Enter latitude to be searched from Data:";
      cin >> latitude;
      cout << "Enter longitude to be searched from Data:";
      cin >> longitude;
      cin.ignore();
    } else {
      cout << "Enter string to be searched from Data:";
      getline(cin, searchString);
    }
    
    //make sure everything's in lowercase
    searchString = get_lower(searchString);

    // start time in bst
    T.Start();
    switch (choice) {
    case 0:
      b = search(bst_id, id);
      break;
    case 1:
      b = search(bst_fname, searchString);
      break;
    case 2:
      b = search(bst_lname, searchString);
      break;
    case 3:
      b = search(bst_address, searchString);
      break;
    case 4:
      b = search(bst_email, searchString);
      break;
    case 5:
      b = search(bst_city, searchString);
      break;
    case 6:
      b = search(bst_state, searchString);
      break;
    case 7:
      b = search(bst_coordinates, latitude, longitude);
      break;
    case 8:
      b = search(bst_car, searchString);
      break;
    case 9:
      b = search(bst_fmovie, searchString);
      break;
    case 10:
      b = search(bst_pet, searchString);
      break;
    case 11:
      b = search(bst_job, searchString);
      break;
    case 12:
      b = search(bst_phone_number, searchString);
      break;
    }
    T.End();
    seconds = T.Seconds();

    cout << "Completed search in BST in " << seconds << " seconds" << endl;

    // start search in LL
    T.Start();
    if (choice == 7)
      l = search_in_LL(linkedlist, latitude, longitude);
    else if (choice == 0)
      l = search_in_LL(linkedlist, id);
    else
      l = search_in_LL(linkedlist, searchString);

    T.End();
    seconds = T.Seconds();

    cout << "Completed search in Linked List in " << seconds << " seconds "
         << endl;
    cout << endl;

    // if found in bst
    if (b != NULL) {
      cout << "Found String " + searchString + " in "
           << b->individual.first_name << "'s file" << endl
           << endl;

      // This iterates over each element in the stocks vector 
      // The iterator is initialized to point to the start of the vector
      // using begin() loop and continues until it reaches the end of 
      //the vector using end()
      for (std::vector<std::string>::const_iterator i =
               b->individual.stocks.begin();
           i != b->individual.stocks.end(); ++i) {
        stocks += *i + ", ";
      }
  
      //once info of the person is found output this
      cout << "The details of the person are" << endl;
      cout << "id : " << b->individual.id
           << "\nfirst_name : " << b->individual.first_name
           << "\nlast_name : " << b->individual.last_name
           << "\nemail: " << b->individual.email
           << "\naddress: " << b->individual.address
           << "\ncity: " << b->individual.city
           << "\nstate: " << b->individual.state
           << "\nlatitude: " << b->individual.latitude
           << "\nlongitude: " << b->individual.longitude
           << "\ncar: " << b->individual.car
           << "\ncar_model: " << b->individual.car_model
           << "\ncar_color: " << b->individual.car_color
           << "\nfavorite_movie: " << b->individual.favorite_movie
           << "\npet: " << b->individual.pet
           << "\njob_title: " << b->individual.job_title
           << "\nphone_number: " << b->individual.phone_number
           << "\nstocks: " << stocks << endl
           << endl;

    } else {
      cout << "Not Found in BST" << endl;
    }

    if (l == NULL) {
      cout << "Not found in Linked List" << endl << endl;
    } else {
      cout << "Also found in Linked List" << endl << endl;
    }
  
    //once done with the current seach give option to start a new one or exit
    searchOptions();  // displays the menu
    cin >> selection; // take in the user input
    if (selection == 1) {
      system("clear");
      searchMenu(); // displays the rules
      cin >> choice;
      cout << endl;
      cout << "Choice is " << choice << endl;
      cin.ignore();
    } else {
      exit(0);
    }
  }

  infile.close();
}
