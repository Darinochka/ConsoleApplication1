#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    int first, last;
    string result;
    first = CheckYear(first_names, year);
    last = CheckYear(last_names, year);
    if (first == -1 && last == -1) {
      result = "Incognito";
    } else if (first == -1 && last > 0) {
      result = last_names[last] + " with unknown first name";
    } else if (first > 0 && last == -1) {
      result = first_names[first] + " with unknown last name";
    } else {
      result = first_names[first] + " " + last_names[last];
    }
    return result;
  }
  private:
    map <int, string> first_names;
    map <int, string> last_names;

    int CheckYear(map<int, string>& names, const int& year) {
      int by_year = -1;
      for (const auto& [key, value] : names) {
        if (key <= year){
          by_year = key;
        }
      }
      return by_year;
    }
};

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}