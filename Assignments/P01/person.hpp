#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// method to convert strings to lower case
string get_lower(string s) {
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
}

// Defining the person struct
struct Person {
  int id;
  string first_name;
  string last_name;
  string email;
  string address;
  string city;
  string state;
  double latitude;
  double longitude;
  string car;
  string car_model;
  string car_color;
  string favorite_movie;
  string pet;
  string job_title;
  string phone_number;
  vector<string> stocks;
};

 // << "0.Id\n"
 // << "1.First Name\n"
 // << "2.Last Name\n"
 // << "3.Email\n"
 // << "4.Address\n"
 // << "5.City\n"
 // << "6.State\n"
 // << "7.Coordinates\n"
 // << "8.Car\n"
 // << "9.Favorite Movie\n"
 // << "10.Pet\n"
 // << "11.Job Title\n"
 // << "12.Phone number\n"
 // << "13.Exit\n";
