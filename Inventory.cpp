#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <conio.h> //for getch
#include <ctype.h>
#include <unistd.h> // for sleep()
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <algorithm>
#include "StoreItem.h"
using namespace std;

void gotoXY(int,int);
void insertion(vector<StoreItem> &StoreItemVector);
void readFiles(vector<StoreItem> &StoreItemVector);
void updation(vector<StoreItem> &StoreItemVector);
void deletion(vector<StoreItem> &StoreItemVector);
void display(vector<StoreItem> &StoreItemVector);
void sorting(vector<StoreItem> &StoreItemVector);
void ascbubbleSort(vector<StoreItem> &StoreItemVector, int z);
void desbubbleSort(vector<StoreItem> &StoreItemVector, int z);
void displayall(vector<StoreItem> &StoreItemVector);
void displaycertain(vector<StoreItem> &StoreItemVector, int i);
vector<int> searchingstring(vector<string> &search, string find);
vector<int> searchingIntEqual(vector<int> &search, int find);
vector<int> searchingIntLess(vector<int> &search, int find);
vector<int> searchingIntMore(vector<int> &search, int find);
void displaySearch(vector<StoreItem> &StoreItemVector, vector<int> &tempvector, int colour);
void displayUpdate(vector<StoreItem> &StoreItemVector, vector<int> &tempvector, int colour);
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
bool notEmpty;
int main(int argc, char const *argv[]) {
  vector<StoreItem> StoreItemVector;
  bool end = 1, done = 1, check = 0;
  char a;

  readFiles(StoreItemVector);

  while (end) {
    if (a != 1 || done || !check) {
      system("cls");
      cout << "Enter your choice."
      << "\n1. Insertion."
      << "\n2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit."<< endl;
      a = getch() - '0';
    } else {
      system("cls");
      cout << "Enter your choice."
      << "\n1. Insertion."
      << "\n2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit."<< endl;
      cout << "\a\n\n\033[1;31mWrong input. \nEnter number between 1-6 only.\033[0m" << endl;
      a = getch() - '0';
      check = 0;
    }
    while (a < 0 || a > 6) {
      system("cls");
      cout << "Enter your choice."
      << "\n1. Insertion."
      << "\n2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit."<< endl;
      cout << "\a\n\n\033[1;31mWrong input. \nEnter number between 1-6 only.\033[0m" << endl;
      a = getch() - '0';
    }
    if (a == 1) {
      insertion(StoreItemVector);
    } else if (a == 2) {
      updation(StoreItemVector);
    } else if (a == 3) {
      deletion(StoreItemVector);
    } else if (a == 4) {
      display(StoreItemVector);
    } else if (a == 5) {
      sorting(StoreItemVector);
    } else if (a == 6) {
      cout << "Exiting the program...";
      end = 0;
    } else {
      check = 1;
    }
  }

  return 0;
}

void readFiles(vector<StoreItem> &StoreItemVector) {
  fstream read;
  read.open("output.txt");
  bool fileexist = 0;
  if (read.good()) {
    fileexist = 1;
  }
  if (!fileexist) {
    read.open("output.txt", ios::in | ios::out | ios::app);
    read << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
    << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
  } else {
    StoreItem StoreItemObj;
    bool first = 0;
    string itemID, name, description, category, manufacturer, date;
    float sellPrice, costPrice;
    int unitInStore, unitSold, year, month, day;
    string tempStr, str[100];
    int pos, pos1, pos2, pos3, x = 0;
    while (!read.eof())
    {
      if (!first) {
        getline(read, tempStr);
      }
      first = 1;
      getline(read, tempStr);
      istringstream temp(tempStr);
      while (!tempStr.empty()) {
        pos = tempStr.find("|");
        pos2 = tempStr.find(" ");
        if (pos == 0) {
          pos1 = tempStr.find("|", pos + 1);
          pos = 1;
        } else {
          pos1 = pos;
          pos = 0;
        }
        if (pos2 == 0) {
          pos = 1;
        }
        str[x] = tempStr.substr(pos, pos1-1);
        pos = str[x].find(" ");
        tempStr.erase(0, pos1 + 1);
        x++;
      }
      itemID = str[0];
      name = str[1];
      description = str[2];
      category = str[3];
      manufacturer = str[4];
      sellPrice = atof(str[5].c_str());
      costPrice = atof(str[6].c_str());
      unitInStore = atoi(str[7].c_str());
      unitSold = atoi(str[8].c_str());
      date = str[9];
      pos = date.find("/");
      string day1 = date.substr(0, pos);
      day = atoi(day1.c_str());
      date.erase(0, pos + 1);
      pos = date.find("/");
      string month1 = date.substr(0, pos);
      month = atoi(month1.c_str());
      date.erase(0, pos + 1);
      pos = date.find("/", pos);
      string year1 = date.substr(0, pos);
      year = atoi(year1.c_str());
      x = 0;
      StoreItemObj.setStoreItem(itemID, name, description, category, manufacturer, sellPrice, costPrice, unitInStore, unitSold, year, month, day);
      StoreItemVector.push_back(StoreItemObj);
    }
    StoreItemVector.pop_back();
    read.close();
  }
}

