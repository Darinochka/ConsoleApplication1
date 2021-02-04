#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

struct Student {
  string firstName;
  string secondName;
  int day;
  int month;
  int year;
  void name() {
    cout << firstName << " " << secondName << endl;
  }
  void date() {
    cout << day << "." << month << "." << year << endl;
  }
};

int main() {
  int n, m, number;
  string command;
  cin >> n;
  vector <Student> students(n);

  for (int i = 0; i < n; i++) {
    cin >> students[i].firstName >> students[i].secondName >> 
          students[i].day >> students[i].month >> students[i].year;
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> command >> number;
    if (command == "name" && 0 < number && number <= students.size()) {
      students[number-1].name();
    } else if (command == "date" && 0 < number && number <= students.size()) {
      students[number-1].date();
    } else {
      cout << "bad request" << endl;
    }
  }
}