void insertion(vector<StoreItem> &StoreItemVector) {
  fstream out("output.txt", ios::in | ios::out | ios::ate);
  char choose;
  string itemID, name, description, category, manufacturer;
  float sellPrice, costPrice;
  int unitInStore, unitSold, year, month, day;
  StoreItem StoreItemObj;
  while (tolower(choose) != 'n') {
    system("cls"); //to clear screen.
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update.\033[0m"
    << "\n\033[90m3. Deletion.\033[0m"
    << "\n\033[90m4. Display data."
    << "\n5. Sorting."
    << "\n\033[90m6. Exit the program.\033[0m"
    << "\n**************************" << endl
    << "\n\nEnter the Item id." << endl;
    cin >> itemID;
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cin.ignore(); //ignore the input before.
    cout << "\n\nEnter the Item Name." << endl;
    getline(cin,name);
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter the Item description." << endl;
    getline(cin,description);
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter the category." << endl;
    cin >> category;
    system("cls");
    cin.ignore();
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter the manufacturer." << endl;
    getline(cin,manufacturer);
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter the Selling Price." << endl;
    cin >> sellPrice;
    while (cin.fail() || sellPrice < 0) {
      cin.clear();
      cin.ignore();
      system("cls");
      cout << "Enter your choice."
      << "\n\033[1;4;93m1. Insertion.\033[0m"
      << "\n\033[90m2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit the program.\033[0m"
      << "\n**************************" << endl;
      cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter Selling Price again.\033[0m" << endl;
      cin >> sellPrice;
    }
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter the Cost Price." << endl;
    cin >> costPrice;
    while (cin.fail() || costPrice < 0) {
      cin.clear();
      cin.ignore();
      system("cls");
      cout << "Enter your choice."
      << "\n\033[1;4;93m1. Insertion.\033[0m"
      << "\n\033[90m2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit the program.\033[0m"
      << "\n**************************" << endl;
      cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter Cost Price again.\033[0m" << endl;
      cin >> costPrice;
    }
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter units in Store." << endl;
    cin >> unitInStore;
    while (cin.fail() || unitInStore < 0) {
      cin.clear();
      cin.ignore();
      system("cls");
      cout << "Enter your choice."
      << "\n\033[1;4;93m1. Insertion.\033[0m"
      << "\n\033[90m2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit the program.\033[0m"
      << "\n**************************" << endl;
      cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter units in store again.\033[0m" << endl;
      cin >> unitInStore;
    }
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter units sold." << endl;
    cin >> unitSold;
    while (cin.fail() || unitSold < 0) {
      cin.clear();
      cin.ignore();
      system("cls");
      cout << "Enter your choice."
      << "\n\033[1;4;93m1. Insertion.\033[0m"
      << "\n\033[90m2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit the program.\033[0m"
      << "\n**************************" << endl;
      cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter units sold again.\033[0m" << endl;
      cin >> unitSold;
    }
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter year of Date First Introduced. (1-2018)" << endl;
    cin >> year;
    while (cin.fail() || year < 0 || year > 2018) {
      if (cin.fail()) {
        cin.clear();
        cin.ignore();
        system("cls");
        cout << "Enter your choice."
        << "\n\033[1;4;93m1. Insertion.\033[0m"
        << "\n\033[90m2. Update."
        << "\n3. Deletion."
        << "\n4. Display data."
        << "\n5. Sorting."
        << "\n6. Exit the program.\033[0m"
        << "\n**************************" << endl;
        cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter year of Date First Introduced again.\033[0m" << endl;
        cin >> year;
      } else {
        system("cls");
        cout << "Enter your choice."
        << "\n\033[1;4;93m1. Insertion.\033[0m"
        << "\n\033[90m2. Update."
        << "\n3. Deletion."
        << "\n4. Display data."
        << "\n5. Sorting."
        << "\n6. Exit the program.\033[0m"
        << "\n**************************" << endl;
        cout << "\a\n\n\033[1;31mInvalid value.\nPlease enter year of Date First Introduced again. (1-2018)\033[0m" << endl;
        cin >> year;
      }
    }
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter month of Date First Introduced. (1-12)" << endl;
    cin >> month;
    while (cin.fail() || month < 0 || month > 12) {
      if (cin.fail()) {
        cin.clear();
        cin.ignore();
        system("cls");
        cout << "Enter your choice."
        << "\n\033[1;4;93m1. Insertion.\033[0m"
        << "\n\033[90m2. Update."
        << "\n3. Deletion."
        << "\n4. Display data."
        << "\n5. Sorting."
        << "\n6. Exit the program.\033[0m"
        << "\n**************************" << endl;
        cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter month of Date First Introduced again.\033[0m" << endl;
        cin >> month;
      } else {
        system("cls");
        cout << "Enter your choice."
        << "\n\033[1;4;93m1. Insertion.\033[0m"
        << "\n\033[90m2. Update."
        << "\n3. Deletion."
        << "\n4. Display data."
        << "\n5. Sorting."
        << "\n6. Exit the program.\033[0m"
        << "\n**************************" << endl;
        cout << "\a\n\n\033[1;31mInvalid value.\nPlease enter month of Date First Introduced again. (1-12)\033[0m" << endl;
        cin >> month;
      }
    }
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nEnter day of Date First Introduced. (1-31)" << endl;
    cin >> day;
    while (cin.fail() || day < 0 || day > 32) {
      if (cin.fail()) {
        cin.clear();
        cin.ignore();
        system("cls");
        cout << "Enter your choice."
        << "\n\033[1;4;93m1. Insertion.\033[0m"
        << "\n\033[90m2. Update."
        << "\n3. Deletion."
        << "\n4. Display data."
        << "\n5. Sorting."
        << "\n6. Exit the program.\033[0m"
        << "\n**************************" << endl;
        cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter day of Date First Introduced again.\033[0m" << endl;
        cin >> day;
      } else {
        system("cls");
        cout << "Enter your choice."
        << "\n\033[1;4;93m1. Insertion.\033[0m"
        << "\n\033[90m2. Update."
        << "\n3. Deletion."
        << "\n4. Display data."
        << "\n5. Sorting."
        << "\n6. Exit the program.\033[0m"
        << "\n**************************" << endl;
        cout << "\a\n\n\033[1;31mInvalid value.\nPlease enter day of Date First Introduced again. (1-31)\033[0m" << endl;
        cin >> day;
      }
    }
    string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    StoreItemObj.setStoreItem(itemID, name, description, category, manufacturer, sellPrice, costPrice, unitInStore, unitSold, year, month, day);
    StoreItemVector.push_back(StoreItemObj);
    out << left <<"|" << setw(15) <<  itemID << "|"  << setw(15) << name << "|"  << setw(15) << description << "|"  << setw(15) << category << "|"  << setw(15) << manufacturer << "|"  << setw(15) << sellPrice << "|"
    << setw(15) << costPrice << "|"  << setw(15) << unitInStore << "|"  << setw(15) << unitSold << "|"  << setw(15) << date << "|" << endl;
    system("cls");
    cout << "Enter your choice."
    << "\n\033[1;4;93m1. Insertion.\033[0m"
    << "\n\033[90m2. Update."
    << "\n3. Deletion."
    << "\n4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit the program.\033[0m"
    << "\n**************************\n\n\n"
    << "\n\nDo you want to enter the next record?: (y/n)";
    cin >> choose;
    while (cin.fail() || (tolower(choose) != 'y' && tolower(choose) != 'n')) {
      system("cls");
      cout << "Enter your choice."
      << "\n\033[1;4;93m1. Insertion.\033[0m"
      << "\n\033[90m2. Update."
      << "\n3. Deletion."
      << "\n4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit the program.\033[0m"
      << "\n**************************\n\n\n"
      << "\a\n\n\033[1;31mInvalid input.\nPlease a valid choice. (y/n)\033[0m" << endl;
      cin >> choose;
    }
  }
}

void updation(vector<StoreItem> &StoreItemVector) {
  if (StoreItemVector.size() > 0) {
    system("cls");
    bool running = 1;
    int recordx = 0, recordy = 0, x = 3, y = 1;
    char temp;
    cout << "Choose your choice to update" << endl;
    cout << "1. Using arrow. (You need to maximise your terminal)"
    << "\n2. Using number."
    << "\n to choose your record to update." << endl;
    temp = getch() - '0';
    while (temp < 0 || temp > 2) {
      cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-2.\nPlease enter your choice again.\033[0m" << endl;
      temp = getch() - '0';
    }
    if (temp == 1) {
      gotoXY(3,0); cout << left <<"\n\n   |" << setw(17) <<  "Item ID" << "|"  << setw(17) << "Name" << "|"  << setw(17) << "Description" << "|"  << setw(17) << "Category" << "|"  << setw(17) << "Manufacturer" << "|"  << setw(17) << "Sell Price" << "|"
      << setw(17) << "Cost Price" << "|"  << setw(17) << "Unit In Store" << "|"  << setw(17) << "Unit Sold" << "|"  << setw(17) << "Date" << "|" << endl;
      gotoXY(1,3); cout << "->";
      for (size_t i = 0; i < StoreItemVector.size(); i++) {
        int day = StoreItemVector[i].getDay();
        int month = StoreItemVector[i].getMonth();
        int year = StoreItemVector[i].getYear();
        string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        gotoXY(3,i+3); cout << left <<"|" << setw(17) <<  StoreItemVector[i].getItemId() << "|"  << setw(17) << StoreItemVector[i].getName() << "|"  << setw(17) << StoreItemVector[i].getDescription() << "|"  << setw(17) << StoreItemVector[i].getCategory() << "|"
        << setw(17) << StoreItemVector[i].getManufacturer() << "|"  << setw(17) << StoreItemVector[i].getSellPrice() << "|" << setw(17) << StoreItemVector[i].getCostPrice() << "|"  << setw(17) << StoreItemVector[i].getUnitInStore() << "|"  << setw(17)
        << StoreItemVector[i].getUnitSold() << "|"  << setw(17) << date << "|" << endl;
      }
      cout << "\n\nUsing arrow keys (arrow up and down) to choose which record you want to update." << endl;
      while (running) {
        system("pause>nul");
        if(GetAsyncKeyState(VK_DOWN) && (x != (StoreItemVector.size() + 2)) && !(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))) //down button pressed
        {
          gotoXY(1,x); cout << "  ";
          x++;
          gotoXY(1,x); cout << "->";
          recordy++;
          continue;
        }
        if(GetAsyncKeyState(VK_UP) && recordy != 0 && !(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))) //up button pressed
        {
          gotoXY(1,x); cout << "  ";
      		x--;
      		gotoXY(1,x); cout << "->";
      		recordy--;
      		continue;
        }
        if(GetAsyncKeyState(VK_RETURN) && !(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))) { // Enter key pressed
          running = 0;
        }
      }
      system("cls");
      gotoXY(3,0); cout << left <<"\n\n   |" << setw(17) <<  "Item ID" << "|"  << setw(17) << "Name" << "|"  << setw(17) << "Description" << "|"  << setw(17) << "Category" << "|"  << setw(17) << "Manufacturer" << "|"  << setw(17) << "Sell Price" << "|"
      << setw(17) << "Cost Price" << "|"  << setw(17) << "Unit In Store" << "|"  << setw(17) << "Unit Sold" << "|"  << setw(17) << "Date" << "|" << endl;
      gotoXY(1,x); cout << "->";
      for (size_t i = 0; i < StoreItemVector.size(); i++) {
        int day = StoreItemVector[i].getDay();
        int month = StoreItemVector[i].getMonth();
        int year = StoreItemVector[i].getYear();
        string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        gotoXY(3,i+3); cout << left <<"|" << setw(17) <<  StoreItemVector[i].getItemId() << "|"  << setw(17) << StoreItemVector[i].getName() << "|"  << setw(17) << StoreItemVector[i].getDescription() << "|"  << setw(17) << StoreItemVector[i].getCategory() << "|"
        << setw(17) << StoreItemVector[i].getManufacturer() << "|"  << setw(17) << StoreItemVector[i].getSellPrice() << "|" << setw(17) << StoreItemVector[i].getCostPrice() << "|"  << setw(17) << StoreItemVector[i].getUnitInStore() << "|"  << setw(17)
        << StoreItemVector[i].getUnitSold() << "|"  << setw(17) << date << "|" << endl;
      }
      cout << "\n\nUsing arrow keys (arrow left and right) to choose which data field you want to update the record." << endl;
      bool running1 = 1;
      while (running1 && !running) {
        system("pause>nul");
        if(GetAsyncKeyState(VK_RIGHT) && recordx != 9 && !(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RETURN))) //down button pressed
        {
          gotoXY(y,x); cout << "  ";
          y += 18;
          gotoXY(y,x); cout << "->";
          recordx++;
          continue;
        }
        if(GetAsyncKeyState(VK_LEFT) && recordx != 0 && !(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_RIGHT))) //up button pressed
        {
          gotoXY(y,x); cout << "  ";
          y -= 18;
          gotoXY(y,x); cout << "->";
          recordx--;
          continue;
        }
        if(GetAsyncKeyState(VK_RETURN) && !(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))) { // Enter key pressed
          running1 = 0;
        }
      }

      if (recordx < 5 && !running && !running1) {
        cout.flush();
        string temp;
        gotoXY(y+3,x);
        if (recordx < 1) {
          cin >> setw(15) >> temp;
          StoreItemVector[recordy].setItemId(temp);
          system("cls");
          cout << "\n The new Item ID is: " << StoreItemVector[recordy].getItemId();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        } else if (recordx < 3) {
          cout.flush();
          if (recordx < 2) {
            cout.flush();
            getline(cin, temp);
            StoreItemVector[recordy].setName(temp);
            system("cls");
            cout << "\n The new Item Name is: " << StoreItemVector[recordy].getName();
            cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
            cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
            << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
            size_t i = recordy;
            int day = StoreItemVector[i].getDay();
            int month = StoreItemVector[i].getMonth();
            int year = StoreItemVector[i].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
            << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
            system("pause");
          } else {
            cout.flush();
            getline(cin, temp);
            StoreItemVector[recordy].setDescription(temp);
            system("cls");
            cout << "\n The new Item Description is: " << StoreItemVector[recordy].getDescription();
            cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
            cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
            << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
            size_t i = recordy;
            int day = StoreItemVector[i].getDay();
            int month = StoreItemVector[i].getMonth();
            int year = StoreItemVector[i].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
            << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
            system("pause");
          }
        } else if (recordx < 4) {
          cin >> temp;
          StoreItemVector[recordy].setCategory(temp);
          system("cls");
          cout << "\n The new Item Category is: " << StoreItemVector[recordy].getCategory();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        } else {
          cout.flush();
          cin.ignore();
          getline(cin, temp);
          StoreItemVector[recordy].setManufacturer(temp);
          system("cls");
          cout << "\n The new Item Manufacturer is: " << StoreItemVector[recordy].getManufacturer();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        }
      } else if (recordx < 7 && !running && !running1) {
        gotoXY(y+3,x);
        float temp;
        cin >> temp;
        if (recordx == 5) {
          system("cls");
          StoreItemVector[recordy].setSellPrice(temp);
          cout << "\n The new Item Selling Price is: " << StoreItemVector[recordy].getSellPrice();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        } else {
          system("cls");
          StoreItemVector[recordy].setCostPrice(temp);
          cout << "\n The new Item Cost Price is: " << StoreItemVector[recordy].getCostPrice();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        }
      } else {
        cout.flush();
        if (recordx == 7) {
          int temp;
          cin >> temp;
          system("cls");
          StoreItemVector[recordy].setUnitInStore(temp);
          cout << "\n The new Item Unit in Store is: " << StoreItemVector[recordy].getUnitInStore();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        } else if (recordx == 8) {
          int temp;
          cin >> temp;
          system("cls");
          StoreItemVector[recordy].setUnitSold(temp);
          cout << "\n The new Item Unit Sold is: " << StoreItemVector[recordy].getUnitSold();
          cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          size_t i = recordy;
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          system("pause");
        } else {
          system("cls");
          int choice;
          cout << "\n\n\n\n\n\n\n\n\n\n\nChoose which data field that you want to update?"
          << "\n1. Year of Date First Introduced"
          << "\n2. Month of Date First Introduced"
          << "\n3. Day of Date First Introduced" << endl;
          cin >> choice;
          while (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore();
            cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again (1-3).\033[0m" << endl;
            cin >> choice;
          }
          int temp;
          if (choice == 1) {
            cout << "\n\033[1;4;93m1. Year of Date First Introduced\033[0m"
            << "\n**************************" << endl
            << "\nEnter new Year of date First Introduced: ";
            cin >> temp;
            while (cin.fail() || temp < 1 || temp > 2018) {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter Year of date First Introduced again.\033[0m" << endl;
              cin >> temp;
            }
            system("cls");
            StoreItemVector[recordy].setYear(temp);
            cout << "\n The new Year of Date First Introduced is: " << StoreItemVector[recordy].getYear();
            cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
            cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
            << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
            size_t i = recordy;
            int day = StoreItemVector[i].getDay();
            int month = StoreItemVector[i].getMonth();
            int year = StoreItemVector[i].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
            << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
            system("pause");
          } else if (choice == 2) {
            cout << "\n\033[1;4;93m1. Month of Date First Introduced\033[0m"
            << "\n**************************" << endl
            << "\nEnter new Month of date First Introduced: ";
            cin >> temp;
            while (cin.fail() || temp < 1 || temp > 12) {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter Month of date First Introduced again.\033[0m" << endl;
              cin >> temp;
            }
            system("cls");
            StoreItemVector[recordy].setMonth(temp);
            cout << "\n The new Month of Date First Introduced is: " << StoreItemVector[recordy].getMonth();
            cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
            cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
            << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
            size_t i = recordy;
            int day = StoreItemVector[i].getDay();
            int month = StoreItemVector[i].getMonth();
            int year = StoreItemVector[i].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
            << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
            system("pause");
          } else {
            cout << "\n\033[1;4;93m1. Day of Date First Introduced\033[0m"
            << "\n**************************" << endl
            << "\nEnter new Day of date First Introduced: ";
            cin >> temp;
            while (cin.fail() || temp < 1 || temp > 31) {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter Day of date First Introduced again.\033[0m" << endl;
              cin >> temp;
            }
            system("cls");
            StoreItemVector[recordy].setDay(temp);
            cout << "\n The new Day of Date First Introduced is: " << StoreItemVector[recordy].getDay();
            cout << "\nThe new record for record number " << recordy+1 << " is: " << endl;
            cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
            << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
            size_t i = recordy;
            int day = StoreItemVector[i].getDay();
            int month = StoreItemVector[i].getMonth();
            int year = StoreItemVector[i].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
            << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
            system("pause");
          }
        }
      }
    } else {
      int record;
      system("cls");
      cout << "\n\033[1;4;93m2. Update.\033[0m"
      << "\n**************************" << endl;
      displayall(StoreItemVector);
      cout << "\n**************************" << endl;
      cout << "Which record do you want to update?" << endl;
      cin >> record;
      while (cin.fail() || record < 1 || record > StoreItemVector.size()) {
        cin.clear();
        cin.ignore();
        cout << "\a\033[1;31mInvalid choice of record. Please enter it again. (1-" << StoreItemVector.size() << ")\033[0m" << endl;
      }
      vector<int> tempvector;
      record--;
      tempvector.push_back(record);
      int choiceint;
      system("cls");
      cout << "\n\033[1;4;93m2. Update.\033[0m"
      << "\n**************************" << endl;
      displaycertain(StoreItemVector, record);
      cout << "\n**************************" << endl;
      cout << "What item do you want to update. Choose your choice (1-12) and press enter."
      << "\n1. Item ID"
      << "\n2. Name"
      << "\n3. Description"
      << "\n4. Category"
      << "\n5. Manufacturer"
      << "\n6. Selling Price"
      << "\n7. Cost Price"
      << "\n8. Units in Store"
      << "\n9. Units Sold"
      << "\n10. Year of Date First Introduced"
      << "\n11. Month of Date First Introduced"
      << "\n12. Day of Date First Introduced" << endl;
      cin >> choiceint;
      while (cin.fail() || choiceint < 1 || choiceint > 12){
        cin.clear();
        cin.ignore();
        cout << "\a\033[1;31mInvalid choice. Please enter it again. (1-12)\033[0m" << endl;
        cin >> choiceint;
      }
      string tempStr;
      int temp;
      if (choiceint == 1) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[1;4;32m1. Item ID\033[0m"
        << "\n\033[90m2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdating Item ID" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new item ID." << endl;
        cin >> tempStr;
        StoreItemVector[record].setItemId(tempStr);
        displayUpdate(StoreItemVector, tempvector, 1);
        system("pause");
      } else if (choiceint == 2) {
        cin.ignore();
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID\033[0m"
        << "\n\033[1;4;32m2. Name\033[0m"
        << "\n\033[90m3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdating Item Name" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new item name" << endl;
        getline(cin,tempStr);
        StoreItemVector[record].setName(tempStr);
        displayUpdate(StoreItemVector, tempvector, 2);
        system("pause");
      } else if (choiceint == 3) {
        cin.ignore();
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name\033[0m"
        << "\n\033[1;4;32m3. Description\033[0m"
        << "\n\033[90m4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdating Item Description" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new item Description" << endl;
        getline(cin,tempStr);
        StoreItemVector[record].setDescription(tempStr);
        displayUpdate(StoreItemVector, tempvector, 3);
        system("pause");
      } else if (choiceint == 4) {
        cin.ignore();
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description\033[0m"
        << "\n\033[1;4;32m4. Category\033[0m"
        << "\n\033[90m5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdating Item category" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new item category" << endl;
        cin >> tempStr;
        StoreItemVector[record].setCategory(tempStr);
        displayUpdate(StoreItemVector, tempvector, 4);
        system("pause");
      } else if (choiceint == 5) {
        cin.ignore();
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category\033[0m"
        << "\n\033[1;4;32m5. Manufacturer\033[0m"
        << "\n\033[90m6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdating Item manufacturer" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new item manufacturer" << endl;
        getline(cin,tempStr);
        StoreItemVector[record].setManufacturer(tempStr);
        displayUpdate(StoreItemVector, tempvector, 5);
        system("pause");
      } else if (choiceint == 6) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer\033[0m"
        << "\n\033[1;4;32m6. Selling Price\033[0m"
        << "\n\033[90m7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;
        cout << "\n\nUpdating Item Selling Price" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new item Selling Price" << endl;
        cin >> temp;
        while (cin.fail() || temp < 0) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again.\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setSellPrice(temp);
        displayUpdate(StoreItemVector, tempvector, 6);
        system("pause");
      } else if (choiceint == 7) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price\033[0m"
        << "\n\033[1;4;32m7. Cost Price\033[0m"
        << "\n\033[90m8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdate Item Cost Price" << endl
        << "\n**************************" << endl;
        cout << "\nEnter the new Cost Price." << endl;
        cin >> temp;
        while (cin.fail() || temp < 0) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again.\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setCostPrice(temp);
        displayUpdate(StoreItemVector, tempvector, 7);
        system("pause");
      } else if (choiceint == 8) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price\033[0m"
        << "\n\033[1;4;32m8. Units in Store\033[0m"
        << "\n\033[90m9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdate Units in Store" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new units in Store." << endl;
        cin >> temp;
        while (cin.fail() || temp < 0) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again.\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setUnitInStore(temp);
        displayUpdate(StoreItemVector, tempvector, 8);
        system("pause");
      } else if (choiceint == 9) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store\033[0m"
        << "\n\033[1;4;32m9. Units Sold\033[0m"
        << "\n\033[90m10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdate Item Units Sold" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new units sold." << endl;
        cin >> temp;
        while (cin.fail() || temp < 0) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again.\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setUnitSold(temp);
        displayUpdate(StoreItemVector, tempvector, 9);
        system("pause");
      } else if (choiceint == 10) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold\033[0m"
        << "\n\033[1;4;32m10. Year of Date First Introduced\033[0m"
        << "\n\033[90m11. Month of Date First Introduced"
        << "\n12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdate Year of Date First Introduced" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new Year of Date First Introduced. (1-2018)" << endl;
        cin >> temp;
        while (cin.fail() || temp < 1 || temp > 2018) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again. (1-2018)\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setYear(temp);
        displayUpdate(StoreItemVector, tempvector, 10);
        system("pause");
      } else if (choiceint == 11) {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced\033[0m"
        << "\n\033[1;4;32m11. Month of Date First Introduced\033[0m"
        << "\n\033[90m12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdate Month of Date First Introduced" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new Month of Date First Introduced. (1-12)" << endl;
        cin >> temp;
        while (cin.fail() || temp < 1 || temp > 12) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again. (1-12)\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setMonth(temp);
        displayUpdate(StoreItemVector, tempvector, 10);
        system("pause");
      } else {
        system("cls");
        cout << "\033[1;4;93m2. Update.\033[0m"
        << "\n**************************" << endl;
        displaycertain(StoreItemVector, record);
        cout << "\n**************************" << endl;
        cout << "What item do you want to update. Choose your choice and press enter."
        << "\n\033[90m1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer"
        << "\n6. Selling Price"
        << "\n7. Cost Price"
        << "\n8. Units in Store"
        << "\n9. Units Sold"
        << "\n10. Year of Date First Introduced"
        << "\n11. Month of Date First Introduced\033[0m"
        << "\n\033[1;4;32m12. Day of Date First Introduced\033[0m" << endl;

        cout << "\n\nUpdate Day of Date First Introduced" << endl
        << "\n**************************" << endl;
        cout << "\nEnter new Day of Date First Introduced. (1-31)" << endl;
        cin >> temp;
        while (cin.fail() || temp < 1 || temp > 31) {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only number accepted.\nPlease enter again. (1-12)\033[0m" << endl;
          cin >> temp;
        }
        StoreItemVector[record].setDay(temp);
        displayUpdate(StoreItemVector, tempvector, 10);
        system("pause");
      }
    }
    ofstream out;
    out.open("output.txt", ios::out);
    out << left << "|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
    << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
    for (size_t i = 0; i < StoreItemVector.size(); i++) {
      int day = StoreItemVector[i].getDay();
      int month = StoreItemVector[i].getMonth();
      int year = StoreItemVector[i].getYear();
      string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
      out << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
      << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
      << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
    }
    out.close();
  } else {
    system("cls");
    cout << "\n\033[1;4;93m2. Update.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nNo data to be update." << endl;
    system("pause");
  }
}

void deletion(vector<StoreItem> &StoreItemVector) {
  if (StoreItemVector.size() > 0) {
    char a;
    system("cls");
    cout << "Enter your choice."
    << "\n\033[90m1. Insertion."
    << "\n2. Update.\033[0m"
    << "\n\033[1;4;93m3. Deletion.\033[0m"
    << "\n\033[90m4. Display data."
    << "\n5. Sorting."
    << "\n6. Exit.\033[0m"
    << "\n**************************" << endl;
    displayall(StoreItemVector);
    cout << "\n**************************" << endl;
    cout << "\n\nChoose your choice."
    << "\n1. Delete whole record."
    << "\n2. Delete a record."
    << "\n3. Delete selected data field." << endl;
    a = getch() - '0';
    while (a < 1 || a > 3) {
      cout << "\a\n\n\033[1;31mInvalid number. Please enter a number between 1-3 only.\033[0m";
      a = getch() - '0';
    }
    if (a == 1) {
      StoreItemVector.clear();
      system("cls");
      cout << "Enter your choice."
      << "\n\033[90m1. Insertion."
      << "\n2. Update.\033[0m"
      << "\n\033[1;4;93m3. Deletion.\033[0m"
      << "\n\033[90m4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit.\033[0m"
      << "\n**************************" << endl;
      displayall(StoreItemVector);
      cout << "\n**************************" << endl;
      cout << "\n\nChoose your choice."
      << "\n\033[1;4;93m1. Delete whole record.\033[0m"
      << "\n\033[90m2. Delete a record."
      << "\n3. Delete selected data field.\033[0m" << endl;
      cout << "\n\nWhole record has been deleted." << endl;
      system("pause");
    } else if (a == 2) {
      int choice;
      system("cls");
      cout << "Enter your choice."
      << "\n\033[90m1. Insertion."
      << "\n2. Update.\033[0m"
      << "\n\033[1;4;93m3. Deletion.\033[0m"
      << "\n\033[90m4. Display data."
      << "\n5. Sorting."
      << "\n6. Exit.\033[0m"
      << "\n**************************" << endl;
      cout << "\n\nChoose your choice."
      << "\n\033[90m1. Delete whole record.\033[0m"
      << "\n\033[1;4;93m2. Delete a record.\033[0m"
      << "\n\033[90m3. Delete selected data field.\033[0m" << endl;
      displayall(StoreItemVector);
      cout << "\n**************************" << endl;
      cout << "\n\nChoose your record that you want to delete.(1-" << StoreItemVector.size() <<") only." << endl;
      cin >> choice;
      while (cin.fail() || choice < 1 || choice > StoreItemVector.size()) {
        cout << "\a\n\n\033[1;31mInvalid number. Please enter a number between 1-" << StoreItemVector.size() << " only.\033[0m";
        cin >> choice;
      }
      choice--;
      StoreItemVector.erase(StoreItemVector.begin() + choice);
      system("cls");
      displayall(StoreItemVector);

      cout << "\n\nData has been deleted." << endl;
      system("pause");
    } else {
      int choice, record;
      system("cls");
      cout << "\n\033[1;4;93m3. Deletion.\033[0m"
      << "\n**************************" << endl;
      displayall(StoreItemVector);
      cout << "\n**************************" << endl;
      cout << "\n\nChoose your record that you want to delete (1-" << StoreItemVector.size() <<") only." << endl;
      cin >> record;
      while (cin.fail() || record < 1 || record > StoreItemVector.size()) {
        cout << "\a\n\n\033[1;31mInvalid number. Please enter a number between 1-" << StoreItemVector.size() << " only.\033[0m";
        cin >> record;
      }
      cout << "\nWhat item do you want to delete. Choose your choice and press enter."
      << "\n1. Item ID"
      << "\n2. Name"
      << "\n3. Description"
      << "\n4. Category"
      << "\n5. Manufacturer"
      << "\n6. Selling Price"
      << "\n7. Cost Price"
      << "\n8. Units in Store"
      << "\n9. Units Sold"
      << "\n10. Year of Date First Introduced"
      << "\n11. Month of Date First Introduced"
      << "\n12. Day of Date First Introduced" << endl;
      cin >> choice;
      while (cin.fail() || choice < 1 || choice > 12) {
        cout << "\a\n\n\033[1;31mInvalid number. Please enter a number between 1-" << StoreItemVector.size() << " only.\033[0m";
        cin >> choice;
      }
      if (choice == 1) {
        StoreItemVector[record].setItemId(" ");
      } else if (choice == 2) {
        StoreItemVector[record].setName(" ");
      } else if (choice == 3) {
        StoreItemVector[record].setDescription(" ");
      } else if (choice == 4) {
        StoreItemVector[record].setCategory(" ");
      } else if (choice == 5) {
        StoreItemVector[record].setManufacturer(" ");
      } else if (choice == 6) {
        StoreItemVector[record].setSellPrice(-1);
      } else if (choice == 7) {
        StoreItemVector[record].setCostPrice(-1);
      } else if (choice == 8) {
        StoreItemVector[record].setUnitInStore(-1);
      } else if (choice == 9) {
        StoreItemVector[record].setUnitSold(-1);
      } else if (choice == 10) {
        StoreItemVector[record].setYear(-1);
      } else if (choice == 11) {
        StoreItemVector[record].setMonth(-1);
      } else {
        StoreItemVector[record].setDay(-1);
      }
      displaycertain(StoreItemVector, record);
    }

    ofstream out;
    out.open("output.txt", ios::out);
    out << left << "|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
    << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
    for (size_t i = 0; i < StoreItemVector.size(); i++) {
      int day = StoreItemVector[i].getDay();
      int month = StoreItemVector[i].getMonth();
      int year = StoreItemVector[i].getYear();
      string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
      out << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
      << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
      << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
    }
    out.close();


  } else {
    system("cls");
    cout << "\n\033[1;4;93m3. Deletion.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nNo data to be delete." << endl;
    system("pause");
  }
}

void display(vector<StoreItem> &StoreItemVector) {
  char temp;
  int menu_item = 0;
  if (StoreItemVector.size() > 0) {
    system("cls");
    cout << "\n\033[1;4;93m4. Display.\033[0m"
    << "\n**************************" << endl;
    cout << "\nEnter your choice."
    << "\n1. Display by selected data field."
    << "\n2. Display by searching data." << endl;
    temp = getch() - '0';
    while (temp < 0 || temp > 2) {
      cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-2.\nPlease enter your choice again.\033[0m" << endl;
      temp = getch() - '0';
    }
    if (temp == 1) {
      system("cls");
      cout << "\n\033[1;4;93m4. Display data.\033[0m"
      << "\n**************************" << endl
      << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
      << "\n**************************" << endl;
      cout << "\nEnter your choice."
      << "\n1. Display all data field."
      << "\n2. Display certain data field." << endl;
      temp = getch() - '0';
      while (temp < 0 || temp > 2) {
        cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-2.\nPlease enter your choice again.\033[0m" << endl;
        temp = getch() - '0';
      }
      if (temp == 1) {
        system("cls");
        cout << "\n\033[1;4;93m4. Display data.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m1. Display all data field.\033[0m" << endl;
        cout << "You have " << StoreItemVector.size() << " total records" << endl;
        cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
        << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
        for (size_t i = 0; i < StoreItemVector.size(); i++) {
          int day = StoreItemVector[i].getDay();
          int month = StoreItemVector[i].getMonth();
          int year = StoreItemVector[i].getYear();
          string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
          cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
          << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
          << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
        }
        system("pause");
      } else if (temp == 2) {
        int tempint;
        system("cls");
        cout << "\n\033[1;4;93m4. Display data.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m2. Display certain data field.\033[0m"
        << "\n**************************" << endl;

        cout << "\nWhat item do you want to display. Choose your choice and press enter."
        << "\n1. Item ID"
        << "\n2. Description"
        << "\n3. Category"
        << "\n4. Manufacturer"
        << "\n5. Selling Price"
        << "\n6. Cost Price"
        << "\n7. Units in Store"
        << "\n8. Units Sold"
        << "\n9. Year of Date First Introduced"
        << "\n10. Month of Date First Introduced"
        << "\n11. Day of Date First Introduced"
        << "\n\nItem name will always appear."<< endl;
        cin >> tempint;
        while (cin.fail() || tempint < 0 || tempint > 12)
        {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-12.\nPlease enter your choice again.\033[0m" << endl;
          cin >> tempint;
        }
        if (tempint == 1) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Item ID\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 2) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Description\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Description" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 3) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m3. Category\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Category" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 4) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m4. Manufacturer\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Manufacturer" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getManufacturer() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 5) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m5. Selling Price\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Selling Price" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 6) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m6. Cost Price\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Cost Price" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getCostPrice() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 7) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m7. Units in Store\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Units in Store" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 8) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m8. Units Sold\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Units Sold" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getUnitSold() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 9) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m9. Year of Date First Introduced\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Year" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getYear() << "|" << endl;
          }
          system("pause");
        } else if (tempint == 10) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m10. Month of Date First Introduced\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Month" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getMonth() << "|" << endl;
          }
          system("pause");
        } else {
          system("cls");
          cout << "\n\033[1;4;93m4. Display data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Display by selected data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display certain data field.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m11. Month of Date First Introduced\033[0m"
          << "\n**************************" << endl;

          cout << "\n\nThe total record that you have is " << StoreItemVector.size() << endl;

          cout << left << "\n|"<< setw(3) << "No." <<"|" << setw(15) <<  "Name" << "|"  << setw(15) << "Day" << "|" << endl;

          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            cout << left << "|" << setw(3) << i+1 <<"|" << setw(15) <<  StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDay() << "|" << endl;
          }
          system("pause");
        }
      }
    } else if (temp == 2) {
      vector<int> tempvector;
      vector<string> search;
      system("cls");
      cout << "\n\033[1;4;93m4. Display.\033[0m"
      << "\n**************************" << endl
      << "\n\033[1;4;32m2. Display by searching data.\033[0m"
      << "\n**************************" << endl;
      cout << "\nSearch by text or number?\nEnter your choice."
      << "\n1. Search by text."
      << "\n2. Search by number." << endl;
      temp = getch() - '0';
      while (temp < 0 || temp > 2) {
        cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-2.\nPlease enter your choice again.\033[0m" << endl;
        temp = getch() - '0';
      }
      if (temp == 1) {
        system("cls");
        int tempint;
        cout << "\n\033[1;4;93m4. Display.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m2. Display by searching data.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m1. Search by text.\033[0m"
        << "\n**************************" << endl;

        cout << "\nWhat item do you want to search. Choose your choice and press enter."
        << "\n1. Item ID"
        << "\n2. Name"
        << "\n3. Description"
        << "\n4. Category"
        << "\n5. Manufacturer" << endl;
        temp = getch() - '0';
        while (cin.fail() || temp < 0 || temp > 5)
        {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-5.\nPlease enter your choice again.\033[0m" << endl;
          temp = getch() - '0';
        }
        string find;
        if (temp == 1) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Search by text.\033[0m"
          << "\n**************************"
          << "\n\033[1;4;32m1. Item ID\033[0m" << endl;

          cout << "\n\nEnter Item ID that you want to search: ";
          cin >> find;
          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            search.push_back(StoreItemVector[i].getItemId());
          }
          tempvector = searchingstring(search, find);
          displaySearch(StoreItemVector, tempvector, 1);
          system("pause");
        } else if (temp == 2) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Search by text.\033[0m"
          << "\n**************************"
          << "\n\033[1;4;32m2. Name\033[0m" << endl;

          cout << "\n\nEnter Item Name that you want to search: ";
          cin.ignore();
          getline(cin, find);
          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            search.push_back(StoreItemVector[i].getName());
          }
          tempvector = searchingstring(search, find);
          displaySearch(StoreItemVector, tempvector, temp);
          system("pause");

        } else if (temp == 3) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Search by text.\033[0m"
          << "\n**************************"
          << "\n\033[1;4;32m3. Description\033[0m" << endl;

          cout << "\n\nEnter Item Description that you want to search: ";
          cin.ignore();
          getline(cin, find);
          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            search.push_back(StoreItemVector[i].getDescription());
          }
          tempvector = searchingstring(search, find);
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          for (size_t i = 0; i < tempvector.size(); i++) {
            int j = tempvector[i];
            int day = StoreItemVector[j].getDay();
            int month = StoreItemVector[j].getMonth();
            int year = StoreItemVector[j].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[j].getItemId() << "|"  << setw(15) << StoreItemVector[j].getName() << "|\033[1;92m"  << setw(15) << StoreItemVector[j].getDescription() << "\033[0m|"  << setw(15) << StoreItemVector[j].getCategory() << "|"
            << setw(15) << StoreItemVector[j].getManufacturer() << "|"  << setw(15) << StoreItemVector[j].getSellPrice() << "|" << setw(15) << StoreItemVector[j].getCostPrice() << "|"  << setw(15) << StoreItemVector[j].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[j].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          }
          system("pause");

        } else if (temp == 4) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Search by text.\033[0m"
          << "\n**************************"
          << "\n\033[1;4;32m3. Category\033[0m" << endl;

          cout << "\n\nEnter Item Category that you want to search: ";
          cin.ignore();
          getline(cin, find);
          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            search.push_back(StoreItemVector[i].getCategory());
          }
          tempvector = searchingstring(search, find);
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          for (size_t i = 0; i < tempvector.size(); i++) {
            int j = tempvector[i];
            int day = StoreItemVector[j].getDay();
            int month = StoreItemVector[j].getMonth();
            int year = StoreItemVector[j].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[j].getItemId() << "|"  << setw(15) << StoreItemVector[j].getName() << "|"  << setw(15) << StoreItemVector[j].getDescription() << "|\033[1;92m"  << setw(15) << StoreItemVector[j].getCategory() << "\033[0m|"
            << setw(15) << StoreItemVector[j].getManufacturer() << "|"  << setw(15) << StoreItemVector[j].getSellPrice() << "|" << setw(15) << StoreItemVector[j].getCostPrice() << "|"  << setw(15) << StoreItemVector[j].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[j].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          }
          system("pause");

        } else {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Search by text.\033[0m"
          << "\n**************************"
          << "\n\033[1;4;32m3. Manufacturer\033[0m" << endl;

          cout << "\n\nEnter Item Manufacturer that you want to search: ";
          cin.ignore();
          getline(cin, find);
          for (size_t i = 0; i < StoreItemVector.size(); i++) {
            search.push_back(StoreItemVector[i].getManufacturer());
          }
          tempvector = searchingstring(search, find);
          cout << left <<"|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
          << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
          for (size_t i = 0; i < tempvector.size(); i++) {
            int j = tempvector[i];
            int day = StoreItemVector[j].getDay();
            int month = StoreItemVector[j].getMonth();
            int year = StoreItemVector[j].getYear();
            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            cout << left <<"|" << setw(15) <<  StoreItemVector[j].getItemId() << "|"  << setw(15) << StoreItemVector[j].getName() << "|"  << setw(15) << StoreItemVector[j].getDescription() << "|"  << setw(15) << StoreItemVector[j].getCategory() << "|\033[1;92m"
            << setw(15) << StoreItemVector[j].getManufacturer() << "\033[0m|"  << setw(15) << StoreItemVector[j].getSellPrice() << "|" << setw(15) << StoreItemVector[j].getCostPrice() << "|"  << setw(15) << StoreItemVector[j].getUnitInStore() << "|"  << setw(15)
            << StoreItemVector[j].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
          }
          system("pause");

        }
      } else {
        system("cls");
        int tempint;
        vector<int> tempvector;
        vector<int> search;
        cout << "\n\033[1;4;93m4. Display.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m2. Display by searching data.\033[0m"
        << "\n**************************" << endl
        << "\n\033[1;4;32m2. Search by number.\033[0m"
        << "\n**************************" << endl;

        cout << "\nWhat type of search do you want to search. Choose your choice and press enter."
        << "\n1. Equivalence condition"
        << "\n2. Less than condition"
        << "\n3. More than condition" << endl;
        temp = getch() - '0';
        while (cin.fail() || temp < 0 || temp > 3 )
        {
          cin.clear();
          cin.ignore();
          cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-8.\nPlease enter your choice again.\033[0m" << endl;
          temp = getch() - '0';
        }
        int find;
        if (temp == 1) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Search by number.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m1. Equivalence condition\033[0m" << endl;

          cout << "\nWhat type of data field do you want to search. Choose your choice and press enter."
          << "\n1. Selling Price"
          << "\n2. Cost Price"
          << "\n3. Units in Store"
          << "\n4. Units Sold"
          << "\n5. Year of Date First Introduced"
          << "\n6. Month of Date First Introduced"
          << "\n7. Day of Date First Introduced" << endl;
          temp = getch() - '0';
          while (cin.fail() || temp < 0 || temp > 8 )
          {
            cin.clear();
            cin.ignore();
            cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-8.\nPlease enter your choice again.\033[0m" << endl;
            temp = getch() - '0';
          }

          if (temp == 1) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Selling Price\033[0m" << endl;

            cout << "\nWhat Sell Price that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getSellPrice());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Sell Price that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 6);
            system("pause");

          } else if (temp == 2) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Cost Price\033[0m" << endl;

            cout << "\nWhat Cost Price that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getCostPrice());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Cost Price that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 7);
            system("pause");

          } else if (temp == 3) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. Units in Store\033[0m" << endl;

            cout << "\nWhat Units in Store that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getUnitInStore());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Unit in Store that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 8);
            system("pause");
          } else if (temp == 4) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m4. Units Sold\033[0m" << endl;

            cout << "\nWhat Units Sold that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getUnitSold());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Unit Sold that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 9);
            system("pause");
          } else if (temp == 5) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m5. Year of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Year of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getYear());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Year of Date First Introduced that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 10);
            system("pause");
          } else if (temp == 6) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m6. Month of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Month of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getMonth());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Month of Date First Introduced that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 11);
            system("pause");
          } else {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Equivalence condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m7. Day of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Day of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getDay());
            }
            tempvector = searchingIntEqual(search,find);
            cout << "The Day of Date First Introduced that you want to search is = " << find;
            displaySearch(StoreItemVector, tempvector, 12);
            system("pause");
          }
        } else if (temp == 2) {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Search by number.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Less than condition\033[0m" << endl;

          cout << "\nWhat type of data field do you want to search. Choose your choice and press enter."
          << "\n1. Selling Price"
          << "\n2. Cost Price"
          << "\n3. Units in Store"
          << "\n4. Units Sold"
          << "\n5. Year of Date First Introduced"
          << "\n6. Month of Date First Introduced"
          << "\n7. Day of Date First Introduced" << endl;
          temp = getch() - '0';
          while (cin.fail() || temp < 0 || temp > 8 )
          {
            cin.clear();
            cin.ignore();
            cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-8.\nPlease enter your choice again.\033[0m" << endl;
            temp = getch() - '0';
          }

          if (temp == 1) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Selling Price\033[0m" << endl;

            cout << "\nWhat Sell Price that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getSellPrice());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Sell Price that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 6);
            system("pause");

          } else if (temp == 2) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Cost Price\033[0m" << endl;

            cout << "\nWhat Cost Price that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getCostPrice());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Cost Price that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 7);
            system("pause");

          } else if (temp == 3) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. Units in Store\033[0m" << endl;

            cout << "\nWhat Units in Store that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getUnitInStore());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Unit in Store that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 8);
            system("pause");
          } else if (temp == 4) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m4. Units Sold\033[0m" << endl;

            cout << "\nWhat Units Sold that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getUnitSold());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Unit Sold that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 9);
            system("pause");
          } else if (temp == 5) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m5. Year of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Year of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getYear());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Year of Date First Introduced that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 10);
            system("pause");
          } else if (temp == 6) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m6. Month of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Month of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getMonth());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Month of Date First Introduced that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 11);
            system("pause");
          } else {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Less than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m7. Day of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Day of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getDay());
            }
            tempvector = searchingIntLess(search,find);
            cout << "The Day of Date First Introduced that you want to search is < " << find;
            displaySearch(StoreItemVector, tempvector, 12);
            system("pause");
          }
        } else {
          system("cls");
          cout << "\n\033[1;4;93m4. Display.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Display by searching data.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m2. Search by number.\033[0m"
          << "\n**************************" << endl
          << "\n\033[1;4;32m3. More than condition\033[0m" << endl;

          cout << "\nWhat type of data field do you want to search. Choose your choice and press enter."
          << "\n1. Selling Price"
          << "\n2. Cost Price"
          << "\n3. Units in Store"
          << "\n4. Units Sold"
          << "\n5. Year of Date First Introduced"
          << "\n6. Month of Date First Introduced"
          << "\n7. Day of Date First Introduced" << endl;
          temp = getch() - '0';
          while (cin.fail() || temp < 0 || temp > 8)
          {
            cin.clear();
            cin.ignore();
            cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-8.\nPlease enter your choice again.\033[0m" << endl;
            temp = getch() - '0';
          }

          if (temp == 1) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m1. Selling Price\033[0m" << endl;

            cout << "\nWhat Sell Price that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getSellPrice());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Sell Price that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 6);
            system("pause");

          } else if (temp == 2) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Cost Price\033[0m" << endl;

            cout << "\nWhat Cost Price that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getCostPrice());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Cost Price that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 7);
            system("pause");

          } else if (temp == 3) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. Units in Store\033[0m" << endl;

            cout << "\nWhat Units in Store that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getUnitInStore());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Unit in Store that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 8);
            system("pause");
          } else if (temp == 4) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m4. Units Sold\033[0m" << endl;

            cout << "\nWhat Units Sold that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getUnitSold());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Unit Sold that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 9);
            system("pause");
          } else if (temp == 5) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m5. Year of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Year of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getYear());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Year of Date First Introduced that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 10);
            system("pause");
          } else if (temp == 6) {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m6. Month of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Month of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getMonth());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Month of Date First Introduced that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 11);
            system("pause");
          } else {
            system("cls");
            cout << "\n\033[1;4;93m4. Display.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Display by searching data.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m2. Search by number.\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m3. More than condition\033[0m"
            << "\n**************************" << endl
            << "\n\033[1;4;32m7. Day of Date First Introduced\033[0m" << endl;

            cout << "\nWhat Day of Date First Introduced that you want to search?" << endl;
            cin >> find;
            while (cin.fail())
            {
              cin.clear();
              cin.ignore();
              cout << "\a\n\n\033[1;31mWrong input. Only integer value.\nPlease enter your choice again.\033[0m" << endl;
              temp = getch() - '0';
            }
            for (size_t i = 0; i < StoreItemVector.size(); i++) {
              search.push_back(StoreItemVector[i].getDay());
            }
            tempvector = searchingIntMore(search,find);
            cout << "The Day of Date First Introduced that you want to search is > " << find;
            displaySearch(StoreItemVector, tempvector, 12);
            system("pause");
          }
        }
      }
    }
  } else {
    system("cls");
    cout << "\n\033[1;4;93m4. Display.\033[0m"
    << "\n**************************" << endl;
    cout << "\n\nNo data to be display." << endl;
    system("pause");
  }
}

void sorting(vector<StoreItem> &StoreItemVector ) {
  char a;
  int temp;
  system("cls");
  cout << "Enter your choice."
  << "\n\033[90m1. Insertion."
  << "\n2. Update."
  << "\n3. Deletion."
  << "\n4. Display data.\033[0m"
  << "\n\033[1;4;93m5. Sorting.\033[0m"
  << "\n\033[90m6. Exit.\033[0m"
  << "\n**************************" << endl;
  cout << "\nWhat type of sorting do you want. Choose your choice."
  << "\n1. Ascending Order"
  << "\n2. Descending Order" << endl;
  a = getch() - '0';
  while (a < 1 || a > 2) {
    cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-2.\nPlease enter your choice again.\033[0m" << endl;
    a = getch() - '0';
  }
  cout << "\n**************************" << endl;
  cout << "\nWhat data field do you want to sort. Choose your choice and press enter."
  << "\n1. Item ID"
  << "\n2. Name"
  << "\n3. Description"
  << "\n4. Category"
  << "\n5. Manufacturer"
  << "\n6. Selling Price"
  << "\n7. Cost Price"
  << "\n8. Units in Store"
  << "\n9. Units Sold"
  << "\n10. Year of Date First Introduced"
  << "\n11. Month of Date First Introduced"
  << "\n12. Day of Date First Introduced" << endl;
  cin >> temp;
  while (temp < 1 || temp > 12) {
    cout << "\a\n\n\033[1;31mWrong input. Only integer value and the number must between 1-2.\nPlease enter your choice again.\033[0m" << endl;
    cin >> temp;
  }
  if (temp == 1) {
    cout << "\n\033[1;36mItem ID\033[0m" << endl;
  } else if (temp == 2) {
    cout << "\n\033[1;36mName\033[0m" << endl;
  } else if (temp == 3) {
    cout << "\n\033[1;36mDescription\033[0m" << endl;
  } else if (temp == 4) {
    cout << "\n\033[1;36mategory\033[0m" << endl;
  } else if (temp == 5) {
    cout << "\n\033[1;36mManufacturer\033[0m" << endl;
  } else if (temp == 6) {
    cout << "\n\033[1;36mSelling Price\033[0m" << endl;
  } else if (temp == 7) {
    cout << "\n\033[1;36mCost Price\033[0m" << endl;
  } else if (temp == 8) {
    cout << "\n\033[1;36mUnits in Store\033[0m" << endl;
  } else if (temp == 9) {
    cout << "\n\033[1;36mUnits Sold\033[0m" << endl;
  } else if (temp == 10) {
    cout << "\n\033[1;36mYear of Date First Introduced\033[0m" << endl;
  } else if (temp == 11) {
    cout << "\n\033[1;36mMonth of Date First Introduced\033[0m" << endl;
  } else {
    cout << "\n\033[1;36mDay of Date First Introduced\033[0m" << endl;
  }
  if (a == 1) {
    cout << "\n\033[1;36mAscending\033[0m" << endl;
    ascbubbleSort(StoreItemVector, temp);
  } else {
    cout << "\n\033[1;36mDescending\033[0m" << endl;
    desbubbleSort(StoreItemVector, temp);
  }
  system("pause");
}

void ascbubbleSort(vector<StoreItem> &StoreItemVector, int z) {
  StoreItem temp;
  bool swap;
  vector<int> y;
  do {
    swap = 0;
    for (size_t i = 0; i < StoreItemVector.size() - 1; i++) {
      if (z < 6) {
        string tempStr, tempStr1;
        if (z == 1) {
          tempStr = StoreItemVector[i].getItemId();
          tempStr1 = StoreItemVector[i+1].getItemId();
        } else if (z == 2) {
          tempStr = StoreItemVector[i].getName();
          tempStr1 = StoreItemVector[i+1].getName();
        } else if (z == 3) {
          tempStr = StoreItemVector[i].getDescription();
          tempStr1 = StoreItemVector[i+1].getDescription();
        } else if (z == 4) {
          tempStr = StoreItemVector[i].getCategory();
          tempStr1 = StoreItemVector[i+1].getCategory();
        } else {
          tempStr = StoreItemVector[i].getManufacturer();
          tempStr1 = StoreItemVector[i+1].getManufacturer();
        }
        if (tempStr > tempStr1) {
          temp = StoreItemVector[i];
          StoreItemVector[i] = StoreItemVector[i + 1];
          StoreItemVector[i + 1] = temp;
          swap = true;
        }
      } else if (z < 8) {
        float tempStr, tempStr1;
        if (z == 6) {
          tempStr = StoreItemVector[i].getSellPrice();
          tempStr1 = StoreItemVector[i+1].getSellPrice();
        } else {
          tempStr = StoreItemVector[i].getCostPrice();
          tempStr1 = StoreItemVector[i+1].getCostPrice();
        }
        if (tempStr > tempStr1) {
          temp = StoreItemVector[i];
          StoreItemVector[i] = StoreItemVector[i + 1];
          StoreItemVector[i + 1] = temp;
          swap = true;
        }
      } else {
        int tempStr, tempStr1;
        if (z == 8) {
          tempStr = StoreItemVector[i].getUnitInStore();
          tempStr1 = StoreItemVector[i+1].getUnitInStore();
        } else if (z == 9) {
          tempStr = StoreItemVector[i].getUnitSold();
          tempStr1 = StoreItemVector[i+1].getUnitSold();
        } else if (z == 10) {
          tempStr = StoreItemVector[i].getYear();
          tempStr1 = StoreItemVector[i+1].getYear();
        } else if (z == 11) {
          tempStr = StoreItemVector[i].getMonth();
          tempStr1 = StoreItemVector[i+1].getMonth();
        } else {
          tempStr = StoreItemVector[i].getDay();
          tempStr1 = StoreItemVector[i+1].getDay();
        }
        if (tempStr > tempStr1) {
          temp = StoreItemVector[i];
          StoreItemVector[i] = StoreItemVector[i + 1];
          StoreItemVector[i + 1] = temp;
          swap = true;
        }
      }
    }
  } while(swap);
  for (size_t j = 0; j < StoreItemVector.size(); j++) {
    y.push_back(j);
  }
  displayUpdate(StoreItemVector, y, z);
}

void desbubbleSort(vector<StoreItem> &StoreItemVector, int z) {
  StoreItem temp;
  bool swap;
  vector<int> y;
  do {
    swap = 0;
    for (size_t i = 0; i < StoreItemVector.size() - 1; i++) {
      if (z < 6) {
        string tempStr, tempStr1;
        if (z == 1) {
          tempStr = StoreItemVector[i].getItemId();
          tempStr1 = StoreItemVector[i+1].getItemId();
        } else if (z == 2) {
          tempStr = StoreItemVector[i].getName();
          tempStr1 = StoreItemVector[i+1].getName();
        } else if (z == 3) {
          tempStr = StoreItemVector[i].getDescription();
          tempStr1 = StoreItemVector[i+1].getDescription();
        } else if (z == 4) {
          tempStr = StoreItemVector[i].getCategory();
          tempStr1 = StoreItemVector[i+1].getCategory();
        } else {
          tempStr = StoreItemVector[i].getManufacturer();
          tempStr1 = StoreItemVector[i+1].getManufacturer();
        }
        if (tempStr < tempStr1) {
          temp = StoreItemVector[i];
          StoreItemVector[i] = StoreItemVector[i + 1];
          StoreItemVector[i + 1] = temp;
          swap = true;
        }
      } else if (z < 8) {
        float tempStr, tempStr1;
        if (z == 6) {
          tempStr = StoreItemVector[i].getSellPrice();
          tempStr1 = StoreItemVector[i+1].getSellPrice();
        } else {
          tempStr = StoreItemVector[i].getCostPrice();
          tempStr1 = StoreItemVector[i+1].getCostPrice();
        }
        if (tempStr < tempStr1) {
          temp = StoreItemVector[i];
          StoreItemVector[i] = StoreItemVector[i + 1];
          StoreItemVector[i + 1] = temp;
          swap = true;
        }
      } else {
        int tempStr, tempStr1;
        if (z == 8) {
          tempStr = StoreItemVector[i].getUnitInStore();
          tempStr1 = StoreItemVector[i+1].getUnitInStore();
        } else if (z == 9) {
          tempStr = StoreItemVector[i].getUnitSold();
          tempStr1 = StoreItemVector[i+1].getUnitSold();
        } else if (z == 10) {
          tempStr = StoreItemVector[i].getYear();
          tempStr1 = StoreItemVector[i+1].getYear();
        } else if (z == 11) {
          tempStr = StoreItemVector[i].getMonth();
          tempStr1 = StoreItemVector[i+1].getMonth();
        } else {
          tempStr = StoreItemVector[i].getDay();
          tempStr1 = StoreItemVector[i+1].getDay();
        }
        if (tempStr < tempStr1) {
          temp = StoreItemVector[i];
          StoreItemVector[i] = StoreItemVector[i + 1];
          StoreItemVector[i + 1] = temp;
          swap = true;
        }
      }
    }
  } while(swap);
  for (size_t j = 0; j < StoreItemVector.size(); j++) {
    y.push_back(j);
  }
  displayUpdate(StoreItemVector, y, z);
}

vector<int> searchingstring(vector<string> &search, string find) {
  vector<int> tempvector;
  for (size_t i = 0; i < search.size(); i++) {
    transform(search[i].begin(),search[i].end(),search[i].begin(), ptr_fun <int, int> (&tolower));
    if(search[i].find(find) != string::npos) {
      tempvector.push_back(i);
    }
  }
  return tempvector;
}

vector<int> searchingIntEqual(vector<int> &search, int find) {
  vector<int> tempvector;
  for (size_t i = 0; i < search.size(); i++) {
    if(search[i] == find) {
      tempvector.push_back(i);
    }
  }
  return tempvector;
}

vector<int> searchingIntLess(vector<int> &search, int find) {
  vector<int> tempvector;
  for (size_t i = 0; i < search.size(); i++) {
    if(search[i] < find) {
      tempvector.push_back(i);
    }
  }
  return tempvector;
}

vector<int> searchingIntMore(vector<int> &search, int find) {
  vector<int> tempvector;
  for (size_t i = 0; i < search.size(); i++) {
    if(search[i] > find) {
      tempvector.push_back(i);
    }
  }
  return tempvector;
}

void displaySearch(vector<StoreItem> &StoreItemVector, vector<int> &tempvector, int colour) {

  cout << "\n\nTotal record that have been found is " << tempvector.size() << " ." << endl;
  string a, b, c, d, e, f, g, h, colouri, colourj, k, l, m, n, o, p, q, r, s, t;
  switch (colour) {
    case 1:
      a = "\033[1;92m"; b = "\033[0m";
      break;
    case 2:
      c = "\033[1;92m"; d = "\033[0m";
      break;
    case 3:
      e = "\033[1;92m"; f = "\033[0m";
      break;
    case 4:
      g = "\033[1;92m"; h = "\033[0m";
      break;
    case 5:
      colouri = "\033[1;92m"; colourj = "\033[0m";
      break;
    case 6:
      k = "\033[1;92m"; l = "\033[0m";
      break;
    case 7:
    m = "\033[1;92m"; n = "\033[0m";
    break;
    case 8:
    o = "\033[1;92m"; p = "\033[0m";
    break;
    case 9:
    q = "\033[1;92m"; r = "\033[0m";
    break;
    case 10:
    s = "\033[1;92m"; t = "\033[0m";
    break;
  }
  cout << left <<"\n\n|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
  << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
  for (size_t i = 0; i < tempvector.size(); i++) {
    int j = tempvector[i];
    int day = StoreItemVector[j].getDay();
    int month = StoreItemVector[j].getMonth();
    int year = StoreItemVector[j].getYear();
    string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << left <<"|" << a << setw(15) <<  StoreItemVector[j].getItemId() << b << "|" << c << setw(15) << StoreItemVector[j].getName() << d << "|" << e << setw(15) << StoreItemVector[j].getDescription() << f << "|" << g << setw(15) << StoreItemVector[j].getCategory() << h << "|"
    << colouri << setw(15) << StoreItemVector[j].getManufacturer() << colourj << "|" << k << setw(15) << StoreItemVector[j].getSellPrice() << l << "|" << m << setw(15) << StoreItemVector[j].getCostPrice() << n << "|" << o << setw(15) << StoreItemVector[j].getUnitInStore() << p << "|" << q << setw(15)
    << StoreItemVector[j].getUnitSold() << r << "|" << s << setw(15) << date << t << "|" << endl;
  }
}

void displayUpdate(vector<StoreItem> &StoreItemVector, vector<int> &tempvector, int colour) {

  string a, b, c, d, e, f, g, h, colouri, colourj, k, l, m, n, o, p, q, r, s, t;
  switch (colour) {
    case 1:
      a = "\033[1;92m"; b = "\033[0m";
      break;
    case 2:
      c = "\033[1;92m"; d = "\033[0m";
      break;
    case 3:
      e = "\033[1;92m"; f = "\033[0m";
      break;
    case 4:
      g = "\033[1;92m"; h = "\033[0m";
      break;
    case 5:
      colouri = "\033[1;92m"; colourj = "\033[0m";
      break;
    case 6:
      k = "\033[1;92m"; l = "\033[0m";
      break;
    case 7:
    m = "\033[1;92m"; n = "\033[0m";
    break;
    case 8:
    o = "\033[1;92m"; p = "\033[0m";
    break;
    case 9:
    q = "\033[1;92m"; r = "\033[0m";
    break;
    case 10:
    s = "\033[1;92m"; t = "\033[0m";
    break;
    case 11:
    s = "\033[1;92m"; t = "\033[0m";
    break;
    case 12:
    s = "\033[1;92m"; t = "\033[0m";
    break;

  }
  cout << left <<"\n\n|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
  << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
  for (size_t i = 0; i < tempvector.size(); i++) {
    int j = tempvector[i];
    int day = StoreItemVector[j].getDay();
    int month = StoreItemVector[j].getMonth();
    int year = StoreItemVector[j].getYear();
    string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << left <<"|" << a << setw(15) <<  StoreItemVector[j].getItemId() << b << "|" << c << setw(15) << StoreItemVector[j].getName() << d << "|" << e << setw(15) << StoreItemVector[j].getDescription() << f << "|" << g << setw(15) << StoreItemVector[j].getCategory() << h << "|"
    << colouri << setw(15) << StoreItemVector[j].getManufacturer() << colourj << "|" << k << setw(15) << StoreItemVector[j].getSellPrice() << l << "|" << m << setw(15) << StoreItemVector[j].getCostPrice() << n << "|" << o << setw(15) << StoreItemVector[j].getUnitInStore() << p << "|" << q << setw(15)
    << StoreItemVector[j].getUnitSold() << r << "|" << s << setw(15) << date << t << "|" << endl;
  }
}

void displaycertain(vector<StoreItem> &StoreItemVector, int i) {
  cout << left << "|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
  << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
  int day = StoreItemVector[i].getDay();
  int month = StoreItemVector[i].getMonth();
  int year = StoreItemVector[i].getYear();
  string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
  cout << left <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
  << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
  << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
}

void displayall(vector<StoreItem> &StoreItemVector) {
  cout << left << "|" << setw(3) << "No." << "|" << setw(15) <<  "Item ID" << "|"  << setw(15) << "Name" << "|"  << setw(15) << "Description" << "|"  << setw(15) << "Category" << "|"  << setw(15) << "Manufacturer" << "|"  << setw(15) << "Sell Price" << "|"
  << setw(15) << "Cost Price" << "|"  << setw(15) << "Unit In Store" << "|"  << setw(15) << "Unit Sold" << "|"  << setw(15) << "Date" << "|" << endl;
  for (size_t i = 0; i < StoreItemVector.size(); i++) {
    int day = StoreItemVector[i].getDay();
    int month = StoreItemVector[i].getMonth();
    int year = StoreItemVector[i].getYear();
    string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    cout << left << "|" << setw(3) << i+1  <<"|" << setw(15) <<  StoreItemVector[i].getItemId() << "|"  << setw(15) << StoreItemVector[i].getName() << "|"  << setw(15) << StoreItemVector[i].getDescription() << "|"  << setw(15) << StoreItemVector[i].getCategory() << "|"
    << setw(15) << StoreItemVector[i].getManufacturer() << "|"  << setw(15) << StoreItemVector[i].getSellPrice() << "|" << setw(15) << StoreItemVector[i].getCostPrice() << "|"  << setw(15) << StoreItemVector[i].getUnitInStore() << "|"  << setw(15)
    << StoreItemVector[i].getUnitSold() << "|"  << setw(15) << date << "|" << endl;
  }
}

void gotoXY(int x, int y) {
  CursorPosition.X = x;
  CursorPosition.Y = y;
  SetConsoleCursorPosition(console, CursorPosition);
}